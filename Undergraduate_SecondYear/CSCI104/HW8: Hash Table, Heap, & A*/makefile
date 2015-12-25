CXX = g++
CPPFLAGS = -Wall -g 
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: doublet hashtable_test minheap_test

doublet: doublet.cpp $(BIN_DIR)/minheap.o $(BIN_DIR)/hashtable.o
	$(CXX) $(CPPFLAGS) $^ -o $(BIN_DIR)/doublet

hashtable_test: hashtable_test.cpp $(BIN_DIR)/hashtable.o
	$(CXX) $(CPPFLAGS) $^ -o $(BIN_DIR)/hashtable_test

$(BIN_DIR)/hashtable.o: hashtable.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@

minheap_test: minheap_test.cpp $(BIN_DIR)/minheap.o $(BIN_DIR)/hashtable.o
	$(CXX) $(CPPFLAGS) $^ -o $(BIN_DIR)/minheap_test

$(BIN_DIR)/minheap.o: minheap.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@



$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

clean:
	rm -rf $(BIN_DIR)