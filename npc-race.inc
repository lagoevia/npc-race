#if defined _INC_npc_race
    #endinput
#endif
#define _INC_npc_race

#include <a_samp>
#include <FCNPC>

static
    driverBotID = INVALID_PLAYER_ID,
    driverBotCarID = INVALID_VEHICLE_ID,
    racingPlayerCarID = INVALID_VEHICLE_ID,
    Text3D:driverBotCarLabel,
    Text3D:racingPlayerCarLabel
    ;

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