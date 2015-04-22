#include <stdio.h>

#include "MyBot.h"

const char* MyBot::name() {
	return "my_bot";
}

void MyBot::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability) {
	this->timesteps=timesteps;
	this->possible_jump_locations=possible_jump_locations;
	this->single_jump_probability=single_jump_probability;
}

void MyBot::new_information(int info,int time) {
	information.push_back(info);
}

void MyBot::trades_history(std::vector<Log::Execution> *trades,int time) {
	this->trades = trades;
}

void MyBot::trading_opportunity(double cash, int shares, double market_belief) {

}

int main(int argc, char* argv[]) {
	srand (time(NULL));

//	User u(0,0);
	std::vector<Trader*> bots = TradingPopulation::get_bots(5,2);
	bots.push_back(new MyBot());
//	std::vector<Log::Execution> x;
//	TradingPopulation tp(10,nullptr,0.2,&bots,&u);
//	tp.new_information(&bd,&x,0);
//	std::vector<TradingPopulation::Trader_tuple> t = tp.active_traders;
//	for (unsigned int i=0;i<t.size();i++) {
//		printf("%s %d %f\n",t[i].user->name,t[i].user->shares,t[i].user->cash);
//	}

//	PlotSimulation::run(&bots,1,250);
	RunExperiments::run(&bots,100,100,250);
}
