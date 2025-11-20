#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void encryptFile();
void decryptFile();

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Rail Fence Cipher Menu ---\n");
        printf("1. Encrypt\n");
        printf("2. Decrypt\n");
        printf("3. Exit\nEnter choice: ");
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

    int r;
    printf("Enter number of rails: ");
    scanf("%d", &r);

    char text[1000], ch;
    int n = 0;

    while ((ch = fgetc(fin)) != EOF)
        if (isalpha(ch))
            text[n++] = toupper(ch);

    text[n] = '\0';

    char rail[r][1000];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < n; j++)
            rail[i][j] = 0;

    int row = 0, dir = 1;

    for (int i = 0; i < n; i++)
    {
        rail[row][i] = text[i];

        if (row == 0)
            dir = 1;
        else if (row == r - 1)
            dir = -1;

        row += dir;
    }

    for (int i = 0; i < r; i++)
        for (int j = 0; j < n; j++)
            if (rail[i][j] != 0)
                fputc(rail[i][j], fout);

    fclose(fin);
    fclose(fout);
    printf("Encrypted → encrypt.txt\n");
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

    int r;
    printf("Enter SAME number of rails: ");
    scanf("%d", &r);

    char text[1000], ch;
    int n = 0;

    while ((ch = fgetc(fin)) != EOF)
        if (isalpha(ch))
            text[n++] = toupper(ch);

    text[n] = '\0';

    char rail[r][1000];
    for (int i = 0; i < r; i++)
        for (int j = 0; j < n; j++)
            rail[i][j] = 0;

    int row = 0, dir = 1;

    for (int i = 0; i < n; i++)
    {
        rail[row][i] = '*';

        if (row == 0)
            dir = 1;
        else if (row == r - 1)
            dir = -1;

        row += dir;
    }

    int idx = 0;
    for (int i = 0; i < r; i++)
        for (int j = 0; j < n; j++)
            if (rail[i][j] == '*')
                rail[i][j] = text[idx++];

    row = 0;
    dir = 1;

    for (int i = 0; i < n; i++)
    {
        fputc(rail[row][i], fout);

        if (row == 0)
            dir = 1;
        else if (row == r - 1)
            dir = -1;

        row += dir;
    }

    fclose(fin);
    fclose(fout);
    printf("Decrypted → decrypt.txt\n");
}
