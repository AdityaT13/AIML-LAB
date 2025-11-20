#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

char matrix[5][5];

void createMatrix(char key[])
{
    int used[26] = {0};
    int i, j, k = 0;
    char ch;

    used['J' - 'A'] = 1;

    for (i = 0; key[i]; i++)
    {
        ch = toupper(key[i]);
        if (ch == 'J')
            ch = 'I';
        if (ch >= 'A' && ch <= 'Z' && !used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }

    for (ch = 'A'; ch <= 'Z'; ch++)
    {
        if (!used[ch - 'A'])
        {
            matrix[k / 5][k % 5] = ch;
            used[ch - 'A'] = 1;
            k++;
        }
    }
}

void findPos(char ch, int *r, int *c)
{
    if (ch == 'J')
        ch = 'I';
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < 5; j++)
            if (matrix[i][j] == ch)
            {
                *r = i;
                *c = j;
                return;
            }
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
    printf("Enter KEY: ");
    scanf("%s", key);

    createMatrix(key);

    char a, b;
    int r1, c1, r2, c2;

    while (1)
    {
        a = fgetc(fin);
        while (a != EOF && !isalpha(a))
            a = fgetc(fin);
        if (a == EOF)
            break;

        b = fgetc(fin);
        while (b != EOF && !isalpha(b))
            b = fgetc(fin);
        if (b == EOF || toupper(a) == toupper(b))
            b = 'X';

        a = toupper(a);
        b = toupper(b);

        findPos(a, &r1, &c1);
        findPos(b, &r2, &c2);

        if (r1 == r2)
        {
            fputc(matrix[r1][(c1 + 1) % 5], fout);
            fputc(matrix[r2][(c2 + 1) % 5], fout);
        }
        else if (c1 == c2)
        {
            fputc(matrix[(r1 + 1) % 5][c1], fout);
            fputc(matrix[(r2 + 1) % 5][c2], fout);
        }
        else
        {
            fputc(matrix[r1][c2], fout);
            fputc(matrix[r2][c1], fout);
        }
    }

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

    char key[100];
    printf("Enter SAME KEY: ");
    scanf("%s", key);

    createMatrix(key);

    char a, b;
    int r1, c1, r2, c2;

    while (1)
    {
        a = fgetc(fin);
        while (a != EOF && !isalpha(a))
            a = fgetc(fin);
        if (a == EOF)
            break;

        b = fgetc(fin);
        while (b != EOF && !isalpha(b))
            b = fgetc(fin);
        if (b == EOF)
            break;

        a = toupper(a);
        b = toupper(b);

        findPos(a, &r1, &c1);
        findPos(b, &r2, &c2);

        if (r1 == r2)
        {
            fputc(matrix[r1][(c1 + 4) % 5], fout);
            fputc(matrix[r2][(c2 + 4) % 5], fout);
        }
        else if (c1 == c2)
        {
            fputc(matrix[(r1 + 4) % 5][c1], fout);
            fputc(matrix[(r2 + 4) % 5][c2], fout);
        }
        else
        {
            fputc(matrix[r1][c2], fout);
            fputc(matrix[r2][c1], fout);
        }
    }

    fclose(fin);
    fclose(fout);
    printf("Decrypted → decrypt.txt\n");
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Playfair Cipher Menu ---\n");
        printf("1. Encrypt\n2. Decrypt\n3. Exit\nEnter choice: ");
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
