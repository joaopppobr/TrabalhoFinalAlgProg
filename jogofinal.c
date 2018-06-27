#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <dos.h>
#include <math.h>
#define _TIME_H
#include <stddef.h>

#define MAXX 80
#define MAXY 24
#define NOME 20
#define NUM_RANK 2
#define COORDENADAS 2
#define NUM_SEGMENTOS 5
#define AGENTESMAX 10
#define CHAVESMAX 5



typedef struct
{
    int x;
    int y;
}
Coordenada;

typedef struct
{
    int num_chaves;
    int num_agentes;
    int num_paredes;
    int vidas;
    int chaves_coletadas;
    int ranking;
    int tempo;
    int modo_de_jogo;
    Coordenada posicao;
    char nome_jogador[NOME];
}
JOGADOR;

typedef struct
{
    Coordenada posicao;
}
AGENTE;

typedef struct
{
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
    Coordenada posicao;
}
OGRO;

typedef struct
{
    JOGADOR Jogador;
    AGENTE listaagentes;
    CHAVE listachaves;
    PAREDE listaparedes;
}
JOGO;

int testaparedes(PAREDE listaparedes[],int x,int y, JOGADOR *Jogador)
{
    int i;
    for(i=0; i < (Jogador->num_paredes * NUM_SEGMENTOS + NUM_SEGMENTOS); i++)
    {
        if(listaparedes[i].posicao.x == x && listaparedes[i].posicao.y == y)
        {
            return 0;
        }
    }
    return 1;
}

void escolher_modo_jogo(JOGADOR *Jogador)
{

    printf("Escolha o modo de jogo:");
    scanf("%d", &Jogador->modo_de_jogo);

    if (Jogador->modo_de_jogo == 1)
    {
        Jogador->num_paredes = 7;
        Jogador->num_chaves = 3;
        Jogador->num_agentes = 6;
    }
    if (Jogador->modo_de_jogo == 0)
    {
        Jogador->num_chaves = 5;
        Jogador->num_agentes = 4;
        Jogador->num_paredes = 5;
    }
}

void desenha_cenario()
{
    int i=0;
    system("COLOR 70");
    for (i=0; i<MAXX; i++)
    {
        if(MAXX == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(MAXX == MAXY)
        {
            putchxy(1, i+1, ' ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, ' ');
            textbackground(BLUE);
        }
    }

    for (i=0; i<MAXY; i++)
    {
        if(MAXX == MAXX)
        {
            putchxy(i+1, 1, ' ');
            textbackground(BLUE);
            putchxy(i+1, MAXY, ' ');
            textbackground(BLUE);
        }
        if(MAXY == MAXY)
        {
            putchxy(1, i+1, ' ');
            textbackground(BLUE);
            putchxy(MAXX, i+1, ' ');
            textbackground(BLUE);
        }
    }
}
void desenha_ogro(OGRO Ogro[])
{
    int i,j;
    for(i=0; i<5; i++)
    {
        for(j=0; j<4; j++)
        {
            Ogro[i].posicao.x = 19 + j;
            Ogro[i].posicao.y = 12 + j;

        }
    }
    for(i=0; i<5; i++)
    {
        textbackground(BLUE);
        putchxy(MAXX-1-4, MAXY/2+i, ' ');
        textbackground(BLUE);
        putchxy(MAXX-1-i, MAXY/2, ' ');
        textbackground(BLUE);
        putchxy(MAXX-1-i, MAXY/2+4, ' ');
        textbackground(BLUE);
        putchxy(MAXX-5, MAXY/2+4, ' ');
        putchxy(Ogro[i].posicao.x, Ogro[i].posicao.y, ' ');
        textbackground(BLUE);
    }
    for(i=0; i<5; i++)
    {
        textbackground(BLUE);
        putchxy(Ogro[i].posicao.x, Ogro[i].posicao.y, ' ');
        textbackground(BLUE);
    }
    putchxy(MAXX-1-2, (MAXY/2+2), 'O');
    textbackground(YELLOW);
}
void gera_paredes(JOGADOR *Jogador, PAREDE listaparedes[])
{
    srand(time(NULL));
    int i, j;
    int direcao = 0;
    int dirx, diry;
    int posx, posy;

    for(i=0; i<Jogador->num_paredes; i++)
    {
        direcao = 0 + rand() % 3;
        posx = 2 + rand() % (MAXX - NUM_SEGMENTOS);
        posy = 2 + rand() % (MAXY - NUM_SEGMENTOS);

        switch(direcao)
        {
        case 0:
            diry = -1;
            dirx = 0;
            break;
        case 1:
            diry = 1;
            dirx = 0;
            break;
        case 2:
            diry = 0;
            dirx = 1;
            break;
        case 3:
            diry = 0;
            dirx = -1;
            break;
        }

        for(j=i*NUM_SEGMENTOS; j < (i*NUM_SEGMENTOS + NUM_SEGMENTOS); j++)
        {
            posx += dirx;
            posy += diry;
            listaparedes[j].posicao.x = posx;
            listaparedes[j].posicao.y = posy;
        }
    }
}

void desenha_paredes(JOGADOR *Jogador, PAREDE listaparedes[])
{
    int i;
    for (i=0; i<(Jogador->num_paredes * NUM_SEGMENTOS + NUM_SEGMENTOS) -1; i++)
    {
        textbackground(BLUE);
        putchxy(listaparedes[i].posicao.x, listaparedes[i].posicao.y, ' ');
        textbackground(BLUE);
    }
}


void desenha_jogador(int x, int y)
{
    char jogador = 'P';

    textbackground(GREEN);
    textcolor(GREEN);
    putchxy(x, y, jogador);
}
void desenha_agente(int x, int y)
{
    char agente = 'G';

    textbackground(RED);
    textcolor(RED);
    putchxy(x, y, agente);
}
void apaga_elemento(int x, int y)
{
    textbackground(7);
    putchxy(x, y, ' ');
}
void movimenta_coisas(int *x, int *y, int direcao, PAREDE listaparedes[], JOGADOR *Jogador)
{

    switch(direcao)
    {
    case 1: //esquerda
        if(*x > 1 && testaparedes(listaparedes, *x-1, *y, Jogador))
        {
            *x-= 1;
        }
        break;

    case 2: //direita
        if(*x <= MAXX-1 && testaparedes(listaparedes, *x+1, *y, Jogador))
        {
            *x+= 1;
        }
        break;

    case 3: // cima
        if(*y > 1 && testaparedes(listaparedes, *x, *y-1, Jogador))
        {
            *y-= 1;
        }
        break;

    case 4: // baixp
        if(*y > 1 && testaparedes(listaparedes, *x, *y+1, Jogador))
        {
            *y+= 1;
        }
        break;
    }
}
void movimenta_jogador(JOGADOR *Jogador, int *ch, PAREDE listaparedes[])
{


    switch(*ch)
    {
    case 75: // esquerda
        if(Jogador->posicao.x > 1 && testaparedes(listaparedes, Jogador->posicao.x-1, Jogador->posicao.y, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 1, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    case 77: // direita
        if(Jogador->posicao.x <= MAXX-1 && testaparedes(listaparedes, Jogador->posicao.x+1, Jogador->posicao.y, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 2, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    case 72: //cima
        if(Jogador->posicao.y > 1 && testaparedes(listaparedes, Jogador->posicao.x, Jogador->posicao.y-1, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 3, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    case 80: // baixo
        if(Jogador->posicao.y <= MAXY-1 && testaparedes(listaparedes, Jogador->posicao.x, Jogador->posicao.y+1, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 4, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    }
}
void desenha_placar(JOGADOR *Jogador)
{
    textbackground(7);
    textcolor(BLACK);
    gotoxy(3, MAXY+1);
    if (Jogador->modo_de_jogo > 0)
    {
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nModo de jogo: Dificil", Jogador->nome_jogador, Jogador->chaves_coletadas, Jogador->vidas);
    }
    else
    {
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nModo de jogo: Facil", Jogador->nome_jogador, Jogador->chaves_coletadas, Jogador->vidas);
    }
}
void desenha_agentes(AGENTE listaagentes[], JOGADOR *Jogador)
{
    int j;

    for(j=0; j<Jogador->num_agentes; j++)
    {
        listaagentes[j].posicao.x =  2 + (rand() % (MAXX - 2));
        listaagentes[j].posicao.y = 2 + (rand() % (MAXY - 2));

        textbackground(RED);
        textcolor(RED);
        putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
    }
}

void movimenta_agentes(AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], JOGADOR *Jogador)
{
    int j=0;
    int direcao = rand() % 3;

    switch(direcao)
    {
    case 0:
        for(j=0; j<Jogador->num_agentes; j++)
        {
            if(listaagentes[j].posicao.x > 1 && testaparedes(listaparedes, listaagentes[j].posicao.x, listaagentes[j].posicao.y, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 1, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
        }
        break;

    case 1:
        for(j=0; j<Jogador->num_agentes; j++)
        {
            if(listaagentes[j].posicao.x<= MAXX-1 && testaparedes(listaparedes, listaagentes[j].posicao.x, listaagentes[j].posicao.y, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 2, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
        }
        break;

    case 2:
        for(j=0; j<Jogador->num_agentes; j++)
        {
            if(listaagentes[j].posicao.y > 1 && testaparedes(listaparedes, listaagentes[j].posicao.x, listaagentes[j].posicao.y, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 3, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
        }
        break;

    case 3:
        for(j=0; j<Jogador->num_agentes; j++)
        {
            if(listaagentes[j].posicao.y <= MAXY-1 && testaparedes(listaparedes, listaagentes[j].posicao.x, listaagentes[j].posicao.y, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 4, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
        }

        break;
    }
}
void desenha_CHAVEs(CHAVE listachaves[], JOGADOR *Jogador)
{
    srand(time(NULL));
    int j;

    for(j=0; j<Jogador->num_chaves; j++)
    {
        listachaves[j].posicao.x = rand() % (MAXX - 3) + 1;
        listachaves[j].posicao.y = rand() % (MAXY - 4) + 2;


        textbackground(YELLOW);
        textcolor(YELLOW);
        putchxy(listachaves[j].posicao.x, listachaves[j].posicao.y, ' ');

    }
}
void testa_agentes(AGENTE listaagentes[], JOGADOR *Jogador)
{
    int i=0;

    for(i=0; i<Jogador->num_agentes; i++)
    {
        if(listaagentes[i].posicao.x ==Jogador->posicao.x && listaagentes[i].posicao.y == Jogador->posicao.y)
        {
            Jogador->vidas -= 1;
            textbackground(RED);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, ' ');

            if (Jogador->posicao.x  - 2 <= MAXX)
            {
                Jogador->posicao.x-= 2;
            }
            else
            {
                Jogador->posicao.x+= 2;
            }

            if (Jogador->posicao.y - 2<= MAXY)
            {
                Jogador->posicao.y-= 2;
            }
            else
            {
                Jogador->posicao.y+= 2;
            }
            textbackground(GREEN);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, ' ');

            desenha_placar(Jogador);
        }
    }
}
void testa_CHAVEs(CHAVE listachaves[], JOGADOR *Jogador)
{
    int i=0;

    for(i=0; i<Jogador->num_chaves; i++)
    {
        if(listachaves[i].posicao.x == Jogador->posicao.x && listachaves[i].posicao.y == Jogador->posicao.y)
        {
            Jogador->chaves_coletadas += 1;
            textbackground(GREEN);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, ' ');
            listachaves[i].posicao.x=1;
            listachaves[i].posicao.y=1;
            desenha_placar(Jogador);
        }
    }
}
int gera_score(clock_t tempo_ini, clock_t tempo_fim)
{
    return (int) ((tempo_fim - tempo_ini) / CLOCKS_PER_SEC);
}
void mensagem_final(JOGADOR *Jogador)
{
    if (Jogador->chaves_coletadas == Jogador->num_chaves)
    {
        clrscr();
        printf("\n\t\t\tVoce ganhou!\n\n");
        printf("\n\t\tTempo de jogo: %d segundos\n",  Jogador->tempo);
    }

    if(Jogador->vidas == 0)
    {
        clrscr();
        printf("\n\t\t\tVoce perdeu!\n\n");
        printf("\n\t\tTempo de jogo: %d segundos\n",  Jogador->tempo);
    }

    Sleep(3000);
}
int adiciona_ranking(JOGADOR *Jogador)
{

    if (Jogador->modo_de_jogo)
    {
        return (30000 * 2) / Jogador->tempo;
    }
    else
    {
        return (30000)/ Jogador->tempo;
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
    arq = fopen("ranking.csv", "a+");
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
int salva_jogo(JOGO jogo)
{
    FILE *arq;
    if(!(arq = fopen("jogo.bin","wb")))
    {
        printf("Erro ao abrir o arquivo");
        return(0);
    }
    else
    {
        fwrite(&jogo,sizeof(JOGO),1,arq);
        fclose(arq);
        return(1);
    }

}

void inicia_novo_jogo(JOGADOR *Jogador, AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], OGRO Ogro[])
{
    int tecla;
    clock_t tempo_ini, tempo_fim;

    Jogador->chaves_coletadas = 0;
    Jogador->vidas = 3;
    Jogador->posicao.x = 2 + rand() % (MAXX - 2);
    Jogador->posicao.y = 2 + rand() % (MAXY - 2);

    tempo_ini = clock();

    desenha_cenario();
    //desenha_ogro(Ogro);
    gera_paredes(Jogador, listaparedes);
    desenha_paredes(Jogador, listaparedes);
    desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
    desenha_placar(Jogador);
    desenha_CHAVEs(listachaves, Jogador);
    desenha_agentes(listaagentes, Jogador);

    double comeco_agente, fim_agente;

    comeco_agente = (double) clock () / (CLOCKS_PER_SEC / 1000);
    fim_agente = comeco_agente;

    do
    {
        testa_CHAVEs(listachaves,Jogador);
        testa_agentes(listaagentes, Jogador);

        if(fim_agente - comeco_agente >= 500)
        {
            movimenta_agentes(listaagentes, listachaves, listaparedes, Jogador);
            comeco_agente = fim_agente;
        }

        if(kbhit())
        {
            tecla = getch();
            movimenta_jogador(Jogador, &tecla, listaparedes);
        }
        fim_agente = (double) clock () / (CLOCKS_PER_SEC / 1000);
    }
    while(Jogador->chaves_coletadas < Jogador->num_chaves && Jogador->vidas > 0);

    tempo_fim = clock();
    Jogador->tempo = gera_score(tempo_ini, tempo_fim);
    if (Jogador->vidas > 0)
    {
        Jogador->ranking = adiciona_ranking(Jogador);
        salva_ranking(*Jogador);
    }
    mensagem_final(Jogador);

}
void menu(JOGADOR *Jogador, AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], OGRO Ogro[])
{
    int opcao;
    int num_partidas = 0;
    clrscr();
    printf("\t\t Resgate o Ogro\t\t\n");
    printf("\t\t Iniciar novo jogo(tecle 1)\t\t\n");
    printf("\t\t Carregar jogo(tecle 2)\t\t\n");
    printf("\t\t Ranking(tecle3)\t\t\n");
    printf("\t\t Sair(tecle 4)\t\t\n");
    fflush(stdin);
    scanf("%d", &opcao);
    switch(opcao)
    {
    case 1:
        do
        {
            clrscr();
            puts("Insira o nome do jogador");
            fflush(stdin);
            gets(Jogador->nome_jogador);
            clrscr();
            escolher_modo_jogo(Jogador);
            inicia_novo_jogo(Jogador, listaagentes, listachaves, listaparedes, Ogro);
            num_partidas++;
        }
        while(num_partidas < NUM_RANK);
        clrscr();
        exibe_ranking();
        break;
    case 2:

        break;

    case 3:
        clrscr();
        exibe_ranking();
        break;

    case 4:
        exit(0);
        break;
    }
}
int main()
{
    srand(time(NULL));
    JOGADOR Jogador;
    AGENTE listaagentes[AGENTESMAX];
    CHAVE listachaves[CHAVESMAX];
    PAREDE listaparedes[40];
    OGRO Ogro[5];
    //JOGO jogo;

    menu(&Jogador, listaagentes, listachaves, listaparedes, Ogro);
    return(0);
}
