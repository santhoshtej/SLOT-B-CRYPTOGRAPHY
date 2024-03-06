#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// Function to decrypt the ciphertext using a given key
void decrypt(char *ciphertext, char *key, char *plaintext) {
    int i;
    for (i = 0; ciphertext[i] != '\0'; ++i) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = key[ciphertext[i] - 'A'];
        } else if (ciphertext[i] >= 'a' && ciphertext[i] <= 'z') {
            plaintext[i] = key[ciphertext[i] - 'a'];
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[i] = '\0';
}

// Function to calculate the frequency of each letter in a given text
void calculateFrequency(char *text, int *frequency) {
    int i;
    for (i = 0; text[i] != '\0'; ++i) {
        if (text[i] >= 'A' && text[i] <= 'Z') {
            frequency[text[i] - 'A']++;
        } else if (text[i] >= 'a' && text[i] <= 'z') {
            frequency[text[i] - 'a']++;
        }
    }
}

// Function to find the most likely plaintexts
void findLikelyPlaintexts(char *ciphertext, int *frequency, char *key) {
    char plaintext[strlen(ciphertext) + 1];
    int i, j, maxIndex, maxValue;
    char tempKey[ALPHABET_SIZE];

    memcpy(tempKey, key, ALPHABET_SIZE);

    for (i = 0; i < ALPHABET_SIZE; ++i) {
        // Find the most frequent letter in the ciphertext
        maxIndex = 0;
        maxValue = frequency[0];
        for (j = 1; j < ALPHABET_SIZE; ++j) {
            if (frequency[j] > maxValue) {
                maxIndex = j;
                maxValue = frequency[j];
            }
        }
        
        // Swap the letters in the temporary key to decrypt with the key corresponding to the most frequent letter
        char temp = tempKey[maxIndex];
        tempKey[maxIndex] = tempKey['E' - 'A'];
        tempKey['E' - 'A'] = temp;

        // Decrypt using the modified key
        decrypt(ciphertext, tempKey, plaintext);
        printf("Plaintext (using key %d): %s\n", i+1, plaintext);

        // Reset the frequency array for the next iteration
        frequency[maxIndex] = 0;
    }
}

int main() {
    char ciphertext[1000];
    char key[ALPHABET_SIZE] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int frequency[ALPHABET_SIZE] = {0};
    int numPlaintexts;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0'; // Remove newline character if present

    printf("Enter the number of possible plaintexts to display: ");
    scanf("%d", &numPlaintexts);

    calculateFrequency(ciphertext, frequency);
    findLikelyPlaintexts(ciphertext, frequency, key);

    return 0;
}
