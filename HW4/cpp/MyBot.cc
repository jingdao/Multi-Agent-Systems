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
	User* u = new User(0,0);
	printf("%s\n",lf.name);
	printf("%f\n",Prices::check(MarketMaker::BUY,100,l,u));
//	printf("%f %d %f %d\n",l->mu,l->quantity_outstanding,l->user_account->cash,l->user_account->shares);
//	printf("%f\n",Prices::execute(MarketMaker::BUY,100,l,u));
//	printf("%f %d %f %d\n",l->mu,l->quantity_outstanding,l->user_account->cash,l->user_account->shares);
	printf("%f\n",Prices::check(MarketMaker::BUY,1,l,u));
	printf("%f\n",Prices::check(MarketMaker::SELL,100,l,u));
	printf("%f\n",Prices::check(MarketMaker::SELL,1,l,u));
}
