#include "Log.h"

void Log::event(int time,Event_type event_type,const char* user,int id,MarketMaker::Transaction buysell,int quantity,double mu,double price_per_share) {
	Event e = {time,event_type,user,id,buysell,quantity,price_per_share};
	events.push_back(e);
	if (event_type == EXECUTE && price_per_share != 0.0) {
		Execution x = {price_per_share,buysell,quantity,mu};
		execution_prices.push_back(x);
	}
}

std::vector<Log::Event> Log::filter(Event_type event_type) {
	std::vector<Event> res;
	for (unsigned int i=0;i<events.size();i++)
		if (events[i].event_type == event_type)
			res.push_back(events[i]);
	return res;
}
