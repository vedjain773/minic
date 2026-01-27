CC = g++

PROJECT = main

.PHONY: build
build:
	rm -rf ./output/*
	@echo "Building..."
	@$(CC) ./src/*.cpp -I./include -o ./out/$(PROJECT)

.PHONY: clean
clean:
	@echo "Cleaning..."
	@rm -rf ./out/$(PROJECT)
