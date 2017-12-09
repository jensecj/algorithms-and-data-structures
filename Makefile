MAKEFLAGS += --no-print-directory

default: release

release:
	mkdir -p build && cd build && cmake ../ -DCMAKE_BUILD_TYPE=Release && cmake --build .

debug:
	mkdir -p build && cd build && cmake ../ -DCMAKE_BUILD_TYPE=Debug && cmake --build .

test:
	@if [ -f ./build/unit-tests ]; then ./build/unit-tests --gtest_color=yes; else echo "Run 'make release' or 'make debug' first" && exit 1; fi

bench:
	@if [ -f ./build/bench-tests ]; then ./build/bench-tests ${ARGS}; else echo "Run 'make release' or 'make debug' first" && exit 1; fi

tidy:
	@if [ -d ./build/ ]; then ./scripts/clang-tidy.sh ${ARGS}; else echo "Run 'make release' or 'make debug' first" && exit 1; fi

asan:
	echo "address sanitizer"

msan:
	echo "memory sanitizer"

clean:
	@if [ -d ./build/ ]; then rm -r build; else echo "Build is already clean"; fi

.PHONY: test bench
