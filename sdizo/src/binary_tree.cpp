#include "binary_tree.h"

binary_tree::binary_tree(std::initializer_list<int32_t> args_vector){

}

binary_tree::~binary_tree(){

}

void binary_tree::generate_data(int32_t size){

}

void binary_tree::clear(){

}

bool binary_tree::load_from_file(std::string file_name){

}

BST_Node* binary_tree::find(int32_t key){
	BST_Node* node = this->root ;
	while( node != nullptr && node->key != key ){
		if( node->key < key)
			node = node->right;
		else
		 	node = node->left;
	}
}

bool binary_tree::push_back(int32_t key){

}

bool binary_tree::remove(int32_t key){

}

void binary_tree::display(std::string sp, std::string sn, int v){

}
