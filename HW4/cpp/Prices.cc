#include "Prices.h"

double Prices::check(MarketMaker::Transaction buysell,int quantity,LMSR* stock_maker,User* user) {
	return stock_maker->price_check(buysell,quantity);
}

double Prices::execute(MarketMaker::Transaction buysell,int quantity,LMSR* stock_maker,User* user) {
	double costPerShare = stock_maker->price_check(buysell,quantity);
	double offeredPrices = costPerShare * quantity;

	if (!(0.01<costPerShare) && buysell==MarketMaker::SELL) {
		Prices::cancel(buysell,quantity,stock_maker,user);
		return 0.0;
	} else if (!(costPerShare<100) && buysell==MarketMaker::BUY) {
		Prices::cancel(buysell,quantity,stock_maker,user);
		return 0.0;
	}

//	double user_power = user->cash;
//	int current_position = user->shares;
//	int trade_position;
//
//	if (buysell==MarketMaker::BUY)
//		trade_position = quantity;
//	if (buysell==MarketMaker::SELL)
//		trade_position = -1 * quantity;

	bool allow_trade = true;

	if (!allow_trade)
		return 0.0;

	double executed_price = stock_maker->execute(buysell,quantity,user);
	//Preliminary processing
	if (buysell==MarketMaker::SELL) {
		offeredPrices = offeredPrices * -1;
		quantity = quantity * -1;
	}

	User* maker_account = stock_maker->user_account;
	//Change cash values
	user->change_cash(-1*offeredPrices);
	maker_account->change_cash(offeredPrices);

	//Change holdings
	user->change_portfolio(quantity);
	maker_account->change_portfolio(-1*quantity);
	return executed_price;
}

double Prices::cancel(MarketMaker::Transaction buysell,int quantity,LMSR* stock_maker, User* user) {
	stock_maker->cancels.push_back(user);
	return stock_maker->execute(buysell,quantity,user,true);
}
