/*
Assignment :
hillrail - Hill cipher followed by Rail Fence transposition

Author : Derek Lopes Oliveira

Language : C 

To Compile :
    gcc -O2 -std=c11 -o hillrail hillrail.c

    To Execute ( on Eustis ):
        ./hillrail encrypt key . txt plain . txt < depth >

where :
    key.txt   = key matrix file
    plain.txt = plaintext file
    <depth>   = integer >= 2 ( Rail Fence )

Notes :
    - Input is 8 - bit ASCII ; process only A - Z ( uppercase ).
    - Tested on Eustis .

Class : CIS3360 - Security in Computing - Fall 2025

Instructor : Dr . Jie Lin

Due Date : September 12 th 2025

*/

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/// @brief Holds a formated plain text to be encrypted and key matrix.
///
/// char* plainTextFormated
///
/// int** key
typedef struct
{
    char* plainTextFormated;
    int** key;
    int matrixSize;

}HillCipherSecretStruct;

/// @brief Holds an encrypted string.
///
/// char* encryptedText 
typedef struct
{
    char* encryptedText;

}EncryptedTextStruct;


char* FormatText(char* plainTextFileLocation);
int** FormatMatrix(char* keyMatrixFileLocation , int* matrixSize);
long GetFileSize(FILE* file);
HillCipherSecretStruct* BuildHillCipherStruct(char* plainText , int** key , int matrixSize);
EncryptedTextStruct EncryptText(char* plainTextFileLocation , char* keyFileLocation);
EncryptedTextStruct PerformEncryption( HillCipherSecretStruct hillCipherStruct);
int* ConvertCharacterArrayToIntArray(char* characterArray);

int main(int argc , char* argv[])
{
    char* mode = argv[1];
    char* keyFileLocation = argv[2];
    char* plainTextFileLocation = argv[3];    
    int rainWeight = atoi(argv[4]);


    EncryptedTextStruct cipherText = EncryptText(plainTextFileLocation , keyFileLocation);

    
    

    //printf("%s" , cipherText.encryptedText);

    printf("\nDone...\n");

    return -1;
}

///@brief Takes in the plain text file location and parses the text into the correct format.
///@param plainTextFileLocation --> Plain text file location
///@return --> Formated text
char *FormatText(char* plainTextFileLocation)
{
    
    FILE* plainTextFile = fopen(plainTextFileLocation , "r");
    
    if(!plainTextFile)
    {
        printf("failed to open file %s" , plainTextFileLocation);
        return "Failed";
    }
    long plainTextFileSize = GetFileSize(plainTextFile) + 1;

    char* plainTextParsed = malloc((size_t) plainTextFileSize);
    char currentCharacter;
    int i = 0;

    while ((currentCharacter = fgetc(plainTextFile)) != EOF)
    {
       if(currentCharacter < 'A')
       {        
        //do nothing
       }else if(currentCharacter >= 'a' && currentCharacter <= 'z')
       {
        plainTextParsed[i] = (currentCharacter - 32);
        i++;
       }else if(currentCharacter > 'z')
       {
        //do nothing
       }else
       {
        plainTextParsed[i] = currentCharacter;
        i++;
       }

    }
    plainTextParsed[i] = '\0';

    fclose(plainTextFile);
    return plainTextParsed;
}

/// @brief Takes the key matrix file location and parses the text to build the key matrix in a two dimensional key matrix
/// @param keyFileLocation --> The location of the key matrix file
/// @param matrixSize --> pointer to store the size of matrix
/// @return --> a two dimentional array of keys
int** FormatMatrix(char* keyFileLocation , int* matrixSize)
{

    FILE* keyMatrixFile = fopen(keyFileLocation , "r");

    
    if(fscanf(keyMatrixFile , "%d " , matrixSize) != 1)
    {
        printf("Error");
    }
    int k = 0;

    int** keyMatrixParsed = malloc((*matrixSize) * sizeof(int*)); 

    for(int i = 0 ; i < (*matrixSize) ; i++)
    {
        keyMatrixParsed[i] = malloc((*matrixSize) * sizeof(int));      

    }
    for(int i = 0 ; i < (*matrixSize) ; i++)
    {
        printf("[\t");
        for(int j = 0 ; j < (*matrixSize) ; j++)
        {       

            fscanf(keyMatrixFile , "%d " , &keyMatrixParsed[i][j]);            
            printf("%d\t" , keyMatrixParsed[i][j]);
            k++;
            
        }
        printf("\t]\n");

    }

    fclose(keyMatrixFile);


    return keyMatrixParsed;
}

/// @brief Builds a struct meant to hold all information for the Hill Cipher. This is not the finished product, but a 
///meer placeholder for the final cipher. 
/// @param plainText --> The formated plain text to be encrypted
/// @param key --> The int matrix key that will encrypt the string
/// @return --> A built hill Cipher struct ready for encryption
HillCipherSecretStruct* BuildHillCipherStruct(char *plainText, int **key , int matrixSize)
{
    HillCipherSecretStruct* hillCipherStruct = malloc(sizeof(HillCipherSecretStruct));
    hillCipherStruct->plainTextFormated = malloc(strlen(plainText) * sizeof(char));

    hillCipherStruct->plainTextFormated = plainText;
    hillCipherStruct->key = key;
    hillCipherStruct->matrixSize = matrixSize;
    return hillCipherStruct;
}

/// @brief Takes in a file to read its size. first we place the cursor at the end of the file, then we read how big it is before we 
/// place the cursor back to the start position.
/// @param file --> the file to be measured
/// @return The size of the file as a long.
long GetFileSize(FILE* file)
{

    long fileSize;

    fseek(file , 0 , SEEK_END);
    fileSize = ftell(file);
    rewind(file);

    return fileSize;

}


/// @brief Encrypts plain text from a .txt file using a key matrix from a different .txt file.
/// @param plainTextFileLocation --> The location of the plain text file to be encrypted
/// @param keyFileLocation --> The location of the key matrix that will be used to perform the respected algebra
/// @return --> A struct containing the encrypted text
EncryptedTextStruct EncryptText(char *plainTextFileLocation, char *keyFileLocation)
{
    EncryptedTextStruct finalCipherStruct = {"Noting"};
    HillCipherSecretStruct* hillCipherStruct;

    int* matrixSize; 
    char *plainText = FormatText(plainTextFileLocation);
    int **buildMatrix = FormatMatrix(keyFileLocation, matrixSize);

    hillCipherStruct = BuildHillCipherStruct(plainText , buildMatrix , (*matrixSize));
    //int *convertedMatrix = ConvertCharacterArrayToIntArray(plainText);


    for(int i = 0 ; i < (*matrixSize); i++) free(buildMatrix[i]);
    free(buildMatrix);
    printf("\nfreeing hillcipher Struct...\n");
    free(hillCipherStruct->plainTextFormated);
    free(hillCipherStruct);
    printf("freed sucessfully...\n");
    return finalCipherStruct;
}

EncryptedTextStruct PerformEncryption( HillCipherSecretStruct hillCipherStruct)
{
    EncryptedTextStruct encripedText;

    int matrixSize = hillCipherStruct.matrixSize;
    char* plainTextFormated = hillCipherStruct.plainTextFormated;
    int** key = hillCipherStruct.key;

    char** letterArray = malloc(matrixSize * sizeof(char*));

    for(int i = 0 ; i < matrixSize ; i++)
    {
        letterArray[i] = malloc(matrixSize * sizeof(char));        

    }

    int* letterValueArray[matrixSize * matrixSize];



    return encripedText;

}
int* ConvertCharacterArrayToIntArray(char* characterArray)
{
    int* convertedArray;
    int stringLength = strlen(characterArray);

    printf("\nConverted character array: \n");
    for(int i = 0 ; i < stringLength ; i++)
    {
        printf("%c " , characterArray[i] );
        //convertedArray[i] = (characterArray[i] - 65);
    }


    return convertedArray;
}