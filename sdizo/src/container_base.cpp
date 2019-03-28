#include "container_base.h"
#include <fstream>
#include <time.h>
#include <random>

void container_base::load_from_file(std::string file_name){
	this->clear();

	std::fstream fs (file_name, std::fstream::in | std::fstream::out);
	
	if (!fs.is_open())
		return;

	int value, elements_count;
	// read size
	fs>>elements_count;
	// read data from file until eof
	while( (elements_count--) ){
		fs >> value;
		this->push_back(value);
	}
	fs.close();
}

void container_base::generate_data(int32_t size){
	srand(time(0));
	for(int i =0; i < size; i++){
		this->push_back( rand() %1337 );
	}
}