#include "ARM9.h"

#define levelCapEventWork 0x4049

__attribute__((section(".FUN_02011168"), target("thumb"), used))
void FUN_02011168(unsigned int* calcExpLvl, unsigned int partyMonLvl) {
    GameData*  gameData  = GSYS_GetGameData(g_GameSystem);
    EventData* eventData = GameData_GetEventData(gameData);
    unsigned short levelCap = *FUN_020143cc(eventData, levelCapEventWork);

    if (levelCap != 0 && partyMonLvl >= levelCap)
        *calcExpLvl = 0;
}
