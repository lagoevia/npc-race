# npc-race

[![sampctl](https://img.shields.io/badge/sampctl-npc--race-2f2f2f.svg?style=for-the-badge)](https://github.com/lagoevia/npc-race)

<!--
Short description of your library, why it's useful, some examples, pictures or
videos. Link to your forum release thread too.

Remember: You can use "forumfmt" to convert this readme to forum BBCode!

What the sections below should be used for:

`## Installation`: Leave this section un-edited unless you have some specific
additional installation procedure.

`## Testing`: Whether your library is tested with a simple `main()` and `print`,
unit-tested, or demonstrated via prompting the player to connect, you should
include some basic information for users to try out your code in some way.

And finally, maintaining your version number`:

* Follow [Semantic Versioning](https://semver.org/)
* When you release a new version, update `VERSION` and `git tag` it
* Versioning is important for sampctl to use the version control features

Happy Pawning!
-->

## Installation

Simply install to your project:

```bash
sampctl package install lagoevia/npc-race
```

Include in your code and begin using the library:

```pawn
#include <npc-race>
```

## Usage

<!--
Write your code documentation or examples here. If your library is documented in
the source code, direct users there. If not, list your API and describe it well
in this section. If your library is passive and has no API, simply omit this
section.
-->

### Function List
*Notes*:
1. Different functions below have the option of taking in user spawn data - if none is supplied, then the default values are used.
2. `NPCR_RaceAsk` will not work without an appropriate define: `#define NPCR_USE_DIALOG`
3. `NPCR_RaceStart` will only perform the countdown actions with an appropriate define: `#define NPCR_USE_COUNTDOWN`

Either/one/both defines above **must** be placed **before** including the library.

- `NPCR_LoadBot(const name[], bool:useCustomSpawn = false, const Float:npcSpawn[4] = {})`: loads the driver bot into the game.
- `NPCR_UnloadBot()`: unloads the driver bot from the game.
- `NPCR_LoadCars(bool:useCustomSpawns = false, const Float:npcCarSpawn[4] = {}, const Float:playerCarSpawn[4] = {})`: loads the npc and player cars, as well as their labels.
- `NPCR_SetPlayerSpawn(const Float:playerSpawn[4])`: sets the spawn data for *any* player that would race the bot.
- `NPCR_RaceAsk(playerid, const recName[] = "race")`: "asks" for a race via dialog, where the user can accept/decline.
- `NPCR_RaceStart(playerid, const recName[] = "race")`: starts a race, either with a cooldown or immediately.
- `NPCR_TeleportToRace(playerid)`: teleports a player to their race spawn.

Functions below this point are internal and should not be called directly other than for debugging purposes.

- `NPCR_PlayBotRecording(const recName[] = "race")`: puts the driver bot in their vehicle and starts the recording.
- `NPCR_CreatePlayerCheckpoint(playerid)`: creates the first checkpoint of the race for the player.
- `NPCR_RaceCleanup(playerid, npcid)`: performs "clean up" tasks, used after the race ends.

### Exposed Callbacks
- `forward NPCR_OnPlayerLoseRace(playerid);`: will be called when `playerid` loses the race.
- `forward NPCR_OnPlayerWinRace(playerid);`: will be called when `playerid` wins the race.

You can use these appropriately as you wish - show a winning screen, give an accomplishment, etc. You should also keep in mind that these are called **before** `NPCR_RaceCleanup`.

### Internal Callbacks
The library (re)uses some callbacks for which it is not responsible. It ensures interoperability with others through ALS hooks.

- `OnPlayerEnterRaceCheckpoint` is internally referred to as `NPCR_OnPlayerEnterRaceCP`.
- `FCNPC_OnFinishPlayback` is internally referred to as `NPCR_OnFinishPlayback`.



## Testing

<!--
Depending on whether your package is tested via in-game "demo tests" or
y_testing unit-tests, you should indicate to readers what to expect below here.
-->

To test, simply run the package:

```bash
sampctl package run
```
