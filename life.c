#include "life.h"
#include <stdio.h>
#include <stdlib.h>

/**********************************************************************
 * Creates new memory for a "grid".
 * x is the height and y is the width.
 * @param x width
 * @param y height
 * @return char** double array
 **********************************************************************/
char** get_grid(int x, int y){

    //Creates a new x by y grid, allocating all memory
    //through malloc. Checks for errors and exits
    //gracefully with appropriate return message if
    //memory cannot be allocated. Returns the grid.

    char** board;
    board = malloc( y * sizeof( char* ) ) ;

    for( int i=0; i < x; ++i )
    {
        board[i] = malloc(y) ;
    }

    return board;
}

/*
 * print_grid
 */
/*********************************************************************
 * Attempts to print an x height by y width grid stored at
 * the location provided by grid
 * @param x width
 * @param y height
 * @param grid gol board
 ********************************************************************/
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
 *
 */
/*********************************************************************
 * Mutate takes a grid and mutates that grid
 * according to Conway's rules.  A new grid is returned.
 * @param x width
 * @param y height
 * @param grid old grid
 * @return new grid
 *********************************************************************/
char** mutate(int x, int y, char** grid) {

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

/*
 
 */
/********************************************************************
 * Helper method that returns the number of live neighbors a cell has
 * @param i given coordinate row
 * @param j given coordinate column
 * @param x number of rows
 * @param y number of columns
 * @param grid board
 * @return returns how many neighbors from i,j are alive
 */
int get_neighbors(int i, int j, int x, int y, char** grid){

    int count = 0;

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

    //in case any checks failed
    else{
        return -1;
    }
}
