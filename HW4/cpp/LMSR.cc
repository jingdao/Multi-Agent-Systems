#include "LMSR.h"

LMSR::LMSR(double max_loss, int quantity_outstanding,double mu,User* user_account) {
	this->max_loss=max_loss;
	this->mu=mu;
	this->quantity_outstanding=quantity_outstanding;
	if (user_account)
		this->user_account=user_account;
	else
		this->user_account=new User(0,0);
}

LMSR::~LMSR() {
	delete user_account;
}

double LMSR::execute(Transaction buysell,int quantity,User* user,bool cancel) {
	if (cancel)
		return 0;
	double offered_price;
	get_update(buysell,quantity,&offered_price,&quantity_outstanding,&mu);
	return offered_price;
}

double LMSR::price_check(Transaction buysell,int quantity) {
	double offered_price,new_mu;
	int new_quantity_outstanding;
	get_update(buysell,quantity,&offered_price,&new_quantity_outstanding,&new_mu);
	return offered_price;
}

//inputs: buysell,quantity
//outputs: offered_price,new_quantity_outstanding,new_mu
void LMSR::get_update(Transaction buysell,int quantity,double* offered_price,int* new_quantity_outstanding,double* new_mu) {
	MarketMaker::hansonPriceCheck(buysell,quantity,quantity_outstanding,max_loss,offered_price,new_quantity_outstanding,new_mu);
	*offered_price = price_per_share(quantity,*offered_price);
}
