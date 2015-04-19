#pragma once

class User {
	public:
		User(double cash,int initial_shares,char* name=nullptr);
		void change_cash(double amount);
		void change_portfolio(double amount);
		double profit(double stock_values);
	
	private:
		double cash, initial_cash;
		int shares, initial_shares;
		char* name;

};

