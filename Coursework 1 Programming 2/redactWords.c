#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

const char* upper_case(char *temp) {
    char *word = strcpy(malloc(strlen(temp) + 1), temp); // copy the word to a new string

    for (int i = 0; i < strlen(word); i++) { // make the word's uppercase
        if (word[i] >= 'a' && word[i] <= 'z') { // if the char is lowercase
            word[i] = word[i] - 32; // make it uppercase
        }
    }
    return word;
}


void redact_words(const char *text_filename, const char *redact_words_filename){
    FILE *text_file = fopen(text_filename, "r");
    FILE *redact_words_file = fopen(redact_words_filename, "r");

    // check if the files are opened
    if (text_file == NULL || redact_words_file == NULL){
        return;
    }

    // Get the size of the text file
    int text_file_size = 0;
    fseek(text_file, 0L, SEEK_END);
    text_file_size = ftell(text_file);
    rewind(text_file);

    // Get the size of the redact words file
    int redact_words_file_size = 0;
    fseek(redact_words_file, 0L, SEEK_END);
    redact_words_file_size = ftell(redact_words_file);
    rewind(redact_words_file);

    // read the text files
    char *text = malloc(sizeof(char) * text_file_size);
    if (text) {
        fread(text, sizeof(char), text_file_size, text_file); // read the text file
        text[text_file_size - 1] = '\0'; // removes the last \n
    }

    // read the redact words file
    char *redact_words = malloc(sizeof(char) * redact_words_file_size);
    if (redact_words) {
        fread(redact_words, sizeof(char), redact_words_file_size, redact_words_file);
    }

    // remove the non-alphabetical or not comma characters
    for (int i = 0 ; i < strlen(redact_words) ; i++) { 
        if (isalpha(redact_words[i]) == 0 && redact_words[i] != ',') {
            memmove(&redact_words[i], &redact_words[i + 1], strlen(redact_words) - i); // remove the char
            i--; // decrement i to check the new char
        }
    }


    // edited text
    char *edited_text = malloc(sizeof(char) * text_file_size);


    // tokens
    char *redact_token, *rest_redact;
    char *text_token, *rest_text;

    for (redact_token = strtok_r(redact_words, ",", &rest_redact); redact_token ; redact_token = strtok_r(NULL, ",", &rest_redact)) { // for each redact word


        for (text_token = strtok_r(text, " ", &rest_text); text_token ; text_token = strtok_r(NULL, " ", &rest_text)) { // for each word in the text

            char *saved_end = malloc(sizeof(char) * strlen(text_token));
            for (int i = 0; i < strlen(text_token); i++) { // remove the non-alphabetical characters
                if (isalpha(text_token[i]) == 0) {
                    strcat(saved_end, &text_token[i]);
                    text_token[i] = '\0';
                }
            }

            // make the current word's uppercase
            const char *upper_current_word = upper_case(text_token);
            const char *upper_current_redact_word = upper_case(redact_token);

            // compare the current words
            if (strcmp(upper_current_word, upper_current_redact_word) == 0){
                int j;
                for (j = 0; j < strlen(text_token); j++) {
                    text_token[j] = '*'; // replace the current word with asterisks
                }
            }

            strcat(edited_text, text_token); // add the current word to the edited text
            strcat(edited_text, saved_end); // add the saved ends to the edited text
            memset(saved_end, 0, strlen(saved_end)); // clear the saved ends
            strcat(edited_text, " "); // add a space to the edited text
        }
        strcpy(text, edited_text); // copy the edited text to the text
        memset(edited_text, 0, sizeof(sizeof(char) * text_file_size)); // clear the edited text

    }

    text[text_file_size - 1] = '\n'; // removes last char, ' ', and replaces with \n

    // write the result to a file
    FILE *result_file = fopen("result.txt", "w");
    fputs(text, result_file);

    // free memory
    fclose(result_file);
    fclose(text_file);
    fclose(redact_words_file);
}

int main(){
    char filename[] = "./check_in.txt";
    char redact_words_filename[] = "./check_redact.txt";

    redact_words(filename, redact_words_filename);
    return 0;
}