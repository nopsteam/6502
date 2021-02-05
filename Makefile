.PHONY: build
debug:
	cmake -DCMAKE_BUILD_TYPE=Debug -B build/debug
	make --no-print-directory -C build/debug

.PHONY: build
release:
	cmake -DCMAKE_BUILD_TYPE=Release -B build/release
	make --no-print-directory -C build/release

test: export CTEST_OUTPUT_ON_FAILURE = 1

.PHONY: test
test:
	cmake -B build/debug
	make --no-print-directory -C build/debug
	make --no-print-directory -C build/debug test

.PHONY: clean
clean:
	make --no-print-directory -C build/debug clean
	make --no-print-directory -C build/release clean
