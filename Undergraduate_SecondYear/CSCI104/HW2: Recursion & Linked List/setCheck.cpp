#include <set>
#include <iostream>
#include <fstream>

using namespace std;

void stringSeparatorHelper(set<string> &s, string readIn);

string toLower(string s);

int main(int argc, char* argv[]){

	//Check for invalid command line inputs
	if(argc != 2){
		cout << "Please enter a file name in the command line" << endl;
		return 1;
	}

	//Instream
	ifstream in_File(argv[1]);

	//The set in which the words will be stored
	set<string> s;

	//Place the words from the input file in a temporary holder, readin, then send them through a helper function to correctly separate them
	string readIn;
	while(in_File>>readIn){
		stringSeparatorHelper(s, readIn);
	}

	//Create a loop that ends when the user presses enter without any inputs
	string userInput;
	do{
		//Prompt for an input
		cout<<"Plesae enter a string: ";
		getline(cin,userInput);

		//Check if the input is empty
		if(userInput.empty()){
			return 0;
		} 
		//The input isn't empty
		else {

			//Convert the user input to all lower cases
			for(int i=0;i<userInput.length();i++){
				userInput[i]=tolower(userInput[i]);
			}			

			//Print the result
			if(s.count(userInput)==1)
				cout<<"in the file"<<endl;
			else
				cout<<"not in the file"<<endl;		
		}
	} while(true);

	in_File.close();
	return 0;
}

void stringSeparatorHelper(set<string> &s, string readIn){

	//Make the word from the input file lower case
	for(int i=0;i<readIn.length();i++){
		readIn[i]=tolower(readIn[i]);
	}

	//Create 2 counters to keep track of all the action
	int counter1=0;
	int counter2=0;

	//Make sure we traverse the entire lenght of the string
	while(counter2<readIn.length()){
		//If anything that isn't an alphabet is encountered
		if(!isalpha(readIn[counter2])){
			//If there is at last something between the two counters
			if(counter2-counter1>0)
				s.insert(readIn.substr(counter1,counter2-counter1));
			counter2++;
			counter1=counter2;
		}
		//If an alphabet is encountered
		else
			counter2++;
	}

	//Check to see if there are any residues from the above loop
	if(counter2-counter1>0){
		s.insert(readIn.substr(counter1,counter2-counter1));
	}
}