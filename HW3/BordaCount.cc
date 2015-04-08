#include <stdio.h>
#include <stdlib.h>
#include <vector>

class BordaCount {
	public:
		int numCandidates;
		std::vector< std::vector<int> > votes;
		int* numPoints;
		int* counts;
		BordaCount(char* file);
		~BordaCount();
		void runBordaCount();
		void runInstantRunoff();
		void showPoints();
		int getWinner();
};

BordaCount::BordaCount(char* file) {
	FILE* f = fopen(file,"r");
	if (!f)
		return;
	char buf[256];
	fgets(buf,255,f);
	numCandidates=strtol(buf,NULL,10);
	numPoints=new int[numCandidates]();
	counts=new int[numCandidates]();
	if (!numPoints||!counts)
		return;
	printf("Reading file %s (%d candidates)\n",file,numCandidates);
	int numVoters=0;
	int numVotes=0;
	while (fgets(buf,255,f)) {
		numVoters++;
		std::vector<int> currentVotes;
		char* ptr=buf+2;
		int numPreferences = strtol(ptr,&ptr,10);
		for (int i=0;i<numPreferences;i++) {
			int index = strtol(ptr,&ptr,10);
			currentVotes.push_back(index);
		}
		numVotes+=currentVotes.size();
		votes.push_back(currentVotes);
	}
	printf("#Voters=%d #Votes=%d\n",numVoters,numVotes);
	fclose(f);
}

BordaCount::~BordaCount() {
	delete[] numPoints;
	delete[] counts;
}

void BordaCount::runBordaCount() {
	for (int i=0;i<votes.size();i++) {
		int rank=numCandidates-1;
		for (int j=0;j<votes[i].size();j++) {
			numPoints[votes[i][j]]+=rank;
			counts[votes[i][j]]++;
			rank--;
		}
	}
}

void BordaCount::runInstantRunoff() {
	delete[] counts;
	counts=new int[numCandidates]();
	bool* isEliminated = new bool[numCandidates]();
	int round=1;
	int numVoters=votes.size();
	int* topChoices = new int[numVoters]();
	//initial count
	for (int i=0;i<votes.size();i++) {
		counts[votes[i][0]]++;
	}
	//find min max
	int min=counts[0],minIndex=0,max=counts[0],maxIndex=0;
	for (int i=1;i<numCandidates;i++) {
		if (counts[i]<min) {min=counts[i];minIndex=i;}
		if (counts[i]>max) {max=counts[i];maxIndex=i;}
	}
	while (1) {
		printf("Round %d: ",round);
		round++;
		if (max>numVoters/2) {
			printf("Candidate %d wins by majority (%d votes)\n",maxIndex,max);
			break;
		} else {
			printf("Candidate %d is eliminated (%d votes)\n",minIndex,min);
		}
		//redistribute votes
		isEliminated[minIndex]=true;
//		counts[minIndex]=-1;
		for (int i=0;i<votes.size();i++) {
			if (topChoices[i]<votes[i].size()&&votes[i][topChoices[i]]==minIndex) {
				while (topChoices[i]<votes[i].size()&&isEliminated[votes[i][topChoices[i]]]) {
					topChoices[i]++;
				}
				if (topChoices[i]==votes[i].size())
					numVoters--;
				else
					counts[votes[i][topChoices[i]]]++;
			}
		}
		min=max; minIndex=maxIndex;
		for (int i=0;i<numCandidates;i++) {
			if (!isEliminated[i]&&counts[i]<min) {min=counts[i];minIndex=i;}
			if (counts[i]>max) {max=counts[i];maxIndex=i;}
		}
	}
	delete[] topChoices;
	delete[] isEliminated;
}

void BordaCount::showPoints() {
	for (int i=0;i<numCandidates;i++) {
		printf("Candidate %2d: %6d points (%4d votes)\n",i,numPoints[i],counts[i]);
	}
}

int BordaCount::getWinner() {
	int highScore=numPoints[0];
	int winner=0;
	for (int i=1;i<numCandidates;i++) {
		if (numPoints[i]>highScore) {
			highScore=numPoints[i];
			winner=i;
		}
	}
	printf("Winner is Candidate %d\n",winner);
}

int main(int argc,char* argv[]) {
	if (argc<2)
		return 1;
	BordaCount bc(argv[1]);
	if (!bc.numPoints)
		return 1;
	printf("Borda count result:\n");
	bc.runBordaCount();
	bc.showPoints();
	bc.getWinner();
	printf("Instant runoff result:\n");
	bc.runInstantRunoff();
}
