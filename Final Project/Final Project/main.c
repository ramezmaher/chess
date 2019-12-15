#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
char board[9][13][1000];
int bx=6,by=0,wx=6,wy=7;
int CM=0,SM=0;
int ywl=0,ybl=0;
int xwl=10,xbl=0;
int turn=1;
int active_move=0;
int moves=0;
int kmoves=0,Kmoves=0;
int r1moves=0,r2moves=0,R1moves=0,R2moves=0;
char z='0';
FILE * fSave;
FILE * fins;
void initializeBoard()
{
    int i,j;
    for (i=0; i<9; i++) /*Loop to empty the board at first*/
    {
        for (j=0; j<13; j++)
        {
            board[i][j][0]=' ';
        }
    }
    board[0][12][0]='1';
    board[1][12][0]='2';
    board[2][12][0]='3';
    board[3][12][0]='4';
    board[4][12][0]='5';
    board[5][12][0]='6';
    board[6][12][0]='7';
    board[7][12][0]='8';
    board[8][2][0]='A';
    board[8][3][0]='B';
    board[8][4][0]='C';
    board[8][5][0]='D';
    board[8][6][0]='E';
    board[8][7][0]='F';
    board[8][8][0]='G';
    board[8][9][0]='H';
    board[8][0][0]='B';
    board[8][1][0]='L';
    board[8][10][0]='W';
    board[8][11][0]='L';
    board[8][12][0]='*';
    board[7][2][0]='r';
    board[7][3][0]='n';
    board[7][4][0]='b';
    board[7][5][0]='q';
    board[7][6][0]='k';
    board[7][7][0]='b';
    board[7][8][0]='n';
    board[7][9][0]='r';
    board[6][2][0]='p';
    board[6][3][0]='p';
    board[6][4][0]='p';
    board[6][5][0]='p';
    board[6][6][0]='p';
    board[6][7][0]='p';
    board[6][8][0]='p';
    board[6][9][0]='p';
    board[0][2][0]='R';
    board[0][3][0]='N';
    board[0][4][0]='B';
    board[0][5][0]='Q';
    board[0][6][0]='K';
    board[0][7][0]='B';
    board[0][8][0]='N';
    board[0][9][0]='R';
    board[1][2][0]='P';
    board[1][3][0]='P';
    board[1][4][0]='P';
    board[1][5][0]='P';
    board[1][6][0]='P';
    board[1][7][0]='P';
    board[1][8][0]='P';
    board[1][9][0]='P';
    // Black squares {}
    // White squares []
}
void printBoard()
{

    int i,j,flag=1;
    for (i=0; i<9; i++)
    {
        for (j=0; j<13; j++)
        {
            if (j>=2 && j<=9 && i<8)
            {
                if (i%2==0)
                {
                    printf("[%c]",board[i][j][active_move]);
                    flag=1;
                }
                else
                {
                    printf("{%c}",board[i][j][active_move]);
                    flag=0;
                }
                for (j=3; j<10; j++)
                {
                    if (flag==0)
                    {
                        printf("[%c]",board[i][j][active_move]);
                        flag=1;
                    }
                    else
                    {
                        printf("{%c}",board[i][j][active_move]);
                        flag=0;
                    }
                }

            }

            printf(" %c ",board[i][j][active_move]);
        }
        printf("\n");
    }
    printf("\n[]white square          {}black square\n");
}
int c_toboard(char x)
{
    switch (x)
    {
    case 'A':
    case 'a':
        return 2;
    case 'B':
    case 'b':
        return 3;
    case 'C':
    case 'c':
        return 4;
    case 'D':
    case 'd':
        return 5;
    case 'E':
    case 'e':
        return 6;
    case 'F':
    case 'f':
        return 7;
    case 'G':
    case 'g':
        return 8;
    case 'H':
    case 'h':
        return 9;
    default:
        return 0;
    }
}
int r_toboard(int x)
{
    return x-1;
}
int teamw(char x)
{
    int found=0,i;
    char team[7]= {'p','r','n','b','q','k'};
    for(i=0; i<6; i++)
    {
        if(x==team[i])
            found=1;
    }
    return found;
}
int teamb(char x)
{
    int found=0,i;
    char team[7]= {'P','R','N','B','Q','K'};
    for(i=0; i<6; i++)
    {
        if(x==team[i])
            found=1;
    }
    return found;

}
int pvmove(int x1,int y1,int x2,int y2,char z)
{
    if (y2==0) /*Checking for promotion*/
    {
        if (!teamw(z) || z=='k' || z=='p')
            z='q';
        if (teamw(z) && z!='k' && z!='p')
        {
            if (x2 == x1 && y2 == y1-1)
            {
                if (board [y2][x2][active_move] == ' ')
                {
                    return 1;
                }
                else
                    return 0;
            }
            else if ((x2 == x1+1 || x2 == x1-1) && y2==y1-1)
            {
                if  (board[y2][x2][active_move] == 'P' || board[y2][x2][active_move]== 'K' || board[y2][x2][active_move] == 'N' || board[y2][x2][active_move] == 'B' || board[y2][x2][active_move] == 'R' || board[y2][x2][active_move] == 'Q')
                {
                    return 1;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    if (x2 == x1 && y2 == y1-1)
    {
        if (board [y2][x2][active_move] == ' ')
        {
            return 1;
        }
        else
            return 0;
    }
    else if ( x2 == x1 && y1 == 6 && y2 ==4 && board[5][x1][active_move]==' ')
    {
        if (board [y2][x2][active_move] == ' ')
        {
            return 1;
        }
        else
            return 0;
    }
    else if ((x2 == x1+1 || x2 == x1-1) && y2==y1-1)
    {
        if  (board[y2][x2][active_move]=='K' || board[y2][x2][active_move] == 'P' || board[y2][x2][active_move] == 'N' || board[y2][x2][active_move] == 'B' || board[y2][x2][active_move] == 'R' || board[y2][x2][active_move] == 'Q')
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
int Pvmove(int x1,int y1,int x2,int y2,char z)
{
    if(y2==7) /*Checking for promotion*/
    {
        if (!teamb(z) || z=='K' || z=='P')
            z='Q';
        if(teamb(z) && z!='K' && z!='P')
        {
            if (x2 == x1 && y2 == y1+1)
            {
                if (board [y2][x2][active_move] == ' ')
                {
                    return 1;
                }
                else
                    return 0;
            }
            else if ((x2 == x1+1 || x2 == x1-1) && y2==y1+1)
            {
                if  (board[y2][x2][active_move] == 'p' || board[y2][x2][active_move] == 'n' || board[y2][x2][active_move] == 'b' || board[y2][x2][active_move] == 'r' || board[y2][x2][active_move] == 'q' || board[y2][x2][active_move]=='k')
                {
                    return 1;
                }
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    if (x2 == x1 && y2 == y1+1)
    {
        if (board [y2][x2][active_move] == ' ')
        {
            return 1;
        }
        else
            return 0;
    }
    else if ( x2 == x1 && y1 == 1 && y2 ==3 && board[2][x1][active_move]==' ')
    {
        if (board [y2][x2][active_move] == ' ')
        {
            return 1;
        }
        else
            return 0;
    }
    else if ((x2 == x1+1 || x2 == x1-1) && y2==y1+1)
    {
        if  (board[y2][x2][active_move]=='k' || board[y2][x2][active_move] == 'p' || board[y2][x2][active_move] == 'n' || board[y2][x2][active_move] == 'b' || board[y2][x2][active_move] == 'r' || board[y2][x2][active_move] == 'q')
        {
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
int nvmove(int x1,int y1,int x2,int y2)
{
    if ((abs(x2-x1) == 2 && abs(y2-y1)==1) || ((abs(x2-x1)==1 && abs(y2-y1)==2)))
    {
        if (board[y2][x2][active_move] == ' ')
            return 1;
        else if ((turn && teamw(board[y2][x2][active_move])) || (!turn && teamb(board[y2][x2][active_move])))
            return 0;
        else
            return 1;
    }
    else
        return 0;
}
int bvmove(int x1,int y1,int x2,int y2)
{
    int i,j;
    if ( abs(x2-x1) == abs(y2-y1))
    {
        if ( (x2-x1)* -1 >0)
        {
            if ((y2-y1)*-1> 0)
            {
                j=y2+1;
                for (i=x2+1; i<=x1-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j++;
                }
            }
            else
            {
                j=y2-1;
                for (i=x2+1; i<=x1-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j--;
                }
            }
        }
        else
        {
            if ((y2-y1)*-1 > 0)
            {
                j=y1-1;
                for (i=x1+1; i<=x2-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j--;
                }

            }
            else
            {
                j=y1+1;
                for (i=x1+1; i<=x2-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j++;
                }
            }
        }
        if (board[y2][x2][active_move] == ' ')
            return 1;
        else if ((turn && teamw(board[y2][x2][active_move])) || (!turn && teamb(board[y2][x2][active_move])))
            return 0;
        else
            return 1;
    }
    else
        return 0;

}
int kvmove(int x1,int y1,int x2,int y2)
{
    int i,j;
    if(abs(x2-x1)<=1 && abs(y2-y1)<=1)
    {
        if (board[y2][x2][active_move] == ' ')
            return 1;
        else if ((turn && teamw(board[y2][x2][active_move])) || (!turn && teamb(board[y2][x2][active_move])))
            return 0;
        else
            return 1;
    }
    else if (board[y1][x1][active_move]=='k' && kmoves==0 ) /*Case of castling of White King*/
    {
        if (y2==7 && x2==4 && r1moves==0)
        {
            for(i=5; i>=3 ; i--)
            {
                if (board[7][i][active_move]!=' ')
                    return 0;
            }
            board[7][4][active_move]='k';
            board[7][5][active_move]='r';
            board[7][6][active_move]=' ';
            board[7][2][active_move]=' ';
            for (i=0; i<=7; i++)
            {
                for (j=2 ; j<=9 ; j++)
                {
                    if (teamb(board[i][j][active_move]))
                    {
                        if (valid (j,i,4,7,' '))
                        {
                            board[7][2][active_move]='r';
                            board[7][4][active_move]=' ';
                            board[7][5][active_move]=' ';
                            board[7][6][active_move]='k';
                            return 0;
                        }
                    }
                }
            }
            board[7][2][active_move]='r';
            board[7][4][active_move]=' ';
            board[7][5][active_move]=' ';
            board[7][6][active_move]='k';
            return 1;
        }
        else if (y2==7 && x2==8 && r2moves==0)
        {
            for(i=7; i<=8 ; i++)
            {
                if (board[7][i][active_move]!=' ')
                    return 0;
            }
            board[7][8][active_move]='k';
            board[7][7][active_move]='r';
            board[7][6][active_move]=' ';
            board[7][9][active_move]=' ';
            for (i=0; i<=7; i++)
            {
                for (j=2 ; j<=9 ; j++)
                {
                    if (teamb(board[i][j][active_move]))
                    {
                        if (valid (j,i,8,7,' '))
                        {
                            board[7][9][active_move]='r';
                            board[7][8][active_move]=' ';
                            board[7][7][active_move]=' ';
                            board[7][6][active_move]='k';
                            return 0;
                        }
                    }
                }
            }
            board[7][9][active_move]='r';
            board[7][8][active_move]=' ';
            board[7][7][active_move]=' ';
            board[7][6][active_move]='k';
            return 1;
        }
        else
            return 0;
    }
    else if (board[y1][x1][active_move]=='K' && Kmoves==0 ) /*Case of castling of Black King*/
    {
        if (y2==0 && x2==4 && R1moves==0)
        {
            for(i=6; i>=3 ; i--)
            {
                if (board[0][i][active_move]!=' ')
                    return 0;
            }
            board[0][4][active_move]='K';
            board[0][5][active_move]='R';
            board[0][6][active_move]=' ';
            board[0][2][active_move]=' ';
            for (i=0; i<=7; i++)
            {
                for (j=2 ; j<=9 ; j++)
                {
                    if (teamw(board[i][j][active_move]))
                    {
                        if (valid (j,i,4,0,' '))
                        {
                            board[0][2][active_move]='R';
                            board[0][4][active_move]=' ';
                            board[0][5][active_move]=' ';
                            board[0][6][active_move]='K';
                            return 0;
                        }
                    }
                }
            }
            board[0][2][active_move]='R';
            board[0][4][active_move]=' ';
            board[0][5][active_move]=' ';
            board[0][6][active_move]='K';
            return 1;
        }
        else if (y2==0 && x2==8 && R2moves==0)
        {
            for(i=7; i<=8 ; i++)
            {
                if (board[0][i][active_move]!=' ')
                    return 0;
            }
            board[0][8][active_move]='K';
            board[0][7][active_move]='R';
            board[0][6][active_move]=' ';
            board[0][9][active_move]=' ';
            for (i=0; i<=7; i++)
            {
                for (j=2 ; j<=9 ; j++)
                {
                    if (teamw(board[i][j][active_move]))
                    {
                        if (valid (j,i,8,0,' '))
                        {
                            board[0][9][active_move]='R';
                            board[0][8][active_move]=' ';
                            board[0][7][active_move]=' ';
                            board[0][6][active_move]='K';
                            return 0;
                        }
                    }
                }
            }
            board[0][9][active_move]='R';
            board[0][8][active_move]=' ';
            board[0][7][active_move]=' ';
            board[0][6][active_move]='K';
            return 1;
        }
        else
            return 0;
    }
    else
        return 0;
}
int rvmove(int x1,int y1,int x2,int y2)
{
    int x,y;
    if(x2==x1 || y2==y1)
    {
        if(x2==x1)
        {
            if(y2>y1)
            {
                for(x=x1,y=y1+1 ; y<y2 ; y++)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
            else
            {
                for(x=x1,y=y1-1 ; y>y2 ; y--)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
        }
        else
        {
            if(x2>x1)
            {
                for(x=x1+1,y=y1 ; x<x2 ; x++)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
            else
            {
                for(x=x1-1,y=y1 ; x>x2 ; x--)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
        }
        if (board[y2][x2][active_move] == ' ')
            return 1;
        else if ((turn && teamw(board[y2][x2][active_move])) || (!turn && teamb(board[y2][x2][active_move])))
            return 0;
        else
            return 1;
    }
    else
        return 0;

}
int qvmove(int x1, int y1, int x2,int y2)
{
    int x,y;
    if(x2==x1 || y2==y1)
    {
        if(x2==x1)
        {
            if(y2>y1)
            {
                for(x=x1,y=y1+1 ; y<y2 ; y++)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
            else
            {
                for(x=x1,y=y1-1 ; y>y2 ; y--)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
        }
        else
        {
            if(x2>x1)
            {
                for(x=x1+1,y=y1 ; x<x2 ; x++)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
            else
            {
                for(x=x1-1,y=y1 ; x>x2 ; x--)
                {
                    if(board[y][x][active_move]!=' ')
                        return 0;
                }
            }
        }
        if (board[y2][x2][active_move] == ' ')
            return 1;
        else if ((turn && teamw(board[y2][x2][active_move])) || (!turn && teamb(board[y2][x2][active_move])))
            return 0;
        else
            return 1;
    }
    int i,j;
    if ( abs(x2-x1) == abs(y2-y1))
    {
        if ( (x2-x1)* -1 >0)
        {
            if ((y2-y1)*-1> 0)
            {
                j=y2+1;
                for (i=x2+1; i<=x1-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j++;
                }
            }
            else
            {
                j=y2-1;
                for (i=x2+1; i<=x1-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j--;
                }
            }
        }
        else
        {
            if ((y2-y1)*-1 > 0)
            {
                j=y1-1;
                for (i=x1+1; i<=x2-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j--;
                }

            }
            else
            {
                j=y1+1;
                for (i=x1+1; i<=x2-1; i++)
                {
                    if (board[j][i][active_move] != ' ')
                        return 0;
                    j++;
                }
            }
        }
        if (board[y2][x2][active_move] == ' ')
            return 1;
        else if ((turn && teamw(board[y2][x2][active_move])) || (!turn && teamb(board[y2][x2][active_move])))
            return 0;
        else
            return 1;
    }
    else
        return 0;

}
int valid(int x1,int y1,int x2,int y2,int z)
{

    char t=board[y1][x1][active_move];
    int v,checkk;
    int tempx,tempy;
    char temp;

    if(x2<2 ||x2>9 || y2<0 ||y2>7)
        return 0;
    else
    {
        switch(t) /*To send the required to move to its suitable function according the to piece having coordinates of x1 and y1*/
        {
        case 'p':
            v=pvmove(x1,y1,x2,y2,z);
            break;
        case 'P':
            v=Pvmove(x1,y1,x2,y2,z);
            break;
        case 'r':
        case 'R':
            v=rvmove(x1,y1,x2,y2);
            break;
        case 'n':
        case 'N':
            v=nvmove(x1,y1,x2,y2);
            break;
        case 'b':
        case 'B':
            v=bvmove(x1,y1,x2,y2);
            break;
        case 'q':
        case 'Q':
            v=qvmove(x1,y1,x2,y2);
            break;
        case 'k':
        case 'K':
            v=kvmove(x1,y1,x2,y2);
            break;
        }
        if(v) /*Checking if the move will result to a check on my own king, or will not protect my king if he's already checked*/
        {
            if((y2==by && x2==bx) || (y2==wy && x2==wx)) /*A move that will eat the opposite king is always a valid move and has the top priority*/
                return 1;
            if(board[y1][x1][active_move]=='k') /*Doing the move temporary to see if it causes a check to my king*/
            {
                tempx=x1;
                tempy=y1;
                wx=x2;
                wy=y2;
            }
            else if(board[y1][x1][active_move]=='K')
            {
                tempx=x1;
                tempy=y1;
                bx=x2;
                by=y2;
            }
            temp=board[y2][x2][active_move];
            board[y2][x2][active_move]=board[y1][x1][active_move];
            board[y1][x1][active_move]=' ';
            if(check()) /*This means after the move, my king will be checked. So it's not a valid move*/
            {
                v=0; 
            }
            board[y1][x1][active_move]=board[y2][x2][active_move]; /*Undoing the temporary move*/ /*Doing any move is the responsibility of the Move function*/
            board[y2][x2][active_move]=temp;
            if(board[y1][x1][active_move]=='k')
            {
                wx=tempx;
                wy=tempy;
            }
            else if(board[y1][x1][active_move]=='K')
            {
                bx=tempx;
                by=tempy;
            }
        }
        return v;
    }
}
int check()
{
    int i,j,S=0;

    turn=!turn;
    for (i=2; i<10; i++) /*Checking if there's any piece that has a valid move to the king's position*/
    {
        for (j=0; j<8; j++)
        {
            if (turn == 1 )
            {
                if (teamw(board[j][i][active_move])== 1)
                {
                    if (valid(i,j,bx,by,z))
                    {
                            S=1;
                    }
                }
            }
            else
            {
                if (teamb(board[j][i][active_move])== 1)
                {
                    if (valid(i,j,wx,wy,z))
                    {
                            S=1;
                    }
                }
            }
        }
    }
    turn=!turn;
    return S;
}
void EndGame(int x)
{
    int i,j,h,g;
    if (turn)
    {
        for (i=0; i<8; i++)
        {
            for (j=2; j<10; j++)
            {
                if (teamw(board[i][j][active_move]))
                {
                    for (h=0; h<8; h++)
                    {
                        for (g=2; g<10; g++)
                        {
                            if (valid(j,i,g,h,z)) /*If there's any piece that has a valid move to another position in the board,the game continues*/
                            {
                                return;
                            }
                        }
                    }
                }
            }
        } /*If the program reaches the end of this function, it means that the current player hasn't any valid move. So, it's the end of the game*/
        if(x)
        {
            CM=1;
            system("cls");
            printBoard();
            printf("\nCheckmate!!\a\nBlack wins\n"); /*Checkmate because the player was already checked by the opposite player*/
        }
        else
        {
            SM=1;
            system("cls");
            printBoard();
            printf("\nStalemate!!\nDRAW\a\n");
        }
    }
    else
    {
        for (i=0; i<8; i++)
        {
            for (j=2; j<10; j++)
            {
                if (teamb(board[i][j][active_move]))
                {
                    for (h=0; h<8; h++)
                    {
                        for (g=2; g<10; g++)
                        {
                            if (valid(j,i,g,h,z))
                            {
                                return;
                            }
                        }
                    }
                }
            }
        }
        if(x)
        {
            CM=1;
            system("cls");
            printBoard();
            printf("\nCheckmate!!\a\nWhite wins\n");
        }
        else
        {
            SM=1;
            system("cls");
            printBoard();
            printf("\nStalemate!!\nDRAW\a\n");
        }
    }
}
void move(int x1,int y1,int x2,int y2,char z)
{
    int i,j;
    if (turn && (!teamw(z) || z=='k' || z=='p')) /*If the move is a pawn's promotion and the player didn't enter a correct character to be promoted to do*/
        z='q';                                   /*the pawn will be promoted to a queen by default*/
    else if (!turn && (!teamb(z) || z=='K' || z=='P'))
        z='Q';
    if (board[y1][x1][active_move]=='k') /*Counting the white king's moves and updating its position on the board*/
    {
        wx=x2;
        wy=y2;
        kmoves++;
    }
    else if (board[y1][x1][active_move]=='K') /*Counting the black king's move and updating its position on the board*/
    {
        bx=x2;
        by=y2;
        Kmoves++;
    }
    else if (board[y1][x1][active_move]=='r') /*Counting each of the four rook's moves*/
    {
        if(y1==7 && x1==2)
            r1moves++;
        else if(y1==7 && x1==9)
            r2moves++;
    }
    else if (board[y1][x1][active_move]=='R')
    {
        if(y1==0 && x1==2)
            R1moves++;
        else if(y1==0 && x1==9)
            R2moves++;
    }
    for(i=0; i<9; i++) /*Loop to copy the previous layer into the new one before updating it with the move*/
    {
        for(j=0; j<13; j++)
            board[i][j][active_move+1]=board[i][j][active_move];
    }
    if (board[y1][x1][active_move]=='k' && x1==6 && x2==4) /*Case of castling of White King*/
    {
        active_move++;
        moves=active_move;
        board[7][4][active_move]='k';
        board[7][5][active_move]='r';
        board[7][2][active_move]=' ';
        board[7][6][active_move]=' ';
        wx=4;
        return;
    }
    else if (board[y1][x1][active_move]=='k' && x1==6 && x2==8)
    {
        active_move++;
        moves=active_move;
        board[7][8][active_move]='k';
        board[7][7][active_move]='r';
        board[7][6][active_move]=' ';
        board[7][9][active_move]=' ';
        wx=8;
        return;
    }
    else if (board[y1][x1][active_move]=='K' && x1==6 && x2==4) /*Case of castling of Black King*/
    {
        active_move++;
        moves=active_move;
        board[0][4][active_move]='K';
        board[0][5][active_move]='R';
        board[0][2][active_move]=' ';
        board[0][6][active_move]=' ';
        bx=4;
        return;
    }
    else if (board[y1][x1][active_move]=='K' && x1==6 && x2==8)
    {
        active_move++;
        moves=active_move;
        board[0][8][active_move]='K';
        board[0][7][active_move]='R';
        board[0][6][active_move]=' ';
        board[0][9][active_move]=' ';
        bx=8;
        return;
    }
    if (board[y1][x1][active_move]=='p' && y2==0) /*Case of Promotion of white pawns*/
    {
        if(teamb(board[y2][x2][active_move]))
        {
            board[ybl++][xbl][active_move+1]=board[y2][x2][active_move];
            if(ybl==8)
            {
                xbl++;
                ybl=0;
            }
        }
        active_move++;
        moves=active_move;
        board[y2][x2][active_move]=z;
        board[y1][x1][active_move]=' ';

        return;
    }
    if (board[y1][x1][active_move]=='P' && y2==7) /*Case of promotion of black pawns*/
    {
        if(teamw(board[y2][x2][active_move]))
        {
            board[ywl++][xwl][active_move+1]=board[y2][x2][active_move];
            if(ywl==7)
            {
                xwl++;
                ywl=0;
            }
        }
        active_move++;
        moves=active_move;
        board[y2][x2][active_move]=z;
        board[y1][x1][active_move]=' ';

        return;
    }
    if(teamw(board[y2][x2][active_move])) /*If a white piece is killed*/
    {
        board[ywl++][xwl][active_move+1]=board[y2][x2][active_move];
        if(ywl==7)
        {
            xwl++;
            ywl=0;
        }
    }
    else if(teamb(board[y2][x2][active_move])) /*If a black piece is killed*/
    {
        board[ybl++][xbl][active_move+1]=board[y2][x2][active_move];
        if(ybl==8)
        {
            xbl++;
            ybl=0;
        }
    }
    board[y2][x2][active_move+1]=board[y1][x1][active_move]; /*Doing the move on the next layer*/
    board[y1][x1][active_move+1]=' ';
    active_move++;
    moves=active_move;
}
void SaveGame(int n)
{
    int i,j;
    fSave = fopen("save.txt", "w");
    fprintf(fSave,"%d\n",turn);
    for (i=0; i<9; i++)
    {
        for (j=0; j<13; j++)
        {
            fprintf(fSave,"%c",board[i][j][n]);
        }
        fprintf(fSave,"\n");
    }
    fclose(fSave);
}
void LoadGame()
{
    int i=0,j,h=0;
    char a[20];
    fSave = fopen("save.txt","r");
    while (!feof(fSave))
    {
        if (h==0)
        {
            fgets(a,20,fSave);
            if(a[0] == '0')
                turn = 0;
            else
                turn =1;
            h=1;
        }
        fgets(a,20,fSave);
        for (j=0; j<13; j++)
        {
            board[i][j][active_move]=a[j];
        }
        i++;
    }
    fclose(fSave);
}
void undo()
{
    int ix,iy;
    if(active_move>0) /*There are available layers to go to*/
    {
        if (xbl==1 && ybl==0 && board[0][1][active_move]!=board[0][1][active_move-1]) /*If there was a kill in the last move*/
        {
            xbl=0;
            ybl=7;
        }
        else if (ybl>0 && board[ybl-1][xbl][active_move]!= board[ybl-1][xbl][active_move-1])
        {
            ybl--;
        }
        if (xwl==11 && ywl==0 && board[0][11][active_move]!=board[0][11][active_move-1])
        {
            xwl=10;
            ywl=0;
        }
        else if (ywl>0 && board[ywl-1][xwl][active_move]!=board[ywl-1][xwl][active_move]-1)
            ybl--;

        for( ix=2 ; ix<=9 ; ix++ ) /*Updating the suitable king's position*/
        {
            for( iy=0 ; iy<=7 ; iy++)
            {
                if(turn)
                {
                    if (board[iy][ix][active_move-1]=='K')
                    {
                        bx=ix;
                        by=iy;
                        break;
                    }
                }
                else
                {
                    if (board[iy][ix][active_move-1]=='k')
                    {
                        wx=ix;
                        wy=iy;
                        break;
                    }
                }
            }
        }
        active_move--;
        turn=!turn;
    }
}
void redo()
{
    int ix,iy;
    if(active_move<moves)/*If there are available layers to be accessed*/
    {
        if (xbl==0 && ybl==7 && board[7][0][active_move]!= board[7][0][active_move+1])/*If there was a kill on the next move*/
        {
            xbl=1;
            ybl=0;
        }
        else if (ybl<8 && board[ybl][xbl][active_move]!= board[ybl][xbl][active_move+1])
            ybl++;
        else if (xwl==10 && ywl==7 && board[7][10][active_move]!= board[7][10][active_move+1])
        {
            xwl=11;
            ywl=0;
        }
        else if (ywl<8 && board[ywl][xwl][active_move]!= board[ywl][xwl][active_move+1])
            ywl++;

        for( ix=2 ; ix<=9 ; ix++ )/*Updating the suitable king's position*/
        {
            for( iy=0 ; iy<=7 ; iy++)
            {
                if(!turn)
                {
                    if (board[iy][ix][active_move+1]=='K')
                    {
                        bx=ix;
                        by=iy;
                        break;
                    }
                }
                else
                {
                    if (board[iy][ix][active_move+1]=='k')
                    {
                        wx=ix;
                        wy=iy;
                        break;
                    }
                }
            }
        }
        active_move++;
        turn=!turn;
    }
}
int main()
{
    int x1=0,x2=0,y1=0,y2=0;
    char rc='\0';
    initializeBoard();
    int i,checkk=0;
    char a[6]={0}, b[1000];
    a[5]='\0';
    do
    {
        fins = fopen("READ ME.txt","r");
        while (!feof(fins))
        {
            fgets(b,1000,fins);
            puts(b);
        }
        fclose(fins);
        printf("\nPress ENTER to continue\n");
        scanf("%c",&rc);
    }
    while (rc != '\n' );

    while (CM == 0 && SM == 0)
    {
        checkk = check();
        EndGame(checkk);
        if (SM == 1 || CM == 1)
        {
            return 0;
        }
        if (checkk)
        {
            while (checkk)
            {
                while(x1<2 || x1>9 || y1 <0 || y1>7 || board[y1][x1][active_move]==' ' || (turn&&teamb(board[y1][x1][active_move])) || (!turn&&teamw(board[y1][x1][active_move])) || (!valid(x1,y1,x2,y2,z)))
                { /*White the move is invalid, keep reading the move*/
                    system("cls");
                    printBoard();
                    printf("\nCheck !!\a\n");
                    printf("\nMove no: %d\n\nPlayer %s (Make a move): ",active_move+1,turn?"White":"Black");
                    for(i=0; i<5 ; i++)
                    {
                        a[i]=getchar();
                        if(a[i]=='\n')
                            break;
                    }
                    x1= c_toboard(a[0]);
                    y1= r_toboard(a[1]-48);
                    x2= c_toboard(a[2]);
                    y2= r_toboard(a[3]-48);
                    z= a[4];
                }
                move(x1,y1,x2,y2,z);
                checkk =check();
            }
            turn =!turn;
        }
        else
        {
            while(x1<2 || x1>9 || y1 <0 || y1>7 || board[y1][x1][active_move]==' ' || (turn&&teamb(board[y1][x1][active_move])) || (!turn&&teamw(board[y1][x1][active_move])) || (!valid(x1,y1,x2,y2,z)))
            {
                system("cls");
                printBoard();
                printf("\nMove no: %d\n\nPlayer %s (Make a move): ",active_move+1,turn?"White":"Black");
                for(i=0; i<5 ; i++)
                {
                    a[i]=getchar();
                    if(a[i]=='\n')
                        break;
                }
                if(a[0]=='U' && a[1]=='N' && a[2]=='D' && a[3]=='O') /*The user wishes for an undo*/
                {
                    undo();
                    x1=0; 
                    continue;
                }
                else if(a[0]=='R' && a[1]=='E' && a[2]=='D' && a[3]=='O') /*The user wishes for a redo*/
                {
                    redo();
                    x1=0;
                    continue;
                }
                else if (a[0]=='S' && a[1]=='A' && a[2]=='V' && a[3]=='E' ) /*The user wishes to save the game*/
                {
                    SaveGame(active_move);
                }
                else if (a[0]=='L' && a[1]=='O' && a[2]=='A' && a[3]=='D' ) /*The user wishes to load the previously saved game*/
                {
                    LoadGame();
                }
                x1= c_toboard(a[0]);
                y1= r_toboard(a[1]-48);
                x2= c_toboard(a[2]);
                y2= r_toboard(a[3]-48);
                z= a[4];
            }

            move(x1,y1,x2,y2,z);
            turn=!turn;
        }
    }
    return 0;
}
