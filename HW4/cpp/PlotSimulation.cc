#include "PlotSimulation.h"

void PlotSimulation::run(std::vector<Trader*> *traders,int timesteps,double lmsr_b) {
	LMSRFactory market_fact(lmsr_b);
	Simulation sim_obj(timesteps,&market_fact,traders);
	sim_obj.simulate();

	if (0) {
//		std::vector<Log::Event> *events = &sim_obj.log->events;
		std::vector<Log::Event> e = sim_obj.log->filter(Log::EXECUTE);
		std::vector<Log::Event> *events = &e;
		for (unsigned int i=0;i<events->size();i++) {
			Log::Event ev = (*events)[i];
			printf("%3d %5s %.6s%1d %4s %3d %5.2f\n",
				ev.time,
				ev.event_type==Log::CHECK?"check":"exec",
				ev.user,
				ev.id,
				ev.buysell==MarketMaker::BUY?"buy":"sell",
				ev.quantity,
				ev.price_per_share
			);
		}
	}

	std::vector<Log::Belief> *beliefs = &sim_obj.log->beliefs;
	printf("\nBeliefs\n");
	printf("%-4s %5s %5s\n","time","p","mu");
	for (unsigned int i=0;i<beliefs->size();i++) {
		printf("%4d %5.2f %5.2f\n",(*beliefs)[i].time,sim_obj.p_vec[i]*100,(*beliefs)[i].mu);
	}

	printf("\nUsers\n");
	printf("%-20s %6s %9s\n","name","shares","cash");
	std::vector<TradingPopulation::Trader_tuple> active_traders = sim_obj.trading_bots->active_traders;
	for (unsigned int i=0;i<active_traders.size();i++) {
		char name[32];
		sprintf(name,"%s%1d",active_traders[i].trader->name(),active_traders[i].user->id);
		printf("%-20s %6d %9.2f\n",name,active_traders[i].user->shares,active_traders[i].user->cash);
	}
	printf("LMSR(b=%6.2f)       %6d %9.2f\n",lmsr_b,sim_obj.market->user_account->shares,sim_obj.market->user_account->cash);

	std::vector<Simulation::Profit> profits = sim_obj.profits_by_user();
	printf("\nProfits\n");
	printf("%-20s %10s\n","trader","profit");
	for (unsigned int i=0;i<profits.size();i++) {
		printf("%-20s %10.2f\n",profits[i].trader_name,profits[i].profit_sum);
	}
	printf("LMSR(b=%6.2f)       %10.2f\n",lmsr_b,sim_obj.market->user_account->profit(sim_obj.liquidation));
}
