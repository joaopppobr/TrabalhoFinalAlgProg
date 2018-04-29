# TrabalhoFinalAlgProg
Trabalho Final da Disciplina de Algoritmos e Programação.
INF01202 – ALGORITMOS E PROGRAMAÇÃO – 2018-1

Objetivo:
Deverá ser desenvolvido o jogo “Resgate o ogro”. O usuário controla um
único jogador que se movimenta em 4 direções no cenário do jogo buscando chaves
e fugindo de guardas inimigos para regatar o ogro da prisão. O objetivo do jogo é
coletar 3 chaves para abrir a prisão onde o ogro se encontra, sem ser eliminado
pelos guardas que se movimentam aleatoriamente no cenário. 

O cenário do jogo será implementado em modo texto. Inclui a área de movimento
entre as coordenadas 2 a 23 (linha) e 2 e 78 (coluna) e a área de informação na
linha 25. Veja exemplo na Figura 1. Uma moldura nas linhas 1 e 24 e as colunas 1
e 80 circunda a área do jogo e limita o movimento dos elementos do jogo. 

O jogo deve ter, no mínimo, dois níveis de dificuldade. Além das dificuldades
mencionadas abaixo para o nível 2, outras podem ser criadas pelos alunos.

a) Elementos do jogo:
Jogador: Elemento único. Movimenta-se em 4 direções - para cima, para baixo,
para a esquerda, para a direita - e coleta chaves. O jogador não pode sair da área
estabelecida pelas paredes do cenário, ao chegar em qualquer dos limites, ele não
se movimenta mais naquela direção. Inicia o jogo com 3 vidas.

O jogador deve ser implementado como uma Struct, com todas as suas
informações: nome, coordenadas, vidas, score, caractere e cor da representação no
jogo e outras que o jogo exigir. 

Guardas: qualquer número, dependendo do nível de dificuldade do jogo. Número
inicial de guarda = 2. Movimentam-se de forma autônoma (sem intervenção do
jogador) e aleatória em 8 direções - para cima, para baixo, para a esquerda, para a
direita, diagonal esquerda e acima, diagonal esquerda e abaixo, diagonal direita e
acima e diagonal direita e abaixo, sempre em uma posição adjacante e livre. Os
guardas atiram se o jogador entrar em qualquer casa a 2 ou menos coordenadas de
distância e fazem decrescer o número de vidas do jogador. Os guardas não podem
sair da área estabelecida pelas paredes do cenário.
Os guardas devem ser implementados como um arranjo de Struct, onde cada
posição do arranjo contem todas as informações de um guarda.

Chaves: no modo fácil existirão 5 chaves espalhadas pelo mapa e, no modo difícil,
3 chaves. As chaves deverão surgir em uma posição aleatória e livre no mapa,
assim que o jogo for iniciado. As chaves ficam invisíveis até o jogador ficar a uma
casa de distância delas. Quando a chave aparece o jogador deverá ir para a mesma
posição dela para poder coletá-la, então ela desaparece do cenário e aumenta o
contador de chaves na área de informação do jogo.
As chaves devem ser implementados como um arranjo de Struct, onde cada
posição do arranjo contem todas as informações de cada chave

Paredes: são distribuídas na área de jogo para proteger o jogador dos guardas e
atrapalhar o movimento do jogador e dos guardas. As paredes devem ser definidas
no arquivo texto que representa o mapa. Devem existir pelo menos dois arquivos
texto para representar o mapa modo fácil e o mapa modo difícil do jogo. O mapa do
modo difícil deverá apresentar uma maior quantidade de paredes internas do que o
modo fácil.
As paredes podem ser representadas como lista de estruturas ou matrizes, como os
alunos decidirem.

Torre do Ogro: A torre do ogro fica posicionada na parte central da parede direita
da área de jogo. Quando as chaves são levadas até lá pelo jogador, as paredes
desaparecem, libertando o ogro.
A Torre pode ser implementada na forma que os alunos desejarem.

Área de informação: 
A linha na base do cenário mostra:
- o nome do jogador, instanciado no inicio do jogo, ou carregado do arquivo;
- o numero de vidas restantes, inciando em 3;
- o numero de chaves coletadas, iniciando em zero;
- o nível do jogo (facil ou dificil)
- o escore ou tempo do jogo, iniciando em zero e aumentando de acordo com o
clock do computador no formato hh:mm:ss.


b) Início do jogo
A tela inicial mostra o nome dos alunos, nome da disciplina e semestre. Ao
iniciar, o jogo pergunta o nome do jogador e oferece as opções do Menu Principal.

● Menu principal: deverá conter pelos menos os seguintes dados e as
opções:

1) Novo Jogo Modo fácil: carrega arquivo texto de configuração inicial, inicializa
as estruturas de dados e mostra o cenário com elementos do jogo.

2) Novo Jogo Modo difícil: carrega arquivo texto de configuração avançada,
inicializa as estruturas de dados e mostra o cenário com elementos do jogo.
Neste modo de jogo, existirão menos chaves e mais guardas que devem se
movimentar mais rápido do que no modo fácil.

3) Retornar ao jogo: se o jogo foi interrompido com ESC, retorna ao mesmo
jogo. Se nao houver jogo interrompido, dá mensagem e retorna ao Menu
Principal.

4) Carregar partida: abre o arquivo binário de jogos, busca o jogador e carrega
as configurações de jogo que foram salvas, no ponto em que parou. Se não
houver o jogador no arquivo, dá uma mensagem e volta ao Menu Principal.

5) Salvar partida: Todas as variáveis do jogo são salvas em um arquivo binário
com os elementos do jogo congelados como estão.

6) Ajuda: deverá mostrar uma descrição de quais controles deverão ser
utilizados para jogar.

7) Rank: abre o arquivo binário de jogos, e mostra a lista em ordem crescente
dos jogadores e seus escores (tempo de jogo). Oferece a opção de Resetar
rank, que zera todos os escores e nome de jogadores, ou Sair, que retorna
ao Menu Principal.

8) Sair: fecha todos os arquivos, mostra uma mensagem e encerra o programa.

C)O fim do jogo ocorre em 3 situações:

1) Vitória: Quando o jogador coletar 3 chaves, poderá ir em direção à cadeia e
libertar o ogro. Na situação de vitória, o escore do jogo (tempo de jogo) é salvo
na lista de jogadores-escores em ordem crescente de escores (menor tempo em
primeiro lugar). Uma mensagem de parabéns com a lista ordenada de jogadores
e seus escores é mostrada. Pode retornar ao Menu Principal.

2) Derrota: Caso o jogador ficar a uma distância de tamanho 2 dos guardas, ele
perderá 1 vida e fugirá automaticamente para uma posição livre e adjacente a
ele. Quando sua vida chegar em 0 ou caso fique encurralado pelos guardas 
(não tendo posição adjacente livre), o jogador perderá o jogo. Uma mensagem
de pesar com a lista ordenada de jogadores e seus escores é mostrada, mas
seu tempo não é armazenado no ranking. É oferecido ao jogador as opções de
jogar um jogo novo, carregar um jogo ou sair.

3) Interrupção: quando o jogador precionar a tecla ESC, o estado atual do jogo
deve pausar e o sistema mostra o Menu Principal.

d) Pontuação do jogo:
A escore do jogo é de acordo com o tempo que foi necessário para vencer
uma partida, ou seja, quanto menor o tempo, melhor colocado o jogador estará no
ranking.

e) Controles:
A movimentação do personagem deverá ser feita pelas flechas do teclado
(NÃO deverão ser utilizados os botões “W/A/S/D”). Estes controles deverão estar
exibidos no Menu Controle.

f) Salvar estado do jogo:
O estado do jogo deverá ser salvo em um arquivo binário que poderá ser
carregado no menu principal, em uma outra execução do jogo. Este arquivo deverá
conter informações sobre o jogador (nome, vidas, número de chaves já coletadas,
posição, ranking e representação no cenário, ou seja, caractere e cor), guardas
(caractere, cor, posição), tempo, chaves ainda não coletadas (caractere, cor,
posição), entre outras variáveis necessárias para a reinicialização correta da partida.

