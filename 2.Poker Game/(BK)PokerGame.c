
#include <stdio.h>
#include<stdlib.h>
#include<time.h>


#define U8 unsigned char

typedef union
{
    struct
    {
        unsigned cardType : 2;
        unsigned cardNo : 6;
    };
    U8 v;
}card;

//==========================================================

int stoi(char* str)
{
    int num = str[0] - 48;

    for (int i = 1; str[i]; i++)
    {
        num *= 10;
        num += str[i] - 48;
    }

    return num;
}


void sort(card* hand, int gamesize)
{//SelectionSort

    int p;
    int tmd;

    for (int i = 1; i <= gamesize; i++)
    {
        p = i;
        for (int j = i + 1; j <= gamesize; j++)
        {
            if (hand[j].v < hand[p].v) { p = j; }
        }
        tmd = hand[i].v;
        hand[i].v = hand[p].v;
        hand[p].v = tmd;
    }
    
    return;
}

//==========================================================

card newcard(int cardType, int cardNo)
{
    card v;
    v.cardType = cardType;
    v.cardNo = cardNo;
    return v;
}

int checkhand(card* hand, card randcard)
{
    for (int i = 1; hand[i].v; i++)
    {
        if (!(randcard.v ^ hand[i].v)) return 1;
    }
    return 0;
}

void showcard(card c)
{
    char* Type[] = { "Club","Diamond","Heart","Spade" };
    printf("(%s:%d)\n", Type[c.cardType], c.cardNo);
}

//==========================================================

card* GetPKcard(int gamesize)
{
    srand(time(NULL));
    card* hand = (card*)malloc(sizeof(card) * (gamesize + 1));
    card randcard;

    hand[0].v = gamesize;
    for (int i = 1; i <= gamesize; i++)
    {
        randcard = newcard(rand() % 4, rand() % 13 + 1);
        while (checkhand(hand, randcard))
        {
            randcard = newcard(rand() % 4, rand() % 13 + 1);
        }
        hand[i] = randcard;
    }

    sort(hand, gamesize);

    return hand;
}

void showhand(card* hand)
{
    int gamesize = hand[0].v;
    printf("Handsize: %d\n", gamesize);
    for (int i = 1; i <= gamesize; i++)
    {
        showcard(hand[i]);
    }

    return;
}

int main(int argc, char* argv[])
{
#ifdef DEBUG
    card* Demo = (card*)malloc(sizeof(card) * 14);
    Demo[0].v = 13;
    Demo[1].v = 4;
    Demo[2].v = 5;
    Demo[3].v = 8;
    Demo[4].v = 9;
    Demo[5].v = 10;
    Demo[6].v = 12;
    Demo[7].v = 13;
    Demo[8].v = 14;
    Demo[9].v = 15;
    Demo[10].v = 16;
    Demo[11].v = 20;
    Demo[12].v = 24;
    Demo[13].v = 28;
    showhand(Demo);
    return 0;
#endif

    card* hand = GetPKcard(5);
    showhand(hand);
}
