#pragma once
#include "LMSR.h" 

class Prices {
	public:
		static double check(MarketMaker::Transaction buysell,int quantity,LMSR* stock_maker,User* user);
		static double execute(MarketMaker::Transaction buysell,int quantity,LMSR* stock_maker,User* user);
		static double cancel(MarketMaker::Transaction buysell,int quantity,LMSR* stock_maker, User* user);
};
