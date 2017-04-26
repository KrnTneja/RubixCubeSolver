#include "cube.h"
#include <unordered_map>
#include <string>
#include <queue>
#include <vector>

using namespace std;

vector<string> solve(string fileName) {
	// READ THE INPUT
	vector<vector<vector<short> > > init_state;
	int terminated = 0;
 	//cout << "Reading input...\n";
 	ifstream inpFile; inpFile.open(fileName);
	init_state.resize(6);
	for (int i = 0; i < 6; ++i) {
		init_state[i].resize(size);
		for (int j = 0; j < size; ++j) {
			init_state[i][j].resize(size);	
			for (int k = 0; k < size; ++k) {
				inpFile >> init_state[i][j][k];
			}
		}
	}
	// INITIALIZATIONS
	cube* init_cube = new cube(init_state, "", NULL); // Will call the initializer of cube which will take the input
	if (solved(init_cube)) {
		vector<string> steps;
		steps.insert(steps.begin(), "No steps, it's already solved!");
		return steps;
	}
	// cout << "Initializing hash table for cube representations...\n";
	unordered_map<string, bool> explored;
	// cout << "Putting up initial state into hash table...\n";
	explored[represent(init_cube)] = true;
	// cout << "Initializing queue for cube states...\n";	
	queue<cube*> q;
	// cout << "Putting up initial state into queue...\n";
	q.push(init_cube);
	// BFS
	// cout << "Starting exploration...\n";
	while(q.size() > 0) {
		cube* top = q.front(); q.pop();
		//cout << "Found at top... which came from " << top->lastStep << "\n";
		// print(top); 
		// cout << "Hunting for next states...\n";
		cube** nextPossibleStates = nextPossible(top);
		vector<vector<vector<short> > >().swap(top->state);
		// cout << "Iterating over 18 possible next moves...\n";				
		for (int i = 0; i < 18; i++) {
			// cout << "Came from " << nextPossibleStates[i]->lastStep << "\n";
			// print(nextPossibleStates[i]); 
		
			if (solved(nextPossibleStates[i])) {
				// BACKTRACING - ONLY PATH TO EXIT IF GIVEN CUBE IS UNSOLVED
				// cout << "\nSolved the problem, preparing stepwise solution...\n";
				vector<string> steps;
				cube* backTracer = nextPossibleStates[i];
				while (backTracer->parent != NULL) {
					steps.insert(steps.begin(), backTracer->lastStep);
					// print(backTracer);
					// cout << "\n";
					backTracer = backTracer->parent;
				}
				cout << "\nThere were " << terminated << " terminated nodes.\n";
				return steps;
			} else {
				if (explored.find(represent(nextPossibleStates[i])) == explored.end()) {  // 
					explored[represent(nextPossibleStates[i])] = true;
					q.push(nextPossibleStates[i]);
				} else terminated++;
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
	// cout << "Solved! Steps are...\n";
	cout << "\n";
	for (int i = 0; i < solution.size(); i++) {
		cout << solution[i] << " ";
	}
	cout << "\n";
	return 0;
}
