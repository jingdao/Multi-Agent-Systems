#include "User.h"

User::User(double cash,int initial_shares,int id) {
	this->cash = cash;
	this->initial_cash = this->cash;
	this->shares = initial_shares;
	this->initial_shares = this->shares;
	this->id = id;
}

void User::change_cash(double amount) {
	cash+=amount;
}

void User::change_portfolio(int amount) {
	shares += amount;
}

double User::profit(double stock_values) {
	double profit=0.0;
	profit += stock_values * (shares-initial_shares);
	profit += cash - initial_cash;
	return profit;
}



