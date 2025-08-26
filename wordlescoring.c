
//  Derek Oliveira 
//  UCDID: 5768501 
//  08/20/2025

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


//Define boundires within my array
#define MAXLETTERCOUNT 5
#define MAXSAMPLESIZE 1000
#define MAXALPHABETSIZE 26


//this struct will be keeping score of our letters
typedef struct
{
    char letter;
    int points;

}LetterStruct;

char** SetupWordleArray(int numberOfWords);
void PrintGrade(char** wordleSetMain, LetterStruct* wordlePointsArrayMain, int numberOfWords, int sizeOfStruct);
LetterStruct* GradeWordlePuzzle(char** wordleSet, int NumberOfWords, int* sizeOfStruct);


int main(void) {

    char currentLetter;
    int numberOfWords;
    int sizeOfStruct = 0;

    printf( "\nWelcome to the wordle scoring program!" );
    printf( "\nProvide the number of words to be scored: " );
    scanf( "%d" , &numberOfWords );

    //build our wordle puzzle on runtime. The function will dynamically allocate memory to the two dimentional pointer.
    char** wordleSetMain = SetupWordleArray(numberOfWords);

    //declare our wordle points array and references the memory location of the graded wordle puzzle in main for easy freeing of memory.
    LetterStruct* wordlePointsArrayMain = GradeWordlePuzzle(wordleSetMain, numberOfWords , &sizeOfStruct);

    PrintGrade(wordleSetMain, wordlePointsArrayMain, numberOfWords, sizeOfStruct);

    //free all the memory previously allocated
    for (int i = 0; i < numberOfWords; i++) 
    {
        free(wordleSetMain[i]);
    }
    free(wordleSetMain);
    free(wordlePointsArrayMain);
    return 0;
}

//function that prints out the resulted grae point for each word.
void PrintGrade(char** wordleSetMain, LetterStruct* wordlePointsArrayMain, int numberOfWords, int sizeOfStruct)
{
    //loops through the the wordle set for grading
    for(int i = 0; i < numberOfWords; i++)
    {

        int totalWordPoints = 0;

        for(int j = 0 ; j < MAXLETTERCOUNT; j++)
        {
            //stores the letter in a variable for quick access
            char letter = wordleSetMain[i][j];

            for(int k = 0; k < sizeOfStruct ; k++)
            {

                //if we find the letter add that to the total points for the word
                if(wordlePointsArrayMain[k].letter == letter)
                {

                    totalWordPoints += wordlePointsArrayMain[k].points;
                }

            }

        }
        printf("%s\t%d\n" , wordleSetMain[i] , totalWordPoints);

    }


}

//Function that grades letters based on their frequencies found in a wordle puzzle. 
//Takes in the wordle set (2d array) and the number of words in the puzzle
LetterStruct* GradeWordlePuzzle(char** wordleSet, int numberOfWords, int* sizeOfStruct)
{
    LetterStruct* gradedWordlePuzzle = NULL;

    //loops that go through the different dimentions of the wordle puzzle array.
    for (int i = 0 ; i < numberOfWords ; i++ )
    {
        //define the length of the word on this row and stores it for easy access later.
        int len = strlen(wordleSet[i]);

        for (int j = 0; j < len ; j++)
        {
            //I save the character into a variable and an integer value that keeps tract is a letter has been found already or not.
            char characterToBeGraded = wordleSet[i][j];
            int found = 0;

            //this loop is for the struct, going through each letter that is found dynamically.
            for(int k = 0; k < * sizeOfStruct ; k++)
            {

                //were checking if we already found the letter previously
                if(gradedWordlePuzzle[k].letter == characterToBeGraded)
                {
                    gradedWordlePuzzle[k].points ++;
                    found = 1;
                    //if we found the letter, no need to keep looping through.
                    break;

                }

            }

            //here we have reached the end of the struct array and still haven't recorded the letter being graded.
            //so we re-allocate the space needed for this growing list. 
            if(!found)
            {
                //I use realloc to allocate more memory for the struct array and set each of the variable on the new 
                //struct.
                gradedWordlePuzzle = realloc(gradedWordlePuzzle, (*sizeOfStruct+1) * sizeof(LetterStruct));
                gradedWordlePuzzle[*sizeOfStruct].letter = characterToBeGraded;
                gradedWordlePuzzle[*sizeOfStruct].points = 1;
                (*sizeOfStruct)++;

            }


        }

    }


    //I return the pointer to the memory of the dynamic array for an organized way to freeing up memory.
    return gradedWordlePuzzle;

}


//This function will build the wordle Array based on the input of the user. I also use a buffer to make sure that the input is in an acceptable format.
char** SetupWordleArray(int numberOfWords)
{
    //use dynamic allocation for setting up the wordle array
    char** wordleSet = (char**) malloc(numberOfWords * sizeof(char*));
    //buffer for formating
    char buffer[100];
    int len;

    //looping through to allocate memory for each word. we have a max of 5 charachters plus 1 for the 'end-of-the-line' character
    for (int i = 0 ; i < numberOfWords ; i++)
    {
        wordleSet[i] = malloc((MAXLETTERCOUNT + 1) * sizeof(char));
    }   
    
    printf("\nProvide the %d words to be graded...\n" , numberOfWords);
    getchar();


    for (int i = 0 ; i < numberOfWords; i++)
    {
        printf("word #%d :", i+1);
        fgets(buffer , sizeof(buffer), stdin);

        //sets every letter that was inputed to
        for (int j = 0 ; j < MAXLETTERCOUNT ; j++)
        {
           
            buffer[j] = (char)tolower(buffer[j]);
            

        }
        strcpy(wordleSet[i] , buffer);
        wordleSet[i][MAXLETTERCOUNT] = '\0';
        
    }
        
    return wordleSet;

}
