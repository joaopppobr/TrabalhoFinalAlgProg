#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>

#define LARGURA 60
#define ALTURA 20
#define MAXX 80
#define MAXY 24
#define NOME 20
#define VALOR_MAXIMO_RANDX 70
#define VALOR_MAXIMO_RANDY 15
#define NUMCHAVES 4

void desenha_cenario(limitex, limitey)
{
    int i=0;

    for (i=0; i<limitex; i++)
    {
        if(limitex == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(limitex == MAXY)
        {
            putchxy(1, i+1, '   ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, '   ');
            textbackground(BLUE);
        }
    }

    for (i=0; i<limitey; i++)
    {
        if(limitey == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(limitey == MAXY)
        {
            putchxy(1, i+1, '   ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, '   ');
            textbackground(BLUE);
        }
    }
}

void desenha_jogador(x, y)
{
    char jogador = 'P';

    textbackground(WHITE);
    textcolor(GREEN);
    putchxy(x, y, jogador);
}

void movimenta_jogador(int *x,int *y, int ch)
{

    char jogador = 'P';


    switch(ch)
    {
    case 75:
        if(*x > 2)
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *x-= 1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    case 77:
        if(*x <= MAXX-2)
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *x+= 1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    case 72:
        if(*y > 2)
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *y-= 1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    case 80:
        if(*y <= MAXY-2)
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *y+=1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    }


}

void desenha_guarda(x, y)
{
    char guarda = 'G';

    textbackground(WHITE);
    textcolor(RED);
    putchxy(x, y, guarda);
}

void desenha_placar(int nomeJogador, int chavesColetadas, int vidas)
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(3, MAXY+1);
    printf("Nome: %s \t\tChaves coletadas: %d \t\tVidas: %d", nomeJogador, chavesColetadas, vidas);
}

void testa_agentes(int guarda_x, int guarda_y, int *jogador_x, int *jogador_y, int nomeJogador, int chavesColetadas, int *vidas)
{

//int distanciaJogadorGuarda = sqrt(((guarda_x - jogador_x) * (guarda_x - jogador_x)) + ((guarda_y - jogador_y) * (guarda_y - jogador_y)));

    if(guarda_x == *jogador_x && guarda_y == *jogador_y)
    {
        *vidas -= 1;
        desenha_placar(nomeJogador, chavesColetadas, *vidas);

          if (*jogador_x <= MAXX - 2)
        {
            *jogador_x-= 2;
        }
        else
        {
            *jogador_x+= 2;
        }

        if (*jogador_y <= MAXY - 2)
        {
            *jogador_y-= 2;
        }
        else
        {
            *jogador_y-= 2;
        }

    }



}
int main()
{

    int ch;
    int tecla;
    int vidas = 3;
    int chavesColetadas = 0;
    char nomeJogador[NOME];
    int jogador_x = 5;
    int jogador_y = 5;
    int guarda_x = MAXX- 5;
    int guarda_y = MAXY - 5;

    puts("Insira o nome do jogador");
    gets(nomeJogador);
    clrscr();


    desenha_cenario(MAXX, MAXY);
    desenha_placar(nomeJogador, chavesColetadas, vidas);
    desenha_jogador(jogador_x, jogador_y);
    desenha_guarda(guarda_x, guarda_y);
    movimenta_jogador(&jogador_x, &jogador_y, ch);

    do
    {
        testa_agentes(guarda_x, guarda_y, &jogador_x, &jogador_y, nomeJogador, chavesColetadas, &vidas);
        if(kbhit())
        {
            tecla = getch();
            movimenta_jogador(&jogador_x, &jogador_y, tecla);
        }


    }
    while(vidas > 0 && ch != 27);





    return(0);
}
