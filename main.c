/*
Quin Irving <irvingq@sheridancollege.ca>
----------------------------------------------------------------------
 /

/
 * File:   main.c
 * Author: Quin Irving <irving@sheridancollege.ca>
 *
 * Created on February 26, 2022, 11:39 AM
 */

// Assignment N2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// The name of the input file and output file
#define IN_FILE "quotes.txt"
#define OUT_FILE "output.txt"

// Defines how many quotes will be in the OUT_FILE
#define MAX_QUOTES 300

// This function will be used in sorting to swap strings ("pointers").
void swap(char**, char**);

// Selection Sort function here.
void selection_sort(char**, size_t);

// Read quotes from file and add them to array of pointers.
// You also must user selection_sort inside this function!
void read_in(char**);

// Print the quotes using array of pointers.
void print_out(char**);

// Save the sorted quotes in the OUT_FILE file.
void write_out(char**);

// Free memory pointed by pointers in the array of pointers!
void free_memory(char**);


int main() {

    // Create array of pointers. Each pointer should point to heap memory where each quote is kept.
    // I.e. quotes[0] points to smallest string.
    // We need +1 to insert the new quote at the end of the array and then re-sort.
    char* quotes[MAX_QUOTES+1]={NULL};

    // Read quotes from file and place them into array quotes.
    // Also, sort as you add them
    // You also need to print how many lines were processed
    read_in(quotes);

    // Print MAX_QUOTES shortest quotes
    print_out(quotes);

    // Save MAX_QUOTES shortest quotes in the file OUT_FILE
    write_out(quotes);

    // Free memory allocated by array of pointers
    free_memory(quotes);

    return (0);
}

// Add all required functions below!
void swap(char** a, char** b) {
    char* tmp = *a;
    *a = *b;
    *b = tmp;
}

void selection_sort(char** c, size_t s) {
    for (int i = 0; i < s - 1; i++) {
        int lowestIndex = i;
        for (int j = i + 1; j < s; j++) {
            if (strlen(c[j]) <= strlen(c[lowestIndex])) {
                if (strlen(c[j]) == strlen(c[lowestIndex])) {
                    if (strcoll(c[j], c[lowestIndex]) < 0) {
                        lowestIndex = j;
                    }
                } else {
                    lowestIndex = j;
                }
            }
        }
        swap(&c[i], &c[lowestIndex]);
    }

}

void read_in(char** ch) {
    int c;
    int maxLength = 0;

    FILE* fp = fopen(IN_FILE, "r");

    if (fp == NULL) {
        perror("Error reading file");
        exit(1);
    }

    int currentCount = 0;

    while((c = fgetc(fp)) != EOF) {
        if (c == '\n') {
            if (currentCount > maxLength) {
                maxLength = currentCount;
            }
            currentCount = 0;
        } else {
            currentCount += 1;
        }
    }
    printf("Characters in the longest quote: %d\n", maxLength);

    rewind(fp);

    char* tmp = (char*) calloc(maxLength, sizeof(char));
    if (tmp == NULL) {
        perror("Error: Failed to allocate heap memory");
        exit(1);
    }

    int i = 0;
    int totalSize = 1;
    int lines = 0;

    while (fgets(tmp, maxLength, fp)) {
        lines += 1;
        if (strlen(tmp) > 3) {
            if (i < MAX_QUOTES) {
                ch[i] = (char *) calloc(strlen(tmp) + 1, sizeof(char));
                if (ch[i] == NULL) {
                    perror("Error: Failed to allocate heap memory");
                    exit(1);
                }
                strcpy(ch[i], tmp);
                selection_sort(ch, totalSize);
                totalSize += 1;
                i++;
            } else {
                ch[i] = (char *) realloc(ch[i], strlen(tmp) * sizeof(char));
                if (ch[i] == NULL) {
                    perror("Error: Failed to allocate heap memory");
                    exit(1);
                }
                strcpy(ch[i], tmp);
                selection_sort(ch, totalSize);
            }

        }

    }

    printf("Lines processed in the input file: %d\n", lines);

    fclose(fp);
    free(tmp);

}

void print_out(char** c) {
    for (int t = 0; t < MAX_QUOTES; t++) {
        if (c[t] != NULL) {
            printf("%s", c[t]);

            if (c[t][strlen(c[t]) - 1] != '\n') {
                printf("\n");
            }
        }
    }
}

void write_out(char** c) {
    FILE* fp = fopen(OUT_FILE, "w+");
    if (fp == NULL) {
        perror("Error reading file");
        exit(1);
    }
    for (int t = 0; t < MAX_QUOTES; t++) {
        if (c[t] != NULL) {
            fprintf(fp, "%s", c[t]);

            if (c[t][strlen(c[t]) - 1] != '\n') {
                fprintf(fp, "\n");
            }
        }
    }
    fclose(fp);
}
void free_memory(char** c) {
    for (int t = 0; t < MAX_QUOTES; t++) {
        if (c[t] != NULL) {
            free(c[t]);
        }
    }
    //free(c);
}