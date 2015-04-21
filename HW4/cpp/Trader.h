#pragma once
#include <stdio.h>
#include "Log.h"
#include "MarketMaker.h"

class Trader {
	public:
		virtual const char* name();
		virtual void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability);
		virtual void new_information(int info,int time);
		virtual void trades_history(std::vector<Log::Execution> *trades,int time);
		virtual void trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu) = 0;
		void optimize_shares(int (*objective)(int),void (*feasible)(int,bool*,bool*),double initial_price,int* final_shares,bool* cancel);
		void execute_max(int shares,double (*execute)(int),double* price_per_share,int* final_shares);

};

