#pragma once

#define ADDR_GSYS_GetGameData      0x020120F5
#define ADDR_GameData_GetEventData 0x0201296D
#define ADDR_FUN_020143cc          0x020143CD

// ROM-conditional addresses
#if   defined IRBO // Black American
    #define ADDR_g_GameSystem          0x02146248
#elif defined IRBI // Black Italian
    #define ADDR_g_GameSystem          0x02146148
#elif defined IRAI // White Italian
    #define ADDR_g_GameSystem          0x02146168
#else
    #error "That ROM does not have defined addresses yet!"
#endif

#ifndef __LINKER__

// Data structures
typedef struct GameSystem GameSystem;
typedef struct GameData   GameData;
typedef struct EventData  EventData;

extern GameSystem* g_GameSystem;
extern GameData* GSYS_GetGameData(GameSystem*);
extern EventData* GameData_GetEventData(GameData*);
extern unsigned short* FUN_020143cc(EventData*, int);

// Compiled/defined functions
void FUN_02011168(unsigned int*, unsigned int);

#endif // __LINKER__
