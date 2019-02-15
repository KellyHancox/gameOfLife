#include "life.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * get_grid creates new memory for a "grid".
 * x is the height and y is the width.
 */
char** get_grid(int x, int y){

    //Creates a new x by y grid, allocating all memory
    //through malloc. Checks for errors and exits gracefully with appropriate return message if
    //memory cannot be allocated. Returns the grid.

    //when could it not be allocated?

    char** board;
    board = malloc( y * sizeof( char* ) ) ;  // Statement 1

    for( int i=0; i < x; ++i )
    {
        board[i] = malloc(y) ; // Statement 2
    }

    return board;
}

/*
 * print_grid attempts to print an x height
 * by y width grid stored at the location
 * provided by grid
 */
void print_grid(int x, int y, char** grid){

    //Prints a human-readable grid.
    for(int i=0; i<x; ++i){
	    for(int j=0; j<y; ++j){
	        printf("%d",  grid[i][j]);
	        //printf("%c", 's');
	    }
        printf("\n");
    }

}

/*
 * Mutate takes a grid and mutates that grid
 * according to Conway's rules.  A new grid
 * is returned.
 */
char** mutate(int x, int y, char** grid) {


    //Given a grid, returns a new grid
    //with Conway’s rules applied to each cell.
    // This function will need to create a new grid; the old
    //grid should not be modified while being examined.

    char** newGrid;
    newGrid = malloc(y * sizeof(char *));  // Statement 1

    for (int i = 0; i < x; ++i) {
        newGrid[i] = malloc(y); // Statement 2
    }

    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {

            int neighbors = get_neighbors(i, j, x, y, grid);
            printf("At %d,%d, you have %d neighbors\n", i, j, neighbors);

            if (grid[i][j] == 1) {
                //cell is alive

                if (neighbors < 2 || neighbors > 3) {
                    newGrid[i][j] = 0;

                } else if (neighbors == 2 || neighbors == 3) {
                    newGrid[i][j] = 1;
                }
            }

            //cell is dead
            if (grid[i][j] == 0) {
                if (neighbors == 3) {
                    newGrid[i][j] = 1;
                }
            }

        }
    }


    return newGrid;
}

/* get_neighbors is a helper method that returns
 * the number of live neighbors a cell has.
 */
int get_neighbors(int i, int j, int x, int y, char** grid){

    int count = 0;

    //Given
    //a coordinate (i,j) and a grid, determine how many
    // neighbors the cell has. Return -1 if the cell
    //can’t exist in the grid. Correctly handle grid boundaries.

    //if out of bounds
    if(i < 0 || i > x || j < 0 || j > y){
        return -1;
    }

    //if in the middle
    else if((i > 0 && i < x-1) && (j > 0 && j < y-1)){
	    //up left i,j
        if(grid[i-1][j-1] == 1){
	        count = count + 1;
	    }
	    //above i,j
	    if(grid[i-1][j] == 1){
            count = count + 1;
	    }
	    //up right i,j
	    if(grid[i-1][j+1] == 1){
            count = count + 1;
	    }
	    //right i,j
	    if(grid[i][j+1] == 1){
            count = count + 1;
	    }
	    //down right i,j
	    if(grid[i+1][j+1] == 1){
            count = count + 1;
	    }
	    //down i,j
	    if(grid[i+1][j] == 1){
            count = count + 1;
	    }
	    //down left i,j
	    if(grid[i+1][j-1] == 1){
            count = count + 1;
	    }
	    //left i,j
	    if(grid[i][j-1] == 1){
            count = count + 1;
	    }

	    return count;
    }

    //checking bottom right corner
    else if(i == x-1 && j == y-1){
        //above i,j
        if(grid[i-1][j] == 1){
            count = count + 1;
        }
        //up left i,j
        if(grid[i-1][j-1] == 1){
            count = count + 1;
        }
        //left i,j
        if(grid[i][j-1] == 1){
            count = count + 1;
        }
        return count;
    }

    //check top right corner
    else if(i == 0 && j == y-1){
        //left i,j
        if(grid[i][j-1] == 1){
            count = count + 1;
        }
        //down i,j
        if(grid[i+1][j] == 1){
            count = count + 1;
        }
        //down left i,j
        if(grid[i+1][j-1] == 1){
            count = count + 1;
        }
        return count;
    }

    //check top left corner
    else if(i == 0 && j == 0){
        //right i,j
        if(grid[i][j+1] == 1){
            count = count + 1;
        }
        //down right i,j
        if(grid[i+1][j+1] == 1){
            count = count + 1;
        }
        //down i,j
        if(grid[i+1][j] == 1){
            count = count + 1;
        }
        return count;
    }

    //checking bottom Left corner
    else if(i == x-1 && j == 0){
        //above i,j
        if(grid[i-1][j] == 1){
            count = count + 1;
        }
        //up right i,j
        if(grid[i-1][j+1] == 1){
            count = count + 1;
        }
        //right i,j
        if(grid[i][j+1] == 1){
            count = count + 1;
        }
        return count;
    }

        //if we're from the bottom row but not in a corner
    else if(i == x-1){
        //right i,j
        if(grid[i][j+1] == 1){
            count = count + 1;
        }
        //left i,j
        if(grid[i][j-1] == 1){
            count = count + 1;
        }
        //up left i,j
        if(grid[i-1][j-1] == 1){
            count += 1;
        }
        //above i,j
        if(grid[i-1][j] == 1){
            count +=1;
        }
        //up right i,j
        if(grid[i-1][j+1] == 1){
            count += 1;
        }
        return count;
    }

    //if we're from the top row but not in a corner
    else if(i == 0){
        //right i,j
        if(grid[i][j+1] == 1){
            count = count + 1;
        }
        //left i,j
        if(grid[i][j-1] == 1){
            count = count + 1;
        }
        //down right i,j
        if(grid[i+1][j+1] == 1){
            count += 1;
        }
        //down i,j
        if(grid[i+1][j] == 1){
            count +=1;
        }
        //down left i,j
        if(grid[i+1][j-1] == 1){
            count += 1;
        }
        return count;
    }

    //if we're in furthest left row but not in a corner
    else if(j == 0){
        //above i,j
        if(grid[i-1][j] == 1){
            count = count + 1;
        }
        //down i,j
        if(grid[i+1][j] == 1){
            count = count + 1;
        }
        //up right i,j
        if(grid[i-1][j+1] == 1){
            count += 1;
        }
        //right i,j
        if(grid[i][j+1] == 1){
            count += 1;
        }
        //down right i,j
        if(grid[i+1][j+1] == 1){
            count += 1;
        }
        return count;
    }

    //if we're in furthest right row but not in a corner
    else if(j == y-1){
        //above i,j
        if(grid[i-1][j] == 1){
            count = count + 1;
        }
        //down i,j
        if(grid[i+1][j] == 1){
            count = count + 1;
        }
        //up left i,j
        if(grid[i-1][j-1] == 1){
            count += 1;
        }
        //down left i,j
        if(grid[i+1][j-1] == 1){
            count += 1;
        }
        //left i,j
        if(grid[i][j-1] == 1){
            count += 1;
        }
        return count;
    }

    else{
        return -1;
    }
}
