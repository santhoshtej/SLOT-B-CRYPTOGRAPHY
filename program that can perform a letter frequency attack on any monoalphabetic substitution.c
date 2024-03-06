#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// English letter frequencies
float letter_frequency[ALPHABET_SIZE] = {
    0.08167, 0.01492, 0.02782, 0.04253, 0.12702, 0.02228, 0.02015,
    0.06094, 0.06966, 0.00153, 0.00772, 0.04025, 0.02406, 0.06749,
    0.07507, 0.01929, 0.00095, 0.05987, 0.06327, 0.09056, 0.02758,
    0.00978, 0.02360, 0.00150, 0.01974, 0.00074
};

// Function to calculate the chi-square score for a given plaintext
float chi_square_score(char *plaintext) {
    int observed_frequency[ALPHABET_SIZE] = {0};
    int total_letters = 0;
    
    // Count letter occurrences
    for (int i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            observed_frequency[plaintext[i] - 'A']++;
            total_letters++;
        }
    }
    
    // Calculate chi-square score
    float score = 0.0;
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        float expected = letter_frequency[i] * total_letters;
        float observed = observed_frequency[i];
        score += ((observed - expected) * (observed - expected)) / expected;
    }
    return score;
}

// Function to decrypt a ciphertext using a given key
void decrypt(char *ciphertext, char *key) {
    for (int i = 0; ciphertext[i] != '\0'; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            printf("%c", key[ciphertext[i] - 'A']);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

// Function to perform letter frequency attack
void frequency_attack(char *ciphertext, int top_n) {
    char key[ALPHABET_SIZE + 1] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char plaintext[strlen(ciphertext) + 1];
    strcpy(plaintext, ciphertext);
    
    float scores[ALPHABET_SIZE] = {0};
    
    // Calculate scores for each possible key
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        for (int j = 0; plaintext[j] != '\0'; j++) {
            if (plaintext[j] >= 'A' && plaintext[j] <= 'Z') {
                plaintext[j] = (plaintext[j] - 'A' + i) % ALPHABET_SIZE + 'A';
            }
        }
        scores[i] = chi_square_score(plaintext);
    }
    
    // Sort scores and corresponding keys
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (scores[i] > scores[j]) {
                float temp_score = scores[i];
                scores[i] = scores[j];
                scores[j] = temp_score;
                char temp_key = key[i];
                key[i] = key[j];
                key[j] = temp_key;
            }
        }
    }
    
    // Output top n possible plaintexts
    printf("Top %d possible plaintexts:\n", top_n);
    for (int i = 0; i < top_n; i++) {
        for (int j = 0; plaintext[j] != '\0'; j++) {
            if (plaintext[j] >= 'A' && plaintext[j] <= 'Z') {
                plaintext[j] = (plaintext[j] - 'A' + i) % ALPHABET_SIZE + 'A';
            }
        }
        printf("Plaintext #%d (chi-square score %.2f): ", i+1, scores[i]);
        decrypt(ciphertext, key);
    }
}

int main() {
    char ciphertext[1000];
    int top_n;

    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);
    ciphertext[strcspn(ciphertext, "\n")] = '\0';  // remove newline character

    printf("Enter the number of possible plaintexts to generate: ");
    scanf("%d", &top_n);

    frequency_attack(ciphertext, top_n);

    return 0;
}
