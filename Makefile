.PHONY: all
all: format test build

.PHONY: format
format:
	clang-format src/* include/* -i

.PHONY: build
build:
	mkdir -p build
	cd build && \
	cmake .. && \
	make

.PHONY: debug
debug:
	mkdir -p build
	cd build && \
	cmake -DCMAKE_BUILD_TYPE=debug .. && \
	make

.PHONY: clean
clean:
	rm -rf build

.PHONY: testsys
testsys:
	cd src && \
	g++ -std=c++17 format.cpp linux_parser.cpp process.cpp processor.cpp system.cpp && \
	./a.out

.PHONY: testparser
testparser:
	cd src && \
	g++ -std=c++17 linux_parser.cpp && \
	./a.out

.PHONY: testprocess
testprocess:
	cd src && \
	g++ -std=c++17 linux_parser.cpp process.cpp && \
	./a.out

