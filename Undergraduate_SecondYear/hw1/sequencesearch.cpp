#include <string>
#include <iostream>
#include <fstream>

using namespace std;

int main (int argc, char * argv[]){
	
	//input and output file streams
	ifstream in_File(argv[1]);
	ofstream out_File(argv[2]);

	//the number of rows
	int rowCount;
	in_File>>rowCount;

	//the number of columns stored in an array
	int* colCount = new int[rowCount];
	for(int row=0;row<rowCount;row++){
		in_File>>colCount[row];
	}

	//create dynamic 2D array
	double** grid = new double*[rowCount];
	for(int row = 0; row < rowCount; ++row){
    	grid[row] = new double[colCount[row]];
		for(int col=0;col<colCount[row];col++){
			in_File>>grid[row][col];
		}    	
	}

	for(int row = 0; row < rowCount; ++row){
		for(int col=0;col<colCount[row];col++){
			cout<<grid[row][col]<<" ";
		}    	
		cout<<endl;
	}

	//variable to store the maximum length
	int maxLength = 0;

	//loop through every value in the 2D array and check the sequence length in all 4 directions.
	for(int row=0;row<rowCount;row++){
		for(int col=0;col<colCount[row];col++){

			//create temporary holders for the maximum length above, below, to the left, and to the right for comparison.
			int maxLengthBelow = 1;
			int maxLengthRight = 1;
			int maxLengthAbove = 1;
			int maxLengthLeft = 1;

			//create holders for the values in all 4 directions for ease of reading;
			double currentValue, aboveValue, belowValue, 
				   rightValue, leftValue;
			
			//BELOW
			//Set hte current value
			currentValue=grid[row][col];
			//Move towards one direction
			for(int below=1;((row+below)<rowCount) 
				&& (colCount[row+below]>=col+1) ;below++){
				//Setting current value to the value in a given direction and that value to the one further in that direction
				if(below==1){
					belowValue=grid[row+below][col];
				}
				else{
					double temp=belowValue;
					belowValue=grid[row+below][col];
					currentValue=temp;
				}

				//Comparing the current value and the next value
				if(belowValue>currentValue){
					maxLengthBelow++;
				}
				else{
					//If the next value stops increasing in value, break out of the loop
					break;
				}
			}
				
			//RIGHT
			currentValue=grid[row][col];
			for(int right=1; (right+col<colCount[row]) ;right++){
				if(right==1){
					rightValue=grid[row][col+right];
				}
				else{
					double temp=rightValue;
					rightValue=grid[row][col+right];
					currentValue=temp;
				}
									
				if(rightValue>currentValue){
					maxLengthRight++;
				}
				else{
					break;
				}
			}


			//ABOVE
			currentValue=grid[row][col];
			for(int above=1; above<row+1 
				&& (colCount[row-1]>=col+1) ;above++){
				if(above==1){
					aboveValue=grid[row-above][col];
				}
				else{
					double temp=aboveValue;
					aboveValue=grid[row-above][col];
					currentValue=temp;
				}

				if(aboveValue>currentValue){
					maxLengthAbove++;
				}
				else{
					break;
				}
			}

			//LEFT
			currentValue=grid[row][col];
			for(int left=0;left<col;left++){
				if(left==0){
					leftValue=grid[row][col-(left+1)];
				}
				else{
					double temp=leftValue;
					leftValue=grid[row][col-1-left];
					currentValue=temp;
				}

				if(leftValue>currentValue){
					maxLengthLeft++;
				}
				else{
					break;
				}
			}

			//Compare the length from all 4 directions to find the maxmimum sequence of a given value in a given direction
			int maxHolder = max(maxLengthLeft,maxLengthLeft);
			int maxHolder2 = max(maxLengthAbove,maxLengthBelow);
			if(maxHolder2>maxHolder){
				maxHolder=maxHolder2;
			}
			if(maxHolder>maxLength){
				maxLength=maxHolder;
			}

		}
	}

	//Deleting the dynamically allocated 2D and 1D arrays
	for(int row=0;row<rowCount;row++){
		delete[] grid[row];
	}
	delete[] grid;
	delete[] colCount;

	//Output
	out_File<<maxLength;
	return 0;
}
