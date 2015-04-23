#pragma once
#include "BinomialDraws.h"
#include "Trader.h"
#include "MovingAverageBot.h"
#include "ShortLongTechnical.h"
#include "RangeTechnical.h"

class TradingPopulation  {
	
	public:
		struct Trader_tuple {
			Trader* trader;
			User* user;
		};

		TradingPopulation(int timesteps,int* possible_jump_locations,double single_jump_probability,std::vector<Trader*> *traders,User* user);
		~TradingPopulation(); 
		void new_information(BinomialDraws* get_info_callback,std::vector<Log::Execution> *execution_prices,int round_number);
		std::vector<Trader_tuple> get_traders();
		static std::vector<Trader*> get_bots(int fundamentals,int technical);

		std::vector<Trader_tuple> active_traders;

	private:
		int timesteps;
		int* possible_jump_locations;
		double single_jump_probability;

};
