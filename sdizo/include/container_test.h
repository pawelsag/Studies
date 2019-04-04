#ifndef TEST_AREA
#define TEST_AREA

#include <string>
enum class TEST_TYPE{
	TEST_TABLE,
	TEST_LIST,
	TEST_HEAP,
	TEST_TREE,
	TEST_ALL,
	INVALID
};

namespace meassure{

	TEST_TYPE convert_to_TEST_TYPE(char op);
	std::string convert_to_TEST_NAME(char op);

	// perform efficency tests dependes on type
	// file_name is the name of file where to save results
	// the results will be saved with .csv extension
	void perform_test(TEST_TYPE type, std::string file_name);
}

#endif