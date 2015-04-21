#pragma once
#include "Trader.h"
#include <vector>

class RangeTechnical : public Trader {
	public:
		const char* name();
		void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability,int window=20,double margin=0.05,double max_exceed=2.0);
//		void new_information(int info,int time);
		void trades_history(std::vector<Log::Execution> *trades,int time);
		void trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu);

	private:
		int window;
		double margin,max_exceed;
		std::vector<Log::Execution> *execution_prices;
		double (*execute_callback)(MarketMaker::Transaction,int);
		double (*check_callback)(MarketMaker::Transaction,int);

		double execute_buy(int amount);
		double execute_sell(int amount);
		int sell_objective(int amount);
		int buy_objective(int amount);
		void sell_feasible(int,bool*,bool*);
		void buy_feasible(int,bool*,bool*);
};
