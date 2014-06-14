/*
# Name			: Derek Pacula
# Class			: Intro To C
# Program #	: 2
# Due Bate		: October 25, 2013	
#
# Honor Pledge: ON my honor as a student of the University of Nebraska at Omaha, I have neither given or recieved
# any unauthorized help on this assignment.
#
#
# Email: derek@pacula.me
# NUID: 8416

#Colleagues: David Beavers, Chris Palwaski, Austin Koehler, Nick Vanderb.
*/



#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Prototype functions for the program*/
char** createPuzzle(int);
char** wordList(int, int*);
void fillWordSearch(char**, char*, int);
void fillForSolving(char**, int);
void searchPuzzle(char**, char**, char*, int, int, int, int);
void solvePuzzle(char**, char**, char **, int , int);
void solutionPrint(char**, int);


int main()
{
	/*Integer variables created to be used to loop in a row loop, to find the postion of the row in the 2d array, to find the column
	int the 2d array, to find the number of words, and to find how big the puzzle is */
	int x = 0;
	int row = 0;
	int column = 0;
	int numberOfWords = 0;
	int puzzleSize = 0;
	
	/*Char pointer to find out how long the puzzle is to be used to determine the actual size of the puzzle*/
	char* puzzleLength;
	
	/*Double char points to be used to fill in the Word Search Puzzle, to place in the Words required to be found in the word search
	and to create a final array with the solved values */
	char** wordSearchPuzzle;
	char** wordSearchWords;
	char** solvedPuzzle;
	
	/*This malloc call gets the actual length of the puzzle*/
	puzzleLength = (char*)malloc(sizeof(char) * 100);
	
	/*Fgets is called to find out the puzzle size and is allocated the memor*/
	fgets(puzzleLength, sizeof(char) * 101, stdin);
	
	/*While the puzzle index at postion x does not hit a \0 or null character it increments the variable puzzleSize to deterimne how 
	big the actual puzzle is. When it finally reaches the Null character the while loop terminates*/
	while(puzzleLength[x] != '\0')
	{
		if(puzzleLength[x] != ' ' && puzzleLength[x] != '\n')
		{
			puzzleSize++;
		}
	    x++;
	}
	
	/*These two items create the memory needed to store the puzzle array*/
	wordSearchPuzzle = createPuzzle(puzzleSize);
	fillWordSearch(wordSearchPuzzle, puzzleLength, puzzleSize);
    

	/*This creates the actual list of words to be found in the puzzle, along with the puzzle of words */
    wordSearchWords = (char**)wordList(puzzleSize, &numberOfWords);
    solvedPuzzle = createPuzzle(puzzleSize);

    
	/*This just creates placeHolders for the solution of the word serach. The array will be filled later*/
	fillForSolving(solvedPuzzle, puzzleSize);
	
	
	/*Function call to solve the puzzle*/
	solvePuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords, numberOfWords, puzzleSize);	
	/*Function that prints out the final Solution*/
	solutionPrint(solvedPuzzle, puzzleSize);
	
	
	return 0;
    
	
}

/*creates the memory needed for the puzzle size. it is passed PuzzleSize so that it does not create memory more then needed */
char** createPuzzle(int puzzleSize)
{
    char** puzzleCreated;
    int x;
    
    puzzleCreated = (char**)malloc(sizeof(char*) * puzzleSize);
    
    for (x = 0; x < puzzleSize; x++)
    {
        puzzleCreated[x] = (char*)malloc(sizeof(char) * puzzleSize);
    }
    
    return puzzleCreated;
}

/*Fills the array empty for a place holder for the actual puzzle */
void fillForSolving(char** puzzleHolder, int puzzleSize)
{
    int x = 0;
    int y = 0;
    
	for(x = 0; x < puzzleSize; x++)
	{
		for(y = 0; y < puzzleSize; y++)
		{
			puzzleHolder[x][y] = ' ';
		}
	}
	
	
}

/*Creates the list of words from fgets and the standard libraby, it terminates when it reaches a null character or end of file */
char **wordList(int puzzleSize, int* numberOfWords)
{
    char** WordListArray;
    char* letters;
    int x = 0;
    int y = 0;
    
    letters = malloc(puzzleSize * sizeof(char));
    WordListArray = (char**)malloc(sizeof(char*));
    
    /*Keeps looping till fgets reaches null character or EOF*/
	while(fgets(letters, sizeof(char) * puzzleSize, stdin) != '\0')
    {
        WordListArray[x] = (char*)calloc(strlen(letters), sizeof(char));
        
        for(y = 0; y < strlen(letters) + 1; y++)
        {
            if(letters[y] != '\n')
            {
                WordListArray[x][y] = letters[y];
            }
        }
        
        x++;
        WordListArray = (char**)realloc(WordListArray, sizeof(char*) * (x + 1));
    }
    
    free(letters);
    *numberOfWords = x;
    return WordListArray;
}

/*Fills the actual puzzle with characters to be used for the word search */
void fillWordSearch(char** wordSearchPuzzle, char *wordLine, int puzzleSize)
{
    int x = 0;
    int postion = 1;
    
    for (x = 0; x < puzzleSize; x ++)
    {
        wordSearchPuzzle[0][x] = wordLine[x * 2];
    }
    
	char* letters = malloc(sizeof(char) * (puzzleSize * 2));
	do
    {
        fgets(letters, 100, stdin);
        for(x = 0; x < puzzleSize; x++)
        {
            wordSearchPuzzle[postion][x] = letters[x * 2];
        }
        postion++;
    }while(postion < puzzleSize);
    
    free(letters);
}

/*Function that itrates through the puzzle size and the number of words to solve the Word Search Puzzle */
void solvePuzzle(char**wordSearchPuzzle, char**solvedPuzzle, char **wordSearchWords, int numberOfWords, int puzzleSize)
{
	int x = 0;
	int row = 0;
	int column = 0;
	
	for(x = 0; x < numberOfWords; x++)
		{
			for (row = 0; row < puzzleSize; row++)
			{
				for(column = 0; column < puzzleSize; column++)
				{
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 1); 
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 2); 
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 3); 
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 4); 
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 5);
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 6);
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 7);
					searchPuzzle(wordSearchPuzzle, solvedPuzzle, wordSearchWords[x], puzzleSize, row, column, 8);
				}
			}
		}
		
}


/*Solves the puzzle by reading in the words and the wordSeaerch puzzle. It creates a temporary boolean value that passes if 1 it is true, if zero false. It also creates UP or down variable as well as left or right variables. These allow us to search the puzzle for the word. */

void searchPuzzle(char** wordSearch, char** solvedPuzzle, char* wordToFind, int puzzleSize, int passRow, int passColumn, int direction)
{
    /*Creates a fake boolean value. 1 for true. 0 for false*/
	int boolean = 1;

    int upOrDown = 0;
    int leftOrRight = 0;
    int x = 0;
    int row = passRow;
    int column = passColumn;
    
  
	/*Looks in the upwards direction for the word */
	if(direction == 1)
    {
        upOrDown = -1;
    }

	/*Looks to the bottom from the first letter for the word */
    else if(direction == 2)
    {
        upOrDown = 1;
    }

	/*Looks to the right for a word */
    else if(direction == 3)
    {
        leftOrRight = 1;
    }

	/*looks to the left for a word*/
    else if(direction == 4)
    {
        leftOrRight = -1;
    }

	/*Looks in the up and to the right direction */
    else if (direction == 5)
    {
        upOrDown = -1;
        leftOrRight = 1;
    }

	/*looks into the up up and left direction */
    else if (direction == 6)
    {
        upOrDown = -1;
        leftOrRight = -1;
    }

	/*Looks into the down and right postion */
    else if(direction == 7)
    {
        upOrDown = 1;
        leftOrRight = 1;
    }

	/*Looks into the down and left position */
    else if(direction == 8)
    {
        upOrDown = 1;
        leftOrRight = 1;
    }

	/*Default case. this should never reach */
    else
    {
        upOrDown = 0;
        leftOrRight = 0;
    }
    
    /*this for loop determines the word to be found. it uses string length to find the length of the word and then iterates through a foor
	loop to be less then the word. if the word is out size the index value the boolean value gets set to 0 or false. it can only contiune until
	the statement is true*/
	for (x = 0; x <strlen(wordToFind); x++)
    {
        if (boolean == 0)
        {
            break;
        }
        
        else if(row < 0 || row >= puzzleSize || column < 0 || column >= puzzleSize)
        {
            boolean = 0;
        }
        
        else if (wordToFind[x] == wordSearch[row][column])
        {
            row = row + leftOrRight;
            column = column + upOrDown;
        }
        
        else
        {
            boolean = 0;
        }
    }
    
	
	/*If the boolean becomes true, aka not 0 then the character is matched to become a space and then it looks for the next letter, if the letter
	is not found it resets and looks for a different direction*/
    if (boolean != 0)
    {
        for (x = 0; x < strlen(wordToFind); x++)
        {
            solvedPuzzle[passRow][passColumn] = wordToFind[x];
            passRow = passRow + leftOrRight;
            passColumn = passColumn + upOrDown;
        }
    }
    
}

/*prints the solution to the word search. uses the assumption the user will use stdout */
void solutionPrint(char** solvedPuzzle, int puzzleSize)
{
	int x = 0;
	int y = 0;
	
	for(x = 0; x < puzzleSize; x++)
		{
			for(y = 0; y < puzzleSize; y++)
			{
				printf("%c ", solvedPuzzle[x][y]);
			}
			puts("");
		}

}



