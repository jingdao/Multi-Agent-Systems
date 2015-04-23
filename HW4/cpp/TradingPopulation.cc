#include "TradingPopulation.h"

TradingPopulation::TradingPopulation(int timesteps,int* possible_jump_locations,double single_jump_probability,std::vector<Trader*> *traders,User* user) {
	this->timesteps = timesteps;
	this->possible_jump_locations = possible_jump_locations;
	this->single_jump_probability = single_jump_probability;

	for (unsigned int i=0;i<traders->size();i++) {
		(*traders)[i]->simulation_params(timesteps,possible_jump_locations,single_jump_probability);
		User* u = new User(user->initial_cash,user->initial_shares,i);
		Trader_tuple t = {(*traders)[i],u};
		active_traders.push_back(t);
	}
}

void TradingPopulation::new_information(BinomialDraws* get_info_callback,std::vector<Log::Execution> *execution_prices,int round_number) {
	for (unsigned int i=0;i<active_traders.size();i++) {
		active_traders[i].trader->trades_history(execution_prices,round_number);
		active_traders[i].trader->new_information(get_info_callback->get_draw(),round_number);
	}
}

std::vector<TradingPopulation::Trader_tuple> TradingPopulation::get_traders() {
	std::vector<Trader_tuple> res = active_traders;
	for (unsigned int i=res.size();i>1;i--) {
		int j  = rand() % i;
		Trader_tuple tmp = res[i-1];
		res[i-1] = res[j];
		res[j] = tmp;
	}
	return res;
}

std::vector<Trader*> TradingPopulation::get_bots(int fundamentals,int technical) {
	std::vector<Trader*> ret;
	for (int i=0;i<fundamentals;i++)
		ret.push_back(new MovingAverageBot());
	for (int i=0;i<technical;i++)
		if (i % 2 == 0)
			ret.push_back(new RangeTechnical());
		else
			ret.push_back(new ShortLongTechnical());
	return ret;
}
