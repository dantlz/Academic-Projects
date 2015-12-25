#include <iostream>
#include "minheap.h"
#include <fstream>
#include <stdexcept>
#include <string>
#include <set>
#include <map>
#include <vector>

using namespace std;

int Heuristic(string first, string second){
	int h = 0;
	for(unsigned int i=0; i < first.size(); i++){
		if(first[i] != second[i])
			h++;
	}
	return h;
}

void print(map<string, string> map_curr_previous, string curr, string start){
	if(curr != start){
		print(map_curr_previous, map_curr_previous[curr], start);
	}		
	cout<<curr<<" ";
}

int main(int argc, char *argv[]){

	//Check for parameter count
	if(argc<4)
		throw std::invalid_argument("ERROR: Missing commandline inputs");


	string start;
	string end;
	set<string> all_words;
	
	bool exit = false;
	int expansions = 0;

	int priority = 0;
	set<string> visited_words;
	map<string, int> map_word_distance;	
	map<string, int> map_word_priority;	
	MinHeap heap(2); 
	map<string, string> map_curr_previous;


	//Read from commandline
		//Check input file
	ifstream input_file(argv[3]);
	if(input_file.fail())
		throw std::invalid_argument("ERROR: Invalid input file");

		//Check for start end validity
	start = argv[1];
	end = argv[2];

	if(start.size() < 1)
		throw std::invalid_argument("ERROR: Invalid start");

	if(end.size() < 1 )
		throw std::invalid_argument("ERROR: Invalid end");
	
	if(start.size() != end.size()){
		cout<<"No Possble Path: start and end are of different length"<<endl;
		return 0;
	} 

	const unsigned int wordLength = start.size();
	for(unsigned int i=0;i<wordLength;i++){
		if(isalpha(start[i]))
			start[i] = tolower(start[i]);
		else
			throw std::invalid_argument("ERROR: start contains non-alphabet characters");

		if(isalpha(end[i]))
			end[i] = tolower(end[i]);
		else
			throw std::invalid_argument("ERROR: end contains non-alphabet characters");
	}

	//Read from input file
	int numOfWords = 0;
	input_file>>numOfWords;
	int counter = 0;
	for(int i=0; i<numOfWords; i++){
		string word;
		input_file >> word;
		if(word.size() == wordLength){
			if(all_words.count(word) == 0){
				for(unsigned int g = 0; g < wordLength; g++){
					if(isalpha(word[g]))
						word[g] = tolower(word[g]);
					else
						throw invalid_argument("ERROR: "+word+" contains non-alphabet characters");		
				}
				if(word == start || word == end)
					counter++;
				all_words.insert(word);
			}
		}
	}
	if(counter != 2){
		cout<<"No Possible Path: provided start or end are not in the list of words"<<endl;
		return 0 ;
	}
	input_file.close();
	if(Heuristic(start, end) == 0){
		cout<<start<<endl<<"expansions = "<<expansions<<endl;
		return 0;
	}


	//Deal with start before starting A*
	priority = (map_word_distance[start] + Heuristic(start, end))*(wordLength + 1) + Heuristic(start, end);
	visited_words.insert(start);
	map_word_distance.insert(make_pair(start, 0));
	map_word_priority.insert(make_pair(start, priority));
	heap.add(start, priority);
	
	//A*
	while(!heap.isEmpty() && !exit){
		string curr = heap.peek();
		heap.remove();
		expansions++;
		set<string>::iterator next;
		for(next = all_words.begin(); next != all_words.end(); ++next){
			//curr to next is a valid move
			if(Heuristic(curr, *next) == 1){
				//Foundeeeeee
				if(*next == end){
					map_curr_previous.insert(make_pair(end, curr));
					exit = true;
					break;
				}
				//next is not visited
				else if(visited_words.count(*next) == 0){
					visited_words.insert(*next);
					map_curr_previous.insert(make_pair(*next, curr));
					map_word_distance.insert(make_pair(*next, map_word_distance[curr]+1));
					priority = (map_word_distance[*next] + Heuristic(*next, end))*(wordLength + 1) + Heuristic(*next, end);
					map_word_priority.insert(make_pair(*next, priority));
					heap.add(*next, priority);
				}
				//next is visited 
				else{	
					priority = ((map_word_distance[curr] + 1) + Heuristic(*next, end))*(wordLength + 1) + Heuristic(*next, end);
					//Going through curr to get to next is better than which ever way we've found before.
					if(priority < map_word_priority[*next]){	
						map_curr_previous[*next] = curr;
						map_word_distance[*next] = map_word_distance[curr] + 1;
						heap.update(*next, priority);
						map_word_priority[*next] = priority;
					}
				}
			}
		}
	}

	if(exit){
		print(map_curr_previous, end, start);
		cout<<endl<<"expansions = "<<expansions<<endl;
		return 0;
	}
	else{
		cout<<"No Path Found"<<endl;
		return 0;
	}
}

