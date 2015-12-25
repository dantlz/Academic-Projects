#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

void makePalindromes(ostream& ofile, char* options, int size);
void makePalindromeHelper(string pal, string options, int numOfChars,int sizeLimit, vector<string> &list);

int main(int argc, char* argv[])
{
  if(argc < 4){
    cerr << "Please provide an output file, a string of characters, and the max length" << endl;
    return 1;
  }

  ofstream ofile(argv[1]);
  int len = atoi(argv[3]);
  makePalindromes(ofile, argv[2], len);
  ofile.close();
  return 0;
}

void makePalindromes(ostream& ofile, char* options, int size){
	//vector to store all combinations of palindromes
	vector<string> list;

	//store the char options into a string file because I like strings
	string chars=options;

	//store the number of options
	int numOfChars=chars.size();

	//Loop through all chars and use them as the starting pal
	for(int i=0;i<numOfChars+1;i++){

		//since I can't add an empty char in the front of a string, this if statement sends an empty string as the first entry
		if(i==0){
			makePalindromeHelper("", 				  chars, numOfChars, size, list);
		}
		//normal entries by looping through each char in the string
		else{
			makePalindromeHelper(chars.substr(i-1,1), chars, numOfChars, size, list);
		}
	}

	//Sort the order of the strings in the vector and remove duplicates for quality check
	sort(list.begin(),list.end());
	list.erase( unique( list.begin(), list.end() ), list.end() );

	//Write the resulting palindromes into the output file
	for(int i=0;i<list.size();i++){
		ofile<<list[i]<<endl;
	}
}

void makePalindromeHelper(string pal, string options, int numOfChars,int sizeLimit, vector<string> &list){
	//Base case
	if(pal.size()+2>sizeLimit){
		list.push_back(pal);
	}
	//Recrusion
	else{
		//For each pal that is sent in, loop through all possible options form the beginning and use them to wrap the given pal
		for(int i=0;i<numOfChars;i++){
			//If the pal that's sent over is a single character, make sure to save it. There could be repeats but a simple clean up
			//would take care of that
			if(pal.size()==1){
				list.push_back(pal);
			}
			//Since there cannot be an empty value before a string, an empty pal that's sent over need to be immediately saved.
			else if(pal.size()==0){
				list.push_back("");
			}	

			//Wrap the pal with a char from options		
			string temp=options[i]+pal+options[i];
			//Send the newly created pal to makePalindromeHelper again.
			makePalindromeHelper(temp, options, numOfChars,sizeLimit,list);

			//Save the newly created pal
			list.push_back(temp);
		}
	}
	
}