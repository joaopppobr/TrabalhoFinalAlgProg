#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <time.h>
#include <windows.h>

#define MAXX 80
#define MAXY 24
#define NOME 20
#define NUM_CHAVES 4
#define NUM_RANK 2
#define COORDENADAS 2
#define NUM_AGENTES 3

typedef struct
{
    int x;
    int y;
} Coordenada;

typedef struct Jogador
{
    int vidas;
    int chavesColetadas;
    char nomeJogador[NOME];
    float tempoJogo;
    int score;
    Coordenada posicao;

};

typedef struct
{
    int status ;
    int ch;
    Coordenada posicao;
} Chave;


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
void movimenta_jogador(int *x,int *y, int ch, Coordenada listaparedes[], int num_paredes)
{

    char jogador = 'P';


    switch(ch)
    {
    case 75:
        if(*x > 2 && testa_paredes(listaparedes, x, y, num_paredes))
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *x-= 1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    case 77:
        if(*x <= MAXX-2 && testa_paredes(listaparedes, x, y, num_paredes))
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *x+= 1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    case 72:
        if(*y > 2 && testa_paredes(listaparedes, x, y, num_paredes))
        {
            textbackground(BLACK);
            putchxy(*x, *y, ' ');
            *y-= 1;
            textbackground(WHITE);
            putchxy(*x, *y, jogador);
        }
        break;

    case 80:
        if(*y <= MAXY-2 && testa_paredes(listaparedes, x, y, num_paredes))
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
void desenha_agente(Coordenada listaagentes[])
{
    srand(time(NULL));
    int i, j;
    char agente = 'G';

     for(j=0; j<NUM_AGENTES; j++)
    {
    listaagentes[j].x = rand() % (MAXX + 1 -  2) + 2;
        listaagentes[j].y = rand() % (MAXY + 1 -  2) + 2;

     for(i=0; i<NUM_AGENTES; i++)
    {
    textbackground(WHITE);
    textcolor(RED);
    putchxy(listaagentes[j].x, listaagentes[j].y, agente);
    }

}
}
void desenha_placar(int nomeJogador, int chavesColetadas, int vidas, float tempoJogo, int modo_de_jogo)
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(3, MAXY+1);
    if (modo_de_jogo)
    {
        printf("Nome: %s \t\tChaves coletadas: %d \t\tVidas: %d \nTempor de jogo: %f\t\tModo de jogo: Dificil", nomeJogador, chavesColetadas, vidas, tempoJogo);
    }
    else
    {
        printf("Nome: %s \t\tChaves coletadas: %d \t\tVidas: %d \nTempor de jogo: %f\t\tModo de jogo: Facil", nomeJogador, chavesColetadas, vidas, tempoJogo);
    }
}
void testa_agentes(Coordenada listaagentes[], int *jogador_x, int *jogador_y, int nomeJogador, int chavesColetadas, int *vidas, int tempoJogo, int modo_de_jogo)
{
int i=0;

for(i=0; i<NUM_AGENTES; i++){
    if(listaagentes[i].x == *jogador_x && listaagentes[i].y == *jogador_y)
    {
        *vidas -= 1;
        textbackground(WHITE);
        putchxy(*jogador_x, *jogador_y, ' ');

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

        textbackground(WHITE);
        putchxy(*jogador_x, *jogador_y, 'P');
        desenha_placar(nomeJogador, chavesColetadas, *vidas, tempoJogo, modo_de_jogo);




    }
}
}
void escolherModoJogo(int *num_paredes, int *num_segmentos, int *modo_de_jogo)
{

    printf("Escolha o modo de jogo:");
    scanf("%d", modo_de_jogo);

    if (*modo_de_jogo)
    {
        *num_paredes = 7;
        *num_segmentos = 7;
    }
    else
    {
        *num_paredes = 5;
        *num_segmentos = 5;
    }



}
void gera_paredes(int num_paredes, int num_segmentos, Coordenada listaparedes[], int *jogador_x, int *jogador_y)
{
    srand(time(NULL));
    int i, j;
    int direcao = 0;

    for(i=0; i<num_paredes; i++)
    {
        direcao = 0 + rand() % 4;
        listaparedes[i].x = rand() % (MAXX + 1 -  2) + 2;
        listaparedes[i].y = rand() % (MAXY + 1 -  2) + 2;


        switch(direcao)
        {
        case 0:
            for(j=0; j<num_segmentos; j++)
            {
                textbackground(BLUE);
                putchxy(listaparedes[i].x, listaparedes[i].y + j, '   ');
                textbackground(BLUE);
            }
            break;
        case 1:
            for(j=0; j<num_segmentos; j++)
            {
                textbackground(BLUE);
                putchxy(listaparedes[i].x, listaparedes[i].y - j, '   ');
                textbackground(BLUE);

            }
            break;
        case 2:
            for(j=0; j<num_segmentos; j++)
            {
                textbackground(BLUE);
                putchxy(listaparedes[i].x + j, listaparedes[i].y, '   ');
                textbackground(BLUE);
            }
            break;
        case 3:
            for(j=0; j<num_segmentos; j++)
            {
                textbackground(BLUE);
                putchxy(listaparedes[i].x - j, listaparedes[i].y, '   ');
                textbackground(BLUE);
            }
            break;
        }
    }
}
int gera_score(clock_t tempo_ini, clock_t tempo_fim)
{
    return (int) ((tempo_fim - tempo_ini) / CLOCKS_PER_SEC);
}
int adiciona_ranking(int score,int modo_de_jogo)
{

    if (modo_de_jogo)
    {
        return(int) ((30000 * 2)/ score);
    }
    else
    {
        return(int) ((30000)/ score);
    }
}
int comp (const void * elem1, const void * elem2)
{
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s)
        return  1;
    if (f < s)
        return -1;
    return 0;
}
void exibe_ranking(int ranking[NUM_RANK])
{
    for (int i = 0 ; i < NUM_RANK ; i++)
        printf ("\n\t\t%d \n", ranking[i]);
}
int testa_paredes (Coordenada listaparedes[], int *jogador_x, int *jogador_y, int num_paredes)
{
int i=0;

for(i=0; i < num_paredes; i++){
    if(listaparedes[i].x == *jogador_x && listaparedes[i].y == *jogador_y)
    {
       return(int)(0);
    }

    else{
        return (int) (1);
    }

}

}

int main()
{

    struct Jogador Jogador;
    struct agente;
    struct Chave;
    struct Coordenada;

    int ch;
    int tecla;
    int num_paredes = 0;
    int num_segmentos = 5;
    int modo_de_jogo = 0;

    int num_partidas = 0;
    int ranking[NUM_RANK] = {-1};

    Coordenada listaparedes[num_paredes];
    Chave listachave[NUM_CHAVES];
    Coordenada listaagentes[NUM_AGENTES];


    clock_t tempo_ini, tempo_fim;


    do
    {
        srand(time(NULL));
        int nrank=0;
        Jogador.tempoJogo = 0;
        Jogador.chavesColetadas = 0;
        Jogador.vidas = 3;
        Jogador.posicao.x = 2 + rand() % (MAXX - 2);
        Jogador.posicao.y = 2 + rand() % (MAXY - 2);

        clrscr();
        fflush(stdin);
        puts("Insira o nome do jogador");
        gets(Jogador.nomeJogador);
        clrscr();

        escolherModoJogo(&num_paredes, &num_segmentos, &modo_de_jogo);
        tempo_ini = clock();



        desenha_placar(Jogador.nomeJogador, Jogador.chavesColetadas, Jogador.vidas, Jogador.tempoJogo, modo_de_jogo);
        desenha_cenario(MAXX, MAXY);
        desenha_jogador(Jogador.posicao.x, Jogador.posicao.y);
        desenha_agente(listaagentes);
        gera_paredes(num_paredes, num_segmentos, listaparedes, &Jogador.posicao.x, &Jogador.posicao.y);

        do
        {
            testa_agentes(listaagentes, &Jogador.posicao.x, &Jogador.posicao.y, Jogador.nomeJogador, Jogador.chavesColetadas, &Jogador.vidas, Jogador.tempoJogo, modo_de_jogo);
            if(kbhit())
            {
                tecla = getch();
                movimenta_jogador(&Jogador.posicao.x, &Jogador.posicao.y, tecla, listaparedes, num_paredes);
            }

        }
        while(Jogador.vidas > 0);
        tempo_fim = clock();
        num_partidas++;

        Jogador.score = gera_score(tempo_ini, tempo_fim);
        ranking[nrank] = adiciona_ranking(Jogador.score, modo_de_jogo);
        nrank++;
        qsort (ranking, sizeof(ranking)/sizeof(*ranking), sizeof(*ranking), comp);

    }
    while(num_partidas < NUM_RANK);


    clrscr();
    printf("\n\t\t\tVoce perdeu!\n\n");
    printf("\n\t\tTempo de jogo: %d segundos\n",  Jogador.score);
    exibe_ranking(ranking);



    return(0);
}

