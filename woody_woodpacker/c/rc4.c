#include "woody.h"

#define N 255

static void    swap(unsigned char *x, unsigned char *y)
{
    int     tmp;

    tmp = *x;
    *y = *x;
    *x = tmp;
}

static void    KSA(char *key, unsigned char *S)
{
    int  j;
    int  len;

    len = ft_strlen(key);
    for (int i = 0; i < N; i++)
        S[i] = i;
    j = 0;
    for (int i = 0; i < N; i++)
    {
        j = (j + S[i] + key[i % len]) % N;
        swap(&S[i], &S[j]);
    }
}

static void    PRGA(unsigned char *S, unsigned char *plaintext, uint32_t size)
{
    int     i = 0;
    int     j = 0;
    int     k = 0;

    for (size_t n = 0; n < size; n++)
    {
        i = (i + 1) % N;
        j = (j + S[i]) % N;
        swap(&S[i], &S[j]);
        k = S[(S[i] + S[j]) % N];
        plaintext[n] = k ^ plaintext[n];
    }
}

void    RC4(char *key, unsigned char *plaintext, uint32_t size)
{
    unsigned char S[N];

    KSA(key, S);

    PRGA(S, plaintext, size);
}