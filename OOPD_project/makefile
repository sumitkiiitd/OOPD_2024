CXX = g++
CXXFLAGS_DEBUG = -g -Wall
CXXFLAGS_OPT = -O2 -Wall

SRC1 = wifi4.cpp #change the csource file

BIN_DEBUG1 = Wifi_debug
BIN_OPT1 = Wifi_opt
all: $(BIN_DEBUG1) $(BIN_OPT1) $(BIN_DEBUG2) $(BIN_OPT2) $(BIN_DEBUG3) $(BIN_OPT3)

$(BIN_DEBUG1): $(SRC1)
	$(CXX) $(CXXFLAGS_DEBUG) $(SRC1) -o $(BIN_DEBUG1)
$(BIN_OPT1): $(SRC1)
	$(CXX) $(CXXFLAGS_OPT) $(SRC1) -o $(BIN_OPT1)

clean:
	rm -f $(BIN_DEBUG1) $(BIN_OPT1) $(BIN_DEBUG2) $(BIN_OPT2) $(BIN_DEBUG3) $(BIN_OPT3)

