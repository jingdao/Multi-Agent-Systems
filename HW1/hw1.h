class AuctionSolver {
	public:
		int numAgents;
	private:
		int* values;
		float epsilon;
	public:
		AuctionSolver(int numAgents,int* values);
		int getAssignment(int* assignment);
		int LPSolve(int* assignment);
}; 
class GaleShapleySolver {
	public:
		int numAgents;
	private:
		int* mPreferences;
		int* wPreferences;
	public:
		GaleShapleySolver(int numAgents,int* mPreferences,int* wPreferences);
		void getAssignment(int* assignment);
		void LPSolve(int* assignment);
}; 
