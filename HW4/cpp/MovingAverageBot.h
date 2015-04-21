#pragma once
#include "Trader.h"

class MovingAverageBot : public Trader {
	public:
		const char* name();
		void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability, double start_belief=50.0,double alpha=0.9,int min_block_size=2,int start_block_size=20);
		void new_information(int info,int time);
		void trades_history(std::vector<Log::Execution> *trades,int time);
		void trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu);

	private:
		int timesteps;
		int* possible_jump_locations;
		double single_jump_probability,belief,alpha;
		int min_block_size,start_block_size;
		std::vector<Log::Execution> *trades;
};
