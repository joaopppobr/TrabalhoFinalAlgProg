//Trabalho final da disciplina de Algoritmos e Programaçao (INF01202) 2018/1
//Por Joao Pedro Porto Pires de Oliveira e Theo Santiago Muller
#include <stdio.h>
#include <stdlib.h>
#include <conio2.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <unistd.h>
#include <dos.h>
#include <math.h>
#include <stddef.h>

#define _TIME_H
#define MAXX 80 //Limite X do cenário;
#define MAXY 24 //Limite Y do cenário;
#define NOME 20 // Tamanho máximo do nome do jogado;
#define NUM_JOGOS 2 //Número de vezes que o loop de jogos roda;
#define NUM_SEGMENTOS 5 //Número de segmentos em cada parede do jogo;
#define AGENTESMAX 20 //Número máximo de agentes permitidos no jogo;
#define CHAVESMAX 5 //Número máximo de chaves permitidos no jogo;
#define PAREDESMAX 100 //Tamanho máximo da array listaparedes



typedef struct
{
    int x;
    int y;
}
Coordenada; //Estrutura que é chamada por outras estruturas para indicar a posicao do elemento representado na tela.

typedef struct
{
    //As informações abaixo variam de acordo com o modo de jogo escolhido
    int num_chaves;
    int num_agentes;
    int num_paredes;
    //
    int vidas; //Sempre inicia com 3
    int chaves_coletadas;
    int ranking;
    int tempo;
    int modo_de_jogo;
    Coordenada posicao;
    char nome_jogador[NOME];
}
JOGADOR; //Estrutura que carrega as informacoes sobre o jogador.

typedef struct
{
    Coordenada posicao;
    int velocidade; //Tempo para cada movimento em milisegundos.
}
AGENTE; //Estrutura que carrega as informacoes sobre os agentes.

typedef struct
{
    Coordenada posicao;
}
CHAVE; //Estrutura que carrega as informacoes sobre as chaves.

typedef struct
{
    Coordenada posicao;
}
PAREDE; //Estrutura que carrega as informacoes sobre as paredes.

typedef struct
{
    Coordenada posicao;
}
OGRO; //Estrutura que carrega as informacoes sobre o ogro.

typedef struct
{
    JOGADOR Jogador;
    AGENTE listaagentes[AGENTESMAX];
    CHAVE listachaves[CHAVESMAX];
    PAREDE listaparedes[PAREDESMAX];
    OGRO Ogro[5];
}
JOGO; //Estrutura que carrega todas as estruturas necessárias para iniciar um novo jogo


//Função utilizada para testar se a posição dos elementos do cenário são iguais as do elemento da parede. Caso for, retorna 0. Caso não, retorna 1.
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
//Função que modifica as variáveis de jogo dependendo da escolha do modo de jogo.
void escolher_modo_jogo(JOGADOR *Jogador, AGENTE *listaagentes)
{
    printf("Escolha o modo de jogo:\n");
    printf("0: facil ; 1: dificil ; 2: muito dificil ; 3: impossivel\n");
    scanf("%d", &Jogador->modo_de_jogo);

    if (Jogador->modo_de_jogo == 0) //Fácil
    {
        Jogador->num_chaves = 5;
        Jogador->num_agentes = 4;
        Jogador->num_paredes = 5;
        listaagentes->velocidade = 500;
    }
    if (Jogador->modo_de_jogo == 1) //Difícil
    {
        Jogador->num_paredes = 7;
        Jogador->num_chaves = 3;
        Jogador->num_agentes = 6;
        listaagentes->velocidade = 200;
    }
    if (Jogador->modo_de_jogo == 2) //Muito Difícil
    {
        Jogador->num_chaves = 5;
        Jogador->num_agentes = 8;
        Jogador->num_paredes = 7;
        listaagentes->velocidade = 200;
    }
    if (Jogador->modo_de_jogo == 3) //Impossível
    {
        Jogador->num_chaves = 7;
        Jogador->num_agentes = 20;
        Jogador->num_paredes = 8;
        listaagentes->velocidade = 30;
    }
}

//Função que desenha o cenário do jogo;
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
//Função que gera a posição das paredes no jogo de forma randomica.
void gera_paredes(JOGADOR *Jogador, PAREDE listaparedes[])
{
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
//Função que dada a posição das paredes gerada na gera_paredes desenha elas no cenário.
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
//Função que dada uma posição, desenha o jogador no cenário.
void desenha_jogador(int x, int y)
{
    char jogador = 'P';

    textbackground(GREEN);
    textcolor(GREEN);
    putchxy(x, y, jogador);
}
//Função que dada uma posição, desenha o agente no cenário.
void desenha_agente(int x, int y)
{
    char agente = 'G';

    textbackground(RED);
    textcolor(RED);
    putchxy(x, y, agente);
}
//Função que dada uma posição, apaga o elemento que está nessa posição no cenário
void apaga_elemento(int x, int y)
{
    textbackground(7);
    putchxy(x, y, ' ');
}
//Função que dada uma posição inicial e uma direção, movimenta o elemento uma casa na direção indicada.
void movimenta_coisas(int *x, int *y, int direcao, PAREDE listaparedes[], JOGADOR *Jogador)
{

    switch(direcao)
    {
    case 1: //esquerda
        if(*x > 1 && testaparedes(listaparedes, *x-1, *y, Jogador)) //Testa as paredes para todas para garantir que o movimento não invade o espaço delas.
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
//Função que dada a tecla digitada pelo jogador, movimenta o personagem na direção indicada
void movimenta_jogador(JOGADOR *Jogador, int *ch, PAREDE listaparedes[])
{


    switch(*ch)
    {
    case 75: //esquerda
        if(Jogador->posicao.x > 2 && testaparedes(listaparedes, Jogador->posicao.x-1, Jogador->posicao.y, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y); //Primeiro apaga a posição anterior
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 1, listaparedes, Jogador); //Depois gera a nova posição
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y); //E finalmente desenha o jogador na nova posição.
        }
        break;

    case 77: //direita
        if(Jogador->posicao.x <= MAXX-2 && testaparedes(listaparedes, Jogador->posicao.x+1, Jogador->posicao.y, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 2, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    case 72: //cima
        if(Jogador->posicao.y > 2 && testaparedes(listaparedes, Jogador->posicao.x, Jogador->posicao.y-1, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 3, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    case 80: //baixo
        if(Jogador->posicao.y <= MAXY-2 && testaparedes(listaparedes, Jogador->posicao.x, Jogador->posicao.y+1, Jogador))
        {
            apaga_elemento(Jogador->posicao.x, Jogador->posicao.y);
            movimenta_coisas(&Jogador->posicao.x, &Jogador->posicao.y, 4, listaparedes, Jogador);
            desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
        }
        break;

    }
}
//Função que desenha o placar com as informações sobre o jogo
void desenha_placar(JOGADOR *Jogador)
{
    textbackground(7);
    textcolor(BLACK);
    gotoxy(3, MAXY+1);
    switch(Jogador->modo_de_jogo)
    {
    case 0: //Fácil
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nModo de jogo: Facil", Jogador->nome_jogador, Jogador->chaves_coletadas, Jogador->vidas);
        break;
    case 1: //Difícil
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nModo de jogo: Dificil", Jogador->nome_jogador, Jogador->chaves_coletadas, Jogador->vidas);
        break;
    case 2: //Muito Difícil
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nModo de jogo: Muito Difícil", Jogador->nome_jogador, Jogador->chaves_coletadas, Jogador->vidas);
        break;
    case 3: //Impossível
        printf("Nome: %s \t\tCHAVEs coletadas: %d \t\tVidas: %d \nModo de jogo: Impossivel", Jogador->nome_jogador, Jogador->chaves_coletadas, Jogador->vidas);
        break;
    }
}
//Função que gera e desenha os agentes em sua posição inicial no jogo.
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
/*Função que testa as chaves para os agentes, e retorna 0 caso a posição das chaves for igual a dos agentes.
Usada para não movimentar os agentes em direção as chaves.*/
int testa_chaves_agentes(CHAVE listachaves[], int x, int y, JOGADOR *Jogador)
{
    int i=0;

    for(i=0; i<Jogador->num_chaves; i++)
    {
        if(listachaves[i].posicao.x == x && listachaves[i].posicao.y == y)
        {
            return 0;
        }
        return 1;
    }
    return 1;
}
//Função que movimenta os agentes no jogo de forma randomica e individual, com os devidos testes para garantir que posição em que ele se move é permitida.
void movimenta_agentes(AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], JOGADOR *Jogador)
{
    int j=0;
    for(j=0; j<Jogador->num_agentes; j++)
    {
        int direcao = 1 + (rand() % 4);

        switch(direcao)
        {
        case 1: //Esquerda
            if(listaagentes[j].posicao.x > 2 && testaparedes(listaparedes, listaagentes[j].posicao.x-1, listaagentes[j].posicao.y, Jogador) && testa_chaves_agentes(listachaves, listaagentes[j].posicao.x-1, listaagentes[j].posicao.y, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y); //Apaga o elemento de sua posição anterior
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 1, listaparedes, Jogador); //Muda sua coordenada para a nova posição.
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);//Dsenha o agente em sua nova posição.
            }
            break;

        case 2: //Direita
            if(listaagentes[j].posicao.x<= MAXX-2 && testaparedes(listaparedes, listaagentes[j].posicao.x+1, listaagentes[j].posicao.y, Jogador) && testa_chaves_agentes(listachaves, listaagentes[j].posicao.x+1, listaagentes[j].posicao.y, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 2, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
            break;

        case 3://Baixo
            if(listaagentes[j].posicao.y > 2 && testaparedes(listaparedes, listaagentes[j].posicao.x, listaagentes[j].posicao.y-1, Jogador) && testa_chaves_agentes(listachaves, listaagentes[j].posicao.x, listaagentes[j].posicao.y-1, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 3, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
            break;

        case 4://Cima
            if(listaagentes[j].posicao.y <= MAXY-2 && testaparedes(listaparedes, listaagentes[j].posicao.x, listaagentes[j].posicao.y+1, Jogador) && testa_chaves_agentes(listachaves, listaagentes[j].posicao.x, listaagentes[j].posicao.y+1, Jogador))
            {
                apaga_elemento(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
                movimenta_coisas(&listaagentes[j].posicao.x, &listaagentes[j].posicao.y, 4, listaparedes, Jogador);
                desenha_agente(listaagentes[j].posicao.x, listaagentes[j].posicao.y);
            }
            break;
        }
    }
}
//Função que gera e desenha as chaves em posições aleatórias do cenário.
void desenha_CHAVEs(CHAVE listachaves[], JOGADOR *Jogador, PAREDE listaparedes[])
{
    int j;

    for(j=0; j<Jogador->num_chaves; j++)
    {

        listachaves[j].posicao.x = rand() % (MAXX - 3) + 1;
        listachaves[j].posicao.y = rand() % (MAXY - 4) + 2;

        if(testaparedes(listaparedes, listachaves[j].posicao.x, listachaves[j].posicao.y, Jogador)) //Testa as paredes para não gerar chaves que não sejam coletaveis
        {
            textbackground(YELLOW);
            textcolor(YELLOW);
            putchxy(listachaves[j].posicao.x, listachaves[j].posicao.y, ' ');
        }
    }
}
/*Função que testa se a posição do jogador e do agente são iguais.
Se a posição for igual, ele movimenta o jogador para longe e decrescenta a vida do jogador*/
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
/*Função que testa se a posição das chaves é igual a posição do jogador.
Se a posição for igual, adiciona uma chave para o contador de chaves do jogador*/
void testa_chaves(CHAVE listachaves[], JOGADOR *Jogador)
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
//Função que gera o tempo de jogo do jogador baseado no tempo inicial e final do loop.
int gera_tempo_jogo(clock_t tempo_ini, clock_t tempo_fim)
{
    return (int) ((tempo_fim - tempo_ini) / CLOCKS_PER_SEC);
}
//Função que desenha na tela a mensagem final de vitória ou derrota ao jogador após o jogo.
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
//Função que gera o ranking no jogador dependo do modo de jogo escolhido por ele.
int adiciona_ranking(JOGADOR *Jogador)
{
    switch(Jogador->modo_de_jogo)
    {
    case 0: //Fácil. Não possui multiplicador.
        return (30000)/ Jogador->tempo;
        break;
    case 1: //Difícil. Possui x2 de multiplicador.
        return (30000*2) / Jogador->tempo;
        break;
    case 2: //Muito Difícil. Possui x3 de multiplicador.
        return (30000*3)/ Jogador->tempo;
        break;
    case 3: //Impossível. Possui x4 de multiplicador.
        return (30000*4)/ Jogador->tempo;
        break;
    }
    return 0;
}
//Algoritmo de Quicksort que é utilizado para ordenar os rankings dos jogadores no arquivo de ranking.
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
//Função que salva o ranking do jogador em um arquivo de texto de no máximo 10 linhas.
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
//Função que exibe o ranking de todos os jogadores na tela a partir do arquivo de ranking.
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
//Função que salva as informações do jogo em um arquivo binário.
int salva_jogo(JOGO *jogo)
{
    JOGO buffer;
    FILE *arq;
    arq = fopen("jogos_salvos.bin","rb+");
    if(!arq){
      printf("Erro na abertura ou arquivo inexistente");
    }
    else
    {
      while(!feof(arq)){
        if(!strcmpfread(&buffer.jogador.nome, jogo->jogador.nome)){
        fseek(arq,- sizeof(JOGO),SEEK_CUR);
        if(fwrite(jogo,sizeof(JOGO),1,arq)){
          fclose(arq);
          return 1;
        }
      }
      if(fwrite(jogo,sizeof(JOGO),1,arq)){
        fclose(arq);
        return 1;
      }
      }
    }
    fclose(arq);
    return 0;
}
//Função que carrega um jogo de um arquivo binário a partir de um nome dado
int carrega_jogo(JOGO *jogo, char nome_procurado[]){
FILE *arq;
JOGO buffer;
arq = fopen("jogos_salvos.bin", "rb");
if(!arq){
    printf("Erro ao abrir o arquivo\n");
    return 0;
}
else {
    while(!feof(arq)){
        if(fread(&buffer, sizeof(JOGO), 1, arq) == 1){
                if(!strcmp(buffer.Jogador.nome_jogador, nome_procurado)){
                     *jogo = buffer;
                     return 1;
                }
                else{
                    printf("Nao achamos nenhum jogador com esse nome");
                    return 0;
                }
        }
    }
}
fclose(arq);
return 1;
}

//Função que inicia um novo jogo.
void inicia_novo_jogo(JOGADOR *Jogador, AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], OGRO Ogro[], JOGO *jogo)
{
    //Dá valor às variáveis iniciais do jogo
    int tecla;
    clock_t tempo_ini, tempo_fim;
    Jogador->chaves_coletadas = 0;
    Jogador->vidas = 3;
    Jogador->posicao.x = 2 + rand() % (MAXX - 2);
    Jogador->posicao.y = 2 + rand() % (MAXY - 2);
    double comeco_agente, fim_agente;

    //Pergunta ao jogador o nome e a dificuldade do jogo a ser iniciado
    clrscr();
    puts("Insira o nome do jogador");
    fflush(stdin);
    gets(Jogador->nome_jogador);
    clrscr();
    escolher_modo_jogo(Jogador, listaagentes);
    clrscr();

    tempo_ini = clock(); //Inicia o relógio do jogo.

    //Aqui se gera e desenha as estruturas do jogo.
    desenha_cenario();
    //desenha_ogro(Ogro);
    gera_paredes(Jogador, listaparedes);
    desenha_paredes(Jogador, listaparedes);
    desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
    desenha_placar(Jogador);
    desenha_CHAVEs(listachaves, Jogador, listaparedes);
    desenha_agentes(listaagentes, Jogador);

    //Começa o relógio do agente para movimentar de acordo com a velocidade determinada na dificuldade.
    comeco_agente = (double) clock () / (CLOCKS_PER_SEC / 1000);
    fim_agente = comeco_agente;

    do //Laço de uma sessão do jogo.
    {
        testa_chaves(listachaves,Jogador);
        testa_agentes(listaagentes, Jogador);

        //Movimenta os agentes a cada X tempo, dependendo da velocidade escolhida pelo jogador, em milisegundos
        if(fim_agente - comeco_agente >= listaagentes->velocidade)
        {
            movimenta_agentes(listaagentes, listachaves, listaparedes, Jogador);
            comeco_agente = fim_agente;
        }
        //Aqui o programa recebe a tecla inserida pelo jogador e executa funções de acordo.
        if(kbhit())
        {
            tecla = getch();
            if (tecla == 27){
                salva_jogo(jogo);
            }
            movimenta_jogador(Jogador, &tecla, listaparedes);
        }
        fim_agente = (double) clock () / (CLOCKS_PER_SEC / 1000);
    }
    while(Jogador->chaves_coletadas < Jogador->num_chaves && Jogador->vidas > 0);

    //Após uma sessão do jogo acabar, ele finaliza o clock e gera o tempo de jogo do jogador
    tempo_fim = clock();
    Jogador->tempo = gera_tempo_jogo(tempo_ini, tempo_fim);

    //Se o jogador ganhou o jogo, ele salva o ranking.
    if (Jogador->vidas > 0)
    {
        Jogador->ranking = adiciona_ranking(Jogador);
        salva_ranking(*Jogador);
    }

    mensagem_final(Jogador);
}
//Função que inicia um novo jogo com as configurações carregadas a partir de um jogo anterior
void inicia_jogo_carregado(JOGADOR *Jogador, AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], OGRO Ogro[], JOGO *jogo)
{
    int tecla;
    clock_t tempo_ini, tempo_fim;
    double comeco_agente, fim_agente;

    tempo_ini = clock(); //Inicia o relógio do jogo.

    clrscr();
    //Aqui se gera e desenha as estruturas do jogo.
    desenha_cenario();
    //desenha_ogro(Ogro);
    gera_paredes(Jogador, listaparedes);
    desenha_paredes(Jogador, listaparedes);
    desenha_jogador(Jogador->posicao.x, Jogador->posicao.y);
    desenha_placar(Jogador);
    desenha_CHAVEs(listachaves, Jogador, listaparedes);
    desenha_agentes(listaagentes, Jogador);

    //Começa o relógio do agente para movimentar de acordo com a velocidade determinada na dificuldade.
    comeco_agente = (double) clock () / (CLOCKS_PER_SEC / 1000);
    fim_agente = comeco_agente;

    do //Laço de uma sessão do jogo.
    {
        testa_chaves(listachaves,Jogador);
        testa_agentes(listaagentes, Jogador);

        //Movimenta os agentes a cada X tempo, dependendo da velocidade escolhida pelo jogador, em milisegundos
        if(fim_agente - comeco_agente >= listaagentes->velocidade)
        {
            movimenta_agentes(listaagentes, listachaves, listaparedes, Jogador);
            comeco_agente = fim_agente;
        }
        //Aqui o programa recebe a tecla inserida pelo jogador e executa funções de acordo.
        if(kbhit())
        {
            tecla = getch();
            if (tecla == 27){
                clrscr();
                salva_jogo(jogo);
                menu_pausa(jogo);
            }
            movimenta_jogador(Jogador, &tecla, listaparedes);
        }
        fim_agente = (double) clock () / (CLOCKS_PER_SEC / 1000);
    }
    while(Jogador->chaves_coletadas < Jogador->num_chaves && Jogador->vidas > 0);

    //Após uma sessão do jogo acabar, ele finaliza o clock e gera o tempo de jogo do jogador
    tempo_fim = clock();
    Jogador->tempo = gera_tempo_jogo(tempo_ini, tempo_fim);

    //Se o jogador ganhou o jogo, ele salva o ranking.
    if (Jogador->vidas > 0)
    {
        Jogador->ranking = adiciona_ranking(Jogador);
        salva_ranking(*Jogador);
    }

    mensagem_final(Jogador);
}
void menu_pausa(JOGO *jogo){
  int opcao;
  int tecla;
  clrscr();
  printf("\t\t Pausa\t\t\n");
  printf("\t\t Voltar ao jogo(tecle 1)\t\t\n");
  printf("\t\t Ajuda(tecle 2)\t\t\n");
  printf("\t\t Sair do jogo(tecle3)\t\t\n");
  fflush(stdin);
  scanf("%d", &opcao);
  switch(opcao)
  {
  case 1: //Volta ao jogo
      carrega_jogo(jogo, jogo->Jogador.nome_jogador);
      do //Faz NUM_JOGOS número de sessões do jogo antes de terminar.
      {
          inicia_novo_jogo(&jogo->Jogador, jogo->listaagentes, jogo->listachaves, jogo->listaparedes, jogo->Ogro, jogo);
          num_partidas++;
      }
      while(num_partidas < NUM_JOGOS);
      clrscr();
      exibe_ranking();
      break;
  case 2://Abre o menu de ajuda do jogo
  clrscr();
  printf("\t\t Jogo do resgate ao Ogro\t\t\n");
  printf("\t\t Movimente o jogador com as setas do teclado\t\t\n");
  printf("\t\t Colete as chaves em menor tempo para vencer\t\t\n");
  printf("\t\t Nao seja atacado por guardas\t\t\n");
  printf("\t\t Pressione 'Esc' para pausar e salvar o jogo\t\t\n");
  printf("\t\t Para voltar tecle 'Esc'\t\t\n");
  tecla = getch();
  if(tecla == 27){
    menu_pausa(jogo);
  }
      break;

  case 3://Sai do jogo
      clrscr();
      exit();
      break;
  }
}
//Função que mostra o menu inicial do jogo para o usuário.
void menu(JOGO *jogo)
{
    int opcao;
    int num_partidas = 0;
    char nome_procurado[NOME];
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
    case 1: //Inicia um novo jogo.
        do //Faz NUM_JOGOS número de sessões do jogo antes de terminar.
        {
            inicia_novo_jogo(&jogo->Jogador, jogo->listaagentes, jogo->listachaves, jogo->listaparedes, jogo->Ogro, jogo);
            num_partidas++;
        }
        while(num_partidas < NUM_JOGOS);
        clrscr();
        exibe_ranking();
        break;
    case 2://Inicia um jogo carregado a partir do arquivo de jogos salvos.
            puts("insira um nome para ser procurado");
            fflush(stdin);
            gets(nome_procurado);
            carrega_jogo(jogo, nome_procurado);
            if(carrega_jogo(jogo, nome_procurado) == 0){
                printf("Não achamos esse nome");
            }
            else{
              do //Faz NUM_JOGOS número de sessões do jogo antes de terminar.
              {
            inicia_jogo_carregado(&jogo->Jogador, jogo->listaagentes, jogo->listachaves, jogo->listaparedes, jogo->Ogro, jogo);
            num_partidas++;
          }
          while(num_partidas < NUM_JOGOS);
          clrscr();
          exibe_ranking();
            }
        break;

    case 3://Exibe o ranking geral na tela.
        clrscr();
        exibe_ranking();
        break;

    case 4://Sai do jogo.
        exit(0);
        break;
    }
}

//Laço principal do programa.
int main()
{
    //Inicializa as estruturas necessárias para executar o programa.
    srand(time(NULL));
    JOGO jogo;

    //Chama o menu do jogo
    menu(&jogo);
    return(0);
}
