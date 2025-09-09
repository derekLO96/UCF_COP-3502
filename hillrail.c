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


char* FormatText(char* plainTextFileLocation , int matrixSize);
int** FormatMatrix(char* keyMatrixFileLocation , int matrixSize);
long GetFileSize(FILE* file);
void RainWeightEncodedText(EncryptedTextStruct* encryptedText , int rainweight);
HillCipherSecretStruct* BuildHillCipherStruct(char* plainText , int** key , int matrixSize);
EncryptedTextStruct* EncryptText(char* plainTextFileLocation , char* keyFileLocation , int rainWeight);
EncryptedTextStruct* PerformHillCipherEncryption( HillCipherSecretStruct* hillCipherStruct);
int* ConvertCharacterArrayToIntArray(char* characterArray);
int GetMatrixSize(char* keyFileLocation);
char* CovertBackToChar(int *encoded , int sizeArray);
void RainWeightTwo(EncryptedTextStruct* encryptedTextStruct);

int main(int argc , char* argv[])
{
    char* mode = argv[1];
    char* keyFileLocation = argv[2];
    char* plainTextFileLocation = argv[3];    
    int rainWeight = atoi(argv[4]);


    EncryptedTextStruct* cipherText = EncryptText(plainTextFileLocation , keyFileLocation, rainWeight);
    

    //printf("%s" , cipherText.encryptedText);

    return 0;
}

///@brief Takes in the plain text file location and parses the text into the correct format.
///@param plainTextFileLocation --> Plain text file location
///@return --> Formated text
char *FormatText(char* plainTextFileLocation , int matrixSize)
{
    
    FILE* plainTextFile = fopen(plainTextFileLocation , "r");
    
    if(!plainTextFile)
    {
        printf("failed to open file %s" , plainTextFileLocation);
        return "Failed";
    }
    long plainTextFileSize = GetFileSize(plainTextFile) + 1;

    char* plainTextParsed = malloc(plainTextFileSize * sizeof(char));
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
       }else if(currentCharacter > 'Z')
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
int** FormatMatrix(char* keyFileLocation , int matrixSize)
{
    printf("\nKey Matrix: \n");

    FILE* keyMatrixFile = fopen(keyFileLocation , "r");    

    int** keyMatrixParsed = malloc(matrixSize * sizeof(int*)); 

    for(int i = 0 ; i < matrixSize ; i++)
    {
        keyMatrixParsed[i] = malloc(matrixSize * sizeof(int));      

    }
    fseek(keyMatrixFile , 1 , SEEK_CUR);
    for(int i = 0 ; i < matrixSize ; i++)
    {
        printf(" ");
        for(int j = 0 ; j < matrixSize ; j++)
        {       

            fscanf(keyMatrixFile , "%d " , &keyMatrixParsed[i][j]);            
            printf("%d " , keyMatrixParsed[i][j]);
            
        }
        printf("\n");

    }

    fclose(keyMatrixFile);


    return keyMatrixParsed;
}

/// @brief Builds a struct meant to hold all information for the Hill Cipher. This is not the finished product, but a 
///meer placeholder for the final cipher. 
/// @param plainText --> The formated plain text to be encrypted
/// @param key --> The int matrix key that will encrypt the string
/// @return --> A built hill Cipher struct ready for encryption
HillCipherSecretStruct* BuildHillCipherStruct(char *plainTextFormatted, int **key , int matrixSize)
{
    int plainTextSize = (int)strlen(plainTextFormatted);
    int padding = (matrixSize - (plainTextSize % matrixSize)) % matrixSize;
    char fillCharacter = 'X';
    char* padded = malloc((plainTextSize + padding + 1) * sizeof(char));

    memcpy(padded , plainTextFormatted , plainTextSize);

    if(plainTextSize > 0 && plainTextFormatted[plainTextSize - 1] == 'X') fillCharacter = 'Z';

    for(int i = 0 ; i < padding ; i++)
    {
        padded[plainTextSize + i] = fillCharacter;
    }

    padded[plainTextSize +padding] = '\0';

    HillCipherSecretStruct* hillCipherStruct = malloc(sizeof(HillCipherSecretStruct));


    hillCipherStruct->plainTextFormated = padded;
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

void RainWeightEncodedText(EncryptedTextStruct *encryptedText, int rainweight)
{

    switch (rainweight)
    {
    case 2:
        RainWeightTwo(encryptedText);
        break;
    
    case 3 :
        //RainWeightThree(encryptedText);
        break;
    }


}

void RainWeightTwo(EncryptedTextStruct* encryptedTextStruct)
{
    char* encryptedTextReference = encryptedTextStruct->encryptedText;
    int encryptedArrayLength = strlen(encryptedTextReference);

    char* tempStr1 = malloc((encryptedArrayLength / 2 + 1) * sizeof(char));
    char* tempStr2 = malloc((encryptedArrayLength / 2 + 1) * sizeof(char));

    int idexOne = 0, indexTwo = 0;

    for (int i = 0; i < encryptedArrayLength; i++)
    {
        if (i % 2 == 0)
            tempStr1[idexOne++] = encryptedTextReference[i];
        else
            tempStr2[indexTwo++] = encryptedTextReference[i];
    }

    tempStr1[idexOne] = '\0';
    tempStr2[indexTwo] = '\0';

    char* resizedString = realloc(tempStr1,
                                  (strlen(tempStr1) + strlen(tempStr2) + 1) * sizeof(char));


    strcat(resizedString, tempStr2);  
    free(tempStr2);

    strcpy(encryptedTextReference, resizedString);

    free(resizedString);
}


/// @brief Encrypts plain text from a .txt file using a key matrix from a different .txt file.
/// @param plainTextFileLocation --> The location of the plain text file to be encrypted
/// @param keyFileLocation --> The location of the key matrix that will be used to perform the respected algebra
/// @return --> A struct containing the encrypted text
EncryptedTextStruct* EncryptText(char *plainTextFileLocation, char *keyFileLocation , int rainweight)
{

    int matrixSize = GetMatrixSize(keyFileLocation);
    char *plainText = FormatText(plainTextFileLocation , matrixSize);
    int **keyMatrix = FormatMatrix(keyFileLocation, matrixSize);


    HillCipherSecretStruct* hillCipherStruct = BuildHillCipherStruct(plainText , keyMatrix , matrixSize);

    free(plainText);

    printf("\nPlainText:\n");
    printf("%s" , hillCipherStruct->plainTextFormated);

    printf("\n\nCipherText:\n");
    EncryptedTextStruct* finalCipherStruct = PerformHillCipherEncryption(hillCipherStruct);
    RainWeightEncodedText(finalCipherStruct , rainweight);
    printf("%s\n" , finalCipherStruct->encryptedText);

    printf("\nDepth: %d\n" , rainweight);


    for(int i = 0 ; i < matrixSize; i++) free(keyMatrix[i]);
    free(keyMatrix);
    free(hillCipherStruct->plainTextFormated);
    free(hillCipherStruct);
    return finalCipherStruct;
}

int GetMatrixSize(char* keyFileLocation)
{
    FILE* keyMatrixFile = fopen(keyFileLocation , "r");
    int matrixSize = 0;
    
    if(fscanf(keyMatrixFile , "%d " , &matrixSize) != 1)
    {
        printf("Error");
    }
    fclose(keyMatrixFile);


    return matrixSize;


}

EncryptedTextStruct* PerformHillCipherEncryption( HillCipherSecretStruct* hillCipherStruct)
{

    int matrixSize = hillCipherStruct->matrixSize;
    char* plainTextFormated = hillCipherStruct->plainTextFormated;
    int dataLength = (int)strlen(plainTextFormated);
    int* letterValueArray = ConvertCharacterArrayToIntArray(plainTextFormated);

    int *encoded = malloc(dataLength * sizeof(int));
    for(int i = 0 ; i < dataLength ; i += matrixSize)
    {
        for (int j = 0 ; j < matrixSize ; j ++)
        {
            int sum = 0;

            for (int z = 0 ; z < matrixSize ; z ++)
            {
                sum += hillCipherStruct->key[j][z] * letterValueArray[i + z];

            
            }
            sum %= 26;
            if(sum < 0) sum += 26;
            encoded[i + j] = sum;

        }

    }

    char* encodedText = CovertBackToChar(encoded , dataLength);
    free(encoded);
    free(letterValueArray);


    EncryptedTextStruct* encrypted = malloc(sizeof(EncryptedTextStruct));
    encrypted->encryptedText = encodedText;


    return encrypted;

}

char* CovertBackToChar(int *encoded , int sizeOfArray)
{
    char* converted = malloc((sizeOfArray + 1) * sizeof(char));

    for (int i = 0; i < sizeOfArray; i++)
    {
        //printf("value : %d\n" , encoded[i]);
        converted[i] = ( (encoded[i] %26) + 'A');
    }
    converted[sizeOfArray] = '\0';
    return converted;

}

int* ConvertCharacterArrayToIntArray(char* characterArray)
{
    int characterArraySize = strlen(characterArray);
    int* convertedArray = malloc((characterArraySize) * sizeof(int));
    //printf("Number of characters in the plainText array: %d\n" , characterArraySize);
    //works... DONT TOUCH
    for (int i = 0 ; i < characterArraySize ; i++)
    {
        convertedArray[i] = (characterArray[i] - 'A') % 26;
        //printf("Letter: %c\t Value: %d\n ", characterArray[i] , convertedArray[i] );
    }
    


    return convertedArray;
}