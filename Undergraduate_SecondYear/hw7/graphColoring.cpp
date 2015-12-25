#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include "rbbst.h"

bool isValid(std::map<char, std::vector<char> >& neighborMap, RedBlackTree<char, int>& colorMap){

	for(RedBlackTree<char, int>::iterator it = colorMap.begin();it!=colorMap.end();++it){
		int currentColor = it->second;
		if(currentColor!=0){
			std::vector<char> neighbors = neighborMap[it->first];
			for(unsigned int i=0;i<neighbors.size();i++){
				if(currentColor == colorMap.find(neighbors[i])->second)
					return false;
			}
		}
	}
	return true;
}

bool backtrack(std::map<char, std::vector<char> >& neighborMap, RedBlackTree<char, int>& colorMap, RedBlackTree<char, int>::iterator& it){

    if(it == NULL){
        return true;
    }

    for(int i=1;i<=4;i++){
        it->second = i;
        if(isValid(neighborMap, colorMap)){
        	RedBlackTree<char, int>::iterator temp = it;
        	if(backtrack(neighborMap, colorMap, ++it)){
        		return true;
        	}
        	else{
        		it=temp;
        		continue;
        	}
       	}
    }
    //Reset the value for next iteration?
    it->second = 0;
    return false;
}

bool notContain(std::vector<char>& v, char c){
	for(unsigned int g=0;g<v.size();g++){
		if(v[g] == c)
			return false;
	}
	return true;
}

int main(int argc, char* argv[]){
	//Check for parameter count
	if(argc<2){
		std::cerr<<"ERROR: Not input file provided!"<<std::endl;
		return 1;
	}

	//Check input file
	std::ifstream input_file(argv[1]);
	if(input_file.fail()){
		std::cerr<<"ERROR: Invalid input file!"<<std::endl;
		return 1;
	}

	int numOfCountries, totalRow, totalCol;
	input_file >> numOfCountries;
	input_file >> totalRow;
	input_file >> totalCol;
	input_file.ignore();

	//Check input file content
	if(numOfCountries < 1 || totalCol < 1|| totalRow < 1){
		std::cerr<<"ERROR: Invalid parameters in the input file!"<<std::endl;
		return 1;
	}
	
	//Make the map into a single string
	std::string input = "";
	std::string input2 = "";

	bool firstLine= std::getline(input_file, input);
	if(firstLine){
		while(getline(input_file, input2))
			input=input+input2;
	}

	//This removes any spaces in the map.
	for(std::string::iterator it=input.begin(); it!=input.end();++it){
		if(isspace(*it)){
			input.erase(it);
		}
	}

	//Variables
	char** graph = new char*[totalRow];
	for(int i=0;i<totalRow;i++){
		graph[i] = new char[totalCol];
	}

	std::map<char, std::vector<char> > neighborMap;
	RedBlackTree<char, int> colorMap;
	std::vector<char> allCountryNames;

	//Put the map into a 2D array
	for(int i=0;i<totalRow;i++){
		for(int k=0;k<totalCol;k++){
			graph[i][k] = input[(totalCol*i)+k];
			if(notContain(allCountryNames, input[(totalCol*i)+k])){
				allCountryNames.push_back(input[(totalCol*i)+k]);
			}
		}
	}

	if(allCountryNames.size()!=(unsigned)numOfCountries){
		std::cerr<<"Something went wrong when retrieving a vector of names, or the given number of countries is wrong"<<std::endl;
		return 1;
	}

	for(unsigned int i=0;i<allCountryNames.size();i++){
		std::vector<char> v;
		neighborMap.insert(std::make_pair(allCountryNames[i],v));
		colorMap.insert(std::make_pair(allCountryNames[i],0));
	}

	//Find out which country has which neighbors
	for(int i=0;i<totalRow;i++){
		for(int k=0;k<totalCol;k++){
			std::vector<char> neighbors=neighborMap[graph[i][k]];
			if(i!=0){
				if(graph[i-1][k] != graph[i][k] && notContain(neighbors, graph[i-1][k])){
					//Look above
					neighborMap[graph[i][k]].push_back(graph[i-1][k]);
				}
			}
			if(i!=totalRow-1){
				if(graph[i+1][k] != graph[i][k] && notContain(neighbors, graph[i+1][k])){
					//Look below
					neighborMap[graph[i][k]].push_back(graph[i+1][k]);
				}
			}
			if(k!=0){
				if(graph[i][k-1] != graph[i][k] && notContain(neighbors, graph[i][k-1])){
					//Look left
					neighborMap[graph[i][k]].push_back(graph[i][k-1]);
				}
			}
			if(k!=totalCol-1){
				if(graph[i][k+1] != graph[i][k] && notContain(neighbors, graph[i][k+1])){
					//Look right
					neighborMap[graph[i][k]].push_back(graph[i][k+1]);				
				}
			}
		}
	}

	RedBlackTree<char, int>::iterator it = colorMap.begin();
	bool success = backtrack(neighborMap, colorMap, it);
	if(success){
		std::ofstream output_file("out.txt",std::ios::out);
		if(output_file.fail()){
			std::cerr<<"ERROR: Invalid Output file"<<std::endl;
		}

		for(it=colorMap.begin();it!=colorMap.end();++it){
			output_file<<(it->first)<<" "<<(it->second)<<std::endl;
		}
	}
	else{
		std::cerr<<"ERROR: Backtracking failed"<<std::endl;
		return 1;
	}

	for(int i=0;i<totalRow;i++){
		delete[] graph[i];
	}
	delete[] graph;
	return 0;
}