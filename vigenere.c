#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void encryptFile();
void decryptFile();

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Vigenere Cipher Menu ---\n");
        printf("1. Encrypt File\n");
        printf("2. Decrypt File\n");
        printf("3. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        if (choice == 1)
            encryptFile();
        else if (choice == 2)
            decryptFile();
        else if (choice == 3)
            break;
        else
            printf("Invalid choice!\n");
    }
    return 0;
}

void encryptFile()
{
    FILE *fin = fopen("plain.txt", "r");
    FILE *fout = fopen("encrypt.txt", "w");

    if (!fin || !fout)
    {
        printf("File error!\n");
        return;
    }

    char key[100];
    printf("Enter KEY (CAPITAL LETTERS): ");
    scanf("%s", key);

    int keyLen = strlen(key), i = 0;
    char ch;

    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            int shift = key[i % keyLen] - 'A';
            ch = ((ch - 'A' + shift) % 26) + 'A';
            i++;
        }
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Encryption done → encrypt.txt\n");
}

void decryptFile()
{
    FILE *fin = fopen("encrypt.txt", "r");
    FILE *fout = fopen("decrypt.txt", "w");

    if (!fin || !fout)
    {
        printf("File error!\n");
        return;
    }

    char key[100];
    printf("Enter SAME KEY (CAPITAL LETTERS): ");
    scanf("%s", key);

    int keyLen = strlen(key), i = 0;
    char ch;

    while ((ch = fgetc(fin)) != EOF)
    {
        if (ch >= 'A' && ch <= 'Z')
        {
            int shift = key[i % keyLen] - 'A';
            ch = ((ch - 'A' - shift + 26) % 26) + 'A';
            i++;
        }
        fputc(ch, fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption done → decrypt.txt\n");
}
