#include "Simulation.h"

Simulation::Simulation(int timesteps,LMSRFactory* market_fact,std::vector<Trader*> *trader_list,
			double initial_cash,int initial_shares,
			double jump_probability,double initial_p,double spread_calculations) {
	this->traders = trader_list;
	this->possible_jump_locations = new int[timesteps];
	for (int i=0;i<timesteps;i++)
		this->possible_jump_locations[i]=i;
	if (jump_probability < 0)
//		this->jump_probability = 1.0 / timesteps;
		this->jump_probability = 0.0;
	else
		this->jump_probability = jump_probability;
	this->initial_cash = initial_cash;
	this->initial_shares = initial_shares;
	this->timesteps = timesteps;
	this->market_fact = market_fact;
	this->trading_bots = nullptr;
	this->log = new Log();
	this->initial_p = 0.5;
//	this->initial_p = initial_p;
}

void Simulation::simulate() {
	market = market_fact->make();
	User u(initial_cash,initial_shares);
	trading_bots = new TradingPopulation(timesteps,possible_jump_locations,jump_probability,traders,&u);
	BinomialDraws binom(initial_p);
	p_vec = new double[timesteps];

	std::vector<TradingPopulation::Trader_tuple> *user_list = &(trading_bots->active_traders);
	for (unsigned int j=0;j<user_list->size();j++) {
		(*user_list)[j].trader->user = (*user_list)[j].user;
		(*user_list)[j].trader->stock_maker = market;
		(*user_list)[j].trader->log = log;
	}

	int i;
	for (i=0;i<timesteps;i++) {
		double r = (double)rand() / (double)RAND_MAX;
		if (r < jump_probability)
			binom.do_jump();
		Log::Belief b = {i,market->mu};
		log->beliefs.push_back(b);
		p_vec[i]=binom.p;
		if (binom.p == 1.0 || binom.p == 0.0)
			break;
		trading_bots->new_information(&binom,&(log->execution_prices),i);
		std::vector<TradingPopulation::Trader_tuple> active_traders = trading_bots->get_traders();
		for (unsigned int j=0;j<active_traders.size();j++) {
			Trader* trader = active_traders[j].trader;
			User* trader_user = active_traders[j].user;
			trader->trading_opportunity(trader_user->cash,trader_user->shares,market->mu);
		}
	}

	liquidation = 100.0 * p_vec[i-1];
}

std::vector<Simulation::Profit> Simulation::profits_by_user() {
	std::vector<Profit> ret;
	std::vector<TradingPopulation::Trader_tuple> *user_list = &(trading_bots->active_traders);
	for (unsigned int i=0;i<user_list->size();i++) {
		bool found=false;
		for (unsigned int j=0;j<ret.size();j++) {
			if (ret[j].trader_name == (*user_list)[i].trader->name()) {
				ret[j].profit_sum += (*user_list)[i].user->profit(liquidation);
				found=true;
				break;
			}
		}
		if (found) continue;
		Profit p = {
			(*user_list)[i].trader->name(),
			(*user_list)[i].user->profit(liquidation)
		};
		ret.push_back(p);
	}
	return ret;
}
