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

class cube {
	
}
