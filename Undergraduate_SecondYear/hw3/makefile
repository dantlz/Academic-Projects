CXX = g++
CPPFLAGS = -Wall -g 
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

all: $(BIN_DIR)/hw3_All

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

clean:
	rm -rf $(BIN_DIR)




alist_test: $(BIN_DIR)/alisttest
	-@$(BIN_DIR)/alisttest

$(BIN_DIR)/alisttest: alisttest.cpp $(BIN_DIR)/alistint.o 
	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@

$(BIN_DIR)/alistint.o: alistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@







gtest_alistint: $(BIN_DIR)/gtest_alistint
	-@$(BIN_DIR)/gtest_alistint

$(BIN_DIR)/gtest_alistint: gtest_alistint.cpp $(BIN_DIR)/alistint.o 
	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@



stackint_test: $(BIN_DIR)/stackinttest
	-@$(BIN_DIR)/stackinttest

$(BIN_DIR)/stackinttest: stackinttest.cpp alistint.cpp $(BIN_DIR)/stackint.o 
	$(CXX) $(CPPFLAGS) $^ $(GTEST_LL) -o $@	

$(BIN_DIR)/stackint.o: stackint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) -c $< -o $@




boolexpr_test: $(BIN_DIR)/boolexpr
	-@$(BIN_DIR)/boolexpr   boolexpr1.in   boolexpr1.vars 

$(BIN_DIR)/boolexpr: boolexpr.cpp stackint.cpp alistint.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) boolexpr.cpp stackint.cpp alistint.cpp -o $@