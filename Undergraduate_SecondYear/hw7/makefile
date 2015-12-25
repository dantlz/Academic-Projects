CXX = g++
CPPFLAGS = -Wall -g 
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/graphColoring

rbbst_test: rbbst_test.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $< -o $(BIN_DIR)/rbbst_test

$(BIN_DIR)/graphColoring: graphColoring.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $< -o $@ 

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

clean:
	rm -rf $(BIN_DIR)