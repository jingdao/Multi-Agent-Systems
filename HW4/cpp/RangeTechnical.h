#pragma once
#include "Trader.h"
#include <vector>

class RangeTechnical : public Trader {
	public:
		const char* name();
		void simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability);
//		void new_information(int info,int time);
		void trades_history(std::vector<Log::Execution> *trades,int time);
		void trading_opportunity(double cash, int shares, double market_belief);

		int sell_objective(int amount);
		int buy_objective(int amount);

	private:
		int window;
		double margin,max_exceed;
		double min_price,max_price;
		std::vector<Log::Execution> *execution_prices;
};
