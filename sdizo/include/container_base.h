#ifndef CONTAINER_BASE
#define CONTAINER_BASE

#include <string>
#include <stdint.h>


class container_base
{
public:
	container_base() {};
	~container_base() {};

	virtual void generate_data(int32_t size)=0;

	virtual bool load_from_file(std::string FileName)=0; 
		
	virtual bool insert(int32_t index, int32_t value)=0;

	virtual bool remove(int32_t index)=0;

	virtual void display()=0;	
};

#endif