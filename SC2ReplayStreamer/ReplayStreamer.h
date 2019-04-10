#include "iostream"
#include "sc2api/sc2_api.h"
#include "vector"

using namespace std;
using namespace sc2;

class ReplayStreamer :public sc2::ReplayObserver
{
public:
	const sc2::ObservationInterface  *obs=Observation();

	vector<uint32_t>	count_units_build;
	std::set <uint64_t> unit_tag;
	
	static unsigned int count;
	static uint32_t self_build_ID;
	static uint32_t self_unit_ID;

	virtual bool IgnoreReplay(const ReplayInfo& replay_info, uint32_t& player_id);

	void OnGameStart() final;
	//void OnBuildingConstructionComplete(const sc2::Unit* unit);   
	void OnUnitCreated(const sc2::Unit* unit);
	void OnGameEnd() final;
};
