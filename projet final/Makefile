PHONY: clean make compile install

clean: 
	cd ./lib && make clean
	cd ./test-projet && make clean

compile:
	cd ./lib && make
	cd ./test-projet && make

install: clean compile
	cd ./test-projet && make install
