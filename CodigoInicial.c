#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>

//Espaco reservado para constantes

#define MAXX 80
#define MAXY 24
#define NOME 20
#define VALOR_MAXIMO_RANDX 70
#define VALOR_MAXIMO_RANDY 15
#define NUMCHAVES 4

//Aqui eu declaro uma variavel global, que eu sei que nao deveria fazer
//mas eu realmente nao sei como fazer se nao for assim. ISSO TA ERRADO.
int chavesColetadas = 0;

//Funcao para a moldura
void moldura(int limite)
{
    int i=0;

    for (i=0; i<limite; i++)
    {
        if(limite == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(limite == MAXY)
        {
            putchxy(1, i+1, '   ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, '   ');
            textbackground(BLUE);
        }
    }
}

void movimentoPersonagem(void)
{
    char ch;
    char jogador = 'P';
    int x = 4;
    int y = 4;

    textbackground(WHITE);
    textcolor(RED);
    putchxy(x, y, jogador);

    do
    {
        ch = getch();
        if(ch == -32);
        ch = getch();

        switch(ch)
        {
        case 75:
            if(x > 2)
            {
                textbackground(BLACK);
                putchxy(x, y, ' ');
                x--;
                textbackground(WHITE);
                putchxy(x, y, jogador);
            }
            break;

        case 77:
            if(x <= MAXX-2)
            {
                textbackground(BLACK);
                putchxy(x, y, ' ');
                x++;
                textbackground(WHITE);
                putchxy(x, y, jogador);
            }
            break;

        case 72:
            if(y > 2)
            {
                textbackground(BLACK);
                putchxy(x, y, ' ');
                y--;
                textbackground(WHITE);
                putchxy(x, y, jogador);
            }
            break;

        case 80:
            if(y <= MAXY-2)
            {
                textbackground(BLACK);
                putchxy(x, y, ' ');
                y++;
                textbackground(WHITE);
                putchxy(x, y, jogador);
            }
            break;

        }
    }
    while(ch != 27);


}


void chaves(void)
{
    char chave[NUMCHAVES];
    srand(time(0));
    int j, rX, rY, i;

    //Crio valores randomicos para a posicao das chaves para NUMCHAVES chaves e apresento elas ao jogador

    for(i=0; i<NUMCHAVES; i++)
    {

        for (j = 0; j < 10; j++)
        {
            rX = (int) (rand() / (double) RAND_MAX * (VALOR_MAXIMO_RANDX + 1));
            if (rX > MAXX){
                rX = 8;
            }
            if (rX == MAXX) {
                rX -= 3;
            }
            if (rX == 1) {
                rX += 2;
            }

        }
        for (j = 0; j < 10; j++)
        {
            rY = (int) (rand() / (double) RAND_MAX * (VALOR_MAXIMO_RANDY + 1));
            if (rY == MAXY)
            {
                rY -= 2;
            }
            if(rY == 1)
            {
                rY += 2;
            }
        }
        textbackground(YELLOW);
        putchxy(rX, rY, chave[i]);

    }


}


int main()
{

    char nomeJogador[NOME];


//Pede para o usuario o nome do jogador
    puts("Insira o nome do jogador");
    gets(nomeJogador);
    clrscr();

//Chama as funcoes pra moldura
    moldura(MAXX);
    moldura(MAXY);

//Chama a funcao para a chave
    chaves();

//Insere na tela as informacoes do jogador
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(3, MAXY+1);
    printf("Nome: %s \t\tChaves coletadas: %d", nomeJogador, chavesColetadas);


//Chama a funcao para o movimento do personagem
    movimentoPersonagem();




    return(0);
}
