#include "MarketMaker.h"

//inputs: transaction,qtyToBuySell,qtyOutstanding,maxLoss
//outputs: costToUser,newq1,currentPrice
void MarketMaker::hansonPriceCheck(Transaction transaction,int qtyToBuySell,int qtyOutstanding, double maxLoss, double* costToUser, int* newq1, double* currentPrice){
    *newq1 = qtyOutstanding;
	int q2 = 0, newq2 = 0;
    if (transaction == BUY)
        *newq1 += qtyToBuySell;
    else if (transaction == SELL)
        *newq1 -= qtyToBuySell;
    //Cost function evaluated at current quantities outstanding
    double cost_init = maxLoss * log(exp(qtyOutstanding/maxLoss) + exp(q2/maxLoss));
    //Cost function evaluated at new quantities outstanding
    double cost_final = maxLoss * log(exp(*newq1/maxLoss) + exp(newq2/maxLoss));
    *costToUser = (cost_final - cost_init) * 100;
    *currentPrice = (exp(*newq1/maxLoss)/(exp(*newq1/maxLoss)+exp(newq2/maxLoss))) * 100;
}

double MarketMaker::prediction_limit(double val) {
	if (val>100.0)
		return 100.0;
	if (val<0.0)
		return 0.0;
	return val;
}

double MarketMaker::price_per_share(double quantity,double total_cost) {
	return prediction_limit(total_cost/quantity);
}
