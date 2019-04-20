/*Interface.c*/

#include "interface.h"


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

void clean(void){
    /*Limpa tela*/
    system("cls");
}

void pause(void){
    /*Pausa no sistema*/
    system("pause");
}
