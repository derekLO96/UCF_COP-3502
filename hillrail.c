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

}HillCipherSecretStruct;

/// @brief Holds an encrypted string.
///
/// char* encryptedText 
typedef struct
{
    char* encryptedText;

}EncryptedTextStruct;


char* FormatText(char* plainText);
int** FormatMatrix(char* matrixStringFromFile);
long GetFileSize(FILE* file);
HillCipherSecretStruct BuildHillCipherStruct(char* plainText , int** key);
EncryptedTextStruct EncryptText(char* plainTextFileLocation , char* keyFileLocation);

int main(int argc , char* argv[])
{
    char* mode = argv[1];
    char* plainTextFileLocation = argv[3] ;
    char* keyFileLocation = argv[2];
    int rainWeight = atoi(argv[4]);


    EncryptedTextStruct cipherText = EncryptText(plainTextFileLocation , keyFileLocation);

    
    

    //printf("%s" , cipherText.encryptedText);


    return 0;
}

///@brief Takes in plain text and formats it into accepted format.
///Only alphabetical letters are accepted, all lowercase letters are converted
//to upper case, all other signs are ignored and deleted from the final string.
///@param plainText --> plain text from a file
///@return --> A formated string to especification
char *FormatText(char *plainText)
{
    char* plainTextParsed;

    return plainTextParsed;
}

/// @brief Takes in a string of integers from a file and formats it into a matrix that is acceptable
///to make the matrix multiplication.
/// @param matrixStringFromFile --> A string of integers
/// @return --> formated matrix
int **FormatMatrix(char *matrixStringFromFile)
{
    int** keyMatrixParsed;


    return keyMatrixParsed;
}

/// @brief Builds a struct meant to hold all information for the Hill Cipher. This is not the finished product, but a 
///meer placeholder for the final cipher. 
/// @param plainText --> The formated plain text to be encrypted
/// @param key --> The int matrix key that will encrypt the string
/// @return --> A built hill Cipher struct ready for encryption
HillCipherSecretStruct BuildHillCipherStruct(char *plainText, int **key)
{
    HillCipherSecretStruct hillCipherStruct;

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
    EncryptedTextStruct finalCipherStruct;
    FILE* plainTextFile;
    FILE* keyMatrixFile;
    long plainTextFileSize;
    long keyMatrixFileSize;
    int endOfFile;

    plainTextFile = fopen(plainTextFileLocation , "r");
    keyMatrixFile = fopen(keyFileLocation , "r");

    plainTextFileSize = GetFileSize(plainTextFile) + 1;
    keyMatrixFileSize = GetFileSize(keyMatrixFile) + 1;

    char* plainTextParsed = malloc(plainTextFileSize);
    char* keyMatrixText = malloc(keyMatrixFileSize);
    
    while(fgets(plainTextParsed , plainTextFileSize, plainTextFile)){}
    while(fgets(keyMatrixText , keyMatrixFileSize, keyMatrixFile)){}

    HillCipherSecretStruct builtHillCypherStruct = BuildHillCipherStruct(
                                        FormatText(plainTextParsed), 
                                              FormatMatrix(keyMatrixText));

    printf("%s" , plainTextParsed);
    printf("%s" , keyMatrixText);

    fclose(plainTextFile);
    fclose(keyMatrixFile);
    free(plainTextParsed);
    free(keyMatrixText);
    return finalCipherStruct;
}
