#include <iostream>
#include <fstream>
#include <string>
#include <vector>


#define WHITE 0
#define RED 1
#define GREEN 2
#define ORANGE 3
#define BLUE 4
#define YELLOW 5

typedef struct cube cube;

using namespace std;

int size = 3;

const string colors[6]= {"WHITE", "RED", "GREEN", "ORANGE", "BLUE", "YELLOW"}; 

struct cube {
	vector<vector<vector<short> > > state; //the state of the cube is represented by a 6*3*3 array
	//0:White(Front), 1:Red(Top), 2:Green(Right), 3:Orange(Bottom), 4:Blue(Left), 5:Yellow(Back)
	string const lastStep;
	cube* const parent;

	cube() : lastStep(""), parent(NULL) {}
	cube(vector<vector<vector<short> > > arr, string givenLastStep, cube* givenParent) : lastStep(givenLastStep), parent(givenParent), state(arr) {} 
};

// VALIDATE
bool validate(cube const &aCube) {
	return true;
}

// CUBE IS SOLVED?
bool solved(cube const *aCube) {
	for (int i = 0; i < 6; i++) {
		// check if all match the center element
		for (int j = 0; j < size; j++) {
			for (int k = 0; k < size; k++) {
				if (aCube->state[i][j][k] != aCube->state[i][1][1]) return false;
			}
		}
	}
	return true;
}

// REPRESENTATION OF STATE IN FORM OF STRING
string represent(cube const *aCube) {
	string r = "";
	for (short i = 0; i < 6; i++) {
		for (short j = 0; j < size; j++) {
			for (short k = 0; k < size; k++) {
				r += to_string(aCube->state[i][j][k]);
			}
		}
	}
	return r;
}

// PRINT THE STATE, BEAUTIFIED
void print6tabs() { for(int i = 0; i < size; i++) cout << "\t";}
void printWithSpace(cube const *aCube, int face) {
	for (int i = 0; i < size; i++) {
		print6tabs();
		for (int j = 0; j < size; j++) cout << colors[aCube->state[face][i][j]] << "\t";
		cout << "\n";
	}
}
void print(cube const *aCube) {
	//0:White(Front), 1:Red(Top), 2:Green(Right), 3:Orange(Bottom), 4:Blue(Left), 5:Yellow(Back)
	// print RED 
	printWithSpace(aCube, 1);
	// print BLUE, WHITE, GREEN (4-0-2)
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) cout << colors[aCube->state[4][i][j]] << "\t";
		for (int j = 0; j < size; j++) cout << colors[aCube->state[0][i][j]] << "\t";
		for (int j = 0; j < size; j++) cout << colors[aCube->state[2][i][j]] << "\t";
		for (int j = 0; j < size; j++) cout << colors[aCube->state[5][i][j]] << "\t";
		cout << "\n";
	}
	// print ORANGE
	printWithSpace(aCube, 3);		
	// print YELLOW
	// printWithSpace(5);
}

// NEXT POSSIBLE STATES
vector<vector<vector<short> > > getStateCopy(vector<vector<vector<short> > > &state) {
	vector<vector<vector<short> > > state_copy;
	state_copy.resize(6);
	for(int i = 0; i < 6; i++) {
		state_copy[i].resize(size);
		for(int j = 0; j<size; j++) {
			state_copy[i][j].resize(size);
			for (int k = 0; k<size; k++) {
				state_copy[i][j][k] = state[i][j][k];
			}
		}
	}
	return state_copy;
}

vector<vector<vector<short> > > R(vector<vector<vector<short> > > state) {
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	for(int i =0; i< size;i++) {
		state_copy[WHITE][i][size-1] = state[ORANGE][i][size-1];
		state_copy[ORANGE][i][size-1] = state[YELLOW][size-1-i][0];
		state_copy[YELLOW][i][0] = state[RED][size-1-i][size-1];
		state_copy[RED][i][size-1] = state[WHITE][i][size-1];
		state_copy[GREEN][i][0] = state[GREEN][size-1][i];
		state_copy[GREEN][0][i] = state[GREEN][size-1-i][0];
		state_copy[GREEN][size-1][i] = state[GREEN][size-1-i][size-1];
		state_copy[GREEN][i][size-1] = state[GREEN][0][i];
	}
	return state_copy;
}

vector<vector<vector<short> > > L(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	for(int i =0; i< size;i++)
	{	state_copy[WHITE][i][0] = state[RED][i][0];
		state_copy[ORANGE][i][0] = state[WHITE][i][0];
		state_copy[YELLOW][i][size-1] = state[ORANGE][size-1-i][0];
		state_copy[RED][i][0] = state[YELLOW][size-1-i][size-1];
		state_copy[BLUE][i][0] = state[BLUE][size-1][i];
		state_copy[BLUE][i][size-1] = state[BLUE][0][i];
		state_copy[BLUE][0][i] = state[BLUE][size-1-i][0];
		state_copy[BLUE][size-1][i] = state[BLUE][size-1-i][size-1];
	}
	return state_copy;
}

vector<vector<vector<short> > > Rd(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return R(R(R(state_copy)));
	//state_copy = R(state_copy);
	//state_copy = R(state_copy);
	//return state_copy;
}

vector<vector<vector<short> > > Ld(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return L(L(L(state_copy)));
	//state_copy = L(state_copy);
	//state_copy = L(state_copy);
	//return state_copy;
}

vector<vector<vector<short> > > RR(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return R(R(state_copy));
}

vector<vector<vector<short> > > LL(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return L(L(state_copy));
}

vector<vector<vector<short> > > T(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	for(int i =0; i< size;i++)
	{	state_copy[WHITE][0][i] = state[GREEN][0][i];
		state_copy[GREEN][0][i] = state[YELLOW][0][i];
		state_copy[YELLOW][0][i] = state[BLUE][0][i];
		state_copy[BLUE][0][i] = state[WHITE][0][i];
		state_copy[RED][0][i] = state[RED][size-1-i][0];
		state_copy[RED][i][0] = state[RED][size-1][i];
		state_copy[RED][size-1][i] = state[RED][size-1-i][size-1];
		state_copy[RED][i][size-1] = state[RED][0][i];
	}
	return state_copy;
}

vector<vector<vector<short> > > D(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	for(int i =0; i< size;i++)
	{	state_copy[WHITE][size-1][i] = state[BLUE][size-1][i];
		state_copy[BLUE][size-1][i] = state[YELLOW][size-1][i];
		state_copy[YELLOW][size-1][i] = state[GREEN][size-1][i];
		state_copy[GREEN][size-1][i] = state[WHITE][size-1][i];
		state_copy[ORANGE][0][i] = state[ORANGE][size-1-i][0];
		state_copy[ORANGE][i][0] = state[ORANGE][size-1][i];
		state_copy[ORANGE][size-1][i] = state[ORANGE][size-1-i][size-1];
		state_copy[ORANGE][i][size-1] = state[ORANGE][0][i];
	}
	return state_copy;
}

vector<vector<vector<short> > > Td(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return T(T(T(state_copy)));
	//state_copy = R(state_copy);
	//state_copy = R(state_copy);
	//return state_copy;
}

vector<vector<vector<short> > > Dd(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return D(D(D(state_copy)));
	//state_copy = L(state_copy);
	//state_copy = L(state_copy);
	//return state_copy;
}

vector<vector<vector<short> > > TT(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return T(T(state_copy));
}

vector<vector<vector<short> > > DD(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return D(D(state_copy));
}

vector<vector<vector<short> > > F(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	for(int i =0; i< size;i++)
	{	state_copy[RED][size-1][i] = state[BLUE][size-1-i][size-1];
		state_copy[BLUE][i][size-1] = state[ORANGE][0][i];
		state_copy[ORANGE][0][i] = state[GREEN][size-1-i][0];
		state_copy[GREEN][i][0] = state[RED][size-1][i];
		state_copy[WHITE][0][i] = state[WHITE][size-1-i][0];
		state_copy[WHITE][i][0] = state[WHITE][size-1][i];
		state_copy[WHITE][size-1][i] = state[WHITE][size-1-i][size-1];
		state_copy[WHITE][i][size-1] = state[WHITE][0][i];
	}
	return state_copy;
}

vector<vector<vector<short> > > B(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	for(int i =0; i< size;i++)
	{	state_copy[RED][0][i] = state[GREEN][i][size-1];
		state_copy[BLUE][i][0] = state[RED][0][size-1-i];
		state_copy[ORANGE][size-1][i] = state[BLUE][i][0];
		state_copy[GREEN][i][size-1] = state[ORANGE][size-1][size-1-i];
		state_copy[YELLOW][i][size-1] = state[YELLOW][0][i];
		state_copy[YELLOW][size-1][i] = state[YELLOW][size-1-i][size-1];
		state_copy[YELLOW][i][0] = state[YELLOW][size-1][i];
		state_copy[YELLOW][0][i] = state[YELLOW][size-1-i][0];	
	}
	return state_copy;
}

vector<vector<vector<short> > > Bd(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return B(B(B(state_copy)));
}

vector<vector<vector<short> > > Fd(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return F(F(F(state_copy)));
}

vector<vector<vector<short> > > BB(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return B(B(state_copy));
}

vector<vector<vector<short> > > FF(vector<vector<vector<short> > > state){
	vector<vector<vector<short> > > state_copy = getStateCopy(state);
	return F(F(state_copy));
}

cube* getNewCube(vector<vector<vector<short> > > arr, string givenLastStep, cube* const givenParent) {
	cube* newCube = new cube(arr, givenLastStep, givenParent);
	return newCube;
}

cube** nextPossible(cube* const &aCube){
	vector<vector<vector<short> > > state_copy;
		state_copy.resize(6);
	for(int i = 0; i < 6; i++) {
		state_copy[i].resize(size);
		for(int j = 0; j<size; j++) {
			state_copy[i][j].resize(size);
			for (int k = 0; k<size; k++) {
				state_copy[i][j][k] = aCube->state[i][j][k];
			}
		}
	}

	// cout << "Done copying!\n";
	cube* right = getNewCube(R(state_copy), "R", aCube);
	// cout << "Parent pointer of " << right << " is " << aCube << "\n";
	// cout << "Last step of " << right << " is " << right->lastStep << "\n";
	// cout << "Parent pointer of parent " << aCube << " is " << aCube->parent << "\n";
	// cout << "Last step of parent " << aCube << " is " << aCube->lastStep << "\n";
	cube* left = getNewCube(L(state_copy), "L", aCube);
	cube* rr = getNewCube(RR(state_copy), "R2", aCube);
	cube* right_d = getNewCube(Rd(state_copy), "R'", aCube);
	cube* left_d = getNewCube(Ld(state_copy), "L'", aCube);
	cube* ll = getNewCube(LL(state_copy), "L2", aCube);
	cube* back = getNewCube(B(state_copy), "B", aCube);
	cube* front = getNewCube(F(state_copy), "F", aCube);
	cube* bb = getNewCube(BB(state_copy), "B2", aCube);
	cube* back_d = getNewCube(Bd(state_copy), "B'", aCube);
	cube* front_d = getNewCube(Fd(state_copy), "F'", aCube);
	cube* ff = getNewCube(FF(state_copy), "F2", aCube);
	cube* top = getNewCube(T(state_copy), "T", aCube);
	cube* down = getNewCube(D(state_copy), "D", aCube);
	cube* tt = getNewCube(TT(state_copy), "T2", aCube);
	cube* top_d = getNewCube(Td(state_copy), "T'", aCube);
	cube* dd = getNewCube(DD(state_copy), "D2", aCube);
	cube* down_d = getNewCube(Dd(state_copy), "D'", aCube);
	// cout << "Compiling next states into an array...\n";
	cube** arr;
	arr = new cube*[18];
	arr[0] = right; arr[1] = left; arr[2] = rr; arr[3] = ll; arr[4] = right_d; arr[5] = left_d; arr[6] = back; arr[7] = front; arr[8] = bb; arr[9] = tt; arr[10] = back_d; arr[11] = front_d; arr[12] = top; arr[13] = down; arr[14] = tt; arr[15] = dd; arr[16] = top_d; arr[17] = down_d;
	return arr;
}
