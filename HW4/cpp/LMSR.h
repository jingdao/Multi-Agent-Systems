#pragma once
#include "MarketMaker.h"
#include <vector>

class LMSR : public MarketMaker {
	public:
		LMSR(double max_loss, int quantity_outstanding=0,double mu=50.0,User* user_account=nullptr);
		double execute(Transaction buysell,int quantity,User* user,bool cancel=false);
		double price_check(Transaction buysell,int quantity);
		User* user_account;
		std::vector<User*> cancels;
	
//	private:
		double max_loss, mu;
		int quantity_outstanding;
		void get_update(Transaction buysell,int quantity,double* offered_price,int* new_quantity_outstanding,double* new_mu);
};
