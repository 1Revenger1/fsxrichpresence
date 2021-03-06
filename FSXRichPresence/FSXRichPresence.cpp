// FSXRichPresence.cpp : Defines the exported functions for the DLL application.
//

#pragma once

#include "stdafx.h"
#include "stdio.h"
#include "time.h"
#include "Windows.h"
#include "strsafe.h"

#ifdef SIM_FSXA
#include "./include_fsxa/SimConnect.h"
#include "./include_fsxa/discord_rpc.h"
#elif SIM_P3D4
#include "./include_p3d4/SimConnect.h"
#include "./include_p3d4/discord_rpc.h"
#endif
#include <thread>
#include "FSXRichPresence.h"
#include "AircraftParse.h"

using namespace std;

int quit = 0;
int oldVelocity;
const char* APPLICATION_ID;
int64_t startTime;
int64_t stopTime;
HANDLE hSimConnect = NULL;
bool discordConnected = false;
bool inFlight = false;
bool flightStartSet = false;
bool flightStopSet = false;
const char* appName;
time_t timer; 
AircraftParse parse;

struct Data {
	char title[256];
	double hdg;
	double spd; //Indicated Speed
	double mach; //Mach
	double gSpd; //Ground speed
	double alt;
	double vSpd; //vertical speed
	double onGround;
	double gearExtended;
};

static enum EVENT_ID {
	EVENT_SIM_START,
	EVENT_SIM_STOP,
};

static enum DATA_DEFINE_ID {
	DEFINITION_1,
};

static enum DATA_REQUEST_ID {
	REQUEST_1,
};

void handlePresence(Data data) {
	char buffer[256];
	char stage[256];
	char altitude[256];
	string strTitle;
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	strTitle = data.title;
	
	string processedString = parse.parsePlane(strTitle).c_str();

	const char* title = processedString.c_str();

	double changeInVelocity = data.gSpd - oldVelocity;

	if (data.alt > 18000) {
		sprintf_s(buffer, "Aircraft: %s | Ground Spd: %d | Mach: %.2f | Hdg: %d",
			data.title,
			(int)data.gSpd,
			data.mach,
			(int)data.hdg);

		sprintf_s(altitude, "FL%d", (int)data.alt / 100);
	}
	else {
		sprintf_s(buffer, "Aircraft: %s | Ground Spd: %d | IAS: %d | Hdg: %d",
			data.title,
			(int)data.gSpd,
			(int)data.spd,
			(int)data.hdg);

		sprintf_s(altitude, "Altitude: %d", (int)data.alt);
	}

	if ((data.vSpd > 50 && data.gearExtended == 1.0) || (changeInVelocity > 0 && data.onGround && data.gSpd > 50)) {
		sprintf_s(stage, "Takeoff");

		if (!flightStartSet) {
			flightStartSet = true;
			startTime = time(0);
		}

	}
	else if (data.vSpd > 250) {
		sprintf_s(stage, "Climbing | %s", altitude);
	}
	else if (data.vSpd < -50 && data.gearExtended == 1.0) {
		sprintf_s(stage, "Approach | %s", altitude);
	}
	else if (changeInVelocity < 0 && data.onGround == 1.0 && data.gSpd > 50) {
		sprintf_s(stage, "Landing (Rollout)");
		if (!flightStopSet) {
			flightStopSet = true;
			stopTime = time(0);
		}
	}
	else if (data.vSpd < -250) {
		sprintf_s(stage, "Descending | %s", altitude);
	}
	else if (data.onGround == 0.0 && data.vSpd < 250 && data.vSpd > -250) {
		sprintf_s(stage, "Cruising | %s", altitude);
	}
	else if (data.onGround == 1.0) {
		sprintf_s(stage, "On the ground");
		flightStartSet = false;
		flightStopSet = false;
		startTime = 0;
		stopTime = 0;
	}
	else {
		sprintf_s(stage, "Unknown");
	}

	discordPresence.largeImageText = data.title;

	if (startTime != 0) {
		discordPresence.startTimestamp = startTime;
	}

//	if (stopTime != 0) {
//		discordPresence.endTimestamp = stopTime;
//	}

	discordPresence.state = buffer;
	discordPresence.details = stage;

	discordPresence.largeImageKey = title;

	Discord_UpdatePresence(&discordPresence);

	oldVelocity = (int)data.gSpd;
}

void CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext) {
	HRESULT hr;

	switch (pData->dwID) {

		case SIMCONNECT_RECV_ID_OPEN:
		{
			SIMCONNECT_RECV_OPEN *evt = (SIMCONNECT_RECV_OPEN*)pData;

			if (strcmp(evt->szApplicationName,"Microsoft Flight Simulator X") == 0) {
				appName = "FSX";
				APPLICATION_ID = "447447349594292226";
			}
			else {
				appName = "P3D";
				APPLICATION_ID = "466739324537405441";

			}

			appName = evt->szApplicationName;
			discordInit();
			setInMainMenu();
		}

		case SIMCONNECT_RECV_ID_EVENT:
		{
			SIMCONNECT_RECV_EVENT *evt = (SIMCONNECT_RECV_EVENT*)pData;

			switch (evt->uEventID) {
				case EVENT_SIM_START:
				{
					hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_SECOND);
					break;
				}
				case EVENT_SIM_STOP:
				{
					hr = SimConnect_RequestDataOnSimObject(hSimConnect, REQUEST_1, DEFINITION_1, SIMCONNECT_OBJECT_ID_USER, SIMCONNECT_PERIOD_NEVER);
					setInMenu();
					break;
				}
			}

			break;
		}

		case SIMCONNECT_RECV_ID_SIMOBJECT_DATA:
		{
			SIMCONNECT_RECV_SIMOBJECT_DATA *pObjData = (SIMCONNECT_RECV_SIMOBJECT_DATA*)pData;

			switch (pObjData->dwRequestID)
			{
				case REQUEST_1:
				{
					Data *pS = (Data*)&pObjData->dwData;
					if (SUCCEEDED(StringCbLengthA(&pS->title[0], sizeof(pS->title), NULL))) {
						handlePresence(*pS);
					}

					if (!inFlight) {
						inFlight = true;
					}

					break;
				}
			}
		}

		case SIMCONNECT_RECV_ID_QUIT:
		{
			quit = 1;

			break;
		}

		default:
			break;
	}
}

void handleDiscordReady(const DiscordUser* connectedUser) {
	printf("\nDiscord: connected to user %s#%s - %s\n",
		connectedUser->username,
		connectedUser->avatar,
		connectedUser->userId);
	discordConnected = true;
}

void handleDiscordDisconnect(int errorCode, const char* message) {
	printf("\nDiscord: error (%d: %s)\n", errorCode, message);
}

void discordInit() {
	DiscordEventHandlers handlers;
	memset(&handlers, 0, sizeof(handlers));
	handlers.ready = handleDiscordReady;
	handlers.disconnected = handleDiscordDisconnect;
	Discord_Initialize(APPLICATION_ID, &handlers, 1, NULL);
}

void setInMainMenu() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	discordPresence.details = "In Main Menu";

	Discord_UpdatePresence(&discordPresence);
}

void setInMenu() {
	DiscordRichPresence discordPresence;
	memset(&discordPresence, 0, sizeof(discordPresence));

	discordPresence.details = "In a menu";

	Discord_UpdatePresence(&discordPresence);
}

void startRPC() {
	HRESULT hr;

	if (SUCCEEDED(SimConnect_Open(&hSimConnect, "Discord RPC", NULL, 0, 0, 0)))
	{
		printf("\nDiscord: RPC has connected to Flight Simulator\nNote we haven't tried Discord yet");

		parse = AircraftParse();

		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "ATC Model", NULL, SIMCONNECT_DATATYPE_STRING256);
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Heading Indicator", "degrees");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Airspeed Indicated", "knots");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Airspeed Mach", "mach");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "GPS Ground Speed", "knots");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Indicated Altitude", "feet");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Vertical Speed", "feet/minute");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Sim On Ground", "Bool");
		hr = SimConnect_AddToDataDefinition(hSimConnect, DEFINITION_1, "Gear Handle Position", "Bool");

		hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_START, "SimStart");
		hr = SimConnect_SubscribeToSystemEvent(hSimConnect, EVENT_SIM_STOP, "SimStop");

		SimConnect_CallDispatch(hSimConnect, MyDispatchProcRD, NULL);
	}
}

int __stdcall DLLStart() {
	startRPC();

	return 0;
}

void __stdcall DLLStop() {
	HRESULT hr = SimConnect_Close(hSimConnect);
	Discord_ClearPresence();
	Discord_Shutdown();
	printf("\nDiscord: Shutting down...");
}

