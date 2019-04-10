#include "ReplayStreamer.h"
#include "CoordinatorStreamer.h"
#include "iostream"
#include "sc2api/sc2_api.h"
#include  "set"
#include "fstream"

using namespace std;
using namespace sc2;

bool ReplayStreamer::IgnoreReplay(const ReplayInfo & replay_info, uint32_t & player_id)
{
	if (replay_info.players[0].race == sc2::Race::Zerg)
	{
		cout << "This replay's player[0] is Zerg" << endl;
		return false;
	}
	else
	{
		cout << "This replay's player[0] is not Zerg" << endl;
		return true;
	}
}

void ReplayStreamer::OnGameStart()
{
	count_units_build.resize(obs->GetUnitTypeData().size());
	std::fill(count_units_build.begin(),count_units_build.end(),0);
	//std::fill(unit_tag.begin(), unit_tag.end(), 0);
}

unsigned int ReplayStreamer::count = 0;

uint32_t ReplayStreamer::self_build_ID = 0;
uint32_t ReplayStreamer::self_unit_ID = 0;

/*
void ReplayStreamer::OnBuildingConstructionComplete(const sc2::Unit * unit)
{ 
		self_build_ID = unit->unit_type;
		uint32_t Current_GameLoop = obs->GetGameLoop();
		++count_units_build[unit->unit_type];
		cout << self_build_ID << " " << Current_GameLoop << endl;
		
}*/
//Because every unit was created and have a unique tag, so use food_requerede and UNIT_TYPEID to determine whether the building of units.
void ReplayStreamer::OnUnitCreated(const sc2::Unit *unit)
{
	count++;

	typedef set<uint64_t>::iterator IT;
	pair<IT, bool> bool_insert;
	
	bool_insert = unit_tag.insert(unit->tag);

	const sc2::UnitTypes& food_type = obs->GetUnitTypeData();
	uint32_t Current_GameLoop = obs->GetGameLoop();

	std::ofstream out_unitdata("ZPlayerUnit (" + to_string(Streamer::Replay_Count) + ").txt", std::ofstream::app);
	if (!out_unitdata.is_open())
		std::ferror(NULL);

	std::ofstream out_builddata("ZPlayerBuild (" + to_string(Streamer::Replay_Count) + ").txt", std::ofstream::app);
	if (!out_builddata.is_open())
		std::ferror(NULL);

	//Unit and Build in different files
	if ((food_type[unit->unit_type].food_required == 0) && (unit->unit_type != sc2::UNIT_TYPEID::ZERG_LARVA))  
	{
		if (bool_insert.second)
		{
			self_build_ID = unit->unit_type;
			out_builddata << self_build_ID << " " << Current_GameLoop << endl;
			++count_units_build[unit->unit_type];
		}
	}
	else if((unit->unit_type != sc2::UNIT_TYPEID::ZERG_LARVA) && (food_type[unit->unit_type].food_required >0))
	{
		if (bool_insert.second)
		{
			self_unit_ID = unit->unit_type;
			out_unitdata << self_unit_ID << " " << Current_GameLoop << endl;
			++count_units_build[unit->unit_type];
		}
	}

			/* This is a different outstream
			if (bool_insert.second)
			{
				++count_units_build[unit->unit_type];
				if ((food_type[unit->unit_type].food_required == 0) && (unit->unit_type != sc2::UNIT_TYPEID::ZERG_LARVA))  //人口等于0和非虫卵
				{
						self_build_ID = unit->unit_type;
				}
				else if ((unit->unit_type != sc2::UNIT_TYPEID::ZERG_LARVA) && (food_type[unit->unit_type].food_required >0))
				{
					self_unit_ID = unit->unit_type;
				}
			}

			out_builddata << self_build_ID << " " << Current_GameLoop << endl;
			out_unitdata << self_unit_ID << " " << Current_GameLoop << endl;
			
			cout << self_unit_ID << " " <<self_build_ID << " " <<Current_GameLoop << endl;
			*/
			
	if (ReplayStreamer::Control()->IsFinishedGame())
	{
		out_unitdata.close();
		out_builddata.close();
	}
}

void ReplayStreamer::OnGameEnd()
{
	cout << "Units created:" << endl;

	const sc2::UnitTypes& unit_type = obs->GetUnitTypeData();
	for (uint32_t i = 0; i<count_units_build.size(); ++i)
	{
		if (count_units_build[i] == 0)
			continue;
		cout << unit_type[i].name <<":"<< to_string(count_units_build[i]) << endl;
	}
	cout << count << endl;
	cout <<"Finished!" << endl;
}
