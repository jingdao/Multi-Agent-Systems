#include "ShortLongTechnical.h"

const char* ShortLongTechnical::name() {
	return "tech_short_long";
}

void ShortLongTechnical::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability,int short_length,int long_length,double max_long_exceed,double max_short_exceed,double margin) {
	this->short_length=short_length;
	this->long_length=long_length;
	this->max_short_exceed=max_short_exceed;
	this->max_long_exceed=max_long_exceed;
	this->margin=margin;
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

void ShortLongTechnical::trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu) {
	if (trade==FALSE)
		return;
	this->execute_callback = execute_callback;
	this->check_callback = check_callback;
//	int shares,final_shares;
//	bool cancel;
//	double price_per_share;

//	if (trade == SELL) {
//		optimize_shares(this->sell_objective,this->sell_feasible,mu,&shares,&cancel);
//		if (shares > 0)
//			execute_max(shares,this->execute_sell,&price_per_share,&final_shares);
//	} else  if (trade == BUY) {
//		optimize_shares(this->buy_objective,this->buy_feasible,mu,&shares,&cancel);
//		if (shares > 0)
//			execute_max(shares,this->execute_buy,&price_per_share,&final_shares);
//	}
	
}

double ShortLongTechnical::execute_buy(int amount) {
	return execute_callback(MarketMaker::BUY,amount);
}

double ShortLongTechnical::execute_sell(int amount) {
	return execute_callback(MarketMaker::SELL,amount);
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
		execution_price >= short_average + max_short_exceed &&
		execution_price < 100.0 &&
		execution_price > 0.0)
		return amount;
	else
		return -1;
}

void ShortLongTechnical::sell_feasible(int amount, bool* feas, bool* used_cancel ) {
	*feas = amount < 200;
	*used_cancel = false;
}

void ShortLongTechnical::buy_feasible(int amount, bool* feas, bool* used_cancel) {
	*feas = amount < 200;
	*used_cancel = false;
}
