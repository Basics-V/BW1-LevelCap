#pragma once
#include "util.h"

// Data structures
typedef struct GameSystem GameSystem;
typedef struct GameData   GameData;
typedef struct EventData  EventData;

extern unsigned int PassPower_ApplyEXP(unsigned int);

extern GameData* GSYS_GetGameData(GameSystem*);
extern EventData* GameData_GetEventData(GameData*);
extern unsigned short* EventWork_GetWkPtr(EventData*, int);

extern GameSystem* g_GameSystem;
