/*Core Files*/
#include <stdio.h>
#include <stdlib.h>

/*String Files*/
#include <conio.h>
#include <string.h>

#define buffer 255

typedef struct{
    int count; // contador de quantas vezes se repete
    char *word; // termo de tamanho dinamico
}item;

typedef struct{
    int total; // Total de palavras encontradas
    int block; // Quantos blocos de palavras encontrados (1 bloco == 10 palavras)
    item **list; //** é usado para ponteiro de ponteiros
}mapa;

/*Funções Mapa*/
void scan_file(mapa *mp);

void re_order(mapa *mp, int *pi);

/*Funções Interface*/
int main_menu();

void clean();

void pause();

void clean(void){
    /*Limpa tela*/
    system("cls");
}

void pause(void){
    /*Pausa no sistema*/
    system("pause");
}

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

void scan_file(mapa *mp){
    char now[buffer], *arq; // Vai guardar a palavra atual.
    int i=0;
    int j,flag;
    int lenght=0;

    FILE *file;

    clean();
    printf("Digite o nome do arquivo que deseja abrir:\n");
    gets(arq);

    //printf("%s",arq);

    file = fopen(arq,"r");
    //fflush(stdin);
    //setbuf(stdin,NULL);

    if(!file){
        clean();
        printf("Erro abrir o arquivo!!\n\n");
        printf("Erro : #0001\n\n");
    }else{
        while( fscanf(file,"%s",now)  != EOF ){
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
                   /*Verifica se já existe a palavra buscada*/

                   flag = 0;

                   for(j=0;j<i;j++){
                     if( strcmp(mp->list[j]->word, now) == 0){
                        flag = 1;
                        break;
                     }
                   }

                   if(flag){
                        mp->list[j]->count += 1;
                        re_order(mp,&j);
                   }else{

                       lenght = (strlen(now) + 1);
                       mp->list[i]->word = (char *) malloc(lenght * sizeof(char));

                       if(mp->list[i]->word == NULL){
                          clean();
                          printf("Memoria Insuficiente.\n\nErro : #0005");
                          exit(1);
                       }else{
                           strcpy(mp->list[i]->word,now);
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

int main_menu(){
    int order;
    int get_key;

    do{
        clean();
        printf("                                |=================|\n");
        printf("                                |  Menu Principal |\n");
        printf("                                |=================|\n\n");
        printf("\n\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 | Abrir Arquivo |    %c\n",order == 0?'<':' '); //Irá verificar onde está o ponteiro, para a escolha da opção
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |    Exibir     |    %c\n",order == 1?'<':' ');
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |    Filtros    |    %c\n",order == 2?'<':' ');
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |     Sair      |    %c\n",order == 3?'<':' ');
        printf("                                 |_______________|\n");


        printf("\n\n");
        printf("                          Aperte Enter para selecionar.\n");

        get_key = getch();

        /*
            72 = ↑ (seta pra cima)

            80 = ↓ (seta para baixo)
        */

        if(get_key == 72){
            order--; //Se for apertado a ↑ (seta pra cima), a variável recebe '0'
        }
        else if(get_key == 80){
            order++ ; //Se for apertado a ↓ (seta para baixo), a variável recebe '0'
        }

        if(order < 0){
            order = 0;
        }else if(order > 3){
            order = 3;
        }
    }

    while( get_key != 13); //Ficará no menu principal até que a tecla 'ENTER' seja pressionada

    return order;
}

int main(void){

    mapa *mp = (mapa *) malloc(sizeof(mapa));
    int i, opt;
    if(mp == NULL){
        clean();
        printf("Falta de Memoria para inicializar.\n\nErro : #0001");
        exit(1);
    }else{
        while(opt != 3){
            opt = main_menu();

            if(opt == 0){
                scan_file(mp);
                    /*clean();
                    for(i=0;i< mp->total;i++){
                        printf("Palavra : %s | Contador : %i | Indice : %i | Tamanho : %i\n",mp->list[i]->word,mp->list[i]->count,i,strlen(mp->list[i]->word));
                    }*/
            }else if(opt == 1){

            }else if(opt == 2){

            }
        }

    }
    return 0;
}
