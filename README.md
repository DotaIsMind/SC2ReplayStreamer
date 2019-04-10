# SC2ReplayStreamer
Goal of this application is to take a number of SC2 replay files (.SC2Replay) as an input and automatically run them via the SC2API, using its C++ library by Blizzard.

# Replay Speed
Running replays works using the SC2API C++ library, but only in non-realtime (i.e., as fast as possibly executed). Setting coordinator->SetRealtime(true); yields an assertion in the C++ library to fail, indicating that this feature is not implemented yet. A ticket for this has been opened here. Caused by this, the SC2Streamer emulates realtime playback by manually making the playback slower on each game loop, approximating the 22.4 game loops per second the game has on speed "Faster".

# Todo:
Configurability of main settings like replay file path and replay speed, if you want to extract replays data faster, you can set coordinator->SetStepSize(int step_size); to control the speed of replays.
CLI parameter to override replay file path
Interoperability with the Sc2LadderServer, probably via the SC2LadderWebHost

# Replay::OnUnitCreatedfunction abnormal condition
* 2019/4/1 The result of this function void Replay::OnUnitCreated is more than the actual number in the replays, and this problem has been solved, more details are available here ->[https://github.com/Blizzard/s2client-api/issues/299].
* 2019/4/10 Now we can collect data from a batch of replays, and I only collected replays of Zerg professional players in WESG 2018 and IEM-Katowice-2019(Two international competitions for StarCraft II, if you are a StarCraft player, you should be familiar with them)
