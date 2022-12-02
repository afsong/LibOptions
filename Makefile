# .PHONY to prevent build directory and build target collision
# format for multiline target
# cmake .. && cmake --build . ;		
.PHONY: build
build: clean
	mkdir build && cd build;											\
	cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo .. && cmake --build . ;		\

# target to create a debug version
.PHONY: debug
debug: clean 
	mkdir build && cd build;											\
	cmake -DCMAKE_BUILD_TYPE=Debug .. && cmake --build . ;				\

.PHONY: clean
clean:
	rm -rf build

.PHONY: driver
driver: build
	./build/driver/driver
