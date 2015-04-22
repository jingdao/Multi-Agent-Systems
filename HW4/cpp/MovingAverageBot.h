#pragma once
#include "Trader.h"

class MovingAverageBot : public Trader {
	public:
		const char* name();
		void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability);
		void new_information(int info,int time);
		void trades_history(std::vector<Log::Execution> *trades,int time);
		void trading_opportunity(double cash, int shares, double market_belief);

	private:
		int timesteps;
		int* possible_jump_locations;
		double single_jump_probability,belief,alpha;
		int min_block_size,start_block_size;
		std::vector<Log::Execution> *trades;
};
