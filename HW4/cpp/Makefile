CXX       = g++
CXXFLAGS  = -O2 -std=c++11
INCLUDE_DIRS =
LIB_DIRS =
LDFLAGS = -lm
debug: CXXFLAGS = -ggdb3 -O0 -Wall -std=c++11
SRC  =  BinomialDraws.cc MarketMaker.cc User.cc LMSR.cc LMSRFactory.cc Prices.cc Trader.cc MovingAverageBot.cc ShortLongTechnical.cc RangeTechnical.cc TradingPopulation.cc Log.cc Simulation.cc PlotSimulation.cc RunExperiments.cc MyBot.cc
EXE = MyBot
OBJ = $(patsubst %.cc,%.o,$(SRC))

$(EXE): $(OBJ)
	$(CXX) $(LIB_DIRS) -o $(EXE) $(OBJ) $(LDFLAGS)

all: $(EXE)

debug: all

clean:
	rm -f $(EXE) $(OBJ) .depend

.PHONY: clean

.cc.o:
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c $<

.depend:
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -MM *.cc > .depend

-include .depend
