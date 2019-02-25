MAKEFLAGS += --no-print-directory

default: release

release:
	mkdir -p build && cd build && cmake ../ -DCMAKE_BUILD_TYPE=Release && cmake --build .

debug:
	mkdir -p build && cd build && cmake ../ -DCMAKE_BUILD_TYPE=Debug && cmake --build .

run:
	@if [ -f ./build/main ]; then ./build/main; else echo "Run 'make release' or 'make debug' first" && exit 1; fi

clean:
	@if [ -d ./build/ ]; then rm -r build; else echo "Build is already clean"; fi
