#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void encryptFile();
void decryptFile();

int modInverse(int a)
{
    a = a % 26;
    for (int x = 1; x < 26; x++)
        if ((a * x) % 26 == 1)
            return x;
    return -1;
}

int main()
{
    int choice;
    while (1)
    {
        printf("\n--- Hill Cipher 3x3 Menu ---\n");
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

void encryptFile()
{
    FILE *fin = fopen("plain.txt", "r");
    FILE *fout = fopen("encrypt.txt", "w");

    if (!fin || !fout)
    {
        printf("File error!\n");
        return;
    }

    int k[3][3];
    printf("Enter 3x3 key matrix:\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &k[i][j]);

    char text[1000], ch;
    int n = 0;

    while ((ch = fgetc(fin)) != EOF)
        if (isalpha(ch))
            text[n++] = toupper(ch);

    while (n % 3 != 0)
        text[n++] = 'X';

    for (int i = 0; i < n; i += 3)
    {
        int a = text[i] - 'A';
        int b = text[i + 1] - 'A';
        int c = text[i + 2] - 'A';

        int r1 = (k[0][0] * a + k[0][1] * b + k[0][2] * c) % 26;
        int r2 = (k[1][0] * a + k[1][1] * b + k[1][2] * c) % 26;
        int r3 = (k[2][0] * a + k[2][1] * b + k[2][2] * c) % 26;

        fputc(r1 + 'A', fout);
        fputc(r2 + 'A', fout);
        fputc(r3 + 'A', fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Encryption → encrypt.txt\n");
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

    int k[3][3];
    printf("Enter SAME 3x3 key matrix:\n");
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            scanf("%d", &k[i][j]);

    int det =
        k[0][0] * (k[1][1] * k[2][2] - k[1][2] * k[2][1]) -
        k[0][1] * (k[1][0] * k[2][2] - k[1][2] * k[2][0]) +
        k[0][2] * (k[1][0] * k[2][1] - k[1][1] * k[2][0]);

    det = (det % 26 + 26) % 26;

    int invDet = modInverse(det);
    if (invDet == -1)
    {
        printf("Key not invertible!\n");
        return;
    }

    int adj[3][3];
    adj[0][0] = (k[1][1] * k[2][2] - k[1][2] * k[2][1]);
    adj[0][1] = -(k[0][1] * k[2][2] - k[0][2] * k[2][1]);
    adj[0][2] = (k[0][1] * k[1][2] - k[0][2] * k[1][1]);

    adj[1][0] = -(k[1][0] * k[2][2] - k[1][2] * k[2][0]);
    adj[1][1] = (k[0][0] * k[2][2] - k[0][2] * k[2][0]);
    adj[1][2] = -(k[0][0] * k[1][2] - k[0][2] * k[1][0]);

    adj[2][0] = (k[1][0] * k[2][1] - k[1][1] * k[2][0]);
    adj[2][1] = -(k[0][0] * k[2][1] - k[0][1] * k[2][0]);
    adj[2][2] = (k[0][0] * k[1][1] - k[0][1] * k[1][0]);

    int inv[3][3];
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
        {
            inv[i][j] = (adj[j][i] * invDet) % 26;
            if (inv[i][j] < 0)
                inv[i][j] += 26;
        }

    char text[1000], ch;
    int n = 0;
    while ((ch = fgetc(fin)) != EOF)
        if (isalpha(ch))
            text[n++] = toupper(ch);

    for (int i = 0; i < n; i += 3)
    {
        int a = text[i] - 'A';
        int b = text[i + 1] - 'A';
        int c = text[i + 2] - 'A';

        int r1 = (inv[0][0] * a + inv[0][1] * b + inv[0][2] * c) % 26;
        int r2 = (inv[1][0] * a + inv[1][1] * b + inv[1][2] * c) % 26;
        int r3 = (inv[2][0] * a + inv[2][1] * b + inv[2][2] * c) % 26;

        fputc(r1 + 'A', fout);
        fputc(r2 + 'A', fout);
        fputc(r3 + 'A', fout);
    }

    fclose(fin);
    fclose(fout);
    printf("Decryption → decrypt.txt\n");
}
