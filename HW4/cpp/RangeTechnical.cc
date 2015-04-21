#include "RangeTechnical.h"

const char* RangeTechnical::name() {
	return "tech_range";
}

void RangeTechnical::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability,int window,double margin,double max_exceed) {
	this->window = window;
	this->margin = margin;
	this->max_exceed = max_exceed;
}

void RangeTechnical::trades_history(std::vector<Log::Execution> *trades,int time) {
	execution_prices = trades;
}

void RangeTechnical::trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu)  {
	if (execution_prices->size() < (unsigned int)window + 1)
		return;
	int endIndex = execution_prices->size()-1;
	double min_price=(*execution_prices)[endIndex-1].price_per_share;
	double max_price=(*execution_prices)[endIndex-1].price_per_share;
	for (int i=1;i<window+1;i++) {
		double p = (*execution_prices)[endIndex-1-i].price_per_share;
		if (p < min_price)
			min_price = p;
		if (p > max_price)
			max_price = p;
	}
	if ((*execution_prices)[endIndex].price_per_share > max_price + max_price * margin) {

	} else if ((*execution_prices)[endIndex].price_per_share < min_price - min_price * margin) {

	}
}
