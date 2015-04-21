#include "Trader.h"

const char* Trader::name() {
	return "generic";
}
void Trader::simulation_params(int timesteps,int* possible_jump_locations,double single_jump_probability){}
void Trader::new_information(int info,int time){printf("%s\n",name());}
void Trader::trades_history(std::vector<Log::Execution> *trades,int time){}

//inputs: objective, feasible, initial_price
//outputs: final_shares, cancel
void Trader::optimize_shares(int (*objective)(int),void (*feasible)(int,bool*,bool*),double initial_price,int* final_shares,bool* cancel) {
//	double price = initial_price;
	int shares = 1;
	*cancel = true;
	double previous_objective = 0.0, current_objective;
	bool feas,used_cancel;
	while (true) {
		feasible(shares,&feas,&used_cancel);
		if (!feas) {
			*cancel=used_cancel;
			break;
		}
		current_objective = objective(shares);
		if (current_objective <= previous_objective)
			break;
		previous_objective = current_objective;
		shares+=1;
	}
	*final_shares = shares - 1;
}

//inputs: shares,execute
//outputs: price_per_share,final_shares
void Trader::execute_max(int shares,double (*execute)(int),double* price_per_share,int* final_shares) {
	*price_per_share = 0.0;
	while (*price_per_share==0.0 && shares > 0)	{
		*price_per_share = execute(shares);
		shares-=1;
	}
	*final_shares = shares + 1;
}

