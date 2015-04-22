#include "RunExperiments.h"

void RunExperiments::run(std::vector<Trader*> *trader_list,int timesteps,int simulations,double lmsr_b) {
	LMSRFactory marketmakers(lmsr_b);

	const char* c = "LMSR";
	std::vector<Profit> results;
	for (int i=0;i<simulations;i++) {
		Simulation sim_obj(timesteps,&marketmakers,trader_list);
		sim_obj.simulate();
		std::vector<Simulation::Profit> profits = sim_obj.profits_by_user();
		if (results.size()==0) {
			for (unsigned int j=0;j<profits.size();j++) {
				Profit p = {
					profits[j].trader_name,
					profits[j].profit_sum,
					profits[j].profit_sum,
					profits[j].profit_sum,
					profits[j].profit_sum * profits[j].profit_sum
				};
				results.push_back(p);
			}
			double d = sim_obj.market->user_account->profit(sim_obj.liquidation);
			Profit p = {c,d,d,d,d};
			results.push_back(p);
		} else {
			for (unsigned int j=0;j<profits.size();j++) {
				double d;
				if (j==profits.size()-1)
					d = sim_obj.market->user_account->profit(sim_obj.liquidation);
				else
					d = profits[j].profit_sum;
				if (d < results[j].min)
					results[j].min = d;
				if (d > results[j].max)
					results[j].max = d;
				results[j].mean += d;
				results[j].std_dev += d * d;
			}
		}
	}

	printf("\nProfits (%d samples)\n",simulations);
	printf("%-20s %8s %8s %8s %7s\n","trader","mean","min","max","std_dev");
	unsigned int i;
	for (i=0;i<results.size()-1;i++) {
		results[i].mean /= simulations;
		results[i].std_dev = sqrt(results[i].std_dev / simulations + results[i].mean * results[i].mean);
		printf("%-20s %8.2f %8.2f %8.2f %7.2f\n",
			results[i].trader_name,results[i].mean,
			results[i].min,results[i].max,results[i].std_dev);
	}
	printf("LMSR(b=%6.2f)       %8.2f %8.2f %8.2f %7.2f\n",
			lmsr_b,results[i].mean,
			results[i].min,results[i].max,results[i].std_dev);

}
