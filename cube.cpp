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

#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define WHITE 0
#define RED 1
#define GREEN 2
#define ORANGE 3
#define BLUE 4
#define YELLOW 5

class cube {

	short state[6][3][3]; //the state of the cube is represented by a 6*3*3 array
	//0:White(Front), 1:Red(Top), 2:Green(Right), 3:Orange(Bottom), 4:Blue(Left), 5:Yellow(Back)
	public:
	static const string colors[6];

public:
	string lastStep;
	cube* parent;

	// Constructors, takes input
	cube() {} 	

	cube(string fileName) {
		cout << "Reading input...\n";
		ifstream inpFile; inpFile.open(fileName);
		for (int i = 0; i < 6; ++i) {
			for (int j = 0; j < 3; ++j) {
				for (int k = 0; k < 3; ++k) {
					inpFile >> state[i][j][k];
				}
			}
		}
		inpFile.close();
		lastStep = "";
		parent = NULL;
		// cout << this << " " << lastStep << " " << parent << "\n";
	}

	cube(int*** arr, string givenLastStep, cube* const givenParent) {
		for (short i = 0; i < 6; i++) {
			for (short j = 0; j < 3; j++) {
				for (short k = 0; k < 3; k++) {
					state[i][j][k] = arr[i][j][k];
				}
			}
		}
		lastStep = givenLastStep;
		parent = givenParent;
	}

	// VALIDATE
	bool validate() {
		return true;
	}

	// CUBE IS SOLVED?
	bool solved() {
		for (int i = 0; i < 6; i++) {
			// check if all match the center element
			for (int j = 0; j < 3; j++) {
				for (int k = 0; k < 3; k++) {
					if (state[i][j][k] != state[i][1][1]) return false;
				}
			}
		}
		return true;
	}
	
	int getState(int i, int j, int k) {
		return state[i][j][k];
	}

	// REPRESENTATION OF STATE IN FORM OF STRING
	string represent() {
		string r = "";
		for (short i = 0; i < 6; i++) {
			for (short j = 0; j < 3; j++) {
				for (short k = 0; k < 3; k++) {
					r += to_string(state[i][j][k]);
				}
			}
		}
		return r;
	}
	
	// PRINT THE STATE, BEAUTIFIED
	void print6tabs() { for(int i = 0; i < 3; i++) cout << "\t";}
	void printWithSpace(int face) {
		for (int i = 0; i < 3; i++) {
			print6tabs();
			for (int j = 0; j < 3; j++) cout << colors[state[face][i][j]] << "\t";
			cout << "\n";
		}
	}
	void print() {
		//0:White(Front), 1:Red(Top), 2:Green(Right), 3:Orange(Bottom), 4:Blue(Left), 5:Yellow(Back)
		// print RED 
		printWithSpace(1);
		// print BLUE, WHITE, GREEN (4-0-2)
		for (int i = 0; i < 3; i++) {
			for (int j = 0; j < 3; j++) cout << colors[state[4][i][j]] << "\t";
			for (int j = 0; j < 3; j++) cout << colors[state[0][i][j]] << "\t";
			for (int j = 0; j < 3; j++) cout << colors[state[2][i][j]] << "\t";
			for (int j = 0; j < 3; j++) cout << colors[state[5][i][j]] << "\t";
			cout << "\n";
		}
		// print ORANGE
		printWithSpace(3);		
		// print YELLOW
		// printWithSpace(5);
	}

	// NEXT POSSIBLE STATES
	int*** getStateCopy(int*** state) {
		int*** state_copy = 0;
		state_copy = new int**[6];
		for(int i = 0; i < 6; i++) {
			state_copy[i] = new int*[3];
			for(int j = 0; j<3; j++) {
				state_copy[i][j] = new int[3];
				for(int k = 0; k<3; k++) {
					state_copy[i][j][k] = state[i][j][k];
				}
			}
		}
		return state_copy;
	}

	int*** R(int*** state){
		int*** state_copy = getStateCopy(state);
		for(int i =0; i< 3;i++)
		{	state_copy[WHITE][i][2] = state[ORANGE][i][2];
			state_copy[ORANGE][i][2] = state[YELLOW][2-i][0];
			state_copy[YELLOW][i][0] = state[RED][2-i][2];
			state_copy[RED][i][2] = state[WHITE][i][2];
			state_copy[GREEN][i][0] = state[GREEN][2][i];
			state_copy[GREEN][0][i] = state[GREEN][2-i][0];
			state_copy[GREEN][2][i] = state[GREEN][2-i][2];
			state_copy[GREEN][i][2] = state[GREEN][0][i];
		}
		return state_copy;
	}

	int*** L(int*** state){
		int*** state_copy = getStateCopy(state);
		for(int i =0; i< 3;i++)
		{	state_copy[WHITE][i][0] = state[RED][i][0];
			state_copy[ORANGE][i][0] = state[WHITE][i][0];
			state_copy[YELLOW][i][2] = state[ORANGE][2-i][0];
			state_copy[RED][i][0] = state[WHITE][i][0];
			state_copy[BLUE][i][0] = state[BLUE][2][i];
			state_copy[BLUE][i][2] = state[BLUE][0][i];
			state_copy[BLUE][0][i] = state[BLUE][2-i][0];
			state_copy[BLUE][2][i] = state[BLUE][2-i][2];
		}
		return state_copy;
	}

	int*** Rd(int*** state){
		int*** state_copy = getStateCopy(state);
		return R(R(R(state_copy)));
		//state_copy = R(state_copy);
		//state_copy = R(state_copy);
		//return state_copy;
	}

	int*** Ld(int*** state){
		int*** state_copy = getStateCopy(state);
		return L(L(L(state_copy)));
		//state_copy = L(state_copy);
		//state_copy = L(state_copy);
		//return state_copy;
	}

	int*** RR(int*** state){
		int*** state_copy = getStateCopy(state);
		return R(R(state_copy));
	}

	int*** LL(int*** state){
		int*** state_copy = getStateCopy(state);
		return L(L(state_copy));
	}

	int*** T(int*** state){
		int*** state_copy = getStateCopy(state);
		for(int i =0; i< 3;i++)
		{	state_copy[WHITE][0][i] = state[GREEN][0][i];
			state_copy[GREEN][0][i] = state[YELLOW][0][i];
			state_copy[YELLOW][0][i] = state[BLUE][0][i];
			state_copy[BLUE][0][i] = state[WHITE][0][i];
			state_copy[RED][0][i] = state[RED][2-i][0];
			state_copy[RED][i][0] = state[RED][2][i];
			state_copy[RED][2][i] = state[RED][2-i][2];
			state_copy[RED][i][2] = state[RED][0][i];
		}
		return state_copy;
	}

	int*** D(int*** state){
		int*** state_copy = getStateCopy(state);
		for(int i =0; i< 3;i++)
		{	state_copy[WHITE][2][i] = state[BLUE][2][i];
			state_copy[BLUE][2][i] = state[YELLOW][2][i];
			state_copy[YELLOW][2][i] = state[GREEN][2][i];
			state_copy[GREEN][2][i] = state[WHITE][2][i];
			state_copy[ORANGE][0][i] = state[ORANGE][2-i][0];
			state_copy[ORANGE][i][0] = state[ORANGE][2][i];
			state_copy[ORANGE][2][i] = state[ORANGE][2-i][2];
			state_copy[ORANGE][i][2] = state[ORANGE][0][i];
		}
		return state_copy;
	}

	int*** Td(int*** state){
		int*** state_copy = getStateCopy(state);
		return T(T(T(state_copy)));
		//state_copy = R(state_copy);
		//state_copy = R(state_copy);
		//return state_copy;
	}

	int*** Dd(int*** state){
		int*** state_copy = getStateCopy(state);
		return D(D(D(state_copy)));
		//state_copy = L(state_copy);
		//state_copy = L(state_copy);
		//return state_copy;
	}

	int*** TT(int*** state){
		int*** state_copy = getStateCopy(state);
		return T(T(state_copy));
	}

	int*** DD(int*** state){
		int*** state_copy = getStateCopy(state);
		return D(D(state_copy));
	}

	int*** F(int*** state){
		int*** state_copy = getStateCopy(state);
		for(int i =0; i< 3;i++)
		{	state_copy[RED][2][i] = state[BLUE][2-i][2];
			state_copy[BLUE][i][2] = state[ORANGE][0][i];
			state_copy[ORANGE][0][i] = state[GREEN][2-i][0];
			state_copy[GREEN][i][0] = state[RED][2][i];
			state_copy[WHITE][0][i] = state[WHITE][2-i][0];
			state_copy[WHITE][i][0] = state[WHITE][2][i];
			state_copy[WHITE][2][i] = state[WHITE][2-i][2];
			state_copy[WHITE][i][2] = state[WHITE][0][i];
		}
		return state_copy;
	}

	int*** B(int*** state){
		int*** state_copy = getStateCopy(state);
		for(int i =0; i< 3;i++)
		{	state_copy[RED][0][i] = state[GREEN][i][2];
			state_copy[BLUE][i][0] = state[RED][0][2-i];
			state_copy[ORANGE][2][i] = state[BLUE][i][0];
			state_copy[GREEN][i][2] = state[ORANGE][2][2-i];
			state_copy[YELLOW][i][2] = state[YELLOW][0][i];
			state_copy[YELLOW][2][i] = state[YELLOW][2-i][2];
			state_copy[YELLOW][i][0] = state[YELLOW][2][i];
			state_copy[YELLOW][0][i] = state[YELLOW][2-i][0];	
		}
		return state_copy;
	}

	int*** Bd(int*** state){
		int*** state_copy = getStateCopy(state);
		return B(B(B(state_copy)));
	}

	int*** Fd(int*** state){
		int*** state_copy = getStateCopy(state);
		return F(F(F(state_copy)));
	}

	int*** BB(int*** state){
		int*** state_copy = getStateCopy(state);
		return B(B(state_copy));
	}

	int*** FF(int*** state){
		int*** state_copy = getStateCopy(state);
		return F(F(state_copy));
	}

	cube* nextPossible(){
		int*** state_copy = 0;
		state_copy = new int**[6];
		for(int i = 0; i < 6; i++) {
			state_copy[i] = new int*[3];
			for(int j = 0; j<3; j++) {
				state_copy[i][j] = new int[3];
				for(int k = 0; k<3; k++) {
					state_copy[i][j][k] = state[i][j][k];
				}
			}
		}
		cube right(R(state_copy), string("R"), this);
		cube left(L(state_copy), "L", this);
		cube rr(RR(state_copy), "R2", this);
		cube right_d(Rd(state_copy), "R'", this);
		cube left_d(Ld(state_copy), "L'", this);
		cube ll(LL(state_copy), "L2", this);
		cube back(B(state_copy), "B", this);
		cube front(F(state_copy), "F", this);
		cube bb(BB(state_copy), "B2", this);
		cube back_d(Bd(state_copy), "B'", this);
		cube front_d(Fd(state_copy), "F'", this);
		cube ff(FF(state_copy), "F2", this);
		cube top(T(state_copy), "T", this);
		cube down(D(state_copy), "D", this);
		cube tt(TT(state_copy), "T2", this);
		cube top_d(Td(state_copy), "T'", this);
		cube dd(DD(state_copy), "D2", this);
		cube down_d(Dd(state_copy), "D'", this);
		// cout << "Compiling next states into an array...\n";
		cube* arr;
		arr = new cube[18];
		arr[0] = right; arr[1] = left; arr[2] = rr; arr[3] = ll; arr[4] = right_d; arr[5] = left_d; arr[6] = back; arr[7] = front; arr[8] = bb; arr[9] = tt; arr[10] = back_d; arr[11] = front_d; arr[12] = top; arr[13] = down; arr[14] = tt; arr[15] = dd; arr[16] = top_d; arr[17] = down_d;
		return arr;
	}
		
};

const string cube::colors[6]= {"WHITE", "RED", "GREEN", "ORANGE", "BLUE", "YELLOW"};
