#include "container_test.h"
#include "table.h"
#include "list.h"
#include "binary_heap.h"
#include "binary_tree.h"
#include "misc.h"

#include <random>
#include <iostream>
#include <time.h>
namespace meassure{

	void perform_test(TEST_TYPE type, std::string file_name){
		using namespace std;
		
		std::string extended_test_header = "Push front;Pop front;Random insert;Random delete;Push back;Search operation;Pop back;Probe size";
		std::string base_test_header = "Push back;Search operation;Pop back;Probe size";

		table my_table;
		list my_list;
		binary_heap my_heap;
		binary_tree my_tree;
		container_base* containers[] = {&my_table, &my_list, &my_heap, &my_tree};

		// create csv file
		file_name += ".csv";
		fstream write(file_name, std::fstream::out);

		if( !write.is_open() ){
			cout << "Can't open file"<<endl;
			return;
		}
		// population table for tests
		int population_table[] = {10000,15000,20000,25000,30000,35000,40000,50000,60000,70000,80000,90000,100000,200000};

		int32_t tab_size = get_tab_size(population_table);
		int32_t *population,*indexes, current_pop_size;
		// init seed
		srand(time(0));

		// perform deep efficency test for given structure
		for (int32_t i = 0; i < tab_size; ++i)
		{

			// get probe size
			current_pop_size = population_table[i];

			// generate data
			population = new int32_t[ current_pop_size ];
			for (int32_t j = 0; j < current_pop_size; ++j)
			{
				population[j] = rand() %10000; 
			}

			// genrate indexes
			indexes = new int32_t[ current_pop_size ];
			indexes[0] = 0;

			// genearte random indexes but they shouldn't be grater then container elements count 
			for (int32_t j = 1; j < current_pop_size; ++j)
			{	
				indexes[j] = rand() % j;
			}

			switch(type){
				case TEST_TYPE::TEST_TABLE:
					cout <<"Testy przeprowdzane na tablicy: "<<endl;
					if(i == 0) write << extended_test_header <<endl;
					my_table.perform_test(write, current_pop_size, population,indexes);

				break;

				case TEST_TYPE::TEST_LIST:
					cout <<"Testy przeprowdzane na liscie: "<<endl;
					if(i == 0) write << extended_test_header <<endl;
					my_list.perform_test(write, current_pop_size, population,indexes);
				break;
				case TEST_TYPE::TEST_HEAP:
					cout <<"Testy przeprowdzane na kopcu: "<<endl;
					write << base_test_header <<endl;
					my_heap.perform_test(write, current_pop_size, population,indexes);

				break;
				case TEST_TYPE::TEST_TREE:
					cout <<"Testy przeprowdzane na drzewie: "<<endl;
					write << base_test_header <<endl;
					my_tree.perform_test(write, current_pop_size, population,indexes);

				break;
				case TEST_TYPE::TEST_ALL:
					cout <<"Testy przeprowdzane na wszystkich klasach" <<endl;
					for(auto&& con : containers){
						con->perform_test(write, current_pop_size, population,indexes);
					}
				break;

				default:
				break;
			};

			delete [] population;
			delete [] indexes;
		}

		write.close();
	}
	
	
	TEST_TYPE convert_to_TEST_TYPE(char op){
		if(op == '1')
			return TEST_TYPE::TEST_TABLE;
		else if(op == '2')
			return TEST_TYPE::TEST_LIST;
		else if(op == '3')
			return TEST_TYPE::TEST_HEAP;
		else if(op == '4')
			return TEST_TYPE::TEST_TREE;
		else if(op == '5')
			return TEST_TYPE::TEST_ALL;
		else
			return TEST_TYPE::INVALID;		
	}

	
	std::string convert_to_TEST_NAME(char op){
		if(op == '1' )
			return "TEST_TABLE";
		else if(op == '2')
			return "TEST_LIST";
		else if(op == '3')
			return "TEST_HEAP";
		else if(op == '4')
			return "TEST_TREE";
		else if(op == '5')
			return "TEST_ALL";
		else
			return "INVALID";		
	}
}