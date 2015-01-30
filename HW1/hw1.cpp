#include <iostream>
#include <cstdlib>
#include <glpk.h>
#include "hw1.h"
#include "Profiler.h"

AuctionSolver::AuctionSolver(int numAgents) {
	this->numAgents=numAgents;
}

void AuctionSolver::setValues(int* values) {
	this->values=values;
}

int AuctionSolver::getAssignment(int* assignment) {
	assignment[0]=0;
	assignment[1]=1;
	assignment[2]=2;
	int totalValue=0;
	for (int i=0;i<numAgents;i++) {
		totalValue+=values[i*numAgents+assignment[i]];
	}
	return totalValue;
}

int AuctionSolver::LPSolve(int* assignment) {
	glp_prob *lp;
	int ia[1+1000], ja[1+1000];
	double ar[1+1000], z, x1, x2;
	/* create problem */
	lp = glp_create_prob();
	glp_set_prob_name(lp, "short");
	glp_set_obj_dir(lp, GLP_MAX);
	/* fill problem */
	glp_add_rows(lp, 2);
	glp_set_row_name(lp, 1, "p");
	glp_set_row_bnds(lp, 1, GLP_UP, 0.0, 1.0);
	glp_set_row_name(lp, 2, "q");
	glp_set_row_bnds(lp, 2, GLP_UP, 0.0, 2.0);
	glp_add_cols(lp, 2);
	glp_set_col_name(lp, 1, "x1");
	glp_set_col_bnds(lp, 1, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 1, 0.6);
	glp_set_col_name(lp, 2, "x2");
	glp_set_col_bnds(lp, 2, GLP_LO, 0.0, 0.0);
	glp_set_obj_coef(lp, 2, 0.5);
	ia[1] = 1, ja[1] = 1, ar[1] = 1.0; /* a[1,1] = 1 */
	ia[2] = 1, ja[2] = 2, ar[2] = 2.0; /* a[1,2] = 2 */
	ia[3] = 2, ja[3] = 1, ar[3] = 3.0; /* a[2,1] = 3 */
	ia[4] = 2, ja[4] = 2, ar[4] = 1.0; /* a[2,2] = 1 */
	glp_load_matrix(lp, 4, ia, ja, ar);
	/* solve problem */
	glp_simplex(lp, NULL);
	/* recover and display results */
	z = glp_get_obj_val(lp);
	x1 = glp_get_col_prim(lp, 1);
	x2 = glp_get_col_prim(lp, 2);
	printf("z = %g; x1 = %g; x2 = %g\n", z, x1, x2);
	/* housekeeping */
	glp_delete_prob(lp);
}

int main(int argc, char** argv) {
	glp_term_out(GLP_MSG_OFF);
	Timer* tm = TimerStart();
	AuctionSolver* as = new AuctionSolver(3);
	int values[]  = {2,4,0,1,5,0,1,3,2};
	as->setValues(values);
	int assignment[3];
	int res = as->getAssignment(assignment);
	double duration1 = TimerLap(tm);
	as->LPSolve(assignment);
	double duration2 = TimerEnd(tm);
	delete as;
	glp_free_env();
	std::cout<<"Value: "<<res<<"\nAssignment: "<<assignment[0]<<" "<<assignment[1]<<" "<<assignment[2]<<"\n";
	std::cout<<"Time: "<<duration1<<" vs "<<duration2<<"\n";
	std::cout<<"Hello World\n";
}
