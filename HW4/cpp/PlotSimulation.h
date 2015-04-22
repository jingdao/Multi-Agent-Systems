#pragma once
#include <stdio.h>
#include "Simulation.h"

class PlotSimulation {
	public:
		static void run(std::vector<Trader*> *traders,int timesteps=100,double lmsr_b=150);
};

