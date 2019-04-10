#pragma once

#include "sc2api/sc2_api.h"

using namespace sc2;

class Streamer: public Coordinator{
public:
	Streamer();
	static unsigned int Replay_Count;
	void run(int argc, char **argv);
};