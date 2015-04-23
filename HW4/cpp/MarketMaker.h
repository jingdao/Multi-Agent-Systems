#pragma once
#include <math.h>
#include "User.h"

class MarketMaker {
	public:
		enum Transaction {
			BUY,SELL
		};
		virtual ~MarketMaker();
		static void hansonPriceCheck(Transaction transaction,int qtyToBuySell,int qtyOutstanding, double maxLoss, double* costToUser, int* newq1, double* currentPrice);
		static double prediction_limit(double val);
		virtual double execute(Transaction buysell,int quantity,User* user,bool cancel=false) = 0;
		virtual double price_check(Transaction buysell,int quantity) = 0;

	protected:
		double price_per_share(double quantity,double total_cost);
};
