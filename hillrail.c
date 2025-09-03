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


char* FormatText(char* plainTextFileLocation);
int** FormatMatrix(char* keyMatrixFileLocation , int* matrixSize);
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

///@brief Takes in the plain text file location and parses the text into the correct format.
///@param plainTextFileLocation --> Plain text file location
///@return --> Formated text
char *FormatText(char* plainTextFileLocation)
{
    FILE* plainTextFile;
    long plainTextFileSize;   

    plainTextFile = fopen(plainTextFileLocation , "r");
    plainTextFileSize = GetFileSize(plainTextFile) + 1;

    char* plainTextParsed = malloc(plainTextFileSize);
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

    fclose(plainTextFile);

    return plainTextParsed;
}

/// @brief Takes the key matrix file location and parses the text to build the key matrix in a two dimensional key matrix
/// @param keyFileLocation --> The location of the key matrix file
/// @return --> a two dimentional array of keys
/// @todo FIX LOGIC. currently reading one caracter at a time, but numbers over 9 are 2 characters long ex: 10 would
/// read as 1 and 0 ... needs to be read as 10, one number.
int **FormatMatrix(char* keyFileLocation , int* matrixSize)
{
    
    int** keyMatrixParsed;

    FILE* keyMatrixFile;
    long keyMatrixFileSize;
    
    keyMatrixFile = fopen(keyFileLocation , "r");
    keyMatrixFileSize = GetFileSize(keyMatrixFile) + 1;

    char* keyMatrixText = malloc(keyMatrixFileSize);
    char currentCharacter;    
    int i = 0 , k = 0;
    int* integerArray;

    //FIX THIS
    while ((currentCharacter = fgetc(keyMatrixFile)) != EOF)
    {
        int integerFromCharacter = (currentCharacter - '0');
        if(i == 0)
        {
            integerArray = (int*) malloc((integerFromCharacter * integerFromCharacter) * sizeof(int));

            keyMatrixParsed = (int**) malloc(integerFromCharacter * sizeof(int*));

            for(int j = 0 ; j < integerFromCharacter ; j++) keyMatrixParsed[j] = (int*) malloc(sizeof(int));

            (*matrixSize) = integerFromCharacter;
            printf("\nDone Allocating memory ; MratrixSize: %d\n" , (*matrixSize));
            i++;
        }else
        {
            if( integerFromCharacter >=0 && integerFromCharacter <=9)
            {
                integerArray[i-1] = integerFromCharacter; 
                printf("\nWriting into array : [%d] value: %d\n", i-1 , integerFromCharacter);       
                i++;
            }   
        }
        
    }

    for(int i = 0 ; i < (*matrixSize) ; i++)
    {
        for(int j = 0 ; j < (*matrixSize) ; j++)
        {
            printf("\nwriting into 2d array location [%d] [%d] value: %d\n", i , j , integerArray[k]);
            keyMatrixParsed[i][j] = integerArray[k];
            k++;

        }
    }


    fclose(keyMatrixFile);
    free(integerArray);

    printf("\ndone...\n");

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
    int* matrixSize; 
    
    char* formatedText = FormatText(plainTextFileLocation);
    int** formatedMatrix = FormatMatrix(keyFileLocation, matrixSize);



// @todo FIX SEGMENTATION FAULT ERROR AFTER FREEING MEM 

    //HillCipherSecretStruct builtHillCypherStruct = BuildHillCipherStruct(FormatText(plainTextFileLocation), FormatMatrix(keyFileLocation));
    //printf("%s" , formatedText);
    printf("Freeing Memory...\n");
    printf("freed formatedText");
    free(formatedMatrix);
    printf("freed formatedMatrix");
    return finalCipherStruct;
}
