#pragma once
#include "TradingPopulation.h"
#include "LMSRFactory.h"
#include "Log.h"

class Simulation {
	public:
		struct Profit {
			const char* trader_name;
			double profit_sum;
		};
		Simulation(int timesteps,LMSRFactory* market_fact,std::vector<Trader*> *trader_list,
					double initial_cash=0,int initial_shares=0,
					double jump_probability=-1,double initial_p=-1,double spread_calculations=-1);
		void simulate();
		std::vector<Profit> profits_by_user();
		
		double* p_vec;
		double liquidation;
		Log* log;
		LMSR* market;
		TradingPopulation* trading_bots;

//	private:
		std::vector<Trader*> *traders;
		int* possible_jump_locations;
		double jump_probability;
		int timesteps;
		double initial_cash;
		int initial_shares;
		LMSRFactory* market_fact;
		double initial_p;

};
