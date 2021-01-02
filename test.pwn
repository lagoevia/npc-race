#include <a_samp>

#define YSI_NO_HEAP_MALLOC
#define YSI_NO_CACHE_MESSAGE
#define YSI_NO_OPTIMISATION_MESSAGE
#include <YSI_Visual\y_commands>

#include "npc-race"

// Spawn Information
#define PLAYER_SPAWN_X      -2259.1196
#define PLAYER_SPAWN_Y      -228.0822
#define PLAYER_SPAWN_Z      36.2685
#define PLAYER_SPAWN_A      186.4773
#define NPC_SPAWN_X         -2236.5586
#define NPC_SPAWN_Y         -226.7776
#define NPC_SPAWN_Z         35.5820
#define NPC_SPAWN_A         101.2237
#define NPC_VEH_SPAWN_X     -2252.4348
#define NPC_VEH_SPAWN_Y     -206.9384
#define NPC_VEH_SPAWN_Z     35.1912
#define NPC_VEH_SPAWN_A     1.0914
#define PLAYER_VEH_SPAWN_X  -2260.0295
#define PLAYER_VEH_SPAWN_Y  -206.6651
#define PLAYER_VEH_SPAWN_Z  35.1849
#define PLAYER_VEH_SPAWN_A  0.7565

main()
{
    print("Welcome to the testing server for the NPC Race library!");
    print("Remember to check cahoa at https://github.com/lagoevia/cahoa");
    print("Credits: phlair");
}

public OnGameModeInit()
{
    AddPlayerClass(52, PLAYER_SPAWN_X, PLAYER_SPAWN_Y, PLAYER_SPAWN_Z, PLAYER_SPAWN_A, 0, 0, 0, 0, 0, 0);
    NPCR_LoadBot("[BOT]Driver");
    NPCR_LoadCars();
    return 1;
}

public OnGameModeExit()
{
    NPCR_UnloadBot();
    return 1;
}

YCMD:startrace(playerid, params[], help)
{
    NPCR_RaceStart(playerid);
    return 1;
}

public NPCR_OnPlayerLoseRace(playerid)
{
    SendClientMessage(playerid, -1, "Info: You lost the race. Better luck next time!");
    return 1;
}

public NPCR_OnPlayerWinRace(playerid)
{
    SendClientMessage(playerid, -1, "Info: You won the race, well done!");
    return 1;
}