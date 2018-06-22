#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <dos.h>
#include <math.h>

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
}
Coordenada;

typedef struct
{
    int vidas;
    int CHAVEs_coletadas;
    char nome_jogador[NOME];
    float tempo_jogo;
    int ranking;
    int tempo;
    int modo_de_jogo;
    Coordenada posicao;


}
JOGADOR;

typedef struct
{
    Coordenada posicao;
}
AGENTE;

typedef struct
{
    int status;
    Coordenada posicao;
}
CHAVE;

typedef struct
{
    Coordenada posicao;
}
PAREDE;

typedef struct
{
    int num_segmentos;
    JOGADOR Jogador;
    AGENTE listaagentes[NUM_AGENTES];
    CHAVE listaCHAVEs[NUM_CHAVES];
    PAREDE listaparedes[];

}
JOGO;

void testaparedes(int num_segmentos, PAREDE listaparedes[][num_segmentos], int *jogador_x, int *jogador_y, int num_paredes, int mais, int menos)
{
    int i,j;

    for(i=0; i < num_paredes; i++)
    {
        for(j=0; j < num_segmentos; j++)
        {
            if(listaparedes[i][j].posicao.x == *jogador_x && listaparedes[i][j].posicao.y == *jogador_y)
        {
            textbackground(BLUE);
            putchxy(*jogador_x, *jogador_y, ' ');
            textbackground(GREEN);
            *jogador_x -=1;
            *jogador_y -= 1;
            putchxy(*jogador_x, *jogador_y, ' ');
        }
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

void desenha_cenario(int limite_x, int limite_y)
{
    int i=0;
    system("COLOR 70");
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
            putchxy(1, i+1, ' ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, ' ');
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
            putchxy(1, i+1, ' ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, ' ');
            textbackground(BLUE);
        }
    }
}
void desenha_ogro() {
  int i=0;
    for (i=0; i<4; i++)
    {
            textbackground(BLUE);
            putchxy(MAXX-1-4, MAXY/2+i, ' ');
            textbackground(BLUE);
            putchxy(MAXX-1-i, MAXY/2, ' ');
            textbackground(BLUE);
            putchxy(MAXX-1-i, MAXY/2+4, ' ');
            textbackground(BLUE);
            putchxy(MAXX-5, MAXY/2+4, ' ');
            textbackground(BLUE);
    }
    putchxy(MAXX-1-2, (MAXY/2+2), 'O');
            textbackground(YELLOW);
}
void gera_paredes(int num_paredes, int num_segmentos, PAREDE listaparedes[][num_segmentos])
{
    srand(time(NULL));
    int i, j, k;
    int direcao = 0;

    for(i=0; i<num_paredes; i++)
    {
            direcao = 0 + rand() % 4;
            listaparedes[i][0].posicao.x = 2 + rand() % (MAXX - num_segmentos);
            listaparedes[i][0].posicao.y = 2 + rand() % (MAXY - num_segmentos);


            switch(direcao)
            {
            case 0:
                for(j=0; j<num_segmentos; j++)
                {
                    for(k=1; k<4; k++)
                    {
                        listaparedes[i][k].posicao.y = listaparedes[i][0].posicao.y + k;
                        textbackground(BLUE);
                        putchxy(listaparedes[i][k].posicao.x, listaparedes[i][0].posicao.y - j, ' ');
                        textbackground(BLUE);

                }}
                break;
            case 1:
                for(j=0; j<num_segmentos; j++)
                {
                    for(k=1; k<4; k++)
                    {
                        listaparedes[i][k].posicao.y = listaparedes[i][0].posicao.y + k;
                        textbackground(BLUE);
                        putchxy(listaparedes[i][0].posicao.x, listaparedes[i][0].posicao.y + j, ' ');
                        textbackground(BLUE);
                    }
                }
                break;
            case 2:
                for(j=0; j<num_segmentos; j++)
                {
                    for(k=1; k<4; k++)
                    {
                        listaparedes[i][k].posicao.x = listaparedes[i][0].posicao.x + k;
                        textbackground(BLUE);
                        putchxy(listaparedes[i][0].posicao.x + j, listaparedes[i][0].posicao.y, ' ');
                        textbackground(BLUE);
                    }
                }
                break;
            case 3:
                for(j=0; j<num_segmentos; j++)
                {
                    for(k=1; k<4; k++)
                    {
                        listaparedes[i][k].posicao.x = listaparedes[i][0].posicao.x - k;
                        textbackground(BLUE);
                        putchxy(listaparedes[i][0].posicao.x - j, listaparedes[i][0].posicao.y, ' ');
                        textbackground(BLUE);
                    }
                }
                break;
            }
        }

}
void desenha_jogador(int x, int y)
{
    char jogador = 'P';

    textbackground(GREEN);
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
            textbackground(7);
            putchxy(*x, *y, ' ');
            *x-= 1;
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(*x, *y, jogador);
        }
        break;

    case 77:
        if(*x <= MAXX-2)
        {
            textbackground(7);
            putchxy(*x, *y, ' ');
            *x+= 1;
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(*x, *y, jogador);
        }
        break;

    case 72:
        if(*y > 2)
        {
            textbackground(7);
            putchxy(*x, *y, ' ');
            *y-= 1;
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(*x, *y, jogador);
        }
        break;

    case 80:
        if(*y <= MAXY-2)
        {
            textbackground(7);
            putchxy(*x, *y, ' ');
            *y+=1;
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(*x, *y, jogador);
        }
        break;

    }


}
void desenha_placar(char nome_jogador[], int CHAVEs_coletadas, int vidas, float tempo_jogo, int modo_de_jogo)
{
    textbackground(7);
    textcolor(BLACK);
    gotoxy(3, MAXY+1);
    if (modo_de_jogo)
    {
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nTempor de jogo: %f\t\tModo de jogo: Dificil", nome_jogador, CHAVEs_coletadas, vidas, tempo_jogo);
    }
    else
    {
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nTempor de jogo: %f\t\tModo de jogo: Facil", nome_jogador, CHAVEs_coletadas, vidas, tempo_jogo);
    }
}
void desenha_agente(AGENTE listaagentes[])
{
    int j;

    for(j=0; j<NUM_AGENTES; j++)
    {
        listaagentes[j].posicao.x =  2 + (rand() % (MAXX - 2));
        listaagentes[j].posicao.y = 2 + (rand() % (MAXY - 2));

        textbackground(RED);
        textcolor(RED);
        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
    }
}
void movimenta_agentes(AGENTE listaagentes[], CHAVE listaCHAVEs[])
{
    int flag = 1;
    int j=0;
    srand(time(NULL));
    int direcao = rand() % 4;
    while(flag)
    {
        srand(time(NULL));
        int direcao = rand() % 8;
        switch(direcao)
        {
        case 1:
            for(j=0; j<NUM_AGENTES; j++)
            {
                if(listaagentes[j].posicao.x > 2)
                {
                    if(listaCHAVEs[j].posicao.x != listaagentes[j].posicao.x && listaCHAVEs[j].posicao.y != listaagentes[j].posicao.y)
                    {

                        textbackground(7);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                        listaagentes[j].posicao.x-= 1;
                        textbackground(RED);
                        textcolor(RED);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                    }
                }
            }
            break;

        case 2:
            for(j=0; j<NUM_AGENTES; j++)
            {
                if(listaagentes[j].posicao.x<= MAXX-2)
                {
                    if(listaCHAVEs[j].posicao.x != listaagentes[j].posicao.x && listaCHAVEs[j].posicao.y != listaagentes[j].posicao.y)
                    {
                        textbackground(7);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                        listaagentes[j].posicao.x+= 1;
                        textbackground(RED);
                        textcolor(RED);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                    }
                }
            }
            break;

        case 3:
            for(j=0; j<NUM_AGENTES; j++)
            {
                if(listaagentes[j].posicao.y > 2)
                {
                    if(listaCHAVEs[j].posicao.x != listaagentes[j].posicao.x && listaCHAVEs[j].posicao.y != listaagentes[j].posicao.y)
                    {

                        textbackground(7);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                        listaagentes[j].posicao.y-= 1;
                        textbackground(RED);
                        textcolor(RED);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                    }
                }
            }
            break;

        case 4:
            for(j=0; j<NUM_AGENTES; j++)
            {
                if(listaagentes[j].posicao.y <= MAXY-2)
                {
                    if(listaCHAVEs[j].posicao.x != listaagentes[j].posicao.x && listaCHAVEs[j].posicao.y != listaagentes[j].posicao.y)
                    {
                        textbackground(7);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                        listaagentes[j].posicao.y+=1;
                        textbackground(RED);
                        textcolor(RED);
                        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                    }
                }
            }
            break;
        }
    }
}
void desenha_CHAVEs(CHAVE listaCHAVEs[])
{
    srand(time(NULL));
    int j;

    for(j=0; j<NUM_CHAVES; j++)
    {
        listaCHAVEs[j].posicao.x = rand() % (MAXX - 3) + 1;
        listaCHAVEs[j].posicao.y = rand() % (MAXY - 4) + 2;


        textbackground(YELLOW);
        textcolor(YELLOW);
        putchxy(listaCHAVEs[j].posicao.x, listaCHAVEs[j].posicao.y, ' ');

    }
}
void testa_agentes(AGENTE listaagentes[], int *jogador_x, int *jogador_y, char nome_jogador[], int CHAVEs_coletadas, int *vidas, int tempo_jogo, int modo_de_jogo)
{
    int i=0;

    for(i=0; i<NUM_AGENTES; i++)
    {
        if(listaagentes[i].posicao.x ==*jogador_x && listaagentes[i].posicao.y == *jogador_y)
        {
            *vidas -= 1;
            textbackground(RED);
            putchxy(*jogador_x, *jogador_y, ' ');

            if (*jogador_x  - 2 <= MAXX)
            {
                *jogador_x-= 2;
            }
            else
            {
                *jogador_x+= 2;
            }

            if (*jogador_y - 2<= MAXY)
            {
                *jogador_y-= 2;
            }
            else
            {
                *jogador_y+= 2;
            }
            textbackground(GREEN);
            putchxy(*jogador_x, *jogador_y, ' ');

            desenha_placar(nome_jogador, CHAVEs_coletadas, *vidas, tempo_jogo, modo_de_jogo);
        }
    }
}
void testa_CHAVEs(CHAVE listaCHAVEs[], int *jogador_x, int *jogador_y, char nome_jogador[], int *CHAVEs_coletadas, int vidas, int tempo_jogo, int modo_de_jogo)
{
    int i=0;

    for(i=0; i<NUM_CHAVES; i++)
    {
        if(listaCHAVEs[i].posicao.x == *jogador_x && listaCHAVEs[i].posicao.y == *jogador_y)
        {
            *CHAVEs_coletadas += 1;
            textbackground(GREEN);
            putchxy(*jogador_x, *jogador_y, ' ');
            listaCHAVEs[i].posicao.x=1;
            listaCHAVEs[i].posicao.y=1;
            desenha_placar(nome_jogador, *CHAVEs_coletadas, vidas, tempo_jogo, modo_de_jogo);




        }
    }
}
int gera_score(clock_t tempo_ini, clock_t tempo_fim)
{
    return (int) ((tempo_fim - tempo_ini) / CLOCKS_PER_SEC);
}
void mensagem_final(JOGADOR Jogador)
{
    if (Jogador.CHAVEs_coletadas == NUM_CHAVES)
    {
        clrscr();
        printf("\n\t\t\tVoce ganhou!\n\n");
        printf("\n\t\tTempo de jogo: %d segundos\n",  Jogador.tempo);
    }

    if(Jogador.vidas == 0)
    {
        clrscr();
        printf("\n\t\t\tVoce perdeu!\n\n");
        printf("\n\t\tTempo de jogo: %d segundos\n",  Jogador.tempo);
    }

    Sleep(3000);
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

void quick_sort(JOGADOR a[], int left, int right)
{
    int i, j, x, y;

    i = left;
    j = right;
    x = a[(left + right) / 2].ranking;

    while(i <= j)
    {
        while(a[i].ranking < x && i < right)
        {
            i++;
        }
        while(a[j].ranking > x && j > left)
        {
            j--;
        }
        if(i <= j)
        {
            y = a[i].ranking;
            a[i].ranking = a[j].ranking;
            a[j].ranking = y;
            i++;
            j--;
        }
    }

    if(j > left)
    {
        quick_sort(a, left, j);
    }
    if(i < right)
    {
        quick_sort(a, i, right);
    }
}

int salva_ranking(JOGADOR Jogador)
{
    FILE *arq;
    JOGADOR buffer[10];
    char nomebuffer[NOME];
    int cont = 0;
    arq = fopen("ranking.csv", "a+");
    if(arq == NULL || ferror(arq))
    {
        printf("erro ao abrir arquivo");
        return(0);
    }

    fclose(arq);
    arq = fopen("ranking.csv", "r");
    while(!feof(arq))
    {
        if(fgets(nomebuffer, NOME, arq) != NULL)
        {
            strcpy(buffer[cont].nome_jogador, strtok(nomebuffer, ";"));
            buffer[cont].ranking = atoi(strtok(NULL, ";"));
            cont++;
        }
    }
    buffer[cont] = Jogador;
    quick_sort(buffer, 0, cont+1);
    fclose(arq);
    arq = fopen("ranking.csv", "w");
    int j;
    for(j = 0; j < cont+1 && j < 10; j++)
        fprintf(arq, "%s;%d\n", buffer[j].nome_jogador, buffer[j].ranking);
    fclose(arq);
    return 1 ;
}
int exibe_ranking()
{
    FILE *arq;
    JOGADOR buffer[10];
    char nomebuffer[NOME];
    int cont = 0;
    int i = 0;
    arq = fopen("ranking.csv", "r");
    if(!arq)
    {
        printf("erro ao abrir arquivo");
        return 0;
    }
    else
    {
        while(!feof(arq))
        {
            if(fgets(nomebuffer, NOME, arq) != NULL)
            {
                strcpy(buffer[cont].nome_jogador, strtok(nomebuffer, ";"));
                buffer[cont].ranking = atoi(strtok(NULL, ";"));
                printf("%d: %s \t %d\n", cont, buffer[cont].nome_jogador, buffer[cont].ranking);
                cont++;
            }
        }

    }

    return 1;

}
int main()
{
    int tecla;
    int num_paredes = 0;
    int num_segmentos = 5;

    int num_partidas = 0;
    int ranking[NUM_RANK] = {-1};

    JOGADOR Jogador;
    AGENTE listaagentes[NUM_AGENTES];
    CHAVE listaCHAVEs[NUM_CHAVES];
    PAREDE listaparedes[num_paredes][num_segmentos];

    clock_t tempo_ini, tempo_fim, tempo;

    srand(time(NULL));

    do
    {
        int num_rank=0;
        Jogador.tempo_jogo = 0;
        Jogador.CHAVEs_coletadas = 0;
        Jogador.vidas = 3;
        Jogador.posicao.x = 2 + rand() % (MAXX - 2);
        Jogador.posicao.y = 2 + rand() % (MAXY - 2);

        clrscr();
        fflush(stdin);
        puts("Insira o nome do jogador");
        gets(Jogador.nome_jogador);
        clrscr();

        escolher_modo_jogo(&num_paredes, &num_segmentos, &Jogador.modo_de_jogo);
        tempo_ini = clock();

        desenha_cenario(MAXX, MAXY);
        desenha_ogro();
        //gera_paredes(num_paredes, num_segmentos, listaparedes);
        desenha_jogador(Jogador.posicao.x, Jogador.posicao.y);
        desenha_placar(Jogador.nome_jogador, Jogador.CHAVEs_coletadas, Jogador.vidas, Jogador.tempo_jogo, Jogador.modo_de_jogo);
        desenha_CHAVEs(listaCHAVEs);
        desenha_agente(listaagentes);

        do
        {
            testa_CHAVEs(listaCHAVEs, &Jogador.posicao.x, &Jogador.posicao.y, Jogador.nome_jogador, &Jogador.CHAVEs_coletadas, Jogador.vidas, Jogador.tempo_jogo, Jogador.modo_de_jogo);
            testa_agentes(listaagentes, &Jogador.posicao.x, &Jogador.posicao.y, Jogador.nome_jogador, Jogador.CHAVEs_coletadas, &Jogador.vidas, Jogador.tempo_jogo, Jogador.modo_de_jogo);
            //testaparedes(num_segmentos, listaparedes, &Jogador.posicao.x, &Jogador.posicao.y, num_paredes);
            if(kbhit())
            {
                tecla = getch();
                movimenta_jogador(&Jogador.posicao.x, &Jogador.posicao.y, tecla);
                /*
                tempo = clock();
                if(tempo - tempo_ini >= 0.3){
                movimenta_agentes(listaagentes, listaCHAVEs);
                }

                tempo = clock();
                */
            }
        }
        while(Jogador.CHAVEs_coletadas < NUM_CHAVES && Jogador.vidas > 0);

        tempo_fim = clock();
        Jogador.tempo = gera_score(tempo_ini, tempo_fim);
        if (Jogador.vidas > 0)
        {
            Jogador.ranking = adiciona_ranking(Jogador.tempo, Jogador.modo_de_jogo);
            salva_ranking(Jogador);
        }
        num_partidas++;
        num_rank++;
        mensagem_final(Jogador);
    }
    while(num_partidas < NUM_RANK);

    clrscr();
    exibe_ranking();

    return(0);
}
