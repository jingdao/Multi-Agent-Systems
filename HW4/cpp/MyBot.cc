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
	//trades is a pointer to a vector of Executions
	//Execution is a struct with the following fields:
	//{execution_price, BUY/SELL, quantity, previous_market_price}
	this->trades = trades;
}

void MyBot::trading_opportunity(double cash, int shares, double market_belief) {
	//cash: how much cash the bot has right now
	//shares: how many shares the bot owns
	//market_belief: the market's belief about the value of a share
	
	//example: check the price per share
	//check_callback(MarketMaker::BUY,0);

	//example: buy shares
	//execute_callback(MarketMaker::BUY,0);

}

int main(int argc, char* argv[]) {
	srand (time(NULL));

	// create 5 fundamental bots and 2 technical bots 
	std::vector<Trader*> agents;
//	agents.push_back(new MyBot());
	std::vector<Trader*> bots = TradingPopulation::get_bots(5,2);
	for (unsigned int i=0;i<bots.size();i++)
		agents.push_back(bots[i]);

	int num_simulations = 1000;
	int num_timesteps = 100;
	double lmsr_b = 250;

	// runs a single simulation and prints out statistics
//	PlotSimulation::run(&agents,num_timesteps,lmsr_b);

	// runs multiple simulations and prints out average profit
	RunExperiments::run(&agents,num_timesteps,num_simulations,lmsr_b);
}
