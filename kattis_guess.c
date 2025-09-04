#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int attributePosition;
    char questionChar;

}Question;

int main(void)
{
    int numberOfCharacters, numberOfAttributes, numberOfQuestions;
    
    scanf("%d %d %d" , &numberOfCharacters, &numberOfAttributes, &numberOfQuestions);
    char** characterAttributesArray = malloc(numberOfCharacters * sizeof(char*));
    char** characterFound = malloc(numberOfCharacters * sizeof(char*));
    
    for(int i = 0 ; i < numberOfCharacters ; i++)
    {
        characterAttributesArray[i] = malloc(numberOfAttributes * sizeof(char));
        characterFound[i] = malloc(numberOfAttributes * sizeof(char));
        scanf("%s" , characterAttributesArray[i]);
    }
    
    Question questions[numberOfQuestions];
    
    for(int k = 0 ; k < numberOfQuestions ; k++)
    {
        scanf("%d %c" , &questions[k].attributePosition, &questions[k].questionChar);       
        questions[k].attributePosition--;
    }

    int characterHasBeenFound = 0;
    int position = 0;
    int found = 0;

    for(int i = 0 ; i < numberOfCharacters ; i++)
    {
        

        for(int j = 0 ; j < numberOfQuestions ; j++)
        {

            if(characterAttributesArray[i][(questions[j].attributePosition)] == questions[j].questionChar)
            {
                found++;

            }
        }

        if(found == numberOfQuestions)
        {
            characterFound[characterHasBeenFound] = characterAttributesArray[i];
            characterHasBeenFound++;
            position = i;
        }
        found = 0;
    }

    if(characterHasBeenFound <= 1 ) 
    {
        printf("unique\n%d\n", ( position+ 1));
    }
    else
    {
        printf("ambiguous\n%d\n" , characterHasBeenFound);

    }
    
    return 0;
}