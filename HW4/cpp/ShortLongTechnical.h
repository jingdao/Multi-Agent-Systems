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
		const char* name();
		void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability);
//		void new_information(int info,int time);
		void trades_history(std::vector<Log::Execution> *trades,int time);
		void trading_opportunity(double cash, int shares, double market_belief);
		int buy_objective(int amount);
		int sell_objective(int amount);

	private:
		int short_length,long_length;
		double max_short_exceed,max_long_exceed,margin;
		double short_average,long_average;
		Trade trade;
		State state;
		std::vector<Log::Execution> *execution_prices;
		double (*execute_callback)(MarketMaker::Transaction,int);
		double (*check_callback)(MarketMaker::Transaction,int);
};
