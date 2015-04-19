#include <stdio.h>

#include "MyBot.h"

int main(int argc, char* argv[]) {
	srand (time(NULL));
//	BinomialDraws bd;
//	for (int i=0;i<10;i++) {
//		printf("p: %f\n",bd.p);
//		bd.do_jump();
//		printf("%d\n",bd.get_draw());
//	}
	LMSRFactory lf(1.2);
	LMSR* l = lf.make();

	printf("%s\n",lf.name);
}
