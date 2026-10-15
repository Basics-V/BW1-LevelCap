// fpm.c - fixed program module
// Authors: MCMi460

#include "wbtypes.h"

#include "system/gamesystem.h"
#include "system/game_data.h"
#include "save/savedata_eventwork.h"

#include "levelcap.h"
#include "util.h"

// Handles checking for the level cap before giving a Pokemon EXP
__attribute__((target("thumb")))
void ExperienceGainCap(u32* calcExpLvl, u32 partyMonLvl) {
    // Call replaced function
    *calcExpLvl = PassPower_ApplyEXP(*calcExpLvl);

    // Fetch the necessary works
    GameData*  gameData  = GSYS_GetGameData(g_GameSystem);
    EventData* eventData = GameData_GetEventData(gameData);
    u16 levelCap = *EventWork_GetWkPtr(eventData, levelCapEventWork);

    // Is the Pokemon already at/above the level cap?
    if (levelCap != 0 && partyMonLvl >= levelCap)
        // If so, reduce EXP gain to zero
        *calcExpLvl = 0;
}
