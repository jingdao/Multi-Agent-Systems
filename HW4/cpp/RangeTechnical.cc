#include "RangeTechnical.h"

const char* RangeTechnical::name() {
	return "tech_range";
}

void RangeTechnical::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability) {
	this->window = 20;
	this->margin = 0.05;
	this->max_exceed = 2.0;
}

void RangeTechnical::trades_history(std::vector<Log::Execution> *trades,int time) {
	execution_prices = trades;
}

void RangeTechnical::trading_opportunity(double cash, int shares, double market_belief) {
	if (execution_prices->size() < (unsigned int)window + 1)
		return;
	int endIndex = execution_prices->size()-1;
	min_price=(*execution_prices)[endIndex-1].price_per_share;
	max_price=(*execution_prices)[endIndex-1].price_per_share;
	for (int i=1;i<window+1;i++) {
		double p = (*execution_prices)[endIndex-1-i].price_per_share;
		if (p < min_price)
			min_price = p;
		if (p > max_price)
			max_price = p;
	}
	int shares_to_trade,final_shares;
	bool cancel;
	double price_per_share;
	if ((*execution_prices)[endIndex].price_per_share > max_price + max_price * margin) {
		optimize_shares(MarketMaker::SELL,&shares_to_trade,&cancel);
		if (shares > 0)
			execute_max(shares_to_trade,MarketMaker::SELL,&price_per_share,&final_shares);
	} else if ((*execution_prices)[endIndex].price_per_share < min_price - min_price * margin) {
		optimize_shares(MarketMaker::BUY,&shares_to_trade,&cancel);
		if (shares > 0)
			execute_max(shares_to_trade,MarketMaker::BUY,&price_per_share,&final_shares);
	}
}

int RangeTechnical::sell_objective(int amount) {
	double price = check_callback(MarketMaker::BUY,amount);
	if (price <= min_price + max_exceed &&
		price < 100.0 && price > 0.0)
		return amount;
	else
		return -1;
}

int RangeTechnical::buy_objective(int amount) {
	double price = check_callback(MarketMaker::BUY,amount);
	if (price >= min_price - max_exceed &&
		price < 100.0 && price > 0.0)
		return amount;
	else
		return -1;
}
