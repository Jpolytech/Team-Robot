PHONY: clean make compile install

clean: 
	cd ./lib && make clean
	cd ./test-svg-picture && make clean

compile:
	cd ./lib && make
	cd ./test-svg-picture && make

install: clean compile
	cd ./test-svg-picture && make install
