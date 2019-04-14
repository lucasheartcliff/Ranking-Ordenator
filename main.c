/*Core Files*/
#include <stdio.h>
#include <stdlib.h>

/*String Files*/
#include <conio.h>
#include <string.h>

#define buffer 180

typedef struct{
    int count; // contador de quantas vezes se repete
    char *word; // termo de tamanho dinamico
}item;

typedef struct{
    int total; // ?
    int block; // total de palavras encontradas sem repetição
    item **list; //** é usado para ponteiro de ponteiros
}mapa;

void clean(void){
    /*Limpa tela*/
    system("cls");
}

void pause(void){
    /*Pausa no sistema*/
    system("pause");
}

/*Funções*/
void insert_word(FILE *file,mapa *mp,int *sum, int *p); //

void scan_file(mapa *mp);

int read_all(char now[], char before[]){
    /*Verifica se o arquivo chamado ja foi lido por completo*/

   if( strcmp(before,now) == 0){
        /*Se a palavra anterior for igual à atual ou à um ponto final*/
        return 1;
    }else{
        /*Se não for igual, armazena o valor para ser comparado na próxima chamada à função.*/
        strcpy(before,now);
        return 0;
    }
}

void scan_file(mapa *mp){
    char now[buffer]; // Vai guardar a palavra atual.
    char pre[buffer]; // Vai guardar a palavra anterior.
    int *p = (int *) malloc(sizeof(int)); // Somente para não ficar vazia
    int i=0,sum=0;

    FILE *file;

    file = fopen("teste.txt","r");

    //fflush(stdin);
    //setbuf(stdin,NULL);

    if(!file){
        clean();
        printf("Erro abrir o arquivo!!\n\n");
        printf("Erro : #0001\n\n");
    }else{
        while( fscanf(file,"%s",now) && !(read_all(now,pre)) ){ //
            sum++;
        }

        fclose(file);

        p = (int*) (realloc(p,sum * sizeof(int)));

        if(p == NULL){
            clean();
            printf("Memória Insuficente.\n\n Erro : #0002");
            exit(1);
        }else{

            strcpy(now,"");
            strcpy(pre,"");

            file = fopen("teste.txt","r");

            while( fscanf(file,"%s",now) && !(read_all(now,pre)) ){ //
               p[i] = (strlen(now));
               i++;
            }
            fclose(file);
            insert_word(file,mp,&sum,p);
        }
    }
}

void insert_word(FILE *file,mapa *mp,int *sum, int *p){
    int i;
    file = fopen("teste.txt","r");

    mp->list = (item **) malloc((*sum) * sizeof(item*));

    if(mp->list == NULL){
       clean();
       printf("Memoria Insuficiente.\n\nErro : #0003");
       exit(1);
    }else{
        for(i=0;i<(*sum);i++){
            mp->list[i] = (item *) malloc(sizeof(item));
            if(mp->list[i] == NULL){
                clean();
                printf("Memoria Insuficiente.\n\nErro : #0004");
                exit(1);
            }else{
                mp->list[i]->word = (char *) malloc((p[i]) * sizeof(char));

                if(mp->list[i]->word == NULL){
                    clean();
                    printf("Memoria Insuficiente.\n\nErro : #0005");
                    exit(1);
                }else{
                    fscanf(file,"%s",mp->list[i]->word);
                    mp->list[i]->count = strlen(mp->list[i]->word);
                    printf("Palavra : %s | Indice : %i | Tamanho : %i | Ponteiro Tamanho : %i\n",mp->list[i]->word,i,mp->list[i]->count,p[i]);
                }
            }
        }
    }
    fclose(file);
    free(p);
}

int main(void){

    mapa *mp = (mapa *) malloc(sizeof(mapa));

    if(mp == NULL){
        clean();
        printf("Falta de Memoria para inicializar.\n\nErro : #0001");
        exit(1);
    }else{
        scan_file(mp);
    }
    return 0;
}
