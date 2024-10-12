COMP="g++"

build:
	mkdir build
	mkdir build/bin
	mkdir build/depen
	$(COMP) -o test test.cpp
	mv test build/bin

clean:
	rm -rf build
