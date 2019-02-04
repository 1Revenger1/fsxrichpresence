#pragma once

#ifdef FSXRICHPRESENCE_EXPORTS
#define FSXRICHPRESENCE_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define FSXRICHPRESENCE_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif

#ifdef SIM_FSXA
#include "./include_fsxa/SimConnect.h"
#include "./include_fsxa/discord_rpc.h"
#elif SIM_P3D4
#include "./include_p3d4/SimConnect.h"
#include "./include_p3d4/discord_rpc.h"
#endif

#include "Windows.h"
#include "AircraftParse.h"

struct Data;
void FSXRICHPRESENCE_API handlePresence(Data data);

void FSXRICHPRESENCE_API CALLBACK MyDispatchProcRD(SIMCONNECT_RECV* pData, DWORD cbData, void *pContext);
void FSXRICHPRESENCE_API handleDiscordReady(const DiscordUser* connectedUser);
void FSXRICHPRESENCE_API handleDiscordDisconnect(int errorCode, const char* message);
void FSXRICHPRESENCE_API discordInit();
void FSXRICHPRESENCE_API setInMainMenu();
void FSXRICHPRESENCE_API setInMenu();
void FSXRICHPRESENCE_API startRPC();
int FSXRICHPRESENCE_API __stdcall DLLStart();
void FSXRICHPRESENCE_API __stdcall DLLStop();