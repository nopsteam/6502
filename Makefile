.PHONY: build
build:
	cmake -B build
	make --no-print-directory -C build

.PHONY: test
test:
	cmake -B build
	make --no-print-directory -C build
	make --no-print-directory -C build test

.PHONY: clean
clean:
	make --no-print-directory -C build clean
