#pragma once
#include <vector>

class Log {
	public:
		enum Event_type {
			CHECK,EXECUTE
		};
		enum Buysell {
			BUY,SELL
		};
		struct Event {
			int time;
			Event_type event_type;
			char* user;
			Buysell buysell;
			int quantity;
			double price_per_share;
		};
		struct Execution {
			double price_per_share;
			Buysell buysell;
			int quantity;
			double mu;	 
		};
		struct Belief {
			int time;
			double mu;
		};
		void event(int time,Event_type event_type,char* user,Buysell buysell,int quantity,double mu,double price_per_share);
		std::vector<Event> filter(Event_type event_type);

		std::vector<Event> events;
		std::vector<Execution> execution_prices;
		std::vector<Belief> beliefs;
};

