setup:
	cmake -DCMAKE_BUILD_TYPE=Debug -B build/debug
	cmake -DCMAKE_BUILD_TYPE=Release -B build/release
.PHONY: setup

debug:
	make --no-print-directory -C build/debug -j
.PHONY: debug

release:
	make --no-print-directory -C build/release -j
.PHONY: release

test:
	make --no-print-directory -C build/debug -j
	make --no-print-directory -C build/debug test ARGS='--output-on-failure'
.PHONY: test

clean:
	make --no-print-directory -C build/debug clean
	make --no-print-directory -C build/release clean
.PHONY: clean

coverage:
	cmake -DCMAKE_BUILD_TYPE=Coverage -B build/coverage
	make --no-print-directory -C build/coverage -j
	make --no-print-directory -C build/coverage coverage
.PHONY: coverage
