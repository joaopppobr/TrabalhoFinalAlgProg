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
#define NUM_AGENTES 4

typedef struct
{
    int x;
    int y;
} Coordenada;

typedef struct Jogador
{
    int vidas;
    int chaves_coletadas;
    char nome_jogador[NOME];
    float tempo_jogo;
    int score;
    Coordenada posicao;

};

typedef struct
{
    int status;
    Coordenada posicao;
} Chave;

void desenha_cenario(limite_x, limite_y)
{
    int i=0;

    for (i=0; i<limite_x; i++)
    {
        if(limite_x == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(limite_x == MAXY)
        {
            putchxy(1, i+1, '   ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, '   ');
            textbackground(BLUE);
        }
    }

    for (i=0; i<limite_y; i++)
    {
        if(limite_y == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(limite_y == MAXY)
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
    listaagentes[j].x = rand() % (MAXX - 2) + 2;
    listaagentes[j].y = rand() % (MAXY - 2) + 2;
     for(i=0; i<NUM_AGENTES; i++)
    {
    textbackground(RED);
    textcolor(RED);
    putchxy(listaagentes[j].x, listaagentes[j].y, agente);
    }

}
}
void desenha_chaves(Coordenada listachaves[])
{
    srand(time(NULL));
    int i, j;

     for(j=0; j<NUM_CHAVES; j++)
    {
    listachaves[j].x = rand() % (MAXX - 3) + 1;
        listachaves[j].y = rand() % (MAXY - 4) + 2;

     for(i=0; i<NUM_CHAVES; i++)
    {
    textbackground(YELLOW);
    textcolor(YELLOW);
    putchxy(listachaves[j].x, listachaves[j].y, ' ');
    }

}
}
void testa_chaves(Coordenada listachaves[], int *jogador_x, int *jogador_y, int nome_jogador, int *chaves_coletadas, int vidas, int tempo_jogo, int modo_de_jogo)
{
int i=0;

for(i=0; i<NUM_CHAVES; i++){
    if(listachaves[i].x == *jogador_x && listachaves[i].y == *jogador_y)
    {
        *chaves_coletadas += 1;
        textbackground(WHITE);
        putchxy(*jogador_x, *jogador_y, ' ');

        //textbackground(WHITE);
      //  putchxy(*jogador_x, *jogador_y, 'P');
        desenha_placar(nome_jogador, *chaves_coletadas, vidas, tempo_jogo, modo_de_jogo);




    }
}
}
void desenha_placar(int nome_jogador, int chaves_coletadas, int vidas, float tempo_jogo, int modo_de_jogo)
{
    textbackground(BLACK);
    textcolor(WHITE);
    gotoxy(3, MAXY+1);
    if (modo_de_jogo)
    {
        printf("Nome: %s \t\tChaves coletadas: %d \t\tVidas: %d \nTempor de jogo: %f\t\tModo de jogo: Dificil", nome_jogador, chaves_coletadas, vidas, tempo_jogo);
    }
    else
    {
        printf("Nome: %s \t\tChaves coletadas: %d \t\tVidas: %d \nTempor de jogo: %f\t\tModo de jogo: Facil", nome_jogador, chaves_coletadas, vidas, tempo_jogo);
    }
}
void testa_agentes(Coordenada listaagentes[], int *jogador_x, int *jogador_y, int nome_jogador, int chaves_coletadas, int *vidas, int tempo_jogo, int modo_de_jogo)
{
int i=0;

for(i=0; i<NUM_AGENTES; i++){
    if(listaagentes[i].x == *jogador_x && listaagentes[i].y == *jogador_y)
    {
        *vidas -= 1;
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

        putchxy(*jogador_x, *jogador_y, 'P');
        desenha_placar(nome_jogador, chaves_coletadas, *vidas, tempo_jogo, modo_de_jogo);




    }
}
}
void escolher_modo_jogo(int *num_paredes, int *num_segmentos, int *modo_de_jogo)
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
        listaparedes[i].x = rand() % (MAXX - num_segmentos) - 1;
        listaparedes[i].y = rand() % (MAXY - num_segmentos) - 1;


        switch(direcao)
        {
        case 0:
            for(j=0; j<num_segmentos; j++)
            {
                textbackground(BLUE);
                putchxy(listaparedes[i].x, listaparedes[i].y - j, '   ');
                textbackground(BLUE);
            }
            break;
            case 1:
            for(j=0; j<num_segmentos; j++)
            {
                textbackground(BLUE);
                putchxy(listaparedes[i].x, listaparedes[i].y + j, '   ');
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
int compara_ranking (const void * elem1, const void * elem2)
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
    Chave listachaves[NUM_CHAVES];
    Coordenada listaagentes[NUM_AGENTES];


    clock_t tempo_ini, tempo_fim;


    do
    {
        srand(time(NULL));
        int num_rank=0;
        Jogador.tempo_jogo = 0;
        Jogador.chaves_coletadas = 0;
        Jogador.vidas = 3;
        Jogador.posicao.x = 2 + rand() % (MAXX - 2);
        Jogador.posicao.y = 2 + rand() % (MAXY - 2);

        clrscr();
        fflush(stdin);
        puts("Insira o nome do jogador");
        gets(Jogador.nome_jogador);
        clrscr();

        escolher_modo_jogo(&num_paredes, &num_segmentos, &modo_de_jogo);
        tempo_ini = clock();



        desenha_placar(Jogador.nome_jogador, Jogador.chaves_coletadas, Jogador.vidas, Jogador.tempo_jogo, modo_de_jogo);
        desenha_cenario(MAXX, MAXY);
        desenha_jogador(Jogador.posicao.x, Jogador.posicao.y);
        desenha_agente(listaagentes);
        desenha_chaves(listachaves);
        gera_paredes(num_paredes, num_segmentos, listaparedes, &Jogador.posicao.x, &Jogador.posicao.y);

        do
        {
            testa_agentes(listaagentes, &Jogador.posicao.x, &Jogador.posicao.y, Jogador.nome_jogador, Jogador.chaves_coletadas, &Jogador.vidas, Jogador.tempo_jogo, modo_de_jogo);
            testa_chaves(listachaves, &Jogador.posicao.x, &Jogador.posicao.y, Jogador.nome_jogador, &Jogador.chaves_coletadas, Jogador.vidas, Jogador.tempo_jogo, modo_de_jogo);
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
        ranking[num_rank] = adiciona_ranking(Jogador.score, modo_de_jogo);
        num_rank++;
        qsort (ranking, sizeof(ranking)/sizeof(*ranking), sizeof(*ranking), compara_ranking);

    }
    while(num_partidas < NUM_RANK);


    clrscr();
    printf("\n\t\t\tVoce perdeu!\n\n");
    printf("\n\t\tTempo de jogo: %d segundos\n",  Jogador.score);
    exibe_ranking(ranking);



    return(0);
}
