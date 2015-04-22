#pragma once
#include "Log.h"
#include "MarketMaker.h"
#include "Prices.h"

class Trader {
	public:
		virtual const char* name();
		virtual void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability);
		virtual void new_information(int info,int time);
		virtual void trades_history(std::vector<Log::Execution> *trades,int time);
		virtual void trading_opportunity(double cash, int shares, double market_belief) = 0;
		void optimize_shares(MarketMaker::Transaction buysell,int* final_shares,bool* cancel);
		void execute_max(int shares,MarketMaker::Transaction buysell,double* price_per_share,int* final_shares);

		virtual int buy_objective(int amount);
		virtual int sell_objective(int amount);

		double check_callback(MarketMaker::Transaction buysell,int quantity);
		double execute_callback(MarketMaker::Transaction buysell,int quantity);

		User* user;
		LMSR* stock_maker;
		Log* log;
		int time;

};

