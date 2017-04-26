/*
Defines the class cube. Each instance of cube is a state of cube.
Class:	cube
		Class Variables:
			state: 			An array (preferable short int of 2 bytes) containing all the colors of all the sides of cube.
							CODE: 	RED			1
									GREEN		2
									BLUE		3
									ORANGE		4
									WHITE		5
									YELLOW		6
		Functions:
			initializer:	Takes up value of state and check if state is valid using validate().
			validate:		A function that returns boolean values true is input is valid.
							CHECKS: 	Does input have 9 squares of each colour?
										Are 6 center pieces uniques?
										Are 12 edge pieces unique and colored as expected?
										Are 8 corner pieces unique and coloured as expected?
										When white center is kept in front, and green center on top...
											is red center on left?
											is orange center on right?
											is blue center on bottom?
											is yellow center at back?
			nextPossible:	Returns an array of 9 new cube instances which are possible by 9 rotations of given cube.
			solved:			Returns boolean value true if the cube is solved.
			represent:		Returns a string representation for key in hashtable.
			print:			Prints the current state of cube in a convienient format.


		REMAINING ISSUES TO BE SOLVED LATER:
			Every input that is valid and not solved is not solvable: need to think of additional validate checks!
*/

// will rather write 9 rotation functions to generate next possible cube
/* indexes on a face
00 01 02
10 11 12
20 21 22
*/
#include <iostream>
#include <string>
using namespace std;
#define WHITE 0
#define RED 1
#define GREEN 2
#define ORANGE 3
#define BLUE 4
#define YELLOW 5
class cube {
	short state[6][3][3];		//the state of the cube is represented by a 6*3*3 array
	//0:White(Front), 1:Red(Top), 2:Green(Right), 3:Orange(Bottom), 4:Blue(Left), 5:Yellow(Back)

	string colors[]={"WHITE", "RED", "GREEN", "ORANGE", "BLUE", "YELLOW"};
public:
	
	cube()					//constructor, takes input
	{
		cout<<"INSTRUCTIONS for placing the cube and feeding the states: \n Place the cube such that WHITE centerpeice is in front and the RED centerpeice is on top";		//Enter the instructions


		for (int i = 0; i < 6; ++i)
		{
			cout<<"Enter the state for "<<colors[i]<<" face.";
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if ((j==1)&&(k==1))		//centerpeice denotes the face
					{
						state[i][1][1]=i;
					}
					cout<<"Enter the state of peice at ( "<<j<<", "<<k<<" ) : ";
				}
			}
		}
	}

	cube(short* arr) {
		for (short i = 0; i < 6; i++) {
			for (short j = 0; j < 6; j++) {
				for (short k = 0; k < 6; k++) {
					state[i][j][k] = arr[i][j][k];
				}
			}
		}
	}
	
	bool validate()
	{
		size_t size[6]={0}

		for (int i = 0; i < 6; ++i)
		{
			for (int j = 0; j < 3; ++j)
			{
				for (int k = 0; k < 3; ++k)
				{
					if (state[i][j][k]==WHITE)
					{
						size[WHITE]++;
					}
					else if (state[i][j][k]==RED)
					{
						size[RED]++;
					}
					else if (state[i][j][k]==GREEN)
					{
						size[GREEN]++;
					}
					else if (state[i][j][k]==ORANGE)
					{
						size[ORANGE]++;
					}
					else if (state[i][j][k]==BLUE)
					{
						size[BLUE]++;
					}
					else if (state[i][j][k]==YELLOW)
					{
						size[YELLOW]++;
					}
				}
			}
		}

		
	}

	cube nextPossible();

	bool solved();


	
	int getState(int i, int j, int k)		//returns state of a given cube
	{
		return state[i][j][k];
	}


};

int main(int argc, char const *argv[])
{
	cube c;
	for(int i=0; i<6; i++)
	{
		for (int j = 0; j < 3; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				cout<<c.getState(i, j, k);
			}
		}
		cout<<endl;
	}
	return 0;
}