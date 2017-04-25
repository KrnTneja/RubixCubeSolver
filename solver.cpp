/*
Solves the cube:
	Functions:
		takeInputCube: 		called when user input is to be taken, return an instance of cube after checking if cube is valid 
			and not solved already.
	
		main:
			take user input (should be valid and not solved already)
			initialize hashtable with user input where key value is string representation (using represent function) of cube and 
				value is pointer of that cube. (LET US USER IN-BUILT C++ HASHTABLE FOR NOW.)
			initialize queue with user input with value as pointer of user input
			while not solved:
				store top of queue (say 'currentCube') and pop it from queue
				iterate over currentCube.nextPossible():
					if next state is not solved:
						if next state is not in hashtable:
							add next state to hash table
							add next state to queue
					else if next state is solved:
						break and return the complete solution (HOW TO RETURN COMPLETE SOLUTION? - NEED TO THINK ABOUT.)
*/

#include "cube.h"
#include <unordered_map>
#include <string>
#include <queue>

using namespace std;

vector<string> solve() {
	cube init_state; // Will call the initializer of cube which will take the input
	clea
unordered_map<string, bool> explored;
	explored[init_state.represent()] = true;
	queue<cube> q;
	q.push(init_state);
	while(q.size() > 0) {
		cube top = q.front(); q.pop();
		cube* nextPossibleStates = top.nextPossible();
		for (int i = 0; i < 18; i++) {
			if (nextPossibleStates[i].solved()) {
				return nextPossibleStates[i].steps();
			} else {
				if (!explored[cube[i].represent()]) {  // 
					explored[cube[i].represent] = true;
					q.push(cube[i]);
				}
			}
		}
	}
}

int main() {
	vector<string> solution = solve();
	for (int i = 0; i < solution.size(); i++) {
		cout << solution[i];
	}
}
