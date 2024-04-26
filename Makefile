all: 
	cmake -B build && cd build && make

clean:
	rm -fr build/*

