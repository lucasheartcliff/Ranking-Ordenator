/*Map.h*/

typedef struct Item item;
typedef struct Query query;
typedef struct Mapa mapa;

/*Funções Mapa*/
void scan_file(mapa *mp); // Escaneia o arquivo

void re_order(mapa *mp, int *pi); // Re-ordena as palavras de acordo com o indice e quantdade de vezes que se repete

void clean_word(char word[]); // Remove caracteres especiais da palavra

int set_filters(mapa* mp);

//int set_word(mapa *mp); // Filtro de buscar por palavra

//int set_gap(mapa *mp); // Filtro de busca por intervalo

//int set_size(mapa *mp); // Filtro de busca por tamanho da palavra
