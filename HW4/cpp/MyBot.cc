#include <stdio.h>

#include "MyBot.h"

int main(int argc, char* argv[]) {
	srand (time(NULL));
	BinomialDraws bd;
//	for (int i=0;i<10;i++) {
//		printf("p: %f\n",bd.p);
//		bd.do_jump();
//		printf("%d\n",bd.get_draw());
//	}
	LMSRFactory lf(1.2);
	LMSR* l = lf.make();
	User* u = new User(50,100);
	printf("%s\n",lf.name);
	printf("%f\n",Prices::check(MarketMaker::BUY,100,l,u));
//	printf("%f %d %f %d\n",l->mu,l->quantity_outstanding,l->user_account->cash,l->user_account->shares);
//	printf("%f\n",Prices::execute(MarketMaker::BUY,100,l,u));
//	printf("%f %d %f %d\n",l->mu,l->quantity_outstanding,l->user_account->cash,l->user_account->shares);
	printf("%f\n",Prices::check(MarketMaker::BUY,1,l,u));
	printf("%f\n",Prices::check(MarketMaker::SELL,100,l,u));
	printf("%f\n",Prices::check(MarketMaker::SELL,1,l,u));

	std::vector<Trader*> bots = TradingPopulation::get_bots(5,2);
	std::vector<Log::Execution> x;
	TradingPopulation tp(10,nullptr,0.2,bots,u);
//	tp.new_information(&bd,&x,0);
	std::vector<TradingPopulation::Trader_tuple> t = tp.active_traders;
	for (unsigned int i=0;i<t.size();i++) {
		printf("%s %d %f\n",t[i].user->name,t[i].user->shares,t[i].user->cash);
	}
}
