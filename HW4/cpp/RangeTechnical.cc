#include "RangeTechnical.h"

void RangeTechnical::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability,int window,double margin,double max_exceed) {
	this->window = window;
	this->margin = margin;
	this->max_exceed = max_exceed;
}

void RangeTechnical::trades_history(double trades, int time) {

}

void RangeTechnical::trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double mu)  {
	if (execution_prices.size() < (unsigned int)window + 1)
		return;
	int endIndex = execution_prices.size()-1;
	double min_price=execution_prices[endIndex-1];
	double max_price=execution_prices[endIndex-1];
	for (int i=1;i<window+1;i++) {
		double p = execution_prices[endIndex-1-i];
		if (p < min_price)
			min_price = p;
		if (p > max_price)
			max_price = p;
	}
	if (execution_prices[endIndex] > max_price + max_price * margin) {

	} else if (execution_prices[endIndex] < min_price - min_price * margin) {

	}
}
