#pragma once
#include <vector>
#include "MarketMaker.h"

class Log {
	public:
		enum Event_type {
			CHECK,EXECUTE
		};
		struct Event {
			int time;
			Event_type event_type;
			const char* user;
			int id;
			MarketMaker::Transaction buysell;
			int quantity;
			double price_per_share;
		};
		struct Execution {
			double price_per_share;
			MarketMaker::Transaction buysell;
			int quantity;
			double mu;	 
		};
		struct Belief {
			int time;
			double mu;
		};
		void event(int time,Event_type event_type,const char* user,int id,MarketMaker::Transaction buysell,int quantity,double mu,double price_per_share);
		std::vector<Event> filter(Event_type event_type);

		std::vector<Event> events;
		std::vector<Execution> execution_prices;
		std::vector<Belief> beliefs;
};

