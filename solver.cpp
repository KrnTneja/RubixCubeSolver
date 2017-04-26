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

vector<string> solve(string fileName) {
	cube init_state = cube(fileName); // Will call the initializer of cube which will take the input
	cout << "Initializing hash table for cube states...\n";
	unordered_map<string, bool> explored;
	cout << "Putting up initial state into hash table...\n";
	explored[init_state.represent()] = true;
	cout << "Initializing queue for cube states...\n";	
	queue<cube> q;
	cout << "Putting up initial state into queue...\n";
	q.push(init_state);
	cout << "Starting exploration...\n";
	while(q.size() > 0) {
		cube top = q.front(); q.pop();
		// cout << "Found at top... which came from " << top.lastStep << "\n";
		// top.print();
		if (top.solved()) {
			vector<string> steps;
			steps.insert(steps.begin(), "No steps, it's already solved!");
			return steps;
		} 
		// cout << "Hunting for next states...\n";
		cube* nextPossibleStates = top.nextPossible();
		// cout << "Iterating over 18 possible next moves...\n";				
		for (int i = 0; i < 18; i++) {
			if (nextPossibleStates[i].solved()) {
				cout << "\nSolved the problem, preparing stepwise solution...\n";
				vector<string> steps;	
				steps.insert(steps.begin(), nextPossibleStates[i].lastStep);
				cube* theParent = nextPossibleStates[i].parent; 
				while (theParent->lastStep != (theParent->parent)->lastStep) {
					steps.insert(steps.begin(), theParent->lastStep);
					theParent = theParent->parent;
				}
				steps.insert(steps.begin(), theParent->lastStep);
				return steps;
			} else {
				if (!explored[nextPossibleStates[i].represent()]) {  // 
					explored[nextPossibleStates[i].represent()] = true;
					q.push(nextPossibleStates[i]);
				} // else cout << "Already explored!\n";
			}
		}
		cout << "\rExplored " << explored.size() << " nodes";
		// for (unordered_map<string, bool>::iterator itr = explored.begin(); itr != explored.end(); itr++) {
		// 	cout << itr->first << " " << itr->second << "\n";
		// }
	}
}

int main(int argc, char *argv[]) {
	vector<string> solution = solve(string(argv[1]));
	cout << "Solved! Steps are...\n";
	for (int i = 0; i < solution.size(); i++) {
		cout << solution[i] << "  ";
	}
	cout << "\n";
	return 0;
}
