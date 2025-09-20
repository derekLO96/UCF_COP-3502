//  Derek Oliveira
//  09/20/2025
//  p2

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct spellingbeeStruct
{
    char* lettersInGame;
    char requiredLetter;

}spellingbeeStruct;

typedef struct validWordsStruct
{
    char* validWord;

    struct validWordsStruct* next;

}validWordsStruct;


spellingbeeStruct* BuildSpellingBeeStruct(char* spellingbeeLetters);

char** PlayGame(int wordCount);
char* SortAlphabetical(char* wordToBeSorted);

validWordsStruct* AddToLinkedList( validWordsStruct* validWordStruct , char* wordToBeChecked);
validWordsStruct* NodeFactory(char* wordToBeChecked);
validWordsStruct* CheckWordValidity(char** validWords, spellingbeeStruct* spellingbeeStructPointer , int wordCount);

int binsearch(char** words, int begginingOfSearch, int endOfSearch, char* target);

void ValidCandidates(char* spellingbeeWord, char requiredCharacter, int used[7], char* buffer, int depth, char** validWords, int dictionarySize, validWordsStruct** outHeadNode);
void PrintResult(validWordsStruct* validWords);
void FreeSpellingBeeStuct(spellingbeeStruct* spellingbeeStructPointer);

int main()
{
    int wordCount = 0;
    char* spellingbeeLetters = malloc(51 * sizeof(char));
    scanf("%s" , spellingbeeLetters);

    spellingbeeStruct* spellingbeeStructPointer = BuildSpellingBeeStruct(spellingbeeLetters); //build out the spelling bee struct

    spellingbeeLetters = SortAlphabetical(spellingbeeLetters);//sort the reqired letters in alphabetical order for bin search

    strcpy(spellingbeeStructPointer->lettersInGame , spellingbeeLetters);//store the SORTED spelling bee letters in our struct

    
    
    free(spellingbeeLetters);//no need anymore

    scanf("%d" , &wordCount);
    char** validWords = PlayGame(wordCount);//we start playing the game


    PrintResult(CheckWordValidity(validWords, spellingbeeStructPointer, wordCount));//recursively print the struct result.

    
    FreeSpellingBeeStuct(spellingbeeStructPointer); //free the spellingbee struct
    return 0;

}

//helper function to free the spellingbeeStruct in full
void FreeSpellingBeeStuct(spellingbeeStruct* spellingbeeStructPointer)
{
    free(spellingbeeStructPointer->lettersInGame);
    free(spellingbeeStructPointer);

}

//The main algorithm in the code. here we use the given binary search algorithm created in class, and we use recusrion within recursion to check if the words 
//given are valid according to the rules stated in the specifications.
void ValidCandidates(char* spellingbeeWord, char requiredCharacter, int used[7], char* buffer, int depth, char** validWords, int dictionarySize, validWordsStruct** outHeadNode)
{
    //at every recursion level we need to make sure that our buffer is a valid
    //string with a null terminator at the end of each word.
    //otherwise our strcmp -> binsearch , might give wierd bug(took hours)
    buffer[depth] = '\0';

    int hasRequiredCharacter = 0;// we need to keep track of wether the word given even has the required character(mandatory)

    //loop through to find that required character
    for(int i = 0; i < depth ; i++)
    {
        if(buffer[i] == requiredCharacter)
        {
            hasRequiredCharacter = 1;//found, so break from the loop
            break;
        }


    }

    //since the words need to be between 4 and 7 characters long, no need to check anything under
    //or over. also needs that required character
    if(depth >= 4 && depth<= 7 && hasRequiredCharacter)
    {
        //we binary search to find the words that have the required characters, if we get > 0 returned then we found it  
        //we call binary search the current preffix, from 0 (initital) to the depth - 1 (before null character) to
        //check if that required letter is present.      
        if(binsearch(validWords , 0 , dictionarySize - 1, buffer) >= 0)
        {
            //our binary search came back with a positive value, indicating that it is a valid word
            //add it to our linked list using our helper function
            *outHeadNode = AddToLinkedList(*outHeadNode, buffer);//so add it to our new valid words linked list

        }
    }

    //too long
    if(depth == 7){return;}

    //we are going to recurse by appending each unused letter
    //one at a time
    for(int i = 0 ; i < 7 ; i++)
    {

        if (used[i]) {continue;}//we already are using this letter, its a REPEAT! (NOT ALLOWED)

        used[i] = 1;//used
        buffer[depth] = spellingbeeWord[i];
        ValidCandidates(spellingbeeWord , requiredCharacter , used , buffer , depth + 1 , validWords , dictionarySize , outHeadNode);//recursive call for next character
        used[i] = 0;//explore other branches, so set to 0
    }


}

//binary search algorithm from class. No need to change it
//changed some variable names for clarity and easy reading/self documentation
int binsearch(char** words, int begginingOfSearch, int endOfSearch, char* targetWord) {

    // Empty search space.
    if (begginingOfSearch > endOfSearch) return -1;

    int middleOfSearch = (begginingOfSearch + endOfSearch) /2;

    // Save this since we need it twice.
    int compareWords = strcmp(targetWord, words[middleOfSearch]);

    // target must be in left side of array.
    if (compareWords < 0)
        return binsearch(words, begginingOfSearch, middleOfSearch-1, targetWord);

    // right side...
    else if (compareWords > 0)
        return binsearch(words, middleOfSearch+1, endOfSearch, targetWord);

    // We found it!
    else
        return middleOfSearch;
}

//helper function that uses recursion to print out each node in our linked list.
void PrintResult(validWordsStruct* validWordsStructPointer)
{
        if(!validWordsStructPointer) return;
        printf("%s\n" , validWordsStructPointer->validWord);
        PrintResult(validWordsStructPointer->next);

        
}


//takes in an array of words in the game, the spelling bee struct and a word count to create a validword struct that has all the valid words for the game.
//calls ValidCandidates() which has the actuall algorithm to sort.
validWordsStruct* CheckWordValidity(char** validWords, spellingbeeStruct* spellingBeeStruct , int wordCount)
{
    char* spelligbeeWord = spellingBeeStruct->lettersInGame;
    int used[7] = {0};
    char buffer[8];
    
    validWordsStruct* headNode = NULL;

    ValidCandidates(spelligbeeWord, spellingBeeStruct->requiredLetter , used, buffer , 0 , validWords , wordCount , &headNode);


    return headNode;
}

//sorts a string into alphabetical order.
char* SortAlphabetical(char* wordToBeSorted)
{
    //store the string length
    int wordLength = strlen(wordToBeSorted);

    //loop through the word keeping two indexes, we compare the first letter to all other
    //letters in the word and see which one has the lowest value, indicating it comes first in the alphabet
    //then we step through to the other letters until we reach the end of the word.
    //we swap the letters in the word if the value of the letter that comes after the one we are comparing is lower.
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


//helper function that reads input from user and returns an array of those words
char** PlayGame(int wordCount)
{
    if(wordCount < 1) return NULL;

    char** wordsInGame = malloc(wordCount * sizeof(char*));
    
    for(int i = 0 ; i < wordCount; i++){
        char buffer[51];
        scanf("%50s" , buffer);
        wordsInGame[i] = malloc(strlen(buffer) + 1);
        strcpy(wordsInGame[i] , buffer);
    }
    
    return wordsInGame;

}

//simple helper funtion that returns a built spellingbee struct
spellingbeeStruct* BuildSpellingBeeStruct(char* spellingbeeLetters)
{
    spellingbeeStruct* spellingbeeStructPointer = malloc(sizeof(spellingbeeStruct));

    spellingbeeStructPointer->lettersInGame = malloc(strlen(spellingbeeLetters) + 1);

    spellingbeeStructPointer->requiredLetter = spellingbeeLetters[3];

    return spellingbeeStructPointer;
}

//builds and returns a new node for a validWordStruct linked list
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
validWordsStruct* AddToLinkedList(validWordsStruct* validWordStructPointer , char* wordToBeChecked)
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


