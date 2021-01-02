#if defined _INC_npc_race
    #endinput
#endif
#define _INC_npc_race

#include <a_samp>
#include <FCNPC>

#define INVALID_RACE_CP     -1
#define MAX_RACE_CP         11
#define NORMAL_RACE_CP      0
#define FINISH_RACE_CP      1
#define RACE_CP_SIZE        10.0

static enum eRaceStatus
{
    e_RACE_STATUS_NONE,
    e_RACE_STATUS_IN_PROGRESS,
    e_RACE_STATUS_FINISHED
};

static
    driverBotID = INVALID_PLAYER_ID,
    driverBotCarID = INVALID_VEHICLE_ID,
    racingPlayerID = INVALID_PLAYER_ID,
    racingPlayerCarID = INVALID_VEHICLE_ID,
    Text3D:driverBotCarLabel,
    Text3D:racingPlayerCarLabel,
    currentCP = INVALID_RACE_CP,
    eRaceStatus:driverBotStatus = e_RACE_STATUS_NONE,
    eRaceStatus:racingPlayerStatus = e_RACE_STATUS_NONE
    ;

static Float:raceCPs[][] = {
    {-2256.4395,-124.9064,35.0073}, // First checkpoint
    {-2254.3975,2.7947, 35.0036},
    {-2298.3350,48.9540,34.9953},
    {-2430.9812,41.3129,34.8003},
    {-2594.0413,39.8761,4.0286},
    {-2706.0566,-3.8357,4.0126},
    {-2706.5227,-153.6011,4.0111},
    {-2685.0757,-210.2791,4.0109},
    {-2662.7595,-242.4410,5.6692},
    {-2705.4150,-289.2620,6.8690},
    {-2774.7522,-289.4026,6.8721}   // Last checkpoint
};

// Exposed functionality for the end user
forward NPCR_OnPlayerLoseRace(playerid);
forward NPCR_OnPlayerWinRace(playerid);

NPCR_LoadBot(const name[], const Float:pos[3], Float:angle)
{
    driverBotID = FCNPC_Create(name);
    FCNPC_Spawn(driverBotID, 2, pos[0], pos[1], pos[2]);
    FCNPC_SetAngle(driverBotID, angle);
}

NPCR_UnloadBot()
{
    FCNPC_Destroy(driverBotID);
    driverBotID = INVALID_PLAYER_ID;
}

NPCR_LoadCars(const Float:npcPos[3], Float:npcAngle, const Float:playerPos[3], Float:playerAngle)
{
    driverBotCarID = AddStaticVehicle(402, npcPos[0], npcPos[1], npcPos[2], npcAngle, 0, 0);
    driverBotCarLabel = Create3DTextLabel("Bot's Car", 0xFF00FFFF, 0.0, 0.0, 0.0, 10.0, 0);
    Attach3DTextLabelToVehicle(driverBotCarLabel, driverBotCarID, 0.0, 0.0, 1.2);
    racingPlayerCarID = AddStaticVehicle(402, playerPos[0], playerPos[1], playerPos[2], playerAngle, 15, 15);
    racingPlayerCarLabel = Create3DTextLabel("Your Car", 0x00FF30FF, 0.0, 0.0, 0.0, 10.0, 0);
    Attach3DTextLabelToVehicle(racingPlayerCarLabel, racingPlayerCarID, 0.0, 0.0, 1.2);
}

NPCR_PlayBotRecording(const recName[] = "race")
{
    driverBotStatus = e_RACE_STATUS_IN_PROGRESS;
    FCNPC_PutInVehicle(driverBotID, driverBotCarID, 0);
    FCNPC_StartPlayingPlayback(driverBotID, recName);
}

public FCNPC_OnFinishPlayback(npcid)
{
    driverBotStatus = e_RACE_STATUS_FINISHED;
    SendClientMessageToAll(-1, "Info: Bot recording has finished!");

    // Already accounted for when player has already finished below; need to cover for in progress and invalid states
    if(racingPlayerStatus == e_RACE_STATUS_IN_PROGRESS)
    {
        // Player didn't finish yet, so bot won
        CallLocalFunction("NPCR_OnPlayerLoseRace", "i", racingPlayerID);
    }
    else
    {
        // Player is on invalid state - something wrong happened
        SendClientMessage(racingPlayerID, -1, "Warn: Please share with devs - BOT FINISHED PLAYER INVALID");
    }

    return 1;
}

NPCR_CreatePlayerCheckpoint(playerid)
{
    racingPlayerID = playerid;
    racingPlayerStatus = e_RACE_STATUS_IN_PROGRESS;
    SetPlayerRaceCheckpoint(racingPlayerID, NORMAL_RACE_CP, raceCPs[0][0], raceCPs[0][1], raceCPs[0][2],
                            raceCPs[1][0], raceCPs[1][1], raceCPs[1][2], RACE_CP_SIZE);
    currentCP = 0;
}

public OnPlayerEnterRaceCheckpoint(playerid)
{
    if(currentCP < MAX_RACE_CP - 1)
    {
        // Player is not in the last checkpoint
        if(currentCP == MAX_RACE_CP - 2)
        {
            // Player is on the next to last checkpoint
            SetPlayerRaceCheckpoint(playerid, FINISH_RACE_CP,
                                    raceCPs[currentCP+1][0], raceCPs[currentCP+1][1], raceCPs[currentCP+1][2],
                                    0.0, 0.0, 0.0, RACE_CP_SIZE);
            SendClientMessage(playerid, -1, "Info: You're on the next to last checkpoint. Almost there!");
        }
        else
        {
            // Player is not on the next to last checkpoint
            SetPlayerRaceCheckpoint(playerid, NORMAL_RACE_CP,
                                    raceCPs[currentCP+1][0], raceCPs[currentCP+1][1], raceCPs[currentCP+1][2],
                                    raceCPs[currentCP+2][0], raceCPs[currentCP+2][1], raceCPs[currentCP+2][2], RACE_CP_SIZE);
        }
        currentCP++;
    }
    else
    {
        // Player is on the last checkpoint
        racingPlayerStatus = e_RACE_STATUS_FINISHED;
        SendClientMessage(playerid, -1, "Info: You've made it all the way to the end, congratulations!");

        if(driverBotStatus == e_RACE_STATUS_FINISHED)
        {
            // Bot has already finished, so player lost
            CallLocalFunction("NPCR_OnPlayerLoseRace", "i", playerid);
        }
        else if(driverBotStatus == e_RACE_STATUS_IN_PROGRESS)
        {
            // Bot didn't finish yet, so player won
            CallLocalFunction("NPCR_OnPlayerWinRace", "i", playerid);
        }
        else
        {
            // Bot is on invalid state - something wrong happened
            SendClientMessage(playerid, -1, "Warn: Please share with devs - PLAYER FINISHED BOT INVALID");
        }
        DisablePlayerRaceCheckpoint(playerid);
    }
    return 1;
}