/*Map.c*/

#include "map.h"


typedef struct Item{
    int count; // contador de quantas vezes se repete
    char *word; // termo de tamanho dinamico
}item;

typedef struct Query{
    int  which; // Um sinalizador para indicar qual filtro usar na hora de exibir se '0', nao há critérios
    int  num_char; // Se quiser filtrar pelo número de caractéres nas palavras
    int  count_bet[2]; // Se quiser filtra por um intervalo
    char *term; // Se quiser filtrar por uma palavra
}query;

typedef struct Mapa{
    query filter; // Opções de filtros
    int total; // Total de palavras encontradas
    int block; // Quantos blocos de palavras encontrados (1 bloco == 10 palavras)
    item **list; //** é usado para ponteiro de ponteiros
}mapa;

void re_order(mapa *mp, int *pi){
    int i;
    item *temp;
    for(i=0;i< *pi;i++){
        if(mp->list[i]->count < mp->list[*pi]->count){
            temp = mp->list[i];
            mp->list[i] = mp->list[*pi];
            mp->list[*pi] = temp;
            break;
        }
    }
}

void clean_word(char word[]){
    int lenght = strlen(word);
    int i,j;
    /*Se algum caracter da palavra for igual à um caracter especial, irá corrigi-lo.*/
    for(i = 0; i <lenght ; i++ ){
        if( (word[i] == '.') || (word[i] == ',')  || (word[i] == '(') || (word[i] == ')')  || (word[i] == ';')  || (word[i] == ':')  || (word[i] == '[') || (word[i] == ']') || (word[i] == '{')  || (word[i] == '}') || (word[i] == '/') || (word[i] == '\\') ){
            for(j=i;j<lenght;j++){
                word[j]= word[j+1]; /*Vai reorganizar o vetor de caracteres. */
            }
        }
    }
}

void scan_file(mapa *mp){
    char word[buffer]; // palavra buscada no arquivo
    char arq[buffer]; // nome do arquivo à ser lido

    int i=0;
    int j,flag;
    int lenght=0;

    FILE *file;

    clean();
    printf("Digite o nome do arquivo, com o formato, que deseja abrir:\n");
    gets(arq);

    /*printf("%s",arq);
      pause();
    */

    file = fopen(arq,"r");
    //fflush(stdin);
    //setbuf(stdin,NULL);

    if(!file){
        clean();
        printf("Erro abrir o arquivo!!\n\n");
        printf("Erro : #0001\n\n");
        pause();
    }else{
        while( fscanf(file,"%s",word)  != EOF ){
            /*Enquanto não chegar ao final do arquivo, continua lendo*/
            if(i==0){
                mp->list = (item **) malloc(sizeof(item*));
            }else{
                mp->list = (item **) realloc(mp->list, (i + 1) * sizeof(item*));
            }

            if(mp->list == NULL){
               clean();
               printf("Memoria Insuficiente.\n\nErro : #0003");
               exit(1);
            }else{
               mp->list[i] = (item*) malloc(sizeof(item));

               if(mp->list[i] == NULL){
                  clean();
                  printf("Memoria Insuficiente.\n\nErro : #0004");
                  exit(1);
               }else{
                   clean_word(word);

                   /*Verifica se já existe a palavra buscada*/

                   flag = 0;

                   for(j=0;j<i;j++){
                     if( strcmp(mp->list[j]->word, word) == 0){
                        flag = 1;
                        break;
                     }
                   }

                   if(flag){
                        mp->list[j]->count += 1;
                        re_order(mp,&j);
                   }else{

                       lenght = (strlen(word) + 1);
                       mp->list[i]->word = (char *) malloc(lenght * sizeof(char));

                       if(mp->list[i]->word == NULL){
                          clean();
                          printf("Memoria Insuficiente.\n\nErro : #0005");
                          exit(1);
                       }else{
                           strcpy(mp->list[i]->word,word);
                           mp->list[i]->count = 1;
                           i++;
                       }
                   }
               }
            }
        }
    }
    fclose(file);
    mp->total = i;
}


int set_filters(mapa *mp){
    int opt = 0;

    while(opt != 3){
        opt = filter_menu();

        if(opt == 0){
           /*if(set_word(mp)){
                mp->filter.which = 1;
           }*/

           return 0;
        }else if(opt == 1){
            /*if(set_gap(mp)){
                mp->filter.which = 2;
           }*/
            return 0;
        }else if(opt == 2){
            /*if(set_word(mp)){
                mp->filter.which = 3;
            }*/
            return 0;
        }else if(opt == 3){
            mp->filter.which = 0;
            mp->filter.count_bet[0] = 0;
            mp->filter.count_bet[1] = 0;
            mp->filter.term = NULL;
            mp->filter.num_char = 0;

            return 0;
        }else{
            return 0;
        }
    }
}
