*** Requires ncurses library
   Cygwin under Windows: Install the ncurses devel package 
   Ubuntu: sudo apt-get install libncurses5-dev libncursesw5-dev 


1) Copy all files into the same directory
2) $ make
3) $ ./game 30 30

Note: The board may look strange if you specify dimensions larger than your terminal window

You may specify the columns and rows of board by passing these as arguments
on the command line, respectively
$ ./game 30 30

Conway's Game of Life:
-The board is populated randomly with live cells
-Each tick, the cells live or die based on the following rules:
  a) If a cell is alive and surrounded by 2 live cells, stay alive
  b) If a cell is surrounded by 3 live cells, stay/become alive
  c) If a cell is surrounded by any other number, the cell is dead
-Every tick the color of the cells change
