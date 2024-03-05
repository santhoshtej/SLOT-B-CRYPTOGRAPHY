#include <stdio.h>
#include <string.h>
void caesarCipher(char message[], int key) {
    int length = strlen(message);
     int i;
    for ( i = 0; i < length; ++i) {
        char ch = message[i];
        if (ch >= 'a' && ch <= 'z')
            ch = 'a' + (ch - 'a' + key) % 26;
        else if (ch >= 'A' && ch <= 'Z')
            ch = 'A' + (ch - 'A' + key) % 26;
        message[i] = ch;
    }
}
int main() {
    char message[100];
    int key;
    printf("Enter a message: ");
    fgets(message, sizeof(message), stdin);
    printf("Enter the key (1-25): ");
    scanf("%d", &key);
    if (key < 1 || key > 25) {
        printf("Invalid key! Please enter a key between 1 and 25.\n");
        return 1;
    }
    caesarCipher(message, key);
    printf("Encrypted message: %s\n", message);
    return 0;
}


OUTPUT:
Enter a message: CRYPTOGRAPHY
Enter the key (1-25): 6
Encrypted message: IXEVZUMXGVNE
