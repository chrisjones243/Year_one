#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

char *read_string(const char *filename){
    FILE *file = fopen(filename, "r");

    if (file == NULL){ // check if the file is opened
        exit(1);
    }

    // Get the size of the file
    int file_size = 0;
    fseek(file, 0L, SEEK_END);
    file_size = ftell(file);
    rewind(file);


    char *text = malloc(sizeof(char) * file_size); // allocate memory for the text
    // read the file
    if (text) {
        fread(text, sizeof(char), file_size, file);
    }


    for (int i = 0 ; i < strlen(text) ; i++) {
        if (!isalnum(text[i])) {
            memmove(&text[i], &text[i + 1], strlen(text) - i); // remove the non-alphanumeric characters
        }
        text[i] = toupper(text[i]); // make the characters uppercase
    }

    fclose(file);

    return text;
}


int cmpfunc (const void * a, const void * b) {
   return ( *(char*)a - *(char*)b );
}

void encrypt_columnar(const char *message_filename, const char *key_filename, char **result){
    char *message = read_string(message_filename);
    char *key = read_string(key_filename);

    int key_length = strlen(key);
    int array_depth = ceil((double) strlen(message) / key_length) + 1;

    char array[key_length][array_depth]; // create a 2D array

    int i = 0; // counter for the message
    for (int r = 0; r < array_depth; r++) { // loop through the rows
        for (int c = 0 ; c < key_length ; c++) { // loop through the columns
            if (r == 0) {
                array[c][r] = key[c]; // add the key to the first row
            } else {
                if (i >= strlen(message)) { // add X's if the message is shorter than the key
                    array[c][r] = 'X';
                } else {
                    array[c][r] = message[i]; // add the message to the array
                }
                i++;
            }
        }
    }

    char *order = malloc(sizeof(char) * key_length);
    strcpy(order, key);

    qsort(order, key_length, sizeof(char), cmpfunc); // sort the key


    char *encrypted = malloc(sizeof(char) * key_length * (array_depth - 1));

    for (int r = 1; r < array_depth; r++) {
        int j = 0;
        for ( int c = 0; (j < key_length) && (c < key_length); c++) {
            if (order[j] == array[c][0]) {
                strncat(encrypted, &array[c][r], 1); // add the characters to the encrypted string
                j++;
                c = -1;
            }
        }
    }
    
    *result = malloc(sizeof(char) * key_length * (array_depth - 1));
    strcpy(*result, encrypted);

    free(encrypted);
    free(order);
    free(message);
    free(key);
      
}


int decrypt_columnar(const char *message_filename, const char *key_filename, char **result){
    char *message = read_string(message_filename);
    char *key = read_string(key_filename);

    int key_length = strlen(key);
    int message_length = strlen(message);

    char *ordered_key = malloc(sizeof(char) * key_length);
    strcpy(ordered_key, key);
    qsort(ordered_key, key_length, sizeof(char), cmpfunc); // sort the key

    int array_depth = ceil((double) message_length / key_length) + 1;

    char array[key_length][array_depth]; // create a 2D array


    // add the message to the 2d array
    int i = 0; // counter for the message
    for (int r = 0 ; r < array_depth ; r++) { // loop through the columns
        for (int c = 0; c < key_length; c++) { // loop through the rows
            if (r == 0) {
                array[c][r] = ordered_key[c]; // add the ordered key to the first row
            } else {
                if (i >= strlen(message)) { // add X's if the message is shorter than the key
                    array[c][r] = 'X';
                } else {
                    array[c][r] = message[i]; // add the message to the array
                }
                i++;
            }
        }
    }

    char *decrypted = malloc(sizeof(char) * message_length);

    for (int r = 1; r < array_depth; r++) {
        int j = 0;
        for ( int c = 0; (j < key_length) && (c < key_length); c++) {
            if (ordered_key[j] == array[c][0]) {
                strncat(decrypted, &array[c][r], 1); // add the characters to the encrypted string
                j++;
                c = -1;
            }
        }
    }

    *result = malloc(sizeof(char) * message_length);
    strcpy(*result, decrypted);

    free(decrypted);
    free(ordered_key);
    free(message);
    free(key);

    return 1;   
}

int main() {
    char message[] = "./message.txt";
    char key[] = "./key.txt";
    char *result = malloc(sizeof(char) * 100);
    encrypt_columnar(message, key, &result);


    char encrypted[] = "./encrypted.txt";
    char *result2 = malloc(sizeof(char) * 100);

    decrypt_columnar(encrypted, key, &result2);


    return 0;
}
