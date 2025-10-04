//Derek Lopes Oliveira
// P3
// 10/04/2025

#include <stdio.h>
#include <stdlib.h>

typedef struct dllnode
{
    char ch;
    struct dllnode** prev;
    struct dllnode** next;
}dllnode;

dllnode*** InitiateStrandGrid(int rows, int cols);
dllnode*** GetWordsAndSet(int numRows, int numCols);
int** GetCodes(int numRows, int numCols);
dllnode* NodeFactory(char character);

const int NUMDIR = 8;
const int NULLPTR = -1;
const int DR[NUMDIR] = {-1, -1, -1, 0, 0, 1, 1, 1};  
const int DC[NUMDIR] = {-1, 0, 1, -1, 1, -1, 0, 1};

int main()
{
    int numRows;
    int numCols;
    dllnode*** strandsGrid;

    scanf("%d", &numRows);
    scanf("%d", &numCols);

    strandsGrid = GetWordsAndSet(numRows, numCols);

    int** nextCodes = GetCodes(numRows, numCols);
    int** prevCodes = GetCodes(numRows, numCols);


    return 0;
}

dllnode*** GetWordsAndSet(int numRows, int numCols)
{

    dllnode*** newSet = InitiateStrandGrid(numRows, numCols);

    char* rowWords = malloc(numCols * sizeof(char));

    for(int i = 0 ; i < numRows; i++)
    {
        getchar();
        scanf("%s", rowWords);

        for(int j = 0; j < numCols; j++)
        {
            newSet[i][j] = NodeFactory(rowWords[j]);
        }
    }

    return newSet;
}   

dllnode* NodeFactory(char character)
{
    dllnode* newNode = malloc(sizeof(dllnode));
    newNode->ch = character;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;

}

//this helper function gets the input for the codes of next and previous, parses them and returns
//them in a, array of integers corresponding to the array of dllnodes
int** GetCodes (int numRows, int numCols)
{
    int** parsedCodes = malloc(numRows * sizeof(int*));
    char* codes;
    for(int i = 0; i < numRows; i++){
        getchar();
        scanf("%[^\n]", codes);
        int codePosition = 0;
        
        parsedCodes[i] = malloc(numCols * sizeof(int));
        for(int j = 0; j < numCols; j++)
        {            
            //since we are skipping white space, the code will see a '-' and not the 1 next to it. we can assume it
            //is a -1.
            if(codes[codePosition] == '-')
            {
                 parsedCodes[i][j] = -1;
                 codePosition++;//correct the offset
                 //potential bug(not of scope in this assignment): if -1 is last input -> goes of bounds
            }
            else
            {
                parsedCodes[i][j] = codes[codePosition] - '0'; //get the actual numerical value out of our input and store it.
                
            }
            codePosition += 2; //skip white space

        }
    }

    return parsedCodes;
}

dllnode*** InitiateStrandGrid(int rows, int cols)
{

    dllnode*** newDLLNode;
    newDLLNode = malloc(rows * sizeof(dllnode**));

    for(int i = 0 ; i < rows ; i++)
    {
        newDLLNode[i] = malloc(cols * sizeof(dllnode*));
        for(int j = 0; j < cols ; j++)
        {
            newDLLNode[i][j] = malloc(sizeof(dllnode));
        }
    }
    return newDLLNode;

}
