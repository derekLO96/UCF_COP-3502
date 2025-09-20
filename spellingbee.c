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

char** PlayGame(int wordCount);
char* SortAlphabetical(char* wordToBeSorted);

validWordsStruct* AddToLinkedList( validWordsStruct* validWordStruct , char* wordToBeChecked);
validWordsStruct* NodeFactory(char* wordToBeChecked);
validWordsStruct* CheckWordValidity(char** validWords, spellingbee* spellingbeeStructPointer , int wordCount);

int binsearch(char** words, int begginingOfSearch, int endOfSearch, char* target);

void ValidCandidates(char* spellingbeeWord, char requiredCharacter, int used[7], char* buffer, int depth, char** validWords, int dictionarySize, validWordsStruct** outHeadNode);
void PrintResult(validWordsStruct* validWords);

int main()
{
    int wordCount = 0;
    char* spellingbeeLetters = malloc(51 * sizeof(char));
    scanf("%s" , spellingbeeLetters);

    spellingbee* spellingbeeStructPointer = BuildSpellingBeeStruct(spellingbeeLetters); 

    spellingbeeLetters = SortAlphabetical(spellingbeeLetters);

    strcpy(spellingbeeStructPointer->lettersInGame , spellingbeeLetters);

    
    
    free(spellingbeeLetters);

    scanf("%d" , &wordCount);
    char** validWords = PlayGame(wordCount);


    PrintResult(CheckWordValidity(validWords, spellingbeeStructPointer, wordCount));

    

    return 0;

}

void ValidCandidates(char* spellingbeeWord, char requiredCharacter, int used[7], char* buffer, int depth, char** validWords, int dictionarySize, validWordsStruct** outHeadNode)
{
    buffer[depth] = '\0';

    int hasRequiredCharacter = 0;

    for(int i = 0; i < depth ; i++)
    {
        if(buffer[i] == requiredCharacter)
        {
            hasRequiredCharacter = 1;
            break;
        }


    }

    if(depth >= 4 && depth<= 7 && hasRequiredCharacter)
    {
        if(binsearch(validWords , 0 , dictionarySize - 1, buffer) >= 0)
        {
            *outHeadNode = AddToLinkedList(*outHeadNode, buffer);

        }
    }

    if(depth == 7){return;}

    for(int i = 0 ; i < 7 ; i++)
    {

        if (used[i]) {continue;}

        used[i] = 1;
        buffer[depth] = spellingbeeWord[i];
        ValidCandidates(spellingbeeWord , requiredCharacter , used , buffer , depth + 1 , validWords , dictionarySize , outHeadNode);
        used[i] = 0;
    }


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
void PrintResult(validWordsStruct* validWordsStructPointer)
{
        if(!validWordsStructPointer) return;
        printf("%s\n" , validWordsStructPointer->validWord);
        PrintResult(validWordsStructPointer->next);

        
}


validWordsStruct* CheckWordValidity(char** validWords, spellingbee* spellingBeeStruct , int wordCount)
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

//simple helper funtion that returns a built struct
spellingbee* BuildSpellingBeeStruct(char* spellingbeeLetters)
{
    spellingbee* spellingbeeStructPointer = malloc(sizeof(spellingbee));

    spellingbeeStructPointer->lettersInGame = malloc(strlen(spellingbeeLetters) + 1);

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


