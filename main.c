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

void set_value(char p_word[] , int *p_acc, int *p_lenght,mapa *mp){
    /**/
    int acc = *p_acc;
    int lenght = *p_lenght;


    printf("\nNa funcao : %s\n",p_word);
    if(mp->list == NULL){
        printf("Memoria Insuficiente \n\n Erro: #0002");
        exit(1);
    }else{
        //printf("Foi ate aqui");

        mp->list[acc]->word = (char *) malloc( lenght *  sizeof(char) );

       // printf("\n%s\n",mp->list[*p_acc]->word);


        if(mp->list[acc]->word == NULL){
            printf("Memoria Insuficiente \n\n Erro: #0003");
            exit(1);

        }else{

            //printf("Foi ate aqui #2");

                strcpy(mp->list[acc]->word ,p_word);

            //strcpy(mp->list[acc]->word, p_word);
               // printf("\nPalavra : %c\n",mp->list[*p_acc]->word[i]);

            printf("\nPalavra Struct : %s | Indice : %i | Palavra : %s\n\n",mp->list[acc]->word, *p_acc, p_word);
            free(mp->list[acc]->word);
        }

    }
}


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

void scan_file(FILE *file, int *sum,int *p){
    /**/
    char now[buffer]; // Vai guardar a palavra atual.
    char pre[buffer]; // Vai guardar a palavra anterior.
    int i=0;

    while( fscanf(file,"%s",now) && !(read_all(now,pre)) ){ //
            (*sum)++;
    }

    p = malloc( (*sum) * sizeof(int));

    while( fscanf(file,"%s",now) && !(read_all(now,pre)) ){ //
            p[i] = strlen(now);
            i++;
    }
}

void insert_word(FILE *file,mapa *mp,int *sum,int *p){
    int i;

    mp->list = (item **) malloc( (*sum) * sizeof(item*));

    for( i=0;i<*sum;i++){
        mp->list[i] = (item*) malloc(sizeof(item));
        mp->list[i]->word = malloc(p[i] * sizeof(char));

        fscanf(file,"%s",mp->list[i]->word);
        mp->list[i]->count = p[i];
    }
}

void read_text(mapa *mp){

    int sum=0;
    int *p;
    FILE *file;

    file = fopen("teste.txt","r");

    //fflush(stdin);
    //setbuf(stdin,NULL);

    if(!file){
        clean();
        printf("Erro abrir o arquivo!!\n\n");
        printf("Erro : #0001\n\n");
    }else{
       scan_file(file,&sum,p);
       insert_word(file,mp,&sum,p);
    }
    fclose(file);
}

int main(void){

    mapa *mp = (mapa *) malloc(sizeof(mapa));
    int i;
    mp->list = (item **) malloc( 4 * sizeof(item*));

   /*for(i=0;i<4;i++){
        mp->list[i] = (item *) malloc(sizeof(item));
    }

    mp->list[0]->word= (char *) malloc(5*sizeof(char));
    mp->list[1]->word= (char *) malloc(5*sizeof(char));
    mp->list[2]->word= (char *) malloc(5*sizeof(char));
    mp->list[3]->word= (char *) malloc(5*sizeof(char));
*/
    read_text(mp);

    return 0;
}
