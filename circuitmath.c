//Derek Lopes Oliveira
// RP2 kattis Circuit Math 
//  09/29/2025 

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

//the actual stack
typedef struct Stack
{

    StackNode* topOfStack;

}Stack;

//start prototypes
TruthTableLinkedList* BuildTruthTable(char* truthtable , int inputVariables);
TruthTableLinkedList* InsertIntoTTLL(TruthTableLinkedList* head , TruthTableLinkedList* newNode);
TruthTableLinkedList* TruthTableNodeFactory(char input , int boolean);

Stack* Stacker(char* circuitDiagram , TruthTableLinkedList* truthTableLL);

StackNode* StackNodeFactory(int boolean);

void PrintResult(Stack* circuitStack);
void FreeTTLL(TruthTableLinkedList* TTLL);

int ANDgate(int booleanOne , int booleanTwo);
int ORgate(int booleanOne , int booleanTwo);
int NOTgate(int booleanOne );
int SearchForInput(TruthTableLinkedList* truthTableLL , char circuitDiagram);
//end prototypes


int main()
{
    int inputVariables;
    scanf("%d" , &inputVariables);
    getchar();

    //the truth table is all possible letters in the alphabet and each has a corresponding white space to specifications. +1 for that null character
    char* truthtable = malloc( (26 * 2) + 1  * sizeof(char) );
    //using %[^/n] to take into account all the white sace before the new line
    scanf("%[^\n]" , truthtable);
    //get the last character inputed so the next scanf function doesnt mistake it for input
    getchar();

    //enough room for the largest of the inputs
    char* circuitDiagram = malloc(10000 * sizeof(char));
    scanf("%[^\n]" , circuitDiagram);
    getchar();

    //build the truth table
    TruthTableLinkedList* truthTableLLS = BuildTruthTable(truthtable , inputVariables);

    //stack them and get back the result
    Stack* circuitStack = Stacker(circuitDiagram , truthTableLLS);

    //print the result
    PrintResult(circuitStack);


    FreeTTLL(truthTableLLS);
    free(circuitStack->topOfStack);
    free(circuitStack);
    return 0; //successfull execution.
}

//recursively frees the truth table linked list
void FreeTTLL(TruthTableLinkedList* TTLL)
{
    if (TTLL == NULL) return;
    FreeTTLL(TTLL->nextNode);
    free(TTLL);

}

//simple helper function to print out the result from the integer boolean value
void PrintResult(Stack* circuitStack)
{

    if(circuitStack->topOfStack->boolean == 0) printf("F\n");

    else printf("T\n");

}


//this funtion goes through the input truth table and builds the corresponding truth table linked list for input checking
TruthTableLinkedList* BuildTruthTable(char* truthtable , int inputVariables)
{
    TruthTableLinkedList* headNode = NULL;
    int boolean;
    int charFound = 0;

    //going through the truth table array
    for(int i = 0 ; i < strlen(truthtable) ; i += 2)
    {
        //reset boolean value
        boolean = 0;
        
        if(truthtable[i] == 'T') boolean = 1;

         //building out linked list
        headNode = InsertIntoTTLL(headNode , TruthTableNodeFactory(charFound + 65 , boolean));
        charFound++;

    }
    
    
    return headNode;

}

//insert new truth table node into the linked list 
TruthTableLinkedList* InsertIntoTTLL(TruthTableLinkedList* head , TruthTableLinkedList* newNode)
{
    //not yet initialized
    if(head == NULL){ 
        return newNode;
        
    }
    TruthTableLinkedList* temp = head;

    //loop through the linked list until we reach the end
    while(temp != NULL){

    
        //set the new end
    if(temp->nextNode == NULL) 
    {
        temp->nextNode = newNode;
        return head;
    }

    //next node
    temp = temp->nextNode;

    }
    return head;

}

//creates a node for our truth table.
TruthTableLinkedList* TruthTableNodeFactory(char input , int boolean)
{
    TruthTableLinkedList* newNode = malloc(sizeof(TruthTableLinkedList));
    newNode->input = input;
    newNode->boolean = boolean;
    newNode->nextNode = NULL;

    return newNode;
}

//initiate the stack by making sure the top of it is NULL
Stack* InitiateStack()
{
    Stack* newStack = malloc(sizeof(Stack));

    newStack->topOfStack = NULL;

    return newStack;

}

//place node on top of the stack, making sure to keep track of the previous top
void PushToStack(Stack* stack , StackNode* nodeToStack)
{
    //there is nothing in the stack
    if(stack->topOfStack == NULL) 
    {
        stack->topOfStack = nodeToStack;
        nodeToStack->nodeBellow = NULL;
        return;
    }

    //the previous top of stack
    StackNode* previousTop = stack->topOfStack;
    //set new top
    stack->topOfStack = nodeToStack;
    //point to previous top of stack
    nodeToStack->nodeBellow = previousTop;


}

//simple pop function that takes the node on top of the stack and returns its boolean value
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

    //making sure we dont make the top of the stack point to NULL!!
    stack->topOfStack = newTop;

    int booleanValue = oldTop->boolean;

    //we wont be needing this node anymore
    free(oldTop);

    return booleanValue;

}

//main algorithm of the code. after we have built our truth table and our circuit diagram, we go through and stack accordingly
Stack *Stacker(char *circuitDiagram , TruthTableLinkedList* truthTableLL)
{
    //initialize the stack
    Stack* myStack = InitiateStack();
    //keep track of the boolean for the input
    int boolean = 0;

    //go through the circuit diagram taking into account for that white space
    for(int i = 0 ; i < strlen(circuitDiagram) ; i +=2)
    {
        //check for the character in that circuit diagram input
        switch (circuitDiagram[i])
        {
            //we found an AND gate
        case '*':
        //we push to the stack brand new node with the AND result of the two popped nodes from our stack
            PushToStack(myStack , StackNodeFactory(ANDgate(PopOutOfStack(myStack) , PopOutOfStack(myStack))));
            break;

            //we found a OR gate
        case '+':
        //we push to the stack brand new node with the OR result of the two popped nodes from our stack
            PushToStack(myStack , StackNodeFactory(ORgate(PopOutOfStack(myStack) , PopOutOfStack(myStack))));
            break;

            //lets Negate the top of the stack
        case '-':
        //take the top of the stack , negate, put into a new node and push it back to top of stack
            PushToStack(myStack , StackNodeFactory(NOTgate(PopOutOfStack(myStack))));
            break;

            //if the circuit diagram is not an operation, then it is a Input
        default:
            //search of the input letter and returns back its boolean value
            boolean = SearchForInput(truthTableLL , circuitDiagram[i]);
            //we push that result back into the stack with a brand new node
            PushToStack(myStack , StackNodeFactory(boolean));

            break;
        }

    }
    
    return myStack;
}

//this creates a Stack node for initialization
StackNode* StackNodeFactory(int boolean)
{
    StackNode* newNode = malloc(sizeof(StackNode));

    newNode->boolean = boolean;
    newNode->nodeBellow = NULL;

    return newNode;

}

//We search through on linked list until we find our desired input character
int SearchForInput(TruthTableLinkedList* truthTableLL , char desiredInput)
{
    TruthTableLinkedList* temp = truthTableLL;

    //make sure we make it to the end of the linked list
    while(temp != NULL)
    {
        //we found it. Return
        if(temp->input == desiredInput) return temp->boolean;

        temp = temp->nextNode;

    }

    return 0;

}


//follow the AND gate truth table
//__A__|____B__|___F___
//  0       0       0
//  0       1       0
//  1       0       0
//  1       1       1
int ANDgate(int booleanOne , int booleanTwo)
{
    //return 1 if one of the inputs is 1 and both of the inputs are the same
    if(booleanOne != 0 && booleanOne == booleanTwo) return 1;
    return 0 ;
}

//follow the OR gate truth table
//__A__|____B__|___F___
//  0       0       0
//  0       1       1
//  1       0       1
//  1       1       1
int ORgate(int booleanOne , int booleanTwo)
{
    //if input A is > B that means that input A is 1
    if(booleanOne > booleanTwo) return booleanOne;

    //if input B > A or B == A then we return B regardless.
    return booleanTwo;
}

//just flip the bit.
int NOTgate(int boolean)
{
    if(boolean == 1) return 0;

    return 1;
}
