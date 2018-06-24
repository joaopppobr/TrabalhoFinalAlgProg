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
#define NUM_SEGMENTOS 5

typedef struct
{
    int x;
    int y;
}
Coordenada;

typedef struct
{
    int vidas;
    int chaves_coletadas;
    char nome_jogador[NOME];
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
    JOGADOR Jogador;
    AGENTE listaagentes[NUM_AGENTES];
    CHAVE listachaves[NUM_CHAVES];
    PAREDE listaparedes[];
}
JOGO;

int testaparedes(PAREDE listaparedes[],int *x,int *y, int num_paredes)
{
    int i;
    for(i=0; i < (num_paredes * NUM_SEGMENTOS + NUM_SEGMENTOS); i++)
    {
        if(listaparedes[i].posicao.x == *x && listaparedes[i].posicao.y == *y)
        {
            return 0;
        }
    }
    return 1;
}

void escolher_modo_jogo(int *num_paredes, JOGADOR *Jogador)
{

    printf("Escolha o modo de jogo:");
    scanf("%d", &Jogador->modo_de_jogo);

    if (Jogador->modo_de_jogo)
    {
        *num_paredes = 7;
    }
    else
    {
        *num_paredes = 5;
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
void desenha_ogro()
{
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
void gera_paredes(int num_paredes, PAREDE listaparedes[])
{
    srand(time(NULL));
    int i, j;
    int direcao = 0;
    int dirx, diry;
    int posx, posy;

    for(i=0; i<num_paredes; i++)
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

void desenha_paredes(int num_paredes, PAREDE listaparedes[])
{
    int i;
    for (i=0; i<(num_paredes * NUM_SEGMENTOS + NUM_SEGMENTOS) -1; i++)
    {
        textbackground(BLUE);
        putchxy(listaparedes[i].posicao.x, listaparedes[i].posicao.y, ' ');
        textbackground(BLUE);
    }
}


void desenha_jogador(JOGADOR *Jogador)
{
    char jogador = 'P';

    textbackground(GREEN);
    textcolor(GREEN);
    putchxy(Jogador->posicao.x, Jogador->posicao.y, jogador);
}
void movimenta_jogador(JOGADOR *Jogador, int ch, PAREDE listaparedes[], int num_paredes)
{
    char jogador = 'P';


    switch(ch)
    {
    case 75:
        Jogador->posicao.x -= 1;
        if(Jogador->posicao.x > 1 && testaparedes(listaparedes, &Jogador->posicao.x, &Jogador->posicao.y, num_paredes))
        {
            textbackground(7);
            putchxy(Jogador->posicao.x+1, Jogador->posicao.y, ' ');
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, jogador);
        }
        else
        {
            Jogador->posicao.x += 1;
        }

        break;

    case 77:
        Jogador->posicao.x+= 1;
        if(Jogador->posicao.x <= MAXX-1 && testaparedes(listaparedes, &Jogador->posicao.x, &Jogador->posicao.y, num_paredes))
        {
            textbackground(7);
            putchxy(Jogador->posicao.x-1, Jogador->posicao.y, ' ');
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, jogador);
        }
        else
        {
            Jogador->posicao.x -= 1;
        }
        break;

    case 72:
        Jogador->posicao.y-= 1;
        if(Jogador->posicao.y > 1 && testaparedes(listaparedes, &Jogador->posicao.x, &Jogador->posicao.y, num_paredes))
        {
            textbackground(7);
            putchxy(Jogador->posicao.x, Jogador->posicao.y +1, ' ');
            textbackground(7);
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, jogador);
        }
        else
        {
            Jogador->posicao.y += 1;
        }
        break;

    case 80:
        Jogador->posicao.y+=1;
        if(Jogador->posicao.y <= MAXY-1 && testaparedes(listaparedes, &Jogador->posicao.x, &Jogador->posicao.y, num_paredes))
        {
            textbackground(7);
            putchxy(Jogador->posicao.x, Jogador->posicao.y -1, ' ');
            textbackground(GREEN);
            textcolor(GREEN);
            putchxy(Jogador->posicao.x, Jogador->posicao.y, jogador);
        }
        else
        {
            Jogador->posicao.y -= 1;
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
void movimenta_agentes(AGENTE listaagentes[], CHAVE listachaves[], PAREDE listaparedes[], int num_paredes)
{
    int j=0;
    srand(time(NULL));
    int direcao = rand() % 3;

    switch(direcao)
    {
    case 0:
        for(j=0; j<NUM_AGENTES; j++)
        {
            listaagentes[j].posicao.x-= 1;
            if(listaagentes[j].posicao.x > 1 && testaparedes(listaparedes, &listaagentes[j].posicao.x, &listaagentes[j].posicao.y, num_paredes))
            {
                    textbackground(7);
                    putchxy(listaagentes[j].posicao.x+1, listaagentes[j].posicao.y, ' ');
                    textbackground(7);
                    textbackground(RED);
                    textcolor(RED);
                    putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
            }
        }
        break;

    case 1:
        for(j=0; j<NUM_AGENTES; j++)
        {
            listaagentes[j].posicao.x+= 1;
            if(listaagentes[j].posicao.x<= MAXX-1 && testaparedes(listaparedes, &listaagentes[j].posicao.x, &listaagentes[j].posicao.y, num_paredes))
            {
                    textbackground(7);
                    putchxy(listaagentes[j].posicao.x-1, listaagentes[j].posicao.y, ' ');
                    textbackground(7);
                    textbackground(RED);
                    textcolor(RED);
                    putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                }
        }
        break;

    case 2:
        for(j=0; j<NUM_AGENTES; j++)
        {
            listaagentes[j].posicao.y-= 1;
            if(listaagentes[j].posicao.y > 1 && testaparedes(listaparedes, &listaagentes[j].posicao.x, &listaagentes[j].posicao.y, num_paredes))
            {
                    textbackground(7);
                    putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y+1, ' ');
                    textbackground(7);
                    textbackground(RED);
                    textcolor(RED);
                    putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                }
        }
        break;

    case 3:
        for(j=0; j<NUM_AGENTES; j++)
        {
            listaagentes[j].posicao.y+=1;
            if(listaagentes[j].posicao.y <= MAXY-1 && testaparedes(listaparedes, &listaagentes[j].posicao.x, &listaagentes[j].posicao.y, num_paredes))
            {
                    textbackground(7);
                    putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y-1, ' ');
                    textbackground(7);
                    textbackground(RED);
                    textcolor(RED);
                    putchxy(listaagentes[j].posicao.x, listaagentes[j].posicao.y, ' ');
                }
        }

        break;
    }
}
void desenha_CHAVEs(CHAVE listachaves[])
{
    srand(time(NULL));
    int j;

    for(j=0; j<NUM_CHAVES; j++)
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

    for(i=0; i<NUM_AGENTES; i++)
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

    for(i=0; i<NUM_CHAVES; i++)
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
void mensagem_final(JOGADOR Jogador)
{
    if (Jogador.chaves_coletadas == NUM_CHAVES)
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
int adiciona_ranking(JOGADOR Jogador)
{

    if (Jogador.modo_de_jogo)
    {
        return(int) ((30000 * 2)/ Jogador.tempo);
    }
    else
    {
        return(int) ((30000)/ Jogador.tempo);
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
int main()
{
    int tecla;
    int num_paredes = 0;
    int num_partidas = 0;

    JOGADOR Jogador;
    AGENTE listaagentes[NUM_AGENTES];
    CHAVE listachaves[NUM_CHAVES];
    PAREDE listaparedes[40];
    //JOGO jogo;

    clock_t tempo_ini, tempo_fim;
    //clock_t tempo;

    srand(time(NULL));

    do
    {
        Jogador.chaves_coletadas = 0;
        Jogador.vidas = 3;
        Jogador.posicao.x = 2 + rand() % (MAXX - 2);
        Jogador.posicao.y = 2 + rand() % (MAXY - 2);

        clrscr();
        fflush(stdin);
        puts("Insira o nome do jogador");
        gets(Jogador.nome_jogador);
        clrscr();

        escolher_modo_jogo(&num_paredes, &Jogador);
        tempo_ini = clock();

        desenha_cenario();
        //desenha_ogro();
        gera_paredes(num_paredes, listaparedes);
        desenha_paredes(num_paredes, listaparedes);
        desenha_jogador(&Jogador);
        desenha_placar(&Jogador);
        desenha_CHAVEs(listachaves);
        desenha_agente(listaagentes);

        do
        {
            testa_CHAVEs(listachaves,&Jogador);
            testa_agentes(listaagentes, &Jogador);
            /*
            tempo = clock();
            if(tempo - tempo_ini >= 1){
            movimenta_agentes(listaagentes, listachaves, listaparedes, num_paredes);
            }
            tempo = clock();
            */

            if(kbhit())
            {
                tecla = getch();
                movimenta_jogador(&Jogador, tecla, listaparedes, num_paredes);
            }

        }
        while(Jogador.chaves_coletadas < NUM_CHAVES && Jogador.vidas > 0);

        tempo_fim = clock();
        Jogador.tempo = gera_score(tempo_ini, tempo_fim);
        if (Jogador.vidas > 0)
        {
            Jogador.ranking = adiciona_ranking(Jogador);
            salva_ranking(Jogador);
        }
        num_partidas++;
        mensagem_final(Jogador);
    }
    while(num_partidas < NUM_RANK);

    clrscr();
    exibe_ranking();

    return(0);
}
