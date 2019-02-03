#pragma once

#ifdef FSXRICHPRESENCE_EXPORTS
#define FSXRICHPRESENCE_API __declspec(dllexport)
#define EXPIMP_TEMPLATE
#else
#define FSXRICHPRESENCE_API __declspec(dllimport)
#define EXPIMP_TEMPLATE extern
#endif

#include "discord_rpc.h"
#include "./include/SimConnect.h"
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