CXX = g++
CPPFLAGS = -Wall -g 
BIN_DIR = bin
GTEST_LL = -I /usr/local/opt/gtest/include/ -l gtest -l gtest_main -pthread

$(BIN_DIR)/.dirstamp:
	mkdir -p $(BIN_DIR)
	touch $(BIN_DIR)/.dirstamp

.PHONY: clean tests

clean:
	rm -rf $(BIN_DIR)



split_test: $(BIN_DIR)/splittest
	-@$(BIN_DIR)/splittest
$(BIN_DIR)/splittest: gtest_llistint_rec.cpp split.cpp $(BIN_DIR)/.dirstamp
	$(CXX) $(CPPFLAGS) $< $(GTEST_LL) -o $@