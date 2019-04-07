#ifndef TEST_AREA
#define TEST_AREA

#include <string>
enum class TEST_TYPE{
	TEST_TABLE  =0,
	TEST_LIST   =1,
	TEST_HEAP   =2,
	TEST_TREE   =3,
	TEST_ALL    =4,
	INVALID     =5
};

namespace meassure{

	TEST_TYPE convert_to_TEST_TYPE(char op);
	std::string convert_to_TEST_NAME(char op);
	inline size_t convert_TEST_TYPE_to_num(TEST_TYPE op);
	// perform efficency tests dependes on type
	// file_name is the name of file where to save results
	// the results will be saved with .csv extension
	void perform_test(TEST_TYPE type, std::string file_name);
}

#endif