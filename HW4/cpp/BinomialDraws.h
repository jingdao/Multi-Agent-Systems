#pragma once
#include <math.h>
#include <float.h>
#include <stdlib.h>

class BinomialDraws {
	public:
		static double jump_sigma;
		static bool truncate_after; 
		BinomialDraws(double initial_p=-1);
		void do_jump();
		int get_draw();

//	private:
		double p;
		double normalvariate(double mu,double sigma);

};

