#include <map>
#include <iostream>
#include "mapcolum.hpp"

int main(int argc, char* argv[]){
	MXPSQL::MapColumn::map_column<int> map_column;
	map_column["ad"]["b"] = 1;
	map_column["ad"]["c"] = 2;

	map_column["a"][".out"] = 1;
	map_column["a"][".bin"] = 1;
	map_column["a"][".exe"] = 1;
	map_column["a"][".elf"] = 0;

	MXPSQL::MapColumn::unordered_map_column<int> unordered_map_column = MXPSQL::MapColumn::ordered_to_unordered_map_column(map_column);
	unordered_map_column["o"]["o"] = 1;

	for(auto pair : unordered_map_column){
		std::cout << pair.first << ": ";
		for(auto pair2 : pair.second){
			std::cout << pair2.first << ": " << pair2.second << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	map_column = MXPSQL::MapColumn::unordered_to_ordered_map_column(unordered_map_column);
	map_column["yes"]["no"] = 0;
	map_column["yes"]["yes"] = 1;

	for(auto pair : map_column){
		std::cout << pair.first << ": ";
		for(auto pair2 : pair.second){
			std::cout << pair2.first << ": " << pair2.second << ", ";
		}
		std::cout << std::endl;
	}

	std::cout << std::endl;

	MXPSQL::MapColumn::dictionary<int> adchild = MXPSQL::MapColumn::get_row_ordered(map_column, "ad");
	for(auto pair : adchild){
		std::cout << pair.first << ": " << pair.second << std::endl;
	}

	std::cout << std::endl;

	return 0;
}