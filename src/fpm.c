// fpm.c - fixed program module
// Authors: MCMi460

#include "arm9.h"
#include "util.h"

#define levelCapEventWork 0x4049

// Handles checking for the level cap before giving a Pokemon EXP
__attribute__((target("thumb")))
void ExperienceGainCap(unsigned int* calcExpLvl, unsigned int partyMonLvl) {
    // Call replaced function
    *calcExpLvl = PassPower_ApplyEXP(*calcExpLvl);

    // Fetch the necessary works
    GameData*  gameData  = GSYS_GetGameData(g_GameSystem);
    EventData* eventData = GameData_GetEventData(gameData);
    unsigned short levelCap = *EventWork_GetWkPtr(eventData, levelCapEventWork);

    // Is the Pokemon already at/above the level cap?
    if (levelCap != 0 && partyMonLvl >= levelCap)
        // If so, reduce EXP gain to zero
        *calcExpLvl = 0;
}
