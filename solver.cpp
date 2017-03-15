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

cube takeInputCube() {

}

int main() {
}
