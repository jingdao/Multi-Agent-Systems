#include "MovingAverageBot.h"

const char* MovingAverageBot::name() {
	return "fund_moving_average";
}

void MovingAverageBot::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability, double start_belief,double alpha,int min_block_size,int start_block_size) {
	this->timesteps=timesteps;
	this->possible_jump_locations=possible_jump_locations;
	this->single_jump_probability=single_jump_probability;
	this->belief=start_belief;
	this->alpha=alpha;
	this->min_block_size=min_block_size;
	this->start_block_size=start_block_size;
}

void MovingAverageBot::new_information(int info,int time) {
	belief = belief * alpha + info * 100 * (1 - alpha);
}

void MovingAverageBot::trades_history(std::vector<Log::Execution> *trades,int time) {
	this->trades = trades;
}

void MovingAverageBot::trading_opportunity(double (*cash_callback)(),int (*shares_callback)(),double (*check_callback)(MarketMaker::Transaction,int), double (*execute_callback)(MarketMaker::Transaction,int),double market_belief) {
	double current_belief = (belief + market_belief) / 2.0;
	current_belief = current_belief<99.0 ? current_belief : 99.0;
	current_belief = current_belief>1.0 ? current_belief : 1.0;
	bool bought_once=false, sold_once=false;
	double block_size = start_block_size;
	while (true) {
		if (!sold_once && (check_callback(MarketMaker::BUY,block_size) < current_belief)) {
			execute_callback(MarketMaker::BUY,block_size);
			bought_once=true;
		} else if (!bought_once && (check_callback(MarketMaker::SELL,block_size) > current_belief)) {
			execute_callback(MarketMaker::SELL,block_size);
			sold_once=true;
		} else {
			if (block_size == min_block_size)
				break;
			block_size/=2;
			if (block_size < min_block_size)
				block_size = min_block_size;
		}
	}
}
