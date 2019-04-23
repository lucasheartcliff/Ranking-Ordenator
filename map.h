/*Map.h*/

/*Core Files*/
#include <stdio.h>
#include <stdlib.h>

/*String Files*/
#include <conio.h>
#include <string.h>

#define buffer 255

#ifndef MAP_H
#define MAP_H

typedef struct _item{
    int count; // contador de quantas vezes se repete
    char *word; // termo de tamanho dinamico
}item;

typedef struct _query{
    int  which; // Um sinalizador para indicar qual filtro usar na hora de exibir se '0', nao há critérios
    int  num_char; // Se quiser filtrar pelo número de caractéres nas palavras
    int  count_bet[2]; // Se quiser filtra por um intervalo
    char *term; // Se quiser filtrar por uma palavra
}query;

typedef struct _mapa{
    query filter; // Opções de filtros
    int total; // Total de palavras encontradas
    int block; // Quantos blocos de palavras encontrados (1 bloco == 10 palavras)
    item **list; //** é usado para ponteiro de ponteiros
}mapa;


/*Funções Mapa*/
void scan_file(mapa *mp); // Escaneia o arquivo

void re_order(mapa *mp, int *pi); // Re-ordena as palavras de acordo com o indice e quantdade de vezes que se repete

void clean_word(char word[]); // Remove caracteres especiais da palavra

int set_filters(mapa* mp);

//int set_word(mapa *mp); // Filtro de buscar por palavra

//int set_gap(mapa *mp); // Filtro de busca por intervalo

//int set_size(mapa *mp); // Filtro de busca por tamanho da palavra

/*Funções da Interface*/

int main_menu(void); // Menu principal

int filter_menu(void); // Menu de Filtros

void clean(void); // Função limpa tela

void pause(void); // Função pausa no sistema

#endif // MAP_H
