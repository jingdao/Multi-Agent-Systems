#include <iostream>
#include <cstdlib>
#include <glpk.h>
#include "hw1.h"
#include "Profiler.h"

AuctionSolver::AuctionSolver(int numAgents,int* values) {
	this->numAgents=numAgents;
	this->epsilon=1.0f/(numAgents+1);
	this->values=values;
}

int AuctionSolver::getAssignment(int* assignment) {
	if (numAgents==1) {
		assignment[0]=1;
		return values[0];
	}
	float prices[numAgents];
	int feasible=0, currentAgent=0;
	int owners[numAgents];
	for (int i=0;i<numAgents;i++) {
		assignment[i]=-1;
		owners[i]=-1;
		prices[i]=0;
	}
	while (feasible<numAgents) {
		while (assignment[currentAgent]!=-1) {
			currentAgent++;
			currentAgent%=numAgents;
		}
		int favorite;
		float bestValue,secondBestValue,p0,p1;
		p0=values[currentAgent*numAgents]-prices[0];
		p1=values[currentAgent*numAgents+1]-prices[1];
		if (p0>=p1) {
			favorite=0;
			bestValue=p0;
			secondBestValue=p1;
		} else {
			favorite=1;
			bestValue=p1;
			secondBestValue=p0;
		}
		for (int i=2;i<numAgents;i++) {
			p0=values[currentAgent*numAgents+i]-prices[i];
			if (p0>=bestValue) {
				secondBestValue=bestValue;
				favorite=i;
				bestValue=p0;
			} else if (p0>=secondBestValue) {
				secondBestValue=p0;
			}
		}
		float bid = bestValue-secondBestValue+epsilon;
		prices[favorite]+=bid;
		if (owners[favorite]==-1) {
			assignment[currentAgent]=favorite;
			owners[favorite]=currentAgent;
			feasible++;
		} else {
			assignment[owners[favorite]]=-1;
			assignment[currentAgent]=favorite;
			owners[favorite]=currentAgent;
		}
//		for (int i=0;i<numAgents;i++) {
//			printf("%f\n",prices[i]);
//		}
	}
	int totalValue=0;
	for (int i=0;i<numAgents;i++) {
		totalValue+=values[i*numAgents+assignment[i]];
	}
	return totalValue;
}

int AuctionSolver::LPSolve(int* assignment) {
	glp_prob *lp= glp_create_prob();
	glp_set_obj_dir(lp, GLP_MAX);
	int numRows=2*numAgents,numColumns=numAgents*numAgents;
	//objective function
	glp_add_cols(lp,numColumns);
	for (int i=1;i<=numColumns;i++) {
		glp_set_col_bnds(lp, i, GLP_LO, 0.0, 0.0);
		glp_set_obj_coef(lp,i,values[i-1]);
	}
	//constraints
	glp_add_rows(lp,numRows);
	for (int i=1;i<=numRows;i++) {
		glp_set_row_bnds(lp, i, GLP_UP, 0.0, 1.0);
	}
	//fill coefficient matrix
	int ne=numRows*numAgents;
	int ia[ne+1],ja[ne+1];
	double ar[ne+1];
	int p=1;
	for (int i=0;i<numAgents;i++) {
		for (int j=0;j<numAgents;j++) {
			ia[p]=i+1;
			ja[p]=j+i*numAgents+1;
			ar[p]=1;
			p++;
			ia[p]=i+numAgents+1;
			ja[p]=i+j*numAgents+1;
			ar[p]=1;
			p++;
		}
	}
//	for (int i=0;i<p;i++) {
//		printf("%d %d %f\n",ia[i],ja[i],ar[i]);
//	}
	glp_load_matrix(lp,ne,ia,ja,ar);
	//solve problem
	glp_smcp parm;
	glp_init_smcp(&parm);
	parm.meth=GLP_PRIMAL;
	glp_simplex(lp,&parm);
//	glp_iptcp parm;
//	glp_init_iptcp(&parm);
//	glp_interior(lp,&parm);
//	for (int i=1;i<=numColumns;i++) {
//		printf("%f\n",glp_get_col_prim(lp,i));
//	}
	for (int i=0;i<numAgents;i++) {
		for (int j=0;j<numAgents;j++) {
			if (glp_get_col_prim(lp,i*numAgents+j+1)>0) {
				assignment[i]=j;
				break;
			}
		}
	}
	double totalValue = glp_get_obj_val(lp);
	glp_delete_prob(lp);
	return (int)totalValue;
}

	GaleShapleySolver::GaleShapleySolver(int numAgents,int* mPreferences,int* wPreferences) {
		this->numAgents=numAgents;
		this->mPreferences=mPreferences;
		this->wPreferences=wPreferences;
	}

	void genRandom(int* values,int n,int M) {
		if (M>RAND_MAX) {
			for (int i=0;i<n*n;i++) {
				values[i]=(int)(1.0/RAND_MAX*rand()/M);
//				printf("%d\n",values[i]);
			}
		} else {
			for (int i=0;i<n*n;i++) {
				values[i]=rand()%M;
//				printf("%d\n",values[i]);
			}
		}
	}

	void plotAverageAssignment() {
		int M=100;
		int values[256*256];
		int assignment[256];
		int auctionResult,lpResult,auctionSum,lpSum;
		for (int n=2;n<=256;n<<=1) {
			auctionSum=0;
			lpSum=0;
			for (int i=0;i<1000;i++) {
				genRandom(values,n,M);
				AuctionSolver* as = new AuctionSolver(n,values);
				auctionResult=as->getAssignment(assignment);
//				lpResult=as->LPSolve(assignment);
//				if (auctionResult!=lpResult) printf("Fail: %d %d %d\n",n,auctionResult,lpResult);
				auctionSum+=auctionResult;
//				lpSum+=lpResult;
				delete as;
			}
//			printf("%d %f %f\n",n,1.0*auctionSum/n/1000,1.0*lpSum/n/1000);
			printf("%d,%f\n",n,1.0*auctionSum/n/1000);
		}
	}

	void plotTiming() {
		int n=10;
		int values[n*n];
		int assignment[n];
		double auctionTime, lpTime;
		Timer* tm = TimerStart();
		for (int M=10;M<=10000000;M*=10) {
			for (int i=0;i<100;i++) {
				genRandom(values,n,M);
				AuctionSolver* as = new AuctionSolver(n,values);
				as->getAssignment(assignment);
				delete as;
			}
			auctionTime=TimerLap(tm);
//			for (int i=0;i<100;i++) {
//				genRandom(values,n,M);
//				AuctionSolver* as = new AuctionSolver(n,values);
//				as->LPSolve(assignment);
//				delete as;
//			}
//			lpTime=TimerLap(tm);
			printf("%8d,%f,%f\n",M,1.0*auctionTime/100,1.0*lpTime/100);
		}
		TimerEnd(tm);
	}

	void testAlgorithm() {
		Timer* tm = TimerStart();
		int values2[]  = {2,4,0,1,5,0,1,3,2};
		int values[]  = {19,88,91,29,63,33,30, 5, 6,31,
						  7,29,35,71,93,85,95,76,22, 2,
						 48,64,70,50,88,22,61,20,34,51,
						 80,70,48,34,16,88,47,45,82,82,
						 80,97,25,17,17,49,19,56,44,95,
						  1,46,19,24,35,62,80,72, 0,35,
						 63,17,18,51,62,19,86,50,94,92,
						 23,86,20,96,17,20,30,37,55,15,
						 39,91,12,24,15,19,91, 0,29,37,
						 95,87,36,25,81,19,27,16,29,97};
		AuctionSolver* as = new AuctionSolver(3,values2);
		int assignment[as->numAgents];
		int res = as->getAssignment(assignment);
		double duration1 = TimerLap(tm);
		printf("Value: %d Assignment: ",res);
		for (int i=0;i<as->numAgents;i++) {
			printf("%d ",assignment[i]);
		}
		printf("\n");
		delete as;
		as = new AuctionSolver(10,values);
		int assignment2[as->numAgents];
		int res2 = as->LPSolve(assignment2);
		double duration2 = TimerEnd(tm);
		printf("Value: %d Assignment: ",res2);
		for (int i=0;i<as->numAgents;i++) {
			printf("%d ",assignment2[i]);
		}
		printf("\n");
		std::cout<<"Time: "<<duration1<<" vs "<<duration2<<"\n";
		delete as;
	}

int main(int argc, char** argv) {
	srand(0);
	glp_term_out(GLP_MSG_OFF);
	plotTiming();
//	plotAverageAssignment();
//	testAlgorithm();
	glp_free_env();
}
