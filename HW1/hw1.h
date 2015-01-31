
class AuctionSolver {
	public:
		int numAgents;
	private:
		int* values;
		float epsilon;
	public:
		AuctionSolver(int numAgents,int* values);
		int getAssignment(int* assigment);
		int LPSolve(int* assignment);
}; 
