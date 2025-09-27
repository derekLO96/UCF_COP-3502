//Derek Lopes Oliveira
// RP2 kattis Circuit Math 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//struct for the node containing letter and boolean value
typedef struct TruthTableLinkedList
{
    char input;
    int boolean;
    struct TruthTableLinkedList* nextNode;

} TruthTableLinkedList;

//stack node
typedef struct StackNode
{
    int boolean;
    struct StackNode* nodeBellow;

}StackNode;

//the stack struct
typedef struct stack
{

    StackNode* topOfStack;

}Stack;


TruthTableLinkedList* BuildTruthTable(char* truthtable , int inputVariables);
void InsertIntoTTLL(TruthTableLinkedList* head , TruthTableLinkedList* newNode);
void PrintResult(Stack* circuitStack);
TruthTableLinkedList* TruthTableNodeFactory(char input , int boolean);
Stack* Stacker(char* circuitDiagram , TruthTableLinkedList* truthTableLL);
StackNode* StackNodeFactory(int boolean);
int ANDgate(int booleanOne , int booleanTwo);
int ORgate(int booleanOne , int booleanTwo);
int NOTgate(int booleanOne );
int SearchForInput(TruthTableLinkedList* truthTableLL , char circuitDiagram);

int main()
{
    int inputVariables;
    scanf("%d" , &inputVariables);
    getchar();

    char* truthtable = malloc( (26 * 2) + 1  * sizeof(char) );
    scanf("%[^\n]" , truthtable);
    getchar();

    char* circuitDiagram = malloc(10000 * sizeof(char));
    scanf("%[^\n]" , circuitDiagram);
    getchar();

    TruthTableLinkedList* truthTableLLS = BuildTruthTable(truthtable , inputVariables);

    Stack* circuitStack = Stacker(circuitDiagram , truthTableLLS);

    PrintResult(circuitStack);


    return 0;
}

void PrintResult(Stack* circuitStack)
{

    if(circuitStack->topOfStack->boolean == 0) printf("F\n");

    else printf("T\n");

}

TruthTableLinkedList* BuildTruthTable(char* truthtable , int inputVariables)
{
    TruthTableLinkedList* headNode;
    int boolean;
    int charFound = 0;

    for(int i = 0 ; i < strlen(truthtable) ; i += 2)
    {
        boolean = 0;
        if(truthtable[i] == 'T') boolean = 1;

         
        InsertIntoTTLL(headNode , TruthTableNodeFactory(charFound + 65 , boolean));
        charFound++;

    }
    
    
    return headNode;

}

void InsertIntoTTLL(TruthTableLinkedList* head , TruthTableLinkedList* newNode)
{
    if(head->nextNode == NULL) 
    {
        head->nextNode = newNode;
        return;
    }
    InsertIntoTTLL(head->nextNode , newNode);

}

TruthTableLinkedList* TruthTableNodeFactory(char input , int boolean)
{
    TruthTableLinkedList* newNode = malloc(sizeof(TruthTableLinkedList));
    newNode->input = input;
    newNode->boolean = boolean;
    newNode->nextNode = NULL;

    return newNode;
}

Stack* InitiateStack()
{
    Stack* newStack = malloc(sizeof(Stack));

    newStack->topOfStack = NULL;

    return newStack;

}

void PushToStack(Stack* stack , StackNode* nodeToStack)
{
    if(stack->topOfStack == NULL) 
    {
        stack->topOfStack = nodeToStack;
        nodeToStack->nodeBellow = NULL;
        return;
    }

    StackNode* nodeBellow = stack->topOfStack;
    stack->topOfStack = nodeToStack;
    nodeToStack->nodeBellow = nodeBellow;


}

int PopOutOfStack(Stack* stack)
{
    StackNode* oldTop = stack->topOfStack;
    StackNode* newTop = stack->topOfStack->nodeBellow;

    //Stack is empty
    if(oldTop == NULL)
    {
        printf("\nStack is Empty!!!!\n\n");
        return -1;
    }

    stack->topOfStack = newTop;

    int booleanValue = oldTop->boolean;

    free(oldTop);

    return booleanValue;

}

Stack *Stacker(char *circuitDiagram , TruthTableLinkedList* truthTableLL)
{
    Stack* myStack = InitiateStack();
    int boolean = 0;

    for(int i = 0 ; i < strlen(circuitDiagram) ; i +=2)
    {
        switch (circuitDiagram[i])
        {
        case '*':
            PushToStack(myStack , StackNodeFactory(ANDgate(PopOutOfStack(myStack) , PopOutOfStack(myStack))));
            break;

        case '+':
            PushToStack(myStack , StackNodeFactory(ORgate(PopOutOfStack(myStack) , PopOutOfStack(myStack))));
            break;

        case '-':
            PushToStack(myStack , StackNodeFactory(NOTgate(PopOutOfStack(myStack))));
            break;

        default:
            boolean = SearchForInput(truthTableLL , circuitDiagram[i]);
            PushToStack(myStack , StackNodeFactory(boolean));

            break;
        }

    }
    
    return myStack;
}

StackNode* StackNodeFactory(int boolean)
{
    StackNode* newNode = malloc(sizeof(StackNode));

    newNode->boolean = boolean;
    newNode->nodeBellow = NULL;

    return newNode;

}

int SearchForInput(TruthTableLinkedList* truthTableLL , char desiredInput)
{
    TruthTableLinkedList* temp = truthTableLL;

    while(temp->nextNode != NULL)
    {
        if(temp->input == desiredInput) return temp->boolean;

        temp = temp->nextNode;

    }

    return 0;

}


int ANDgate(int booleanOne , int booleanTwo)
{
    if(booleanOne == booleanTwo) return 1;
    return 0 ;
}

int ORgate(int booleanOne , int booleanTwo)
{
    if(booleanOne > booleanTwo) return booleanOne;
    return booleanTwo;
}

int NOTgate(int boolean)
{
    if(boolean == 1) return 0;

    return 1;
}
