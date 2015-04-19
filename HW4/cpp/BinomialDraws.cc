#include "BinomialDraws.h"

double BinomialDraws::jump_sigma = 0.2;
bool BinomialDraws::truncate_after = false;

BinomialDraws::BinomialDraws(double initial_p) {
	if (initial_p>=0.0&&initial_p<=1.0) {
		p=initial_p;
	} else {
		p = (double)rand() / (double)RAND_MAX;
	}
}

//standard Box-Mueller transform
double BinomialDraws::normalvariate(double mu, double sigma) {
	const double epsilon = DBL_MIN;
	const double two_pi = 2.0*M_PI;
	static double z0, z1;
	static bool generate;
	generate = !generate;
				 
	if (!generate)
		return z1 * sigma + mu;

	double u1, u2;
	do
	{
		u1 = (double)rand() / (double)RAND_MAX;
		u2 = (double)rand() / (double)RAND_MAX;
	}
	while ( u1 <= epsilon );

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}

void BinomialDraws::do_jump() {
	bool have_good_p = false;
	double delta_p,new_p;
	while (!have_good_p) {
		delta_p = normalvariate(0.0,jump_sigma);
		new_p = delta_p + p;
		if (truncate_after) {
			new_p = new_p>=0.0 ? new_p : 0.0;
			new_p = new_p<=0.0 ? new_p : 1.0;
			have_good_p = true;
		} else {
			have_good_p = (new_p<=1.0 && new_p>=0.0);
		}
	}
	p=new_p;
}

int BinomialDraws::get_draw() {
	double r = (double)rand() / (double)RAND_MAX;
	if ( r < p) {
		return 1;
	} else {
		return 0;
	}
}
