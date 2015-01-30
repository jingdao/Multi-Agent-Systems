
class AuctionSolver {
	private:
		int numAgents;
		int* values;
	public:
		AuctionSolver(int numAgents);
		void setValues(int* values);
		int getAssignment(int* assigment);
		int LPSolve(int* assignment);
}; 
