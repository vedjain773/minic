LLVM_CONFIG = /home/ved/Documents/minic/llvm-18/bin/llvm-config

CXX = g++
CXXFLAGS = -std=c++17 -Wall -Iinclude `$(LLVM_CONFIG) --cxxflags`
LDFLAGS = `$(LLVM_CONFIG) --ldflags`
LDLIBS = `$(LLVM_CONFIG) --libs core` `$(LLVM_CONFIG) --system-libs`

SRC = src/*.cpp
OUT = out/main

all:
	@echo "Building..."
	@$(CXX) $(SRC) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) -o $(OUT)

clean:
	rm -f $(OUT)
