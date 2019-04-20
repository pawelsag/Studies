#include "container_test.h"
#include "table.h"
#include "list.h"
#include "binary_heap.h"
#include "binary_tree.h"
#include "red_black_tree.h"

#include <random>
#include <iostream>
#include <time.h>

namespace meassure{

	void perform_test(TEST_TYPE type, std::string file_name){
		using namespace std;
		
		std::string extended_test_header = "Random insert;Search operation;Random delete;Push back;Pop back;Push front;Pop front;Probe size";
		std::string base_test_header = "Random insert;Search operation;Random remove;Probe size";

		table my_table;
		list_sdizo my_list;
		binary_heap my_heap;
		binary_tree my_tree;
		
    container_base* containers[] = {&my_table, &my_list, &my_heap, &my_tree};
		TEST_TYPE type_array[] = {TEST_TYPE::TEST_TABLE, TEST_TYPE::TEST_LIST, TEST_TYPE::TEST_HEAP, TEST_TYPE::TEST_TREE}; 

		auto type_index = convert_TEST_TYPE_to_num(type);
		// create csv file
		file_name += ".csv";
		fstream write(file_name, std::fstream::out);

		if( !write.is_open() ){
			cout << "Can't open file"<<endl;
			return;
		}

		// population table for tests
		int population_table[POPULATION_SIZE];
		for(auto i =0llu; i < POPULATION_SIZE; i++)
			population_table[i] = 10000 + 20000 * i;
		
		int n = 100;
		int32_t current_pop_size, index, value;

		// init seed
		srand(time(0));

		if(type != TEST_TYPE::TEST_ALL){

			switch(type){
				case TEST_TYPE::TEST_TABLE:
					cout <<"Testy przeprowdzane na tablicy: "<<endl;
					write << extended_test_header << endl;
					cout <<endl;
				break;

				case TEST_TYPE::TEST_LIST:
					cout <<"Testy przeprowdzane na liscie: "<<endl;
					write << extended_test_header <<endl;
					cout <<endl;
				break;
				case TEST_TYPE::TEST_HEAP:
					cout <<"Testy przeprowdzane na kopcu: "<<endl;
					write << base_test_header <<endl;				
					cout << endl;
				break;
				case TEST_TYPE::TEST_TREE:
					cout << endl <<"Testy przeprowdzane na drzewie: "<<endl;
					write << base_test_header <<endl;				
					cout <<endl;
				break;
				
				default:
				break;
			};
			// perform deep efficency test for given structure
			for (auto i = 0llu; i < POPULATION_SIZE; ++i)
			{
				// get probe size
				current_pop_size = population_table[i];
        containers[type_index]->generate_data(current_pop_size);
        for(int32_t _n =0 ; _n < n; _n++){ 
          // generate value to put
          value = 0xffffffff;
          // genrate index
					index = rand() % current_pop_size;
					containers[type_index]->perform_test(index,value);
				}

        containers[type_index]->clear();
				containers[type_index]->save_test_averege(write);
				write << current_pop_size<<endl;
				containers[type_index]->reset_average();
			}
		}else{
			for(auto type: type_array){
				type_index = convert_TEST_TYPE_to_num(type);
			
				// code below should be separated funtion
				// maybe later...
				switch(type){
					case TEST_TYPE::TEST_TABLE:
						cout <<"Testy przeprowdzane na tablicy: "<<endl;
						write << extended_test_header << endl;
						cout <<endl;
					break;

					case TEST_TYPE::TEST_LIST:
						cout <<"Testy przeprowdzane na liscie: "<<endl;
						write << extended_test_header <<endl;
						cout <<endl;
					break;
					case TEST_TYPE::TEST_HEAP:
						cout <<"Testy przeprowdzane na kopcu: "<<endl;
						write << base_test_header <<endl;				
						cout << endl;
					break;
					case TEST_TYPE::TEST_TREE:
						cout << endl <<"Testy przeprowdzane na drzewie: "<<endl;
						write << base_test_header <<endl;				
						cout <<endl;
					break;
					
					default:
					break;
				};
				// perform deep efficency test for given structure
				for (auto i = 0llu; i < POPULATION_SIZE; ++i)
        {
          // get probe size
          current_pop_size = population_table[i];
          
          containers[type_index]->generate_data(current_pop_size);

          for(int32_t _n =0 ; _n < n; _n++){ 
            // generate value to put
            value = rand() % 0xbadcafe;
            // genrate index
            index = rand() % current_pop_size;
            
            containers[type_index]->perform_test(index,value);
            
          }
          containers[type_index]->clear();
          containers[type_index]->save_test_averege(write);
          write << current_pop_size<<endl;
          containers[type_index]->reset_average();
        }
			}
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

	size_t convert_TEST_TYPE_to_num(TEST_TYPE type){
		return static_cast<size_t>(type);
	}

}