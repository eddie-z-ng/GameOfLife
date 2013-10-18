/*********************

Conway's Game of Life

Eddie Ng
Date: 8/8/13

 An implementation of Conway's Game of Life in C and using
 a very basic portion of the ncurses lib to add diamonds to the
 representing live cells to the standard windows and to 
 change colors every tick

 (Specify columns and rows on commandline)

*********************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <curses.h>


static void showBoard(void *refBoard, int rows, int columns);
static void runBoard(void *refBoard, int rows, int columns);
static void finish(int sig);

typedef struct {
    char liveneighbors;
    char alive;
} CELL;


int main(int argc, char **argv)
{
    int i = 0, j = 0, n = 0;
    int rows = 0, columns = 0;

    if (argc > 1)
        columns = atoi(argv[1]);
    if (argc > 2)
        rows = atoi(argv[2]);

    if (columns <= 0)
        columns = 50;
    if (rows <= 0)
        rows = 50;

    CELL gboard[rows][columns];

    (void) signal(SIGINT, finish);      /* arrange interrupts to terminate */

    (void) initscr();      /* initialize the curses library */
    (void) nonl();         /* tell curses not to do NL->CR/NL on output */
    (void) cbreak();       /* take input chars one at a time, no wait for \n */

    if (has_colors())
    {
        start_color();
        init_pair(1, COLOR_RED,     COLOR_BLACK);
        init_pair(2, COLOR_GREEN,   COLOR_BLACK);
        init_pair(3, COLOR_YELLOW,  COLOR_BLACK);
        init_pair(4, COLOR_BLUE,    COLOR_BLACK);
        init_pair(5, COLOR_CYAN,    COLOR_BLACK);
        init_pair(6, COLOR_MAGENTA, COLOR_BLACK);
    }

    /* Blinker example */
    /*
       for (i=0; i< rows; i++)
    {
        gboard[i][0].alive = 0;
        gboard[i][1].alive = 1;
        gboard[i][2].alive = 0;
    }  
    */

    /* Sorta randomly populate the board */
    for(i=0; i<rows; i++)
    {
        for (j=0; j<columns; j++)
        {
            gboard[i][j].alive = (rand() % 1000) % 2;
       }
    }
    
   while (true)
   {
       /* Change colors every screen update! */
       attrset(COLOR_PAIR(n % 6 + 1));

       showBoard(gboard, rows, columns);
       runBoard(gboard, rows, columns);   
       usleep(400000);
       n++;
   }

    finish(0);          
    return 0;
}

/* Pass a pointer to the whole board -- pointer to array of size "columns"*/
/* Method # 2 in */
/* www.ibiblio.org/pub/languages/fortran/append-c.html */
static void showBoard(void *refBoard, int rows, int columns)
{
    int x, y;
    CELL (*board)[columns] = refBoard;

    erase(); // Clear the stdscr window 
    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < columns; x++)
        {
            if(board[y][x].alive)
                addch(ACS_DIAMOND | A_STANDOUT);
            //    addch(' '|A_REVERSE);
            else
                addch(' ');
        }
        printw("\n");
    } 
    refresh(); // Reupdate the stdscr window
}

static void runBoard(void *refBoard, int rows, int columns)
{
    int x,y, xn, yn;
    CELL (*board)[columns] = refBoard;

    /* Count liveneighbors */
    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < columns; x++)
        {
            board[y][x].liveneighbors = 0;

            // Count up all the live cells in a 3x3 square (includes this cell itself)
            for (yn = y-1; yn <= y+1; yn++)
            {
                for (xn = x-1; xn <= x+1; xn++)
                {
                    if (xn < 0 || yn < 0 || xn >= columns || yn >= rows)
                        continue;

                    if (board[yn][xn].alive)
                        board[y][x].liveneighbors++;
                }

            }
            // We counted ourself as a live neighbor so decrement once
            if (board[y][x].alive)
                board[y][x].liveneighbors--;
        }
    }

    /* Spawn, keep, or kill the cells */
    for (y = 0; y < rows; y++)
    {
        for (x = 0; x < columns; x++)
        {
            // Rules:
            // 1. Spawn/Keep live cell if surrounded by 3
            // 2. Keep live cell with 2 neighbors 
            // 3. Kill cell otherwise 
            board[y][x].alive = ( (board[y][x].liveneighbors == 3) ||
                    ((board[y][x].liveneighbors == 2) && (board[y][x].alive)) );
        }
    }
}


/* Exit game */
static void finish(int sig)
{
    endwin();
    exit(0);
}
