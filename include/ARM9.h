#pragma once
#include "util.h"

// Data structures
typedef struct GameSystem GameSystem;
typedef struct GameData   GameData;
typedef struct EventData  EventData;

// Hardcoded addresses
#define ADDR_g_GameSystem          0x02146248
#define ADDR_GSYS_GetGameData      0x020120F5
#define ADDR_GameData_GetEventData 0x0201296D
#define ADDR_FUN_020143cc          0x020143CD

// Inline assembly to match addresses w/ symbols
__asm__(
    ".global g_GameSystem\n\t"
    "g_GameSystem = " STR(ADDR_g_GameSystem) "\n\t"

    ".global GSYS_GetGameData\n\t"
    ".type GSYS_GetGameData, %function\n\t"
    "GSYS_GetGameData = " STR(ADDR_GSYS_GetGameData) "\n\t"

    ".global GameData_GetEventData\n\t"
    ".type GameData_GetEventData, %function\n\t"
    "GameData_GetEventData = " STR(ADDR_GameData_GetEventData) "\n\t"

    ".global FUN_020143cc\n\t"
    ".type FUN_020143cc, %function\n\t"
    "FUN_020143cc = " STR(ADDR_FUN_020143cc) "\n\t"
);

extern GameSystem* g_GameSystem;
extern GameData* GSYS_GetGameData(GameSystem*);
extern EventData* GameData_GetEventData(GameData*);
extern unsigned short* FUN_020143cc(EventData*, int);

// Compiled/defined functions
void FUN_02011168(unsigned int*, unsigned int);
