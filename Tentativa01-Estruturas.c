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
#define NUMPAREDES 2
#define COORDENADAS 2
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

void desenha_placar(int nomeJogador, int chavesColetadas, int vidas, double tempoJogo)
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(3, MAXY+1);
    printf("Nome: %s \t\tChaves coletadas: %d \t\tVidas: %d \nTempor de Jogo: %f", nomeJogador, chavesColetadas, vidas, tempoJogo);
}

void testa_agentes(int guarda_x, int guarda_y, int *jogador_x, int *jogador_y, int nomeJogador, int chavesColetadas, int *vidas, int tempoJogo)
{


    if(guarda_x == *jogador_x && guarda_y == *jogador_y)
    {
        *vidas -= 1;
        desenha_placar(nomeJogador, chavesColetadas, *vidas, tempoJogo);

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

struct Jogador
{
    int jogador_x;
    int jogador_y;
    int vidas;
    int chavesColetadas;
    char nomeJogador[NOME];
    double tempoJogo;

};

struct Guarda
{
    int guarda_x;
    int guarda_y;
};

struct Chaves
{
    char simboloChave;
    int chave_x, chave_y;
    char status;
    int chave[NUMCHAVES];
};

struct Paredes
{
    int coordenada[NUMPAREDES][COORDENADAS];
};
int main()
{
    struct Jogador Jogador;
    struct Guarda Guarda;
    struct Chaves Chaves;
    struct Paredes Paredes;
    int ch;
    int tecla;
    srand(time(NULL));
    Jogador.chavesColetadas = 0;
    Jogador.vidas = 3;
    Guarda.guarda_x = MAXX - 5;
    Guarda.guarda_y = MAXY - 5;
    Jogador.jogador_x = 4;
    Jogador.jogador_y = 4;

    Jogador.jogador_x = 2 + rand() % (MAXX - 2);
    Jogador.jogador_y = 2 + rand() % (MAXY - 2);
    Guarda.guarda_x = 2 + rand() % (MAXX - 2);
    Guarda.guarda_y = 2 + rand() % (MAXY - 2);



    do
    {



        puts("Insira o nome do jogador");
        gets(Jogador.nomeJogador);
        clrscr();

        desenha_cenario(MAXX, MAXY);
        desenha_placar(Jogador.nomeJogador, Jogador.chavesColetadas, Jogador.vidas, Jogador.tempoJogo);
        desenha_jogador(Jogador.jogador_x, Jogador.jogador_y);
        desenha_guarda(Guarda.guarda_x, Guarda.guarda_y);
        movimenta_jogador(&Jogador.jogador_x, &Jogador.jogador_y, ch);

        do
        {
            testa_agentes(Guarda.guarda_x, Guarda.guarda_y, &Jogador.jogador_x, &Jogador.jogador_y, Jogador.nomeJogador, Jogador.chavesColetadas, &Jogador.vidas, Jogador.tempoJogo);
            if(kbhit())
            {
                tecla = getch();
                movimenta_jogador(&Jogador.jogador_x, &Jogador.jogador_y, tecla);
            }

        }
        while(Jogador.vidas > 0);

    }
    while(Jogador.vidas > 0 && ch != 27);


    return(0);
}

