#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <stdbool.h>
#include <conio.h>
#include <mmsystem.h>

#define  menu_items_number 4

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

unsigned short selected = 0;
char * menu[menu_items_number] = {"Nouveau jeu","Meuilleurs Scores","A propos","Quitter"};

/** common functions **/

void cls(){

    system("cls");

}

bool isEmpty(char *chaine){

    if(chaine[0]=='\0'){
        return true;
    }else{
        return false;
    }

}

void cursor_hide(void)
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;

    hOut=GetStdHandle(STD_OUTPUT_HANDLE);

    ConCurInf.dwSize=10;
    ConCurInf.bVisible=FALSE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}

void cursor_show(void)
{
    HANDLE hOut;
    CONSOLE_CURSOR_INFO ConCurInf;
    hOut=GetStdHandle(STD_OUTPUT_HANDLE);

    ConCurInf.dwSize=10;
    ConCurInf.bVisible=TRUE;

    SetConsoleCursorInfo(hOut, &ConCurInf);
}

char * trim(char *ch){
    unsigned short C = strlen(ch);
    if(C<1) return 0;
    while(isspace(ch[--C])) ch[C] = '\0'; C=0;
    while(isspace(ch[0])&&(strlen(ch)>0)) {memmove(ch,ch+1,strlen(ch)-1); ch[strlen(ch)-1] = '\0';}
    return ch;

}

char * tolowerall(char *ch){
    int i;
    for(i=0;i<strlen(ch);i++){
        ch[i] = tolower(ch[i]);
    }
    return  ch;
}

void gotoxy( short x, short y )
{
    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE) ;
    COORD position = { x, y } ;

    SetConsoleCursorPosition( hStdout, position ) ;
}

void q(){

    exit(0);

}


/*** main functions ***/

void apropos(){
    SetConsoleOutputCP(65001);
    printf("                                    ,$$.       ,$$.      \n                                   ,$'`$.     ,$'`$.     \n                                   $'  `$     $'  `$     \n                                  :$    $;   :$    $;    \n  Ce program est developer par:   $$    $$   $$    $$    \n     Sghaier Seifeddine           $$  _.$bqgpd$._  $$    \n            et                    ;$gd$$^$$$$$^$$bg$:    \n        Najjar Chedy           .d$P^*'   \\\"*\\\"   `*^T$b.  \n                               d$$$    ,*\\\"   \\\"*.    $$$b \n                              d$$$b._    o   o    _.d$$$b\n                             *T$$$$$P             T$$$$$P*\n                               `^T$$    :\\\"---\\\";    $$P^' \n                                  `$._   `---'   _.$'    \n                                 .d$$P\\\"**-----**\\\"T$$b.   \n                                d$$P'             `T$$b  \n                               d$$P                 T$$b \n                              d$P'.'               `.`T$b\n                              `--:                   ;--'\n                                 |                   |   \n                                 :                   ;   \n                                  \\\\                 /    \n                                  .`-.           .-'.    \n                                 /   .\\\"*--+g+--*\\\".   \\\\   \n                                :   /     $$$     \\\\   ;  \n                                `--'      $$$      `--'  \n                                          $$$ \n                                          $$$        \n                                          :$$;       		\n                                          :$$;       	\n                                           :$$           \n                                           'T$bg+.____   \n                                             'T$$$$$  :  \n                                                 \\\"**--'  ");
    gotoxy(0,0);getch(); cls();
    screen_principale();

}

void process_selected(){

        cls();
        switch(selected){
            case 2: apropos();break;
            case 3: printf("Ciao!");q();break;
        }

}

void menu_principale(){



 /*   strcpy(menu[0],"Nouveau jeu");
    strcpy(menu[1],"Meuilleurs Scores");
    strcpy(menu[2],"A propos");
    strcpy(menu[3],"Quitter");*/



    unsigned short compteur;
    for(compteur = 0;compteur<menu_items_number;compteur++){
        if(compteur == selected){
            gotoxy(38 - ( ( 1 + strlen(menu[compteur]) )/2),15+compteur);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
            printf("> %s",menu[compteur]);
            SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
        }else{
            gotoxy(40 - ( ( 1 + strlen(menu[compteur]) )/2),15+compteur);
            printf("%s",menu[compteur]);
        }
    }
    //gotoxy(0,0);
    cursor_hide();
    char function_key,pressed_key;
    while(pressed_key=getch()){
                //function_key = getch();

                if(pressed_key == 80){
                    if(selected<3){
                        ++selected;
                        printf("\a");
                        break;

                    }
                }else if(pressed_key==72){
                    if(selected>0){
                        --selected;
                        printf("\a");
                        break;
                    }
                }
                else if(pressed_key == 13){
                        process_selected();
                        break;
                }

    }

    cls();
    screen_principale();
    gotoxy(0,0);printf("\n%d\n",pressed_key);

}

void screen_principale(){
    gotoxy(75,32);
    printf("v 0.1");
    gotoxy(0,7);
    printf("                     _____     _                            \n                    /__   \\___| |_ _ __ __ _/\\   /\\_____  __\n                      / /\\/ _ \\ __| '__/ _` \\ \\ / / _ \\ \\/ /\n                     / / |  __/ |_| | | (_| |\\ V /  __/>  < \n                     \\/   \\___|\\__|_|  \\__,_| \\_/ \\___/_/\\_\\\n                                                            ");
    menu_principale();


}

void init_game(){

    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
    SetConsoleTextAttribute(wHnd, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    SetConsoleTitle("TetraVex");
    SMALL_RECT windowSize = {0, 0, 79, 32};
    SetConsoleWindowInfo(wHnd, 1, &windowSize);
    COORD bufferSize = {10, 10};
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    screen_principale();

}

int main()
{
    init_game();
    return 0;
}
