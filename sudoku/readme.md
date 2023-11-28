# Sudko Solver

This is a simple sudko solver written in python. It uses a backtracking algorithm to solve sudko puzzles, and it uses forward checking to speed up the backtracking algorithm.

## Code explanation

The code is contained within the 'sudko.ipynb' file and is within a class called 'SudkoSolver'. The class contains the following methods:

-   `__init__` - This is the constructor of the class. It takes a sudko puzzle as an argument. It will set the necessary variables for the class and will also check if the sudko puzzle is valid, after is has been solved.

-   `submatrix_box`, `submatrix_row`, `submatrix_column` - These methods makes use of the
    ```
    array[row_start:row_end, column_start:column_end]
    ``` 
    notation, in order to ger the part of the array the current cell is within. Also just using `:` as the start and end index will return the the whole row or column.
    For the `submatrix_box` method, we used a formula to get the start of the column and row of the box. The formula is:
    ```
    start = (index // 3) * 3
    end = start + 3 
    ```
    (3 is the size of the box)
    It will then return a 'flattened' version of the submatrix, using the 'reshape' method in numpy.

-   `possible_values` - This is called a forward checking method. It takes the box, row and column of the current cell as arguments. And it returns a list of possible values for the current cell.
    ```
    possible_values = np.setdiff1d(np.arange(1,10), np.concatenate((box, row, column)))
    ```
    This line of code is where all the magic happens. It will return a list of possible values for the current cell, by removing the values that are already present in all submatrix's from the list of numbers from 1 to 9.

-   `is_fully_valid` - This method is used to check if the entire sudko puzzle is solved and correct. It checks that every cell is valid, it will return a boolean.

-   `is_valid` - This method is used to check if the value that the backtracking algorithm is trying to place in the cell is valid. It takes the row, column, soduko and the value of the cell as arguments. It returns a boolean.

-   `backtracking` - This method is used to solve the sudko puzzle. Like the name suggests, it uses a backtracking algorithm to solve the sudko puzzle. It takes the partial soduko solution as an argument. And will recursively call itself until the sudko puzzle is solved, by placing a value in the cell, and then calling itself again. If the value is not valid, it will try the next value in the list of possible values. If there are no more possible values, it will return False, and the backtracking algorithm will try the next value in the previous cell and so on... If the sudko puzzle is solved (i.e. no more 0's), it will return True.


We also have a `sudoku_solver` function outside the class that takes a sudko puzzle as an argument. It will then create and return an instance of the SudkoSolver class, and it's solved sudko puzzle. This function is used so the testing code can still work.