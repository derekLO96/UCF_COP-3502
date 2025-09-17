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
validWordsStruct* CheckWordValidity( validWordsStruct* validWordStruct , char* wordToBeChecked , spellingbee* spellingbeeStructPointer);
validWordsStruct* ConstructValidWordsStruct(char* wordToBeChecked);
void printLinkedList(validWordsStruct* validWords);

int main()
{
    int wordCount = 0;
    char* spellingbeeLetters = malloc(51 * sizeof(char));
    scanf("%s" , spellingbeeLetters);
    spellingbee* spellingbeeStructPointer = BuildSpellingBeeStruct(spellingbeeLetters);

    scanf("%d" , &wordCount);
    validWordsStruct* validWords = PlayGame(wordCount , spellingbeeStructPointer);

    printLinkedList(validWords);


    printf("\n");
    

    return 0;

}
void printLinkedList(validWordsStruct* validWords)
{
    while(validWords->next != NULL)
    {
        printf("%s\t" , validWords->validWord);

        validWords = validWords->next;
    }
}

validWordsStruct* PlayGame(int wordCount , spellingbee* spellingbeeStructPointer)
{
    char* wordToBeChecked = malloc(51 * sizeof(char));
    validWordsStruct* validWords = malloc(sizeof(validWordsStruct));
    validWords->validWord = malloc(51 * sizeof(char));

    if(wordCount < 1) return NULL;

    while(wordCount > 0)
    {
        char* wordToBeChecked = malloc(51 * sizeof(char));
        scanf("%s" , wordToBeChecked);

        validWords = CheckWordValidity(validWords , wordToBeChecked , spellingbeeStructPointer);

        wordCount--;

    }

    free(wordToBeChecked);
    return validWords;

}

spellingbee* BuildSpellingBeeStruct(char* spellingbeeLetters)
{
    spellingbee* spellingbeeStructPointer = malloc(sizeof(spellingbee));

    spellingbeeStructPointer->lettersInGame = malloc(strlen(spellingbeeLetters) + 1);
    strcpy(spellingbeeStructPointer->lettersInGame , spellingbeeLetters);

    spellingbeeStructPointer->requiredLetter = spellingbeeLetters[3];

    return spellingbeeStructPointer;
}

validWordsStruct* ConstructValidWordsStruct(char* wordToBeChecked)
{
    validWordsStruct* temporary = malloc(sizeof(validWordsStruct));
        temporary->validWord = malloc(strlen(wordToBeChecked) + 1);
        strcpy(temporary->validWord , wordToBeChecked);
        temporary->next = NULL;

    return temporary;

}

validWordsStruct* CheckWordValidity(validWordsStruct* validWordStructPointer , char* wordToBeChecked, spellingbee* spellingbeeStructPointer)
{

    /*
        int wordLength = strlen(wordToBeChecked);
        
        int found = 0;

        for(int i = 0 ; i < wordLength ; i++)
        {

            if(wordToBeChecked[i] == spellingbeeStructPointer->requiredLetter) found = 1;
            

        }

        if(found == 0) return;*/

        validWordsStruct* temporary = ConstructValidWordsStruct(wordToBeChecked);

        if(validWordStructPointer == NULL)
        {
            validWordStructPointer = temporary;
        }
        else
        {
            temporary->next = validWordStructPointer;
        }

        return temporary;

}

