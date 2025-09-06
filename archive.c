//Derek Lopes Oliveira
//  p1
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAXSTRINGLENGTH 20

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

char** readPuzzleTypes(int *countOut); //used
Player *createPlayer(char *name); //used
Archive *createArchive(int puzzleCount); //used
Player ** readPlayerPool(int *playerCount);//used
char* getPuzzleTypePtr(char **puzzleTypes , int count , char*type);//used
Player* getPlayerPtrByName(Player **playerPool , int playerCount, char *playerName);// used
void printBestScorer(Puzzle *puzzle);//used
void printMaxTotalScorer(Player** playerPool, int numPlayers); //used
void freePlayerPool(Player **pool, int count);//used
void freeArchive(Archive *archive);//used

Puzzle* CreatePuzzleArray(int puzzleTypeCount , char** puzzleTypes);
void PopulatePuzzlesArray(int puzzleTypeCount , Puzzle* puzzles , Player** playerPool , int playerCount, int *puzzlesAttemptedOut);

int main(void)
{
    char** puzzleTypes; // to store array of dynamically allocated strings for puzzle types (e.g., {"Wordle", "Crossword", "Connections"}) 
    int puzzleTypeCount = 0; // number of puzzle types
    // ofcourse you may need other variables and pointers to complete the tasks.
    int playerCount = 0;
    int puzzlesAttemptedOut = 0;

    //Get the puzzle types and return it to a 2D array of strings
    puzzleTypes = readPuzzleTypes(&puzzleTypeCount);
    Archive* archive = createArchive(puzzleTypeCount);
    Puzzle* puzzles = CreatePuzzleArray(puzzleTypeCount , puzzleTypes);
    archive->puzzles = puzzles;
    archive->puzzleCount = puzzleTypeCount;


    Player** playerPool = readPlayerPool( &playerCount);


    PopulatePuzzlesArray(puzzleTypeCount, puzzles , playerPool , playerCount , &puzzlesAttemptedOut);

    int numberOfQueries, queryTypeNumber;
    scanf("%d" , &numberOfQueries);
    for(int i = 0 ; i < numberOfQueries ; i++)
    {
        scanf("%d" , &queryTypeNumber);
        if(queryTypeNumber == 1)
        {
            printMaxTotalScorer(playerPool, playerCount);
            

        }
        else
        {
            for (int i = 0 ; i < puzzlesAttemptedOut ; i++)
            {
                printBestScorer(&archive->puzzles[i]);
            }
                   

        }
    }


    free(puzzles);
    return 1;

}

void PopulatePuzzlesArray(int puzzleTypeCount , Puzzle* puzzles , Player** playerPool , int playerCount , int *puzzlesAttemptedOut)
{

    char* puzzlePLayed = malloc(MAXSTRINGLENGTH * sizeof(char));
    scanf("%d" , puzzlesAttemptedOut);
    int puzzleID , puzzlePlayerCount;
    for(int i = 0 ; i < *puzzlesAttemptedOut ; i++)
    {
        char* puzzlePLayed = realloc(puzzlePLayed , MAXSTRINGLENGTH * sizeof(char));
        getchar();
        scanf("%s %d %d", puzzlePLayed , &puzzleID, &puzzlePlayerCount);

        for(int j = 0 ; j < puzzleTypeCount ; j ++)
        {
            if(!strcmp(puzzles[j].puzzleType, puzzlePLayed))
            {
                puzzles[j].puzzleNo = puzzleID;
                puzzles[j].playerCount = puzzlePlayerCount;
                puzzles[j].players = malloc(puzzlePlayerCount * sizeof(Player*));
                puzzles[j].scores = malloc(puzzlePlayerCount * sizeof(int));

                //Player** puzzlesPlayerPool = malloc(puzzlePlayerCount * sizeof(Player*));
                char* playerNameThatAttemptedPuzzle = malloc(MAXSTRINGLENGTH * sizeof(char));
                int theirScore = 0;
                for(int k = 0 ; k < puzzlePlayerCount ; k++)
                {
                    scanf("%s %d" , playerNameThatAttemptedPuzzle , &theirScore);
                    puzzles[j].players[k] = getPlayerPtrByName(playerPool, playerCount, playerNameThatAttemptedPuzzle);
                    puzzles[j].players[k]->totalScore += theirScore;
                    puzzles[j].scores[k] = theirScore;
                    theirScore = 0;

                }
                free(playerNameThatAttemptedPuzzle);
                break;
            }

        }
        
        

    }

}

Puzzle* CreatePuzzleArray(int puzzleTypeCount , char** puzzleTypes)
{

    Puzzle* puzzles = malloc(puzzleTypeCount * sizeof(Puzzle));

    for(int i = 0 ; i < puzzleTypeCount ; i++)
    {
        puzzles[i].puzzleType = getPuzzleTypePtr(puzzleTypes , puzzleTypeCount , puzzleTypes[i]);
    }

    return puzzles;
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
    char* puzzleName = malloc(MAXSTRINGLENGTH * sizeof(char));
    for(int i = 0 ; i < *countOut ; i++) 
    {
        scanf("%s", puzzleName);
        puzzleType[i] = malloc(strlen(puzzleName) * sizeof(char));
        strcpy(puzzleType[i] ,puzzleName);
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
    Archive* newArchive = malloc(sizeof(Archive));
    newArchive->puzzleCount = puzzleCount;
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
    char* playerName = malloc(MAXSTRINGLENGTH * sizeof(char));
    scanf("%d", playerCount);
    Player **playerPool = malloc(*playerCount * sizeof(Player*));
    for(int i = 0 ; i < *playerCount ; i++)
    {       
        scanf("%s" , playerName);
        playerPool[i] = createPlayer(playerName);

    }
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

    for(int i = 0 ; i < count ; i++)
    {
        if(!strcmp(puzzleTypes[i] , type))
        {
            return puzzleTypes[i];

        }

    }

    return NULL;

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

    for (int i = 0 ; i < playerCount; i++)
    {

        if(!strcmp(playerPool[i]->playerName , playerName))
        {
            return playerPool[i];

        }
    }

    return NULL;
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

    printf("Top scorer per puzzle:\n"); 

    int topScorerPosition = 0;

    for(int i = 0 ; i < puzzle->playerCount ; i++)
    {
        if(puzzle->scores[i] > puzzle->scores[topScorerPosition])
        {
            topScorerPosition = i;

        }
        
    }
    printf("%s#%d %s %d\n" , puzzle->puzzleType , puzzle->puzzleNo , puzzle->players[topScorerPosition]->playerName , puzzle->scores[topScorerPosition]);
        
    
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
    Player* bestOverallScorer = playerPool[0];

    for (int i = 0 ; i < numPlayers ; i++)
    {
        if(playerPool[i]->totalScore > bestOverallScorer->totalScore)
        {
            bestOverallScorer = playerPool[i];

        }

    }

    printf("Top player: %s with total score %d\n" , bestOverallScorer->playerName , bestOverallScorer->totalScore);

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
    for (int i = 0 ; i < count ; i++)
    {
        free(pool[i]->playerName);
        free(pool[i]);
    }
    free(pool);
}


/*
Preconditions:
• archive must be a valid pointer to an Archive structure.
Postconditions:
• Frees all puzzles in the archive and then frees the archive itself.
*/
void freeArchive(Archive *archive)
{
    for (int i = 0 ; i < archive->puzzleCount ; i++)
    {
        free(archive->puzzles[i].puzzleType);
        free(archive->puzzles[i].scores);
    }

    free(archive->puzzles);
    free(archive);

}
