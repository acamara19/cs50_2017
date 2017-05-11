/**
 * fifteen.c
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE *file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = get_int();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    //assign the last element of the array to tile
    int tile = d*d;
    
    // outer and inner for loop to iterate through rows and columns
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            //initialize the array in a decreamented order from the largest to smallest 
            board[i][j] = --tile;
        }
        //check if the board created has an even numbers of tiles, then swap the value of 1 and 2
        if(d*d %2 == 0)
        {
            int temp = board[d-1][d-2];
            board[d-1][d-2] = board[d-1][d-3];
            board[d-1][d-3] = temp;
        }
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    // outer and inner for loop to iterate through rows and columns
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            //if board of row and column is equal to "0", replace the "0" with "_"
            if(board[i][j] == 0)
            {
                printf(" |  _");
            }
            else
            {
                //otherise, print the 2 dimentional array
                printf(" | %2i", board[i][j]);
            }
        }
    //prints 2 spaces of new line to screen
    printf("\n\n");
    }
    
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    // check to make sure the tiles are within the correct bound
    if(tile > d*d - 1 || tile < 1)
    {
        return false;
    }
    
    //creates two variable rows and column
    int row, col;
    
    // outer and inner for loop to iterate through rows and columns
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            //check the current state of the tile and assign i to rows and j to columns
            if(board[i][j] == tile)
            {
                row = i;
                col = j;
            }
        }
    }
    
    //check around the current tile to see if it's next to a zero
    if(row - 1 >= 0 && board[row - 1][col] == 0)
    {
        board[row - 1][col] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    else if( row + 1 < d && board[row + 1][col] == 0)
    {
        board[row + 1][col] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    else if(col - 1 >= 0 && board[row][col - 1] == 0)
    {
        board[row][col - 1] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    else if(col + 1 < d && board[row][col + 1] == 0)
    {
        board[row][col + 1] = board[row][col];
        board[row][col] = 0;
        return true;
    }
    
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    //initial variable count and set it to "0"
    int count = 0;
    // outer and inner for loop to iterate through rows and columns
    for(int i = 0; i < d; i++)
    {
        for(int j = 0; j < d; j++)
        {
            //check to current state of the board to see if the 2d array is in correct order from 1 - (d*d - 1)
            if (++count != (d * d) && board[i][j] != count)
            {
                return false;
            }
        }
    }
    return true;
}
