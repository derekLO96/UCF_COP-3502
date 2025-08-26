/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct myNums
{

    int number;

}myNums;

myNums** BuildArray(int items, int maxItems);
void PrintContentsOfArray(myNums* array, int size);
int AverageOfArray(myNums* array, int size);
int MaxValueInArray(myNums* array, int sizeOfArray);



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

    for(int i = 0; i < numberOfItems; i++) free(myArray[i]);
    free(myArray);

    return 0;
}

myNums** BuildArray(int items, int maxItems)
{
    myNums** builtArray = calloc (items, sizeof(int*));
    int number;

    for(int i = 0; i < items; i++)
    {        
        number = rand();
        builtArray[i] = malloc(sizeof(myNums));

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
    */
