//Derek Lopes Oliveira
//  p1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


// Represents a player in the system
typedef struct {
 char *playerName;//dynamically allocated name of the player withoutwasting space
 int totalScore; // cumulative score across all puzzles
} Player;


// Represents one puzzle instance (e.g., Wordle #751, Crossword #202)
typedef struct {
 char *puzzleType; // points to an already allocated puzzle type string(Wordle, Crossword, etc.). No malloc/calloc for this property
 int puzzleNo; // ID number of the puzzle (e.g., 751, 202)
 Player** players; // dynamic array of pointers to players who playedthis puzzle
 int *scores; // dynamic array of scores corresponding to eachplayer (index-aligned with players)
 int playerCount; // number of players who played this puzzle
} Puzzle;


// Represents the archive of all puzzle instances
typedef struct {
 Puzzle* puzzles; // dynamic array of puzzles
 int puzzleCount; // number of puzzles stored
} Archive;

char** readPuzzleTypes(int *countOut);
Player *createPlayer(char *name);
Archive *createArchive(int puzzleCount);
Player ** readPlayerPool(int *playerCount);
char* getPuzzleTypePtr(char **puzzleTypes , int count , char*type);
Player* getPlayerPtrByName(Player **playerPool , int playerCount, char *playerName);
void printBestScorer(Puzzle *puzzle);
void printMaxTotalScorer(Player** playerPool, int numPlayers);
void freePlayerPool(Player **pool, int count);
void freeArchive(Archive *archive);

int main(void)
{
    char** puzzleTypes; // to store array of dynamically allocated strings for puzzle types (e.g., {"Wordle", "Crossword", "Connections"}) 
    int puzzleTypeCount = 0; // number of puzzle types
    // ofcourse you may need other variables and pointers to complete the tasks.


    //Get the puzzle types and return it to a 2D array of strings
    puzzleTypes = readPuzzleTypes(&puzzleTypeCount);
    Puzzle* puzzle = malloc(puzzleTypeCount * sizeof(Puzzle));
    for(int i = 0 ; i < puzzleTypeCount ; i++)
    {
        puzzle[i].puzzleType = puzzleTypes[i];
    }


    int playerCount = 0;
    scanf("%d", &playerCount);
    Player** playerPool = malloc(playerCount * sizeof(Player*));
    char* playerName = malloc(50 * sizeof(char));
    for(int i = 0 ; i < playerCount ; i++)
    {       
        scanf("%s" , playerName);
        playerPool[i] = createPlayer(playerName);

    }
    int puzzleCount;
    

    scanf("%d" , &puzzleCount);
    Archive* archive = createArchive(puzzleCount);







    free(puzzle);
    return 1;

}

/* 
countOut must be a valid memory address where the number of puzzle types can be stored.
Postconditions:
• Returns a dynamically allocated array of strings loaded with the puzzle
types from the input.
• countOut is updated to reflect the number of puzzle types.*/
char **readPuzzleTypes(int *countOut)
{
    char** puzzleType;

    scanf("%d" , countOut);
    puzzleType = malloc(*countOut * sizeof(char*));
    char* puzzleName = malloc(20 * sizeof(char));
    for(int i = 0 ; i < *countOut ; i++) 
    {
        scanf("%s", puzzleName);
        puzzleType[i] = malloc(strlen(puzzleName) * sizeof(char));
        puzzleType[i] = puzzleName;
    }


    return puzzleType;
}


/*
• name must be a valid non-null string representing the player's name.
Postconditions:
• Returns a pointer to a newly allocated Player structure with the
player's name stored and other properties initialized.
*/
Player *createPlayer(char *name)
{
    Player* player = calloc(1 , sizeof(Player));

    player->playerName = realloc(player->playerName , strlen(name) * sizeof(char));
    strcpy(player->playerName, name);

    return player;
}


/*
• puzzleCount represents the number of puzzle in the archive
Postconditions:
• Returns a pointer to a new Archive structure containing an array of
Puzzle structures.
*/
Archive *createArchive(int puzzleCount)
{
    Archive* newArchive = malloc(puzzleCount * sizeof(Archive));
    int puzzleID , playersInPuzzle;
    char * puzzleType = malloc(100 * sizeof(char));

    for(int i = 0 ; i < puzzleCount; i++)
    {
        scanf("%s %d %d" , puzzleType , &puzzleID , &playersInPuzzle);

    }
    
    return newArchive;
}


/*
• playerCount must be a valid memory address where the number of players
can be stored.
Postconditions:
• Returns a dynamically allocated array of pointers to Player structures.
• Each pointer points to a dynamically allocated player.
• playerCount is updated with the number of players read.
• Must take the help from the createPlayer function
*/
Player **readPlayerPool(int *playerCount)
{
    Player** playerPool;

    return playerPool;
}


/*
• puzzleTypes must be a valid pointer to an array of strings.
• count should represent the number of puzzle types available.
• type must be a valid non-null string representing the type to find.
Postconditions:
• Returns a pointer to the matching puzzle type string, or NULL if not
found.
*/
char *getPuzzleTypePtr(char **puzzleTypes, int count, char *type)
{
    char* puzzleTypePointer;


    return puzzleTypePointer;
}


/*
Preconditions:
• playerPool must be a valid pointer to an array of player pointers.
• playerCount must indicate the number of players in playerPool.
• playerName must be a valid non-null string to search for.
Postconditions:
• Returns a pointer to the matching Player structure, or NULL if not
found.
*/
Player *getPlayerPtrByName(Player **playerPool, int playerCount, char *playerName)
{
    Player* player;

    return player;
}


/*
Preconditions:
• playerPool must be a valid pointer to an array of player pointers.
• playerCount must indicate the number of players in playerPool.
• playerName must be a valid non-null string to search for.
Postconditions:
• Returns a pointer to the matching Player structure, or NULL if not
found.
*/
void printBestScorer(Puzzle *puzzle)
{
}


/*
Preconditions:
• archive must be a valid pointer to an Archive structure with puzzles.
Postconditions:
• Displays the player with the highest total score. In case of a tie, the
player who appears first in the input is considered the top scorer.
*/
void printMaxTotalScorer(Player** playerPool, int numPlayers)
{

}


/*
Preconditions:
• pool must be a valid pointer to an array of player pointers.
count must be > 0 to indicate the number of players in the pool.
Postconditions:
• Frees each player and their associated name, then frees the array of
players.
*/
void freePlayerPool(Player **pool, int count)
{
}


/*
Preconditions:
• archive must be a valid pointer to an Archive structure.
Postconditions:
• Frees all puzzles in the archive and then frees the archive itself.
*/
void freeArchive(Archive *archive)
{
}
