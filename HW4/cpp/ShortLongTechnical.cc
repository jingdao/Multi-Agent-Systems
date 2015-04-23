#include "ShortLongTechnical.h"

const char* ShortLongTechnical::name() {
	return "tech_short_long";
}

void ShortLongTechnical::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability) {
	this->short_length=10;
	this->long_length=30;
	this->max_short_exceed=2.0;
	this->max_long_exceed=2.0;
	this->margin=0.05;
	this->state=NONE;
	this->trade=FALSE;
	this->short_average=0.0;
	this->long_average=0.0;
}

void ShortLongTechnical::trades_history(std::vector<Log::Execution> *trades,int time) {
	execution_prices = trades;
	if (execution_prices->size() < (unsigned int)long_length) {
		trade=FALSE;
		return;
	}
	short_average=0.0;
	long_average=0.0;
	int endIndex = execution_prices->size()-1;
	for (int i=0;i<long_length;i++) {
		if (i<short_length)
			short_average+=(*execution_prices)[endIndex-i].price_per_share;
		long_average+=(*execution_prices)[endIndex-i].price_per_share;
	}
	short_average/=short_length;
	long_average/=long_length;
	if (state==NONE) {
		trade=FALSE;
		if (short_average > long_average)
			state = HIGH;
		else
			state = LOW;
	} else if (state==HIGH) {
		if (long_average > short_average + margin * short_average ) {
			state = LOW;
			trade = SELL;
		}
	} else if (state==LOW) {
		if (long_average < short_average - margin * short_average) {
			state = HIGH;
			trade = BUY;
		}
	}
}

void ShortLongTechnical::trading_opportunity(double cash, int shares, double market_belief) {
	if (trade==FALSE)
		return;
	int shares_to_trade,final_shares_to_trade;
	bool cancel;
	double price_per_share;

	if (trade == SELL) {
		optimize_shares(MarketMaker::SELL,&shares_to_trade,&cancel);
		if (shares_to_trade > 0)
			execute_max(shares_to_trade,MarketMaker::SELL,&price_per_share,&final_shares_to_trade);
	} else if (trade == BUY) {
		optimize_shares(MarketMaker::BUY,&shares_to_trade,&cancel);
		if (shares_to_trade > 0)
			execute_max(shares_to_trade,MarketMaker::BUY,&price_per_share,&final_shares_to_trade);
	}
	
}

int ShortLongTechnical::sell_objective(int amount) {
	double execution_price = check_callback(MarketMaker::SELL,amount);
	if (execution_price >= long_average - max_long_exceed &&
		execution_price >= short_average - max_short_exceed &&
		execution_price < 100.0 &&
		execution_price > 0.0)
		return amount;
	else
		return -1;
}

int ShortLongTechnical::buy_objective(int amount) {
	double execution_price = check_callback(MarketMaker::BUY,amount);
	if (execution_price <= long_average + max_long_exceed &&
		execution_price <= short_average + max_short_exceed &&
		execution_price < 100.0 &&
		execution_price > 0.0)
		return amount;
	else
		return -1;
}
