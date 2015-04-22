#include "Trader.h"

const char* Trader::name() {
	return "generic";
}
void Trader::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability){}
void Trader::new_information(int info,int time){}
void Trader::trades_history(std::vector<Log::Execution> *trades,int time){}
int Trader::buy_objective(int amount) { return -1;}
int Trader::sell_objective(int amount) { return -1;}

void Trader::optimize_shares(MarketMaker::Transaction buysell,int* final_shares,bool* cancel) {
	int shares = 1;
	*cancel = true;
	double previous_objective = 0.0, current_objective;
	bool feas,used_cancel=false;
	while (true) {
		feas = shares < 200;
		if (!feas) {
			*cancel=used_cancel;
			break;
		}
		if (buysell == MarketMaker::BUY)
			current_objective = buy_objective(shares);
		else
			current_objective = sell_objective(shares);
		if (current_objective <= previous_objective)
			break;
		previous_objective = current_objective;
		shares += 1;
	}
	*final_shares = shares - 1;
}

void Trader::execute_max(int shares,MarketMaker::Transaction buysell,double* price_per_share,int* final_shares) {
	*price_per_share = 0.0;
	while (*price_per_share==0.0 && shares > 0)	{
		*price_per_share = execute_callback(buysell,shares);
		shares-=1;
	}
	*final_shares = shares + 1;
}

double Trader::check_callback(MarketMaker::Transaction buysell,int quantity) {
	double per_share = Prices::check(buysell,quantity,stock_maker,user);
	log->event(time,Log::CHECK,name(),buysell,quantity,stock_maker->mu,per_share);
	return per_share;
}

double Trader::execute_callback(MarketMaker::Transaction buysell,int quantity) {
	double previous_mu = stock_maker->mu;
	double success = Prices::execute(buysell,quantity,stock_maker,user);
	log->event(time,Log::EXECUTE,name(),buysell,quantity,previous_mu,success);
	return success;
}
