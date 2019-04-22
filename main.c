/*Core Files*/
#include <stdio.h>
#include <stdlib.h>

/*String Files*/
#include <conio.h>
#include <string.h>

/*Map File*/
#include "map.h"

int main(void){
    mapa *mp = (mapa *) malloc(sizeof(mapa));
    int opt;

    if(mp == NULL){
        clean();
        printf("Falta de Memoria para inicializar.\n\nErro : #0001");
        exit(1);
    }else{
        while(opt != 3){
            opt = main_menu();

            if(opt == 0){
                scan_file(mp);
                    /*Para facilitar o rastreio na hora da correção.*/

                    /*clean();
                    for(int i=0;i< mp->total;i++){
                        printf("Palavra : %s | Contador : %i | Indice : %i | Tamanho : %i\n",mp->list[i]->word,mp->list[i]->count,i,strlen(mp->list[i]->word));
                    }
                    pause();*/
            }else if(opt == 1){

            }else if(opt == 2){
                set_filters(mp);
            }
        }
    }
    free(mp);
    return 0;
}
