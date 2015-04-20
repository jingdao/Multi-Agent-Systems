#pragma once
#include "Trader.h"
#include <vector>

class ShortLongTechnical : public Trader {
	public:
		enum State {
			HIGH,LOW,NONE
		};
		enum Trade {
			BUY,SELL,FALSE
		};
		const char* name = "tech_short_long";
		void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability,int short_length=10,int long_length=10,double max_long_exceed=2.0,double max_short_exceed=2.0,double margin=0.05);
//		void new_information(int info,int time);
		void trades_history(double trades,int time);
		void trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu) = 0;

	private:
		int short_length,long_length;
		double max_short_exceed,max_long_exceed,margin;
		double short_average,long_average;
		Trade trade;
		State state;
		std::vector<double> execution_prices;
		double (*execute_callback)(MarketMaker::Transaction,int);
		double (*check_callback)(MarketMaker::Transaction,int);

		double execute_buy(int amount);
		double execute_sell(int amount);
		int sell_objective(int amount);
		int buy_objective(int amount);
		void sell_feasible(int,bool*,bool*);
		void buy_feasible(int,bool*,bool*);
};
