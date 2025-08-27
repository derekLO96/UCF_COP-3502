
#include <stdio.h>
#include <stdlib.h>

typedef struct myNums
{
    char* phrase;
    int number;

}myNums;

myNums** BuildArray(int items, int maxItems);
void PrintContentsOfArray(myNums* array, int size);
int AverageOfArray(myNums* array, int size);
int MaxValueInArray(myNums* array, int sizeOfArray);
void AddPhrases(myNums** array, int numberOfItems);
void PrintPhrase(myNums** array, int numberOfItems);



int main()
{

    int numberOfItems;
    int maxValueOfItems;
    

    printf("\nProvide the number of Items: ");
    scanf("%d", &numberOfItems);
    printf("\nProvide the max value for those Items: ");
    scanf("%d", &maxValueOfItems);

    myNums** myArray = BuildArray(numberOfItems, maxValueOfItems);

    printf("\nHighest value int the array: %d\n", MaxValueInArray((*myArray) , numberOfItems));

    printf("\nAverage value in array: %d\n\n", AverageOfArray((*myArray),numberOfItems));

    printf("\n\n String portion of the code...\n\n");

    AddPhrases(myArray, numberOfItems);
    PrintPhrase(myArray, numberOfItems);

    for(int i = 0; i < numberOfItems; i++)
    { 
        free(myArray[i]->phrase);
        free(myArray[i]);
    }
    free(myArray);

    return 0;
}



myNums** BuildArray(int items, int maxItems)
{
    myNums** builtArray = calloc (items, sizeof(myNums*));
    int number;

    for(int i = 0; i < items; i++)
    {        
        number = rand();
        builtArray[i] = calloc(1, sizeof *builtArray[i]);

        while (number > maxItems)
        {

            number = rand();
        }
        
        (*builtArray[i]).number = number;
    }

    return builtArray;

}

void PrintContentsOfArray(myNums *array, int size)
{
    for (int i = 0; i < size ; i++)
    {

        printf("%d", array[i].number);

    }
}

int AverageOfArray(myNums *array, int size)
{
    int average;

    for (int i = 0; i < size; i++)
    {
        average += array[i].number;

    }


    return ( average / size );
}

int MaxValueInArray(myNums* array ,int sizeOfArray)
{
    int maxValue = 0;

    for(int i = 0; i < sizeOfArray; i++)
    {
        if(array[i].number > maxValue)
        {
            maxValue = array[i].number;
        }

    }

    return maxValue;
}

void AddPhrases(myNums **array, int numberOfItems)
 {

    printf("\nProvide %d phrases to be stored in the array:", numberOfItems);
    
    for(int i = 0; i < numberOfItems; i++)
    {
        char* phrase = malloc(100* sizeof(char));
        printf("\nPhrase %d:", i+1);
        scanf("%s", phrase);
        (*array)[i].phrase = calloc(1 , sizeof *array[i]->phrase );
        (*array)[i].phrase = phrase;
    }

 }

void PrintPhrase(myNums **array, int numberOfItems)
{
    for(int i = 0 ; i < numberOfItems; i++)
    {
        printf("\nphrase #%d: %s", i+1 , (*array)[i].phrase);

    }

}
