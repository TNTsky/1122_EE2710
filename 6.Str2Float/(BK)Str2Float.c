#include<stdio.h>
#include<stdlib.h>

typedef union
{
    float f; // to check answer conveniently
    struct
    {
        unsigned F : 23;
        unsigned E : 8;
        unsigned S : 1;
    };
}bin32;

bin32 init__bin32()
{
    bin32 i;
    i.S = 0;
    i.E = (1 << 7) - 1;
    i.F = 0;

    return i;
}

void show__bin32(int S, int E, int F)
{
    if (S) { printf("1, "); }
    else { printf("0, "); }

    int pow = 1 << 7;
    for (int i = 0; i < 8; i++)
    {
        if (E & pow) { printf("1"); }
        else { printf("0"); }
        pow >>= 1;
    }
    printf(", ");

    pow = 1 << 22;
    for (int i = 0; i < 23; i++)
    {
        if (F & pow) { printf("1"); }
        else { printf("0"); }
        pow >>= 1;
    }
    printf("\n");
}

int isdigit(char c)
{
    if ((c > 47) & (c < 58)) { return 1; }
    return 0;
}

int getbound(int m0, int pF)
{
    int bound = 1;

    while (m0) { bound *= 10; m0--; }
    while (pF) { bound *= 10; pF /= 10; }

    return bound;
}

int* readDATA()
{
    int* DATA = (int*)calloc(3, sizeof(int)); // integer-part,float-part and missed zero
    char c;

    while (isdigit(c = getchar()))
    {
        DATA[0] *= 10;
        DATA[0] += c - 48;
    }

    if (c == '\n') { return DATA; }
    while (c = getchar())
    {
        if (c == '0') { DATA[2]++; }
        else { DATA[1] += c - 48; break; }
    }

    while (isdigit(c = getchar()))
    {
        DATA[1] *= 10;
        DATA[1] += c - 48;
    }

    return DATA;
}

void check(int* DATA, int bound)
{
    printf("\nread: %d.", DATA[0]);
    for (int i = 0; i < DATA[2]; i++) { printf("0"); }
    printf("%d\n", DATA[1]);

    printf("bound: %d\n\n", bound);
}

bin32 stof()
{
    bin32 f = init__bin32();


    // check is it negative.
    char c = getchar();
    if (isdigit(c)) { ungetc(c, stdin); }
    else { f.S = 1; }

    int* DATA = readDATA(); // integer-part,float-part and missed zero
    int bound = getbound(DATA[2], DATA[1]);
    int i;

#ifdef DEBUG
    check(DATA, bound);
#endif

    if (DATA[0])
    { // integer-part is non-zero
        for (i = 22; DATA[0] ^ 1; i--)
        {
            f.F >>= 1;
            if (DATA[0] & 1) { f.F |= 1 << 22; }
            f.E++;
            DATA[0] >>= 1;
        }
        for (i = i; i >= 0; i--)
        {
            DATA[1] <<= 1;
            if (DATA[1] >= bound)
            {
                f.F |= 1 << i;
                DATA[1] -= bound;
            }
        }
    }
    else
    { // inteeger-part is zero
        while (DATA[1] < bound)
        {
            DATA[1] <<= 1;
            f.E--;
        }
        DATA[1] -= bound;
        for (i = 22; i >= 0; i--)
        {
            DATA[1] <<= 1;
            if (DATA[1] >= bound)
            {
                f.F |= 1 << i;
                DATA[1] -= bound;
            }
        }
    }

    return f;
}

int main()
{
    while(1)
    {
        bin32 f = stof();

#ifdef DEBUG
        printf("f.f = %f\n", f.f);
#endif

        show__bin32(f.S, f.E, f.F);
    }
}