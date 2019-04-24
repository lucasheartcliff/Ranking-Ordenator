/*Map.c*/
#include "map.h"

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
                word[j] = word[j+1]; /*Vai reorganizar o vetor de caracteres.*/
            }
            i--;
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

    free(mp->list); // Se já houver algum conteúdo de uma busca anterior.

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

void show(mapa *mp){
    if(mp->total == 0){
        clean();
        printf("Nenhum registro encontrado.\n\n");
        pause();
    }else{
        if(mp->filter.which == 1){
            clean();
            header();
            for(int i=0;i<mp->total;i++){
                if(!(strcmp(mp->list[i]->word,mp->filter.term))){
                    printf("                                |%s\t            |    \t%i|\n",mp->list[i]->word, mp->list[i]->count);
                    printf("                                |-------------------|------------|\n");
                }
            }
            footer();
            pause();

        }else if(mp->filter.which == 2){
            clean();
            header();
            for(int i=0;i<mp->total;i++){
                if( (mp->list[i]->count <= mp->filter.count_bet[1]) && (mp->list[i]->count >= mp->filter.count_bet[0]) ){
                    printf("                                |%s\t            |    \t%i|\n",mp->list[i]->word, mp->list[i]->count);
                    printf("                                |-------------------|------------|\n");
                }
            }
            footer();
            pause();

        }else if(mp->filter.which == 3){
            clean();
            header();
            for(int i=0;i<mp->total;i++){
                if( strlen(mp->list[i]->word) == mp->filter.num_char){
                    printf("                                |%s\t            |    \t%i|\n",mp->list[i]->word, mp->list[i]->count);
                    printf("                                |-------------------|------------|\n");
                }
            }
            footer();
            pause();


        }else{
            clean();
            header();
            for(int i=0;i<mp->total;i++){
                printf("                                |%s\t            |    \t%i|\n",mp->list[i]->word, mp->list[i]->count);
                printf("                                |-------------------|------------|\n");
            }
            footer();
            pause();
        }
    }
}

int set_filters(mapa *mp){
    int opt = 0;

    while(opt != 3){
        opt = filter_menu();

        if(opt == 0){
           if(set_word(mp)){
                mp->filter.which = 1;
           }

           return 0;
        }else if(opt == 1){
           if(set_gap(mp)){
                mp->filter.which = 2;
           }

            return 0;
        }else if(opt == 2){
            if(set_size(mp)){
                mp->filter.which = 3;
            }

            return 0;
        }else if(opt == 3){
            mp->filter.which = 0;
            mp->filter.count_bet[0] = 0;
            mp->filter.count_bet[1] = 0;
            mp->filter.num_char = 0;
            free(mp->filter.term);

            return 0;
        }else{
            return 0;
        }
    }

    return 0;
}

int set_word(mapa *mp){
    char strn[buffer];

    free(mp->filter.term);

    printf("Digite a palavra que deseja buscar:\n");
    gets(strn);

    clean_word(strn);

    mp->filter.term = (char *) malloc( (strlen(strn) + 1) * sizeof(char) );
    if(!(mp->filter.term == NULL) ){
        strcpy(mp->filter.term, strn);

        return 1;
    }else{
        clean();
        printf("Memoria Insuficiente.\n\nErro : #0006");
        exit(1);

        return 0;
    }
}

int set_gap(mapa *mp){
    printf("Digite o intervalo de quantidade que deseja filtrar\n\n");

    printf("Quantidade Maxima: ");
    scanf("%i", &mp->filter.count_bet[1]);

    printf("\n");

    printf("Quantidade Minima: ");
    scanf("%i", &mp->filter.count_bet[0]);

    return 1;
}

int set_size(mapa *mp){
    printf("Digite a quantidade de letras que deseja filtrar:\n");
    scanf("%i", &mp->filter.num_char);

    return 1;
}

int main_menu(void){
    int order = 0;
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
            order--; //Se for apertado a ↑ (seta pra cima), a variável recebe '-1'
        }
        else if(get_key == 80){
            order++ ; //Se for apertado a ↓ (seta para baixo), a variável recebe '+1'
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

int filter_menu(void){
    int order = 0;
    int get_key;

    do{
        clean();
        printf("                                |==================|\n");
        printf("                                |  Menu de Filtros |\n");
        printf("                                |==================|\n\n");
        printf("                         Deseja filtrar as palavras por:\n\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |    Palavra    |    %c\n",order == 0?'<':' '); //Irá verificar onde está o ponteiro, para a escolha da opção
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |   Intervalo   |    %c\n",order == 1?'<':' ');
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |    Tamanho    |    %c\n",order == 2?'<':' ');
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |    Limpar     |    %c\n",order == 3?'<':' ');
        printf("                                 |_______________|\n");
        printf("                                  _______________\n");
        printf("                                 |               |\n");
        printf("                                 |    Voltar     |    %c\n",order == 4?'<':' ');
        printf("                                 |_______________|\n");

        printf("\n\n");
        printf("                          Aperte Enter para selecionar.\n");

        get_key = getch();

        /*
            72 = ↑ (seta pra cima)

            80 = ↓ (seta para baixo)
        */

        if(get_key == 72){
            order--; //Se for apertado a ↑ (seta pra cima), a variável recebe '-1'
        }else if(get_key == 80){
            order++ ; //Se for apertado a ↓ (seta para baixo), a variável recebe '+1'
        }

        if(order < 0){
            order = 0;
        }else if(order > 4){
            order = 4;
        }
    }

    while( get_key != 13); //Ficará no menu principal até que a tecla 'ENTER' seja pressionada

    return order;
}

void header(void){
    printf("                                 ________________________________\n");
    printf("                                |                   |            |\n");
    printf("                                |      Palavra      | Quantidade |\n");
    printf("                                |___________________|____________|\n");
}
void footer(void){
    printf("                                |___________________|____________|\n");
}

void clean(void){
    /*Limpa tela*/
    system("cls");
}

void pause(void){
    /*Pausa no sistema*/
    system("pause");
}
