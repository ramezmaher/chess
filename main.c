#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct pieces
{
    char name;
    int team;
    int stat;
    int* position;
};
struct player
{
    int team;
    char loss[16];
};
int main()
{
    int i,j,flag=1;
    char board[9][13];
    for (i=0; i<9; i++)
    {
        for (j=0; j<13; j++)
        {
            board[i][j]=' ';
        }
    }
    struct player player1,player2;
    player1.team=1; //white
    player2.team=-1; //black
    struct pieces k= {'k',1,1,&k.name},q= {'q',1,1,&q.name},r1= {'r',1,1,&r1.name},r2= {'r',1,1,&r2.name},b1= {'b',1,1,b1.name},b2= {'b',1,1,&b2.name},n1= {'n',1,1,&n1.name},n2= {'n',1,1,&n2.name}; //white pieces
    struct pieces p1= {'p',1,1,&p1.name},p2= {'p',1,1,&p2.name},p3= {'p',1,1,&p3.name},p4= {'p',1,1,&p4.name},p5= {'p',1,1,&p5.name},p6= {'p',1,1,&p6.name},p7= {'p',1,1,&p7.name},p8= {'p',1,1,&p8.name}; //white pieces
    struct pieces K= {'K',-1,1,&K.name},Q= {'Q',-1,1,&Q.name},R1= {'R',-1,1,&R1.name},R2= {'R',-1,1,&R2.name},B1= {'B',-1,1,&B1.name},B2= {'B',-1,1,&B2.name},N1= {'N',-1,1,&N1.name},N2= {'N',-1,1,&N2.name}; //black pieces
    struct pieces P1= {'P',-1,1,&P1.name},P2= {'P',-1,1,&P2.name},P3= {'P',-1,1,&P3.name},P4= {'P',-1,1,&P4.name},P5= {'P',-1,1,&P5.name},P6= {'P',-1,1,&P6.name},P7= {'P',-1,1,&P7.name},P8= {'P',-1,1,&P8.name}; //black pieces
    board[0][12]='1';
    board[1][12]='2';
    board[2][12]='3';
    board[3][12]='4';
    board[4][12]='5';
    board[5][12]='6';
    board[6][12]='7';
    board[7][12]='8';
    board[8][2]='A';
    board[8][3]='B';
    board[8][4]='C';
    board[8][5]='D';
    board[8][6]='E';
    board[8][7]='F';
    board[8][8]='G';
    board[8][9]='H';
    board[8][0]='B';
    board[8][1]='L';
    board[8][10]='W';
    board[8][11]='L';
    board[8][12]='*';
    board[7][2]=r1.name;
    board[7][3]=n1.name;
    board[7][4]=b1.name;
    board[7][5]=q.name;
    board[7][6]=k.name;
    board[7][7]=b2.name;
    board[7][8]=n2.name;
    board[7][9]=r2.name;
    board[6][2]=p1.name;
    board[6][3]=p2.name;
    board[6][4]=p3.name;
    board[6][5]=p4.name;
    board[6][6]=p5.name;
    board[6][7]=p6.name;
    board[6][8]=p7.name;
    board[6][9]=p8.name;
    board[0][2]=R1.name;
    board[0][3]=N1.name;
    board[0][4]=B1.name;
    board[0][5]=Q.name;
    board[0][6]=K.name;
    board[0][7]=B2.name;
    board[0][8]=N2.name;
    board[0][9]=R2.name;
    board[1][2]=P1.name;
    board[1][3]=P2.name;
    board[1][4]=P3.name;
    board[1][5]=P4.name;
    board[1][6]=P5.name;
    board[1][7]=P6.name;
    board[1][8]=P7.name;
    board[1][9]=P8.name;
    // Black squares {}
    // White squares []
    for (i=0; i<9; i++)
    {
        for (j=0; j<13; j++)
        {
            if (j>=2 && j<=9 && i<8)
            {
                if (i%2==0)
                {
                    printf("[%c]",board[i][j]);
                    flag=1;
                }
                else
                {
                    printf("{%c}",board[i][j]);
                    flag=0;
                }
                for (j=3; j<10; j++)
                {
                    if (flag==0)
                    {
                        printf("[%c]",board[i][j]);
                        flag=1;
                    }
                    else
                    {
                        printf("{%c}",board[i][j]);
                        flag=0;
                    }
                }

            }

            printf(" %c ",board[i][j]);
        }
        printf("\n");
    }
    int turn=1;
    char move[4];
    while (k.stat != 0 && K.stat != 0)
    {
        if (turn ==1 )
        {
            printf("Insert your move player 1:\n");
            gets(move);
            turn*=-1;
        }
        else
        {
            printf("Insert your move player 2:\n");
            gets(move);
            turn*=-1;
        }
    }

    return 0;
}
