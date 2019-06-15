#include <Turboc.h>
struct Pos{
int m;
int p;
BOOL enp;
}Pos[8][8];
struct Pos TPos[8][8];
struct Pos RPos[8][8][1000];
BOOL casl = TRUE;
BOOL casr = TRUE;
BOOL bcasl = TRUE;
BOOL bcasr = TRUE;
BOOL enpg;
int tem;
int rp;
int kT;
extern void CustomGame();
main()
{
    BOOL c;
    BOOL mov;
    int temch;
    system("title Chess");
    setcursortype(SOLIDCURSOR);
    int i, j, ch, x, y;
    int n50;
    int Cx, Cy;
    RESTART:
    x=2;
    y=1;
    n50=0;
    tem=1;
    printf("Chess 1.1\n1. 기본 게임 시작  2. 사용자 지정 게임 시작\n3. 게임 설명  4. 크레딧  5. 게임 종료\n");
    while(1)
    {
        temch=getch();
        if(temch=='1')
        {
            NormalGame();
            break;
        }
        else if(temch=='2')
        {
            CustomGame();
            break;
        }
        else if(temch=='3')
        {
            //HowtoPlay();
            continue;
        }
        else if(temch=='4')
        {
            //Credit();
            continue;
        }
        else if(temch=='5')
            exit(0);
    }



    while(1)
    {



        TURNWHITE:
            Boardfill();

            DisplayText("백 차례입니다.");
            if(ifcanpmoveT(1)==0)
            {
              if(ifcheck(1)==1)
             {
                 DisplayText("체크메이트. 흑 승리입니다.");
                 delay(5000); Gameend(); goto RESTART;
             }
             else
             {
                DisplayText("스테일메이트. 무승부입니다.");
                 delay(5000); Gameend(); goto RESTART;
             }
            }
            if(Counpiece(2,1)==0&&Counpiece(2,4)==0&&Counpiece(2,5)==0)
            {
                if(Counpiece(2,3)+Counpiece(2,2)<=1)
                {
                    DisplayText("기물 부족. 무승부입니다.");
                    delay(5000); Gameend(); goto RESTART;
                }
            }
            if(n50>=100)
            {
                DisplayText("50수가 지날 동안 기물의 변화나 폰의 전진이 없었으므로 무승부입니다.");
                delay(5000); Gameend(); goto RESTART;
            }
            if(ifcheck(1)==1)
                DisplayText("백 차례입니다. 체크 상태입니다!");
            for(i=0; i<8; i++)
                for(j=0; j<8; j++)
                {
                    if(Pos[i][j].p==1)
                        Pos[i][j].enp =FALSE;
                    else if(Pos[i][j].m==0)
                        Pos[i][j].enp =FALSE;
                }

            if(Pos[4][7].m!=6)
            {
                casl = FALSE;
                casr = FALSE;
            }
            if(Pos[0][7].m!=4)
                casl = FALSE;
            if(Pos[7][7].m!=4)
                casr = FALSE;
        while(1)
        {
            gotoxy(x,y);
            ch=getch();
            if(ch == 0xE0 || ch == 0)
                ch=getch();
            switch(ch)
            {
            case 75:
                x -= 4; break;
            case 77:
                x += 4; break;
            case 72:
                y -= 2; break;
            case 80:
                y += 2; break;
            }
            if(x>30)
                x=30;
            if(y>15)
                y=15;
            if(x<2)
                x=2;
            if(y<1)
                y=1;
            if(ch==13&&Pos[(x-2)/4][(y-1)/2].p==1)
            {
                c=TRUE;
                Boardfill();
                Cx=(x-2)/4;
                Cy=(y-1)/2;
                ch = 0;
                ColorEmp(Cx,Cy);
                rev((x-2)/4,(y-1)/2);
            }
            if(ch==13&&(Pos[(x-2)/4][(y-1)/2].p==0||Pos[(x-2)/4][(y-1)/2].m==0)&&c==TRUE)
            {

                 mov = FALSE;
                switch(Pos[Cx][Cy].m)
                {
                case 4:
                    if(Cx==(x-2)/4||Cy==(y-1)/2)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4)
                        for(i=Cx+1; i<(x-2)/4; i++)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4)
                        for(i=Cx-1; i>(x-2)/4; i--)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cy<(y-1)/2)
                        for(i=Cy+1; i<(y-1)/2; i++)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    if(Cy>(y-1)/2)
                        for(i=Cy-1; i>(y-1)/2; i--)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    }
                    else mov = FALSE; break;

                case 2:
                    if(abs(Cx-(x-2)/4)==abs(Cy-(y-1)/2)&&Cx-(x-2)/4!=0)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx+1, j=Cy+1; i<(x-2)/4&& j<(y-1)/2; i++, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx-1, j=Cy+1; i>(x-2)/4&& j<(y-1)/2; i--, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx<(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx+1, j=Cy-1; i<(x-2)/4&& j>(y-1)/2; i++, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx-1, j=Cy-1; i>(x-2)/4&& j>(y-1)/2; i--, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    }else mov = FALSE; break;
                case 3:
                    if((abs(Cx-(x-2)/4)==1&&abs(Cy-(y-1)/2)==2)||(abs(Cx-(x-2)/4)==2&&abs(Cy-(y-1)/2)==1))
                        mov = TRUE;
                    else mov = FALSE; break;
                case 5:
                    if(Cx==(x-2)/4||Cy==(y-1)/2)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4)
                        for(i=Cx+1; i<(x-2)/4; i++)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4)
                        for(i=Cx-1; i>(x-2)/4; i--)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cy<(y-1)/2)
                        for(i=Cy+1; i<(y-1)/2; i++)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    if(Cy>(y-1)/2)
                        for(i=Cy-1; i>(y-1)/2; i--)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    }
                    else if(abs(Cx-(x-2)/4)==abs(Cy-(y-1)/2)&&Cx-(x-2)/4!=0)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx+1, j=Cy+1; i<(x-2)/4&& j<(y-1)/2; i++, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx-1, j=Cy+1; i>(x-2)/4&& j<(y-1)/2; i--, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx<(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx+1, j=Cy-1; i<(x-2)/4&& j>(y-1)/2; i++, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx-1, j=Cy-1; i>(x-2)/4&& j>(y-1)/2; i--, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    }else mov = FALSE; break;
                case 6:
                    if((x-2)/4==2&&(y-1)/2==7&&Pos[1][7].m==0&&Pos[2][7].m==0&&Pos[3][7].m==0&&casl&&!(ifattack(2,7,1))&&!(ifattack(3,7,1))&&!(ifattack(4,7,1)))
                    {
                        Pos[3][7].p = 1; Pos[3][7].m = 4; Pos[0][7].p = 2; Pos[0][7].m = 0;
                        mov = TRUE;
                    }
                    else if((x-2)/4==6&&(y-1)/2==7&&Pos[5][7].m==0&&Pos[6][7].m==0&&casr&&!(ifattack(5,7,1))&&!(ifattack(6,7,1))&&!(ifattack(4,7,1)))
                    {
                        Pos[5][7].p = 1; Pos[5][7].m = 4; Pos[7][7].p = 2; Pos[7][7].m = 0;
                        mov = TRUE;
                    }
                    else if(abs(Cx-(x-2)/4)+abs(Cy-(y-1)/2)>0&&abs(Cx-(x-2)/4)<2&&abs(Cy-(y-1)/2)<2)
                    mov = TRUE;
                    else mov = FALSE; break;
                case 1:
                    if(Cy-(y-1)/2==2&&Cx==(x-2)/4)
                        if(Pos[Cx][Cy-1].m==0&&Pos[Cx][Cy-2].m==0&&Cy==6)
                        {
                           mov = TRUE;
                           Pos[Cx][Cy-2].enp = TRUE;
                        }

                        else mov = FALSE;
                    else if(Cy-(y-1)/2==1&&Cx==(x-2)/4)
                        if(Pos[Cx][Cy-1].m==0)
                        mov = TRUE;
                        else mov = FALSE;
                    else if(Cy-1==(y-1)/2&&Cx-1==(x-2)/4&&Pos[Cx-1][Cy-1].m>0&&Pos[Cx-1][Cy-1].p==0)
                        mov = TRUE;
                    else if(Cy-1==(y-1)/2&&Cx+1==(x-2)/4&&Pos[Cx+1][Cy-1].m>0&&Pos[Cx+1][Cy-1].p==0)
                        mov = TRUE;
                    else if(Pos[Cx-1][Cy].enp&&Cx-1==(x-2)/4&&Cy-1==(y-1)/2&&Cy==3){
                        mov = TRUE; enpg = TRUE;
                    }
                    else if(Pos[Cx+1][Cy].enp&&Cx+1==(x-2)/4&&Cy-1==(y-1)/2&&Cy==3){
                        mov = TRUE; enpg = TRUE;
                    }

                 }

                    if(mov == TRUE)
                    {
                    Copyboard();
                    TPos[(x-2)/4][(y-1)/2].m = TPos[Cx][Cy].m;
                    TPos[(x-2)/4][(y-1)/2].p = TPos[Cx][Cy].p;
                    TPos[Cx][Cy].m = 0;
                    TPos[Cx][Cy].p = 2;
                    if(ifcheckT(1)==1)
                    {
                        c = FALSE;
                        mov = FALSE;
                        goto TURNWHITE;
                    }

                    if(Pos[(x-2)/4][(y-1)/2].p == !(Pos[Cx][Cy].p) || Pos[Cx][Cy].m==1)
                        n50 = 0;
                    else
                        n50++;

                    Pos[(x-2)/4][(y-1)/2].m = Pos[Cx][Cy].m;
                    Pos[(x-2)/4][(y-1)/2].p = Pos[Cx][Cy].p;
                    Pos[Cx][Cy].m = 0;
                    Pos[Cx][Cy].p = 2;

                    if(enpg)
                    {
                        if(Pos[Cx-1][Cy].enp)
                        {
                            Pos[Cx-1][Cy].m = 0; Pos[Cx-1][Cy].p = 2; Pos[Cx-1][Cy].enp = FALSE; enpg = FALSE;
                        }
                        else
                        {
                            Pos[Cx+1][Cy].m = 0; Pos[Cx+1][Cy].p = 2; Pos[Cx+1][Cy].enp = FALSE; enpg = FALSE;
                        }
                    }
                    c = FALSE;
                    Boardfill();
                    ch = 0;
                    for(i=0; i<8; i++)
                        if(Pos[i][0].m==1&&Pos[i][0].p==1)
                    {
                        DisplayText("프로모션할 기물을 선택하세요 : Q = 퀸, R = 룩, B = 비숍, N = 나이트");
                        while(ch!='q'&&ch!='r'&&ch!='b'&&ch!='n')
                            ch=getch();
                        switch(ch)
                        {
                        case 'q':
                            Pos[i][0].m=5; break;
                        case 'r':
                            Pos[i][0].m=4; break;
                        case 'b':
                            Pos[i][0].m=2; break;
                        case 'n':
                            Pos[i][0].m=3; break;
                        }
                    }
                    poscmp();
                    if(kT>=3)
                    {
                        DisplayText("3수 반복 무승부입니다.");
                        delay(5000); Gameend(); goto RESTART;
                    }
                    goto TURNBLACK;

                    }





            }

        }
        TURNBLACK:
            Boardfill();

            DisplayText("흑 차례입니다.");
            if(ifcanpmoveT(0)==0)
            {
              if(ifcheck(0)==1)
             {
                 DisplayText("체크메이트. 백 승리입니다.");
                 delay(5000); Gameend(); goto RESTART;
             }
             else
             {
                 DisplayText("스테일메이트. 무승부입니다.");
                 delay(5000); Gameend(); goto RESTART;
             }
            }
            if(Counpiece(2,1)==0&&Counpiece(2,4)==0&&Counpiece(2,5)==0)
            {
                if(Counpiece(2,3)+Counpiece(2,2)<=1)
                {
                    DisplayText("기물 부족. 무승부입니다.");
                    delay(5000); Gameend(); goto RESTART;
                }
            }
            if(n50>=100)
            {
                DisplayText("50수가 지날 동안 기물의 변화나 폰의 전진이 없었으므로 무승부입니다.");
                delay(5000); Gameend(); goto RESTART;
            }
            if(ifcheck(0)==1)
                DisplayText("흑 차례입니다. 체크 상태입니다!");
            for(i=0; i<8; i++)
                for(j=0; j<8; j++)
                {
                    if(Pos[i][j].p==0)
                        Pos[i][j].enp =FALSE;
                    else if(Pos[i][j].m==0)
                        Pos[i][j].enp =FALSE;
                }
            if(Pos[4][0].m!=6)
            {
                bcasl = FALSE;
                bcasr = FALSE;
            }
            if(Pos[0][0].m!=4)
                bcasl = FALSE;
            if(Pos[7][0].m!=4)
                bcasr = FALSE;
        while(1)
        {
            gotoxy(x,y);
            ch=getch();
            if(ch == 0xE0 || ch == 0)
                ch=getch();
            switch(ch)
            {
            case 75:
                x -= 4; break;
            case 77:
                x += 4; break;
            case 72:
                y -= 2; break;
            case 80:
                y += 2; break;
            }
            if(x>30)
                x=30;
            if(y>15)
                y=15;
            if(x<2)
                x=2;
            if(y<1)
                y=1;
            if(ch==13&&Pos[(x-2)/4][(y-1)/2].p==0)
            {
                c=TRUE;
                Boardfill();
                Cx=(x-2)/4;
                Cy=(y-1)/2;
                ch = 0;
                ColorEmp(Cx,Cy);
                rev((x-2)/4,(y-1)/2);
            }
            if(ch==13&&(Pos[(x-2)/4][(y-1)/2].p==1||Pos[(x-2)/4][(y-1)/2].m==0)&&c==TRUE)
            {
                 mov = FALSE;
                switch(Pos[Cx][Cy].m)
                {
                case 4:
                    if(Cx==(x-2)/4||Cy==(y-1)/2)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4)
                        for(i=Cx+1; i<(x-2)/4; i++)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4)
                        for(i=Cx-1; i>(x-2)/4; i--)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cy<(y-1)/2)
                        for(i=Cy+1; i<(y-1)/2; i++)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    if(Cy>(y-1)/2)
                        for(i=Cy-1; i>(y-1)/2; i--)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    }
                    else mov = FALSE; break;

                case 2:
                    if(abs(Cx-(x-2)/4)==abs(Cy-(y-1)/2)&&Cx-(x-2)/4!=0)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx+1, j=Cy+1; i<(x-2)/4&& j<(y-1)/2; i++, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx-1, j=Cy+1; i>(x-2)/4&& j<(y-1)/2; i--, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx<(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx+1, j=Cy-1; i<(x-2)/4&& j>(y-1)/2; i++, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx-1, j=Cy-1; i>(x-2)/4&& j>(y-1)/2; i--, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    }else mov = FALSE; break;
                case 3:
                    if((abs(Cx-(x-2)/4)==1&&abs(Cy-(y-1)/2)==2)||(abs(Cx-(x-2)/4)==2&&abs(Cy-(y-1)/2)==1))
                        mov = TRUE;
                    else mov = FALSE; break;
                case 5:
                    if(Cx==(x-2)/4||Cy==(y-1)/2)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4)
                        for(i=Cx+1; i<(x-2)/4; i++)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4)
                        for(i=Cx-1; i>(x-2)/4; i--)
                            if(Pos[i][Cy].p<2)
                                mov = FALSE;
                    if(Cy<(y-1)/2)
                        for(i=Cy+1; i<(y-1)/2; i++)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    if(Cy>(y-1)/2)
                        for(i=Cy-1; i>(y-1)/2; i--)
                            if(Pos[Cx][i].p<2)
                                mov = FALSE;
                    }
                    else if(abs(Cx-(x-2)/4)==abs(Cy-(y-1)/2)&&Cx-(x-2)/4!=0)
                    {
                    mov = TRUE;
                    if(Cx<(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx+1, j=Cy+1; i<(x-2)/4&& j<(y-1)/2; i++, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy<(y-1)/2)
                        for(i=Cx-1, j=Cy+1; i>(x-2)/4&& j<(y-1)/2; i--, j++)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx<(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx+1, j=Cy-1; i<(x-2)/4&& j>(y-1)/2; i++, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    if(Cx>(x-2)/4&&Cy>(y-1)/2)
                        for(i=Cx-1, j=Cy-1; i>(x-2)/4&& j>(y-1)/2; i--, j--)
                            if(Pos[i][j].p<2)
                                mov = FALSE;
                    }else mov = FALSE; break;
                case 6:
                    if((x-2)/4==2&&(y-1)/2==0&&Pos[1][0].m==0&&Pos[2][0].m==0&&Pos[3][0].m==0&&bcasl&&!(ifattack(2,0,0))&&!(ifattack(3,0,0))&&!(ifattack(4,0,0)))
                    {
                        Pos[3][0].p = 0; Pos[3][0].m = 4; Pos[0][0].p = 2; Pos[0][0].m = 0;
                        mov = TRUE;
                    }
                    else if((x-2)/4==6&&(y-1)/2==0&&Pos[5][0].m==0&&Pos[6][0].m==0&&bcasr&&!(ifattack(5,0,0))&&!(ifattack(6,0,0))&&!(ifattack(4,0,0)))
                    {
                        Pos[5][0].p = 0; Pos[5][0].m = 4; Pos[7][0].p = 2; Pos[7][0].m = 0;
                        mov = TRUE;
                    }
                    else if(abs(Cx-(x-2)/4)+abs(Cy-(y-1)/2)>0&&abs(Cx-(x-2)/4)<2&&abs(Cy-(y-1)/2)<2)
                    mov = TRUE;
                    else mov = FALSE; break;
                case 1:
                    if(Cy-(y-1)/2==-2&&Cx==(x-2)/4)
                        if(Pos[Cx][Cy+1].m==0&&Pos[Cx][Cy+2].m==0&&Cy==1)
                        {
                           mov = TRUE;
                           Pos[Cx][Cy+2].enp = TRUE;
                        }
                        else mov = FALSE;
                    else if(Cy-(y-1)/2==-1&&Cx==(x-2)/4)
                        if(Pos[Cx][Cy+1].m==0)
                        mov = TRUE;
                        else mov = FALSE;
                    else if(Cy+1==(y-1)/2&&Cx-1==(x-2)/4&&Pos[Cx-1][Cy+1].m>0&&Pos[Cx-1][Cy+1].p==1)
                        mov = TRUE;
                    else if(Cy+1==(y-1)/2&&Cx+1==(x-2)/4&&Pos[Cx+1][Cy+1].m>0&&Pos[Cx+1][Cy+1].p==1)
                        mov = TRUE;
                    else if(Pos[Cx-1][Cy].enp&&Cx-1==(x-2)/4&&Cy+1==(y-1)/2&&Cy==4){
                        mov = TRUE; enpg = TRUE;
                    }
                    else if(Pos[Cx+1][Cy].enp&&Cx+1==(x-2)/4&&Cy+1==(y-1)/2&&Cy==4){
                        mov = TRUE; enpg = TRUE;

                 }
                }

                    if(mov == TRUE)
                    {
                    Copyboard();
                    TPos[(x-2)/4][(y-1)/2].m = TPos[Cx][Cy].m;
                    TPos[(x-2)/4][(y-1)/2].p = TPos[Cx][Cy].p;
                    TPos[Cx][Cy].m = 0;
                    TPos[Cx][Cy].p = 2;
                    if(ifcheckT(0)==1)
                    {
                        c = FALSE;
                        mov = FALSE;
                        goto TURNBLACK;
                    }

                    if(Pos[(x-2)/4][(y-1)/2].p == !(Pos[Cx][Cy].p) || Pos[Cx][Cy].m==1)
                        n50 = 0;
                    else
                        n50++;

                    Pos[(x-2)/4][(y-1)/2].m = Pos[Cx][Cy].m;
                    Pos[(x-2)/4][(y-1)/2].p = Pos[Cx][Cy].p;
                    Pos[Cx][Cy].m = 0;
                    Pos[Cx][Cy].p = 2;
                    if(enpg)
                    {
                        if(Pos[Cx-1][Cy].enp)
                        {
                            Pos[Cx-1][Cy].m = 0; Pos[Cx-1][Cy].p = 2; Pos[Cx-1][Cy].enp = FALSE; enpg = FALSE;
                        }
                        else
                        {
                            Pos[Cx+1][Cy].m = 0; Pos[Cx+1][Cy].p = 2; Pos[Cx+1][Cy].enp = FALSE; enpg = FALSE;
                        }
                    }
                    c = FALSE;
                    Boardfill();
                    ch = 0;
                    for(i=0; i<8; i++)
                        if(Pos[i][7].m==1&&Pos[i][7].p==0)
                    {
                        DisplayText("프로모션할 기물을 선택하세요 : Q = 퀸, R = 룩, B = 비숍, N = 나이트");
                        while(ch!='q'&&ch!='r'&&ch!='b'&&ch!='n')
                            ch=getch();
                        switch(ch)
                        {
                        case 'q':
                            Pos[i][7].m=5; break;
                        case 'r':
                            Pos[i][7].m=4; break;
                        case 'b':
                            Pos[i][7].m=2; break;
                        case 'n':
                            Pos[i][7].m=3; break;
                        }
                    }
                    tem++;
                    poscmp();
                    if(kT>=3)
                    {
                        DisplayText("3수 반복 무승부입니다.");
                        delay(5000); Gameend(); goto RESTART;
                    }
                    goto TURNWHITE;

                    }





            }

        }

    }


}


void Setcolor(int color)
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}
void Boardfill()
{
    int i,j;
    gotoxy(0,0);
    Setcolor(7);
    printf("┏━┳━┳━┳━┳━┳━┳━┳━┓\n");
    for(i=0; i<7; i++)
    {
      printf("｜　｜　｜　｜　｜　｜　｜　｜　｜\n");
    printf("┣━╋━╋━╋━╋━╋━╋━╋━┫\n");
    }
    printf("｜　｜　｜　｜　｜　｜　｜　｜　｜\n");
    printf("┗━┻━┻━┻━┻━┻━┻━┻━┛\n");
    for(j=0; j<8; j++)
    for(i=0; i<8; i++)
    {
        gotoxy(2+4*i, 2*j+1);
        if(Pos[i][j].p==0)
            Setcolor(13);
        else
            Setcolor(11);
        switch(Pos[i][j].m)
        {
            case 0:
            puts("　"); break;
            case 1:
            puts("Ｐ"); break;
            case 2:
            puts("Ｂ"); break;
            case 3:
            puts("Ｎ"); break;
            case 4:
            puts("Ｒ"); break;
            case 5:
            puts("Ｑ"); break;
            case 6:
            puts("Ｋ"); break;
        }
        Setcolor(7);

    }
}
void DisplayText(const char* A)
{
    clrscr();
    Boardfill();
    Setcolor(7);
    gotoxy(0, 18);
    printf("방향키 : 칸 이동\nEnter : 말 선택/말 이동\n%d번째 수", tem);
    gotoxy(0, 17);
    printf("%s", A);
}
void DisPlayTextW(const char* A, int B)
{
    gotoxy(0, B);
    printf("%s", A);
}
void ColorReverse(int x, int y)
{
    gotoxy(x*4+2,y*2+1);
    if(Pos[x][y].p==0)
    {
        Setcolor(0xE5);
        switch(Pos[x][y].m)
        {
        case 0:
            puts("　"); break;
            case 1:
            puts("Ｐ"); break;
            case 2:
            puts("Ｂ"); break;
            case 3:
            puts("Ｎ"); break;
            case 4:
            puts("Ｒ"); break;
            case 5:
            puts("Ｑ"); break;
            case 6:
            puts("Ｋ"); break;
        }
    }
    else
    {
        Setcolor(0xE3);
        switch(Pos[x][y].m)
        {
        case 0:
            puts("　"); break;
            case 1:
            puts("Ｐ"); break;
            case 2:
            puts("Ｂ"); break;
            case 3:
            puts("Ｎ"); break;
            case 4:
            puts("Ｒ"); break;
            case 5:
            puts("Ｑ"); break;
            case 6:
            puts("Ｋ"); break;
        }
    }

}
void ColorEmp(int x, int y)
{
    gotoxy(x*4+2,y*2+1);
        Setcolor(0xAC);
        switch(Pos[x][y].m)
        {
        case 0:
            puts("　"); break;
            case 1:
            puts("Ｐ"); break;
            case 2:
            puts("Ｂ"); break;
            case 3:
            puts("Ｎ"); break;
            case 4:
            puts("Ｒ"); break;
            case 5:
            puts("Ｑ"); break;
            case 6:
            puts("Ｋ"); break;
        }

}
int ifcheck(int p)
{
    int Kx, Ky, i, j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        if(Pos[i][j].p==p&&Pos[i][j].m==6)
        {
            Kx = i; Ky = j;
        }
    for(i=Kx+1; i<=7; i++)
    {
        if(Pos[i][Ky].p==!p&&(Pos[i][Ky].m==4||Pos[i][Ky].m==5))
            return 1;
        if(Pos[i][Ky].m>0)
            break;
    }
    for(i=Kx-1; i>=0; i--)
    {
        if(Pos[i][Ky].p==!p&&(Pos[i][Ky].m==4||Pos[i][Ky].m==5))
            return 1;
        if(Pos[i][Ky].m>0)
            break;
    }
    for(i=Ky+1; i<=7; i++)
    {
        if(Pos[Kx][i].p==!p&&(Pos[Kx][i].m==4||Pos[Kx][i].m==5))
            return 1;
        if(Pos[Kx][i].m>0)
            break;
    }
    for(i=Ky-1; i>=0; i--)
    {
        if(Pos[Kx][i].p==!p&&(Pos[Kx][i].m==4||Pos[Kx][i].m==5))
            return 1;
        if(Pos[Kx][i].m>0)
            break;
    }
    for(i=Kx+1, j=Ky+1; i<=7&& j<=7; i++, j++)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky+1; i>=0&& j<=7; i--, j++)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    for(i=Kx+1, j=Ky-1; i<=7&& j>=0; i++, j--)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky-1; i>=0&& j>=0; i--, j--)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    if(Pos[Kx+1][Ky+2].p!=p&&Pos[Kx+1][Ky+2].m==3&&(Kx+1<8&&Ky+2<8))
        return 1;
    if(Pos[Kx-1][Ky+2].p!=p&&Pos[Kx-1][Ky+2].m==3&&(Kx-1>=0&&Ky+2<8))
        return 1;
    if(Pos[Kx+1][Ky-2].p!=p&&Pos[Kx+1][Ky-2].m==3&&(Kx+1<8&&Ky-2>=0))
        return 1;
    if(Pos[Kx-1][Ky-2].p!=p&&Pos[Kx-1][Ky-2].m==3&&(Kx-1>=0&&Ky-2>=0))
        return 1;
    if(Pos[Kx+2][Ky+1].p!=p&&Pos[Kx+2][Ky+1].m==3&&(Kx+2<8&&Ky+1<8))
        return 1;
    if(Pos[Kx-2][Ky+1].p!=p&&Pos[Kx-2][Ky+1].m==3&&(Kx-2>=0&&Ky+1<8))
        return 1;
    if(Pos[Kx+2][Ky-1].p!=p&&Pos[Kx+2][Ky-1].m==3&&(Kx+2<8&&Ky-1>=0))
        return 1;
    if(Pos[Kx-2][Ky-1].p!=p&&Pos[Kx-2][Ky-1].m==3&&(Kx-2>=0&&Ky-1>=0))
        return 1;
    if(p==1)
    {
        if(Pos[Kx-1][Ky-1].p!=p&&Pos[Kx-1][Ky-1].m==1&&(Kx-1>=0&&Ky-1>=0))
            return 1;
        if(Pos[Kx+1][Ky-1].p!=p&&Pos[Kx+1][Ky-1].m==1&&(Kx+1<8&&Ky-1>=0))
            return 1;
    }
    else
    {
        if(Pos[Kx-1][Ky+1].p!=p&&Pos[Kx-1][Ky+1].m==1&&(Kx-1>=0&&Ky+1<8))
            return 1;
        if(Pos[Kx+1][Ky+1].p!=p&&Pos[Kx+1][Ky+1].m==1&&(Kx+1<8&&Ky+1<8))
            return 1;
    }
    for(i=-1; i<=1; i++)
        for(j=-1; j<=1; j++)
        if(Pos[Kx+i][Ky+j].p!=p&&Pos[Kx+i][Ky+j].m==6&&(Kx+i>=0&&Kx+i<8)&&(Ky+j>=0&&Ky+j<8))
            return 1;
    return 0;
}
void Copyboard()
{
    int i, j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
    {
        TPos[i][j].m = Pos[i][j].m;
        TPos[i][j].p = Pos[i][j].p;
        TPos[i][j].enp = Pos[i][j].enp;
    }
}
int ifcheckT(int p)
{
    int Kx, Ky, i, j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        if(TPos[i][j].p==p&&TPos[i][j].m==6)
        {
            Kx = i; Ky = j;
        }
    for(i=Kx+1; i<=7; i++)
    {
        if(TPos[i][Ky].p==!p&&(TPos[i][Ky].m==4||TPos[i][Ky].m==5))
            return 1;
        if(TPos[i][Ky].m>0)
            break;
    }
    for(i=Kx-1; i>=0; i--)
    {
        if(TPos[i][Ky].p==!p&&(TPos[i][Ky].m==4||TPos[i][Ky].m==5))
            return 1;
        if(TPos[i][Ky].m>0)
            break;
    }
    for(i=Ky+1; i<=7; i++)
    {
        if(TPos[Kx][i].p==!p&&(TPos[Kx][i].m==4||TPos[Kx][i].m==5))
            return 1;
        if(TPos[Kx][i].m>0)
            break;
    }
    for(i=Ky-1; i>=0; i--)
    {
        if(TPos[Kx][i].p==!p&&(TPos[Kx][i].m==4||TPos[Kx][i].m==5))
            return 1;
        if(TPos[Kx][i].m>0)
            break;
    }
    for(i=Kx+1, j=Ky+1; i<=7&& j<=7; i++, j++)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky+1; i>=0&& j<=7; i--, j++)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    for(i=Kx+1, j=Ky-1; i<=7&& j>=0; i++, j--)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky-1; i>=0&& j>=0; i--, j--)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    if(TPos[Kx+1][Ky+2].p!=p&&TPos[Kx+1][Ky+2].m==3&&(Kx+1<8&&Ky+2<8))
        return 1;
    if(TPos[Kx-1][Ky+2].p!=p&&TPos[Kx-1][Ky+2].m==3&&(Kx-1>=0&&Ky+2<8))
        return 1;
    if(TPos[Kx+1][Ky-2].p!=p&&TPos[Kx+1][Ky-2].m==3&&(Kx+1<8&&Ky-2>=0))
        return 1;
    if(TPos[Kx-1][Ky-2].p!=p&&TPos[Kx-1][Ky-2].m==3&&(Kx-1>=0&&Ky-2>=0))
        return 1;
    if(TPos[Kx+2][Ky+1].p!=p&&TPos[Kx+2][Ky+1].m==3&&(Kx+2<8&&Ky+1<8))
        return 1;
    if(TPos[Kx-2][Ky+1].p!=p&&TPos[Kx-2][Ky+1].m==3&&(Kx-2>=0&&Ky+1<8))
        return 1;
    if(TPos[Kx+2][Ky-1].p!=p&&TPos[Kx+2][Ky-1].m==3&&(Kx+2<8&&Ky-1>=0))
        return 1;
    if(TPos[Kx-2][Ky-1].p!=p&&TPos[Kx-2][Ky-1].m==3&&(Kx-2>=0&&Ky-1>=0))
        return 1;
    if(p==1)
    {
        if(TPos[Kx-1][Ky-1].p!=p&&TPos[Kx-1][Ky-1].m==1&&(Kx-1>=0&&Ky-1>=0))
            return 1;
        if(TPos[Kx+1][Ky-1].p!=p&&TPos[Kx+1][Ky-1].m==1&&(Kx+1<8&&Ky-1>=0))
            return 1;
    }
    else
    {
        if(TPos[Kx-1][Ky+1].p!=p&&TPos[Kx-1][Ky+1].m==1&&(Kx-1>=0&&Ky+1<8))
            return 1;
        if(TPos[Kx+1][Ky+1].p!=p&&TPos[Kx+1][Ky+1].m==1&&(Kx+1<8&&Ky+1<8))
            return 1;
    }
    for(i=-1; i<=1; i++)
        for(j=-1; j<=1; j++)
        if(TPos[Kx+i][Ky+j].p!=p&&TPos[Kx+i][Ky+j].m==6&&(Kx+i>=0&&Kx+i<8)&&(Ky+j>=0&&Ky+j<8))
            return 1;
    return 0;
}
void moveT(int a, int b, int e, int d)
{
    if(a<0||a>7||b<0||b>7||e<0||e>7||d<0||d>7)
        return;
    TPos[e][d].m = TPos[a][b].m;
    TPos[e][d].p = TPos[a][b].p;
    TPos[a][b].m = 0;
    TPos[a][b].p = 2;
}
int ifcanmoveT(int a, int b, int e, int d)
{
    int i, j, p;
    BOOL cmov;
    Copyboard();
    p = TPos[a][b].p;
    cmov = FALSE;
    if(a<0||a>7||b<0||b>7||e<0||e>7||d<0||d>7)
        return 0;
    if(a==e&&b==d)
        return 0;
    if(TPos[e][d].p==p)
        return 0;
    switch(TPos[a][b].m)
                {

                case 4:
                    if(a==e||b==d)
                    {
                    cmov = TRUE;
                    if(a<e)
                        for(i=a+1; i<e; i++)
                            if(TPos[i][b].p<2)
                                cmov = FALSE;
                    if(a>e)
                        for(i=a-1; i>e; i--)
                            if(TPos[i][b].p<2)
                                cmov = FALSE;
                    if(b<d)
                        for(i=b+1; i<d; i++)
                            if(TPos[a][i].p<2)
                                cmov = FALSE;
                    if(b>d)
                        for(i=b-1; i>d; i--)
                            if(TPos[a][i].p<2)
                                cmov = FALSE;
                    }
                    else cmov = FALSE; break;

                case 2:
                    if(abs(a-e)==abs(b-d)&&a-e!=0)
                    {
                    cmov = TRUE;
                    if(a<e&&b<d)
                        for(i=a+1, j=b+1; i<e&& j<d; i++, j++)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    if(a>e&&b<d)
                        for(i=a-1, j=b+1; i>e&& j<d; i--, j++)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    if(a<e&&b>d)
                        for(i=a+1, j=b-1; i<e&& j>d; i++, j--)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    if(a>e&&b>d)
                        for(i=a-1, j=b-1; i>e&& j>d; i--, j--)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    }else cmov = FALSE; break;
                case 3:
                    if((abs(a-e)==1&&abs(b-d)==2)||(abs(a-e)==2&&abs(b-d)==1))
                        cmov = TRUE;
                    else cmov = FALSE; break;
                case 5:
                    if(a==e||b==d)
                    {
                    cmov = TRUE;
                    if(a<e)
                        for(i=a+1; i<e; i++)
                            if(TPos[i][b].p<2)
                                cmov = FALSE;
                    if(a>e)
                        for(i=a-1; i>e; i--)
                            if(TPos[i][b].p<2)
                                cmov = FALSE;
                    if(b<d)
                        for(i=b+1; i<d; i++)
                            if(TPos[a][i].p<2)
                                cmov = FALSE;
                    if(b>d)
                        for(i=b-1; i>d; i--)
                            if(TPos[a][i].p<2)
                                cmov = FALSE;
                    }
                    else if(abs(a-e)==abs(b-d)&&a-e!=0)
                    {
                    cmov = TRUE;
                    if(a<e&&b<d)
                        for(i=a+1, j=b+1; i<e&& j<d; i++, j++)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    if(a>e&&b<d)
                        for(i=a-1, j=b+1; i>e&& j<d; i--, j++)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    if(a<e&&b>d)
                        for(i=a+1, j=b-1; i<e&& j>d; i++, j--)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    if(a>e&&b>d)
                        for(i=a-1, j=b-1; i>e&& j>d; i--, j--)
                            if(TPos[i][j].p<2)
                                cmov = FALSE;
                    }else cmov = FALSE; break;
                case 6:
                    if(abs(a-e)+abs(b-d)>0&&abs(a-e)<2&&abs(b-d)<2)
                    cmov = TRUE;
                    else cmov = FALSE;
                    if(p)
                    {
                      if(e==2&&d==7&&TPos[1][7].m==0&&TPos[2][7].m==0&&TPos[3][7].m==0&&casl&&!(ifTattack(2,7,1))&&!(ifTattack(3,7,1))&&!(ifTattack(4,7,1)))
                    {
                        cmov = TRUE;
                    }
                    else if(e==6&&d==7&&TPos[5][7].m==0&&TPos[6][7].m==0&&casr&&!(ifTattack(4,7,1))&&!(ifTattack(5,7,1)))
                    {
                        cmov = TRUE;
                    }
                    }
                    else
                    {
                        if(e==2&&d==0&&TPos[1][0].m==0&&TPos[2][0].m==0&&TPos[3][0].m==0&&bcasl&&!(ifTattack(2,0,0))&&!(ifTattack(3,0,0))&&!(ifTattack(4,0,0)))
                    {
                        cmov = TRUE;
                    }
                        else if(e==6&&d==0&&TPos[5][0].m==0&&TPos[6][0].m==0&&bcasr&&!(ifTattack(4,0,0))&&!(ifTattack(5,0,0)))
                    {
                        cmov = TRUE;
                    }
                    }

                     break;
                case 1:
                    if(p)
                    {

                    if(b-d==2&&a==e)
                        if(TPos[a][b-1].m==0&&TPos[a][b-2].m==0&&b==6)
                        {
                           cmov = TRUE;
                        }

                        else cmov = FALSE;
                    else if(b-d==1&&a==e)
                        if(TPos[a][b-1].m==0)
                        cmov = TRUE;
                        else cmov = FALSE;
                    else if(b-1==d&&a-1==e&&TPos[a-1][b-1].m>0&&TPos[a-1][b-1].p==0)
                        cmov = TRUE;
                    else if(b-1==d&&a+1==e&&TPos[a+1][b-1].m>0&&TPos[a+1][b-1].p==0)
                        cmov = TRUE;
                    else if(TPos[a-1][b].enp&&a-1==e&&b-1==d&&b==3){
                        cmov = TRUE;
                    }
                    else if(TPos[a+1][b].enp&&a+1==e&&b-1==d&&b==3){
                        cmov = TRUE;
                    }
                    }
                    else
                    {
                     if(b-d==-2&&a==e)
                        if(TPos[a][b+1].m==0&&TPos[a][b+2].m==0&&b==1)
                        {
                           cmov = TRUE;
                        }
                        else cmov = FALSE;
                    else if(b-d==-1&&a==e)
                        if(TPos[a][b+1].m==0)
                        cmov = TRUE;
                        else cmov = FALSE;
                    else if(b+1==d&&a-1==e&&TPos[a-1][b+1].m>0&&TPos[a-1][b+1].p==1)
                        cmov = TRUE;
                    else if(b+1==d&&a+1==e&&TPos[a+1][b+1].m>0&&TPos[a+1][b+1].p==1)
                        cmov = TRUE;
                    else if(TPos[a-1][b].enp&&a-1==e&&b+1==d&&b==4){
                        cmov = TRUE;
                    }
                    else if(TPos[a+1][b].enp&&a+1==e&&b+1==d&&b==4){
                        cmov = TRUE;
                    }
                    }



                }
                Copyboard();
                if(cmov==TRUE)
                    moveT(a,b,e,d);
                if(ifcheckT(p)==1)
                    cmov=FALSE;
                return cmov;
}
int ifcanpmoveT(int p)
{
    int i, j, k, l;
    Copyboard();
    for(i=0; i<8; i++)
    for(j=0; j<8; j++)
    {
        if(TPos[i][j].p==p)
        {
            switch(TPos[i][j].m)
            {
            case 1:
                if(p)
                {
                    if(ifcanmoveT(i,j,i,j-1))
                    return 1;
                    if(ifcanmoveT(i,j,i,j-2))
                    return 1;
                    if(ifcanmoveT(i,j,i+1,j-1))
                    return 1;
                    if(ifcanmoveT(i,j,i-1,j-1))
                    return 1;
                }
                else
                {
                    if(ifcanmoveT(i,j,i,j+1))
                    return 1;
                    if(ifcanmoveT(i,j,i,j+2))
                    return 1;
                    if(ifcanmoveT(i,j,i+1,j+1))
                    return 1;
                    if(ifcanmoveT(i,j,i-1,j+1))
                    return 1;
                }break;
            case 2:
                for(k=i+1, l=j+1; k<=7&& l<=7; k++, l++)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i+1, l=j-1; k<=7&& l>=0; k++, l--)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i-1, l=j+1; k>=0&& l<=7; k--, l++)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i-1, l=j-1; k>=0&& l>=0; k--, l--)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
            case 3:
                if(ifcanmoveT(i,j,i+2,j+1))
                    return 1;
                if(ifcanmoveT(i,j,i-2,j+1))
                    return 1;
                if(ifcanmoveT(i,j,i+2,j-1))
                    return 1;
                if(ifcanmoveT(i,j,i-2,j-1))
                    return 1;
                if(ifcanmoveT(i,j,i+1,j+2))
                    return 1;
                if(ifcanmoveT(i,j,i-1,j+2))
                    return 1;
                if(ifcanmoveT(i,j,i+1,j-2))
                    return 1;
                if(ifcanmoveT(i,j,i-1,j-2))
                    return 1;
                break;
            case 4:
                for(k=i+1; k<=7; k++)
                    if(ifcanmoveT(i,j,k,j))
                    return 1;
                for(k=i-1; k>=0; k--)
                    if(ifcanmoveT(i,j,k,j))
                    return 1;
                for(k=j+1; k<=7; k++)
                    if(ifcanmoveT(i,j,i,k))
                    return 1;
                for(k=j-1; k>=0; k--)
                    if(ifcanmoveT(i,j,i,k))
                    return 1; break;
            case 5:
                for(k=i+1, l=j+1; k<=7&& l<=7; k++, l++)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i+1, l=j-1; k<=7&& l>=0; k++, l--)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i-1, l=j+1; k>=0&& l<=7; k--, l++)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i-1, l=j-1; k>=0&& l>=0; k--, l--)
                    if(ifcanmoveT(i,j,k,l))
                    return 1;
                for(k=i+1; k<=7; k++)
                    if(ifcanmoveT(i,j,k,j))
                    return 1;
                for(k=i-1; k>=0; k--)
                    if(ifcanmoveT(i,j,k,j))
                    return 1;
                for(k=j+1; k<=7; k++)
                    if(ifcanmoveT(i,j,i,k))
                    return 1;
                for(k=j-1; k>=0; k--)
                    if(ifcanmoveT(i,j,i,k))
                    return 1; break;
            case 6:
                for(k=i-1; k<=i+1; k++)
                    for(l=j-1; l<=j+1; l++)
                    if(ifcanmoveT(i,j,k,l)&&!(l==0&&k==0))
                        return 1;

            }
        }
    }
    return 0;
}
int ifattack(int Kx, int Ky, int p)
{
    int i, j;
    for(i=Kx+1; i<=7; i++)
    {
        if(Pos[i][Ky].p==!p&&(Pos[i][Ky].m==4||Pos[i][Ky].m==5))
            return 1;
        if(Pos[i][Ky].m>0)
            break;
    }
    for(i=Kx-1; i>=0; i--)
    {
        if(Pos[i][Ky].p==!p&&(Pos[i][Ky].m==4||Pos[i][Ky].m==5))
            return 1;
        if(Pos[i][Ky].m>0)
            break;
    }
    for(i=Ky+1; i<=7; i++)
    {
        if(Pos[Kx][i].p==!p&&(Pos[Kx][i].m==4||Pos[Kx][i].m==5))
            return 1;
        if(Pos[Kx][i].m>0)
            break;
    }
    for(i=Ky-1; i>=0; i--)
    {
        if(Pos[Kx][i].p==!p&&(Pos[Kx][i].m==4||Pos[Kx][i].m==5))
            return 1;
        if(Pos[Kx][i].m>0)
            break;
    }
    for(i=Kx+1, j=Ky+1; i<=7&& j<=7; i++, j++)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky+1; i>=0&& j<=7; i--, j++)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    for(i=Kx+1, j=Ky-1; i<=7&& j>=0; i++, j--)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky-1; i>=0&& j>=0; i--, j--)
    {
        if(Pos[i][j].p==!p&&(Pos[i][j].m==2||Pos[i][j].m==5))
            return 1;
        if(Pos[i][j].m>0)
            break;
    }
    if(Pos[Kx+1][Ky+2].p!=p&&Pos[Kx+1][Ky+2].m==3&&(Kx+1<8&&Ky+2<8))
        return 1;
    if(Pos[Kx-1][Ky+2].p!=p&&Pos[Kx-1][Ky+2].m==3&&(Kx-1>=0&&Ky+2<8))
        return 1;
    if(Pos[Kx+1][Ky-2].p!=p&&Pos[Kx+1][Ky-2].m==3&&(Kx+1<8&&Ky-2>=0))
        return 1;
    if(Pos[Kx-1][Ky-2].p!=p&&Pos[Kx-1][Ky-2].m==3&&(Kx-1>=0&&Ky-2>=0))
        return 1;
    if(Pos[Kx+2][Ky+1].p!=p&&Pos[Kx+2][Ky+1].m==3&&(Kx+2<8&&Ky+1<8))
        return 1;
    if(Pos[Kx-2][Ky+1].p!=p&&Pos[Kx-2][Ky+1].m==3&&(Kx-2>=0&&Ky+1<8))
        return 1;
    if(Pos[Kx+2][Ky-1].p!=p&&Pos[Kx+2][Ky-1].m==3&&(Kx+2<8&&Ky-1>=0))
        return 1;
    if(Pos[Kx-2][Ky-1].p!=p&&Pos[Kx-2][Ky-1].m==3&&(Kx-2>=0&&Ky-1>=0))
        return 1;
    if(p==1)
    {
        if(Pos[Kx-1][Ky-1].p!=p&&Pos[Kx-1][Ky-1].m==1&&(Kx-1>=0&&Ky-1>=0))
            return 1;
        if(Pos[Kx+1][Ky-1].p!=p&&Pos[Kx+1][Ky-1].m==1&&(Kx+1<8&&Ky-1>=0))
            return 1;
    }
    else
    {
        if(Pos[Kx-1][Ky+1].p!=p&&Pos[Kx-1][Ky+1].m==1&&(Kx-1>=0&&Ky+1<8))
            return 1;
        if(Pos[Kx+1][Ky+1].p!=p&&Pos[Kx+1][Ky+1].m==1&&(Kx+1<8&&Ky+1<8))
            return 1;
    }
    for(i=-1; i<=1; i++)
        for(j=-1; j<=1; j++)
        if(Pos[Kx+i][Ky+j].p!=p&&Pos[Kx+i][Ky+j].m==6&&(Kx+i>=0&&Kx+i<8)&&(Ky+j>=0&&Ky+j<8))
            return 1;
    return 0;
}
int Counpiece(int p, int m)
{
    int i, j, ct=0;
    if(p!=2)
    {
        for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        if(Pos[i][j].m==m&&Pos[i][j].p==p) ct++;
    }
    else
    {
        for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        if(Pos[i][j].m==m) ct++;
    }

    return ct;
}

int rposcmp(int a, int b)
{
    register int i, j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
            if(RPos[i][j][a].p!=RPos[i][j][b].p||RPos[i][j][a].m!=RPos[i][j][b].m)
                return 0;
    return 1;
}
void poscmp()
{
    int k, i, j;

    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            RPos[i][j][rp].p = Pos[i][j].p;
            RPos[i][j][rp].m = Pos[i][j].m;
        }
    for(k=0; k<rp; k++)
        if(rposcmp(k, rp))
            kT++;
    rp++;

}
void rev(int a, int b)
{
    int i, j;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
    {
        Copyboard();
        if(ifcanmoveT(a,b,i,j))
            ColorReverse(i,j);
    }
}
void Gameend()
{
    DisplayText("돌아가려면 'N'키를 누르세요");
    while(1)
    {
        if(getch()=='n'||getch()=='N')
            break;
    }
    clrscr();
}
int ifTattack(int Kx, int Ky, int p)
{
    int i, j;
    for(i=Kx+1; i<=7; i++)
    {
        if(TPos[i][Ky].p==!p&&(TPos[i][Ky].m==4||TPos[i][Ky].m==5))
            return 1;
        if(TPos[i][Ky].m>0)
            break;
    }
    for(i=Kx-1; i>=0; i--)
    {
        if(TPos[i][Ky].p==!p&&(TPos[i][Ky].m==4||TPos[i][Ky].m==5))
            return 1;
        if(TPos[i][Ky].m>0)
            break;
    }
    for(i=Ky+1; i<=7; i++)
    {
        if(TPos[Kx][i].p==!p&&(TPos[Kx][i].m==4||TPos[Kx][i].m==5))
            return 1;
        if(TPos[Kx][i].m>0)
            break;
    }
    for(i=Ky-1; i>=0; i--)
    {
        if(TPos[Kx][i].p==!p&&(TPos[Kx][i].m==4||TPos[Kx][i].m==5))
            return 1;
        if(TPos[Kx][i].m>0)
            break;
    }
    for(i=Kx+1, j=Ky+1; i<=7&& j<=7; i++, j++)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky+1; i>=0&& j<=7; i--, j++)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    for(i=Kx+1, j=Ky-1; i<=7&& j>=0; i++, j--)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    for(i=Kx-1, j=Ky-1; i>=0&& j>=0; i--, j--)
    {
        if(TPos[i][j].p==!p&&(TPos[i][j].m==2||TPos[i][j].m==5))
            return 1;
        if(TPos[i][j].m>0)
            break;
    }
    if(TPos[Kx+1][Ky+2].p!=p&&TPos[Kx+1][Ky+2].m==3&&(Kx+1<8&&Ky+2<8))
        return 1;
    if(TPos[Kx-1][Ky+2].p!=p&&TPos[Kx-1][Ky+2].m==3&&(Kx-1>=0&&Ky+2<8))
        return 1;
    if(TPos[Kx+1][Ky-2].p!=p&&TPos[Kx+1][Ky-2].m==3&&(Kx+1<8&&Ky-2>=0))
        return 1;
    if(TPos[Kx-1][Ky-2].p!=p&&TPos[Kx-1][Ky-2].m==3&&(Kx-1>=0&&Ky-2>=0))
        return 1;
    if(TPos[Kx+2][Ky+1].p!=p&&TPos[Kx+2][Ky+1].m==3&&(Kx+2<8&&Ky+1<8))
        return 1;
    if(TPos[Kx-2][Ky+1].p!=p&&TPos[Kx-2][Ky+1].m==3&&(Kx-2>=0&&Ky+1<8))
        return 1;
    if(TPos[Kx+2][Ky-1].p!=p&&TPos[Kx+2][Ky-1].m==3&&(Kx+2<8&&Ky-1>=0))
        return 1;
    if(TPos[Kx-2][Ky-1].p!=p&&TPos[Kx-2][Ky-1].m==3&&(Kx-2>=0&&Ky-1>=0))
        return 1;
    if(p==1)
    {
        if(TPos[Kx-1][Ky-1].p!=p&&TPos[Kx-1][Ky-1].m==1&&(Kx-1>=0&&Ky-1>=0))
            return 1;
        if(TPos[Kx+1][Ky-1].p!=p&&TPos[Kx+1][Ky-1].m==1&&(Kx+1<8&&Ky-1>=0))
            return 1;
    }
    else
    {
        if(TPos[Kx-1][Ky+1].p!=p&&TPos[Kx-1][Ky+1].m==1&&(Kx-1>=0&&Ky+1<8))
            return 1;
        if(TPos[Kx+1][Ky+1].p!=p&&TPos[Kx+1][Ky+1].m==1&&(Kx+1<8&&Ky+1<8))
            return 1;
    }
    for(i=-1; i<=1; i++)
        for(j=-1; j<=1; j++)
        if(TPos[Kx+i][Ky+j].p!=p&&TPos[Kx+i][Ky+j].m==6&&(Kx+i>=0&&Kx+i<8)&&(Ky+j>=0&&Ky+j<8))
            return 1;
    return 0;
}
void NormalGame()
{
    int i, j;
    casl = TRUE;
    casr = TRUE;
    bcasl = TRUE;
    bcasr = TRUE;
    enpg = FALSE;
    rp = 0;
    kT = 0;
    tem = 0;
    for(i=0; i<8; i++)
        for(j=0; j<8; j++)
        {
            Pos[i][j].p = 2;
            Pos[i][j].m = 0;
            Pos[i][j].enp = FALSE;
        }

    for(i=0; i<8; i++)
    {
        Pos[i][1].m = 1;
        Pos[i][6].m = 1;
        Pos[i][0].p = 0;
        Pos[i][1].p = 0;
        Pos[i][6].p = 1;
        Pos[i][7].p = 1;
    }
    Pos[0][0].m = 4;
    Pos[7][0].m = 4;
    Pos[0][7].m = 4;
    Pos[7][7].m = 4;
    Pos[1][0].m = 3;
    Pos[6][0].m = 3;
    Pos[1][7].m = 3;
    Pos[6][7].m = 3;
    Pos[2][0].m = 2;
    Pos[5][0].m = 2;
    Pos[2][7].m = 2;
    Pos[5][7].m = 2;
    Pos[3][0].m = 5;
    Pos[4][0].m = 6;
    Pos[3][7].m = 5;
    Pos[4][7].m = 6;
}

