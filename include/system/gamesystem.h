#include "wbtypes.h"

#include "system/game_data.h"

// Data structures
STRUCT_DECLARE(GameSystem)

// Functions
C_DECL_BEGIN

GameData* GSYS_GetGameData(GameSystem*);

C_DECL_END

// Globals
extern GameSystem* g_GameSystem;
