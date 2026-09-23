#pragma once

typedef struct GameSystem GameSystem;
typedef struct GameData   GameData;
typedef struct EventData  EventData;

// Hardcoded addresses
__asm__(
    ".global g_GameSystem\n\t"
    "g_GameSystem = 0x02146248\n\t"

    ".global GSYS_GetGameData\n\t"
    ".type GSYS_GetGameData, %function\n\t"
    "GSYS_GetGameData = 0x020120F5\n\t"

    ".global GameData_GetEventData\n\t"
    ".type GameData_GetEventData, %function\n\t"
    "GameData_GetEventData = 0x0201296D\n\t"

    ".global FUN_020143cc\n\t"
    ".type FUN_020143cc, %function\n\t"
    "FUN_020143cc = 0x020143CD\n\t"
);

extern GameSystem* g_GameSystem;
extern GameData* GSYS_GetGameData(GameSystem*);
extern EventData* GameData_GetEventData(GameData*);
extern unsigned short* FUN_020143cc(EventData*, int);

// Compiled/defined functions
void FUN_02011168(unsigned int*, unsigned int);
