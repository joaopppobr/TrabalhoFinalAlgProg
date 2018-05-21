# Como escrever o código

## Regras de sintaxe:
### Estruturas:

Todas as estruturas devem ser nomeadas iniciando com letra maiúscula e precedida por um typedef;

`typedef struct NomeDaEstrutura`


### Constantes:
Todas as constantes devem estar contidas após os includes, e devem ser escritas em Caps Lock.

`#define CONSTANTE NUMERO`

### Variáveis:
Todas as variáveis devem ser escritas em letras minusculas. Variaveis com nomes espaçados devem ser separados por underscore("_").

`int minha_variavel = valor`
`char caractere = valor`

Variáveis que são indicativas de quantidade devem ser precedidas de "num", como a seguir:

`int num_jogadores = valor` // Indicando a quantidade de jogadores

### Funções:

Funções devem possuir seu objetivo claro no nome, e nomes espaçados devem ser separados com underscore("_")

`void minha_funcao() {}`

## Estruturação do código

Todos os programas do repositório devem possuir a seguinte estrutura:

- Chamada de Bibliotecas
- Definição de constantes
- Definição de Estruturas
- Definição de funções
- Main  
