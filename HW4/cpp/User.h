#pragma once

class User {
	public:
		User(double cash,int initial_shares,const char* name=nullptr);
		void change_cash(double amount);
		void change_portfolio(int amount);
		double profit(double stock_values);
		double cash, initial_cash;
		int shares, initial_shares;
		const char* name;

};

