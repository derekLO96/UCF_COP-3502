#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct spellingbee
{
    char* lettersInGame;
    char requiredLetter;
}spellingbee;

typedef struct validWordsStruct
{
    char* validWord;

    struct validWordsStruct* next;

}validWordsStruct;

spellingbee* BuildSpellingBeeStruct(char* spellingbeeLetters);
validWordsStruct* PlayGame(int wordCount , spellingbee* spellingbeeStructPointer);
char* SortAlphabetical(char* wordToBeSorted);
validWordsStruct* AddToLinkedList( validWordsStruct* validWordStruct , char* wordToBeChecked , spellingbee* spellingbeeStructPointer);
validWordsStruct* NodeFactory(char* wordToBeChecked);
validWordsStruct* CheckWordValidity(validWordsStruct* validWords, spellingbee* spellingbeeStructPointer);
int CheckForSpecialCharacter(validWordsStruct* temporary , char specialCharacter);
void printLinkedList(validWordsStruct* validWords);

int main()
{
    int wordCount = 0;
    char* spellingbeeLetters = malloc(51 * sizeof(char));
    scanf("%s" , spellingbeeLetters);
    spellingbeeLetters = SortAlphabetical(spellingbeeLetters);

    spellingbee* spellingbeeStructPointer = BuildSpellingBeeStruct(spellingbeeLetters);    

    scanf("%d" , &wordCount);
    validWordsStruct* validWords = PlayGame(wordCount , spellingbeeStructPointer);


    printLinkedList(CheckWordValidity(validWords, spellingbeeStructPointer));


    printf("\n");
    

    return 0;

}

//TO DO: figure out where this goes
//binary search algorithm from class to find the words?
int binsearch(char** words, int begginingOfSearch, int endOfSearch, char* target) {

    // Empty search space.
    if (begginingOfSearch > endOfSearch) return -1;

    int middleOfSearch = (begginingOfSearch+endOfSearch)/2;

    // Save this since we need it twice.
    int cmp = strcmp(target, words[middleOfSearch]);

    // target must be in left side of array.
    if (cmp < 0)
        return binsearch(words, begginingOfSearch, middleOfSearch-1, target);

    // right side...
    else if (cmp > 0)
        return binsearch(words, middleOfSearch+1, endOfSearch, target);

    // We found it!
    else
        return middleOfSearch;
}

//helper function that uses recursion to print out each node in our linked list.
void printLinkedList(validWordsStruct* validWordsStructPointer)
{
        if(!validWordsStructPointer) return;
        printf("\t%s\n" , validWordsStructPointer->validWord);
        printLinkedList(validWordsStructPointer->next);

        
}
validWordsStruct* CheckWordValidity(validWordsStruct* validWords, spellingbee* spellingBeeStruct)
{
    validWordsStruct* validWordStructLinkedList;

    validWordsStruct* head = validWords;
    while(validWords->next != NULL)
    {
        validWordsStruct* temporary = validWords;

        if(CheckForSpecialCharacter(temporary , spellingBeeStruct->lettersInGame[3]))
        {

        }
        else
        {
            

        }

    }


    return validWordStructLinkedList;
}

//sorts a string into alphabetical order.
char* SortAlphabetical(char* wordToBeSorted)
{
    //store the string length
    int wordLength = strlen(wordToBeSorted);

    //loop through the word keeping two indexes, we compare the first letter to all other
    //letters in the word and see which one has the lowest value, indicating it comes first in the alphabet
    //then we step through to the other letters until we reach the end of the word.
    for(int i = 0 ; i < wordLength ; i++)
    {
        for(int j = (i + 1) ; j < wordLength ; j++)
        {
            char temporaryCharacter = wordToBeSorted[i];
            if(wordToBeSorted[j] < temporaryCharacter)
            {
                wordToBeSorted[i] = wordToBeSorted[j];
                wordToBeSorted[j] = temporaryCharacter;
            }
        }

    }

    return wordToBeSorted;

}


//simple helper function that returns 1(True) if the special spellingbee character is in the string and 0(if its not)
int CheckForSpecialCharacter(validWordsStruct* temporary , char specialCharacter)
{
    for(int i = 0 ; i < strlen(temporary->validWord) ; i++)
    {
        if(temporary->validWord[i] == specialCharacter) return 1;

    }

    return 0;
}

//takes in a number of how many words in the game and the struct to the pellingbee characters(already sorted) to pass to a 
//helper function. 
//this function is just to return the already built final answer to our problem.
validWordsStruct* PlayGame(int wordCount , spellingbee* spellingbeeStructPointer)
{
    validWordsStruct* validWordsLinkedList = NULL;

    char* wordToBeChecked = malloc(51 * sizeof(char));

    if(wordCount < 1) return NULL;

    while(wordCount > 0)
    {
        scanf("%s" , wordToBeChecked);

        validWordsLinkedList = AddToLinkedList(validWordsLinkedList , wordToBeChecked , spellingbeeStructPointer);

        wordCount--;

        
    }

    free(wordToBeChecked);
    return validWordsLinkedList;

}

//simple helper funtion that returns a built struct
spellingbee* BuildSpellingBeeStruct(char* spellingbeeLetters)
{
    spellingbee* spellingbeeStructPointer = malloc(sizeof(spellingbee));

    spellingbeeStructPointer->lettersInGame = malloc(strlen(spellingbeeLetters) + 1);
    strcpy(spellingbeeStructPointer->lettersInGame , spellingbeeLetters);

    spellingbeeStructPointer->requiredLetter = spellingbeeLetters[3];

    return spellingbeeStructPointer;
}

//builds and returns a new node to the linked list
validWordsStruct* NodeFactory(char* wordToBeChecked)
{
    validWordsStruct* newNode = malloc(sizeof(validWordsStruct));
        newNode->validWord = malloc(strlen(wordToBeChecked) + 1);
        strcpy(newNode->validWord , wordToBeChecked);
        newNode->next = NULL;

    return newNode;

}


//takes in some parameters to append to the end of the linked list, maintaining the original order of 
//the input to the program(already in alphabetical order!)
validWordsStruct* AddToLinkedList(validWordsStruct* validWordStructPointer , char* wordToBeChecked, spellingbee* spellingbeeStructPointer)
{
        validWordsStruct* newNode = NodeFactory(wordToBeChecked);

        if(validWordStructPointer == NULL){
             return newNode;
            }

        validWordsStruct* headNode = validWordStructPointer;

        while(validWordStructPointer->next != NULL)
        {
            validWordStructPointer = validWordStructPointer->next;

        }

        validWordStructPointer->next = newNode;

        return headNode;

}


