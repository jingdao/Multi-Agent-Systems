#pragma once
#include <stdio.h>
#include "Simulation.h"

class RunExperiments {
	public:
		struct Profit {
			const char* trader_name;
			double min;
			double max;
			double mean;
			double std_dev;
		};
		static void run(std::vector<Trader*> *trader_list,int timesteps=100,int simulations=2000,double lmsr_b=150.0);
};
