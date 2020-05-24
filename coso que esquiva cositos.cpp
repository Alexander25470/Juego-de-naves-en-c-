#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include <stdlib.h>

#define arriba 72
#define izquierda 75
#define derecha 77
#define abajo 80

void gotoxy(int x, int y){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X=x;
    dwPos.Y=y;
    SetConsoleCursorPosition(hCon, dwPos);
    printf;
}
void eliminarCosito(){
    HANDLE hCon;
    hCon = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cci;
    cci.dwSize=100; //tamaño del cursor
    cci.bVisible=FALSE; //hace lo que dice su nombre
    SetConsoleCursorInfo(hCon, &cci); //hay que usar un & antes del parametro del cursor
}
class NAVE{
int x,y;
int health;
int lifes;
public:
    NAVE(int _x, int _y, int _health, int _lifes);
    int x_navePublica(){return x;}
    int y_navePublica(){return y;}
    void dibujar();//dibuja la nave
    void borrar();//borra la nave
    void mover();//mueve la nave
    void dibujar_vida();
    void perder_vida();
    void perder_health();
};
NAVE::NAVE(int _x, int _y, int _health, int _lifes){
x=_x;
y=_y;
health=_health;
lifes=_lifes;
};
 void NAVE::perder_health(){
     health--;
    }


class COSOSQUECAEN{
    int x,y;
public:
    COSOSQUECAEN(int _x, int _y):x(_x),y(_y){}
        void pintar();
        void mover();
        void chocar(class NAVE &cosita);

};
void COSOSQUECAEN::chocar(class NAVE &cosita){
    if(x>=cosita.x_navePublica()&& x<=cosita.x_navePublica()+2 && y>=cosita.y_navePublica() && y<=cosita.y_navePublica()+1){
        //f
        Sleep(100);
        cosita.perder_health();
        cosita.borrar();
        cosita.dibujar();
        cosita.dibujar_vida();
        x=rand()%76+2;
        y=2;
        Sleep(100);
    }
}

void COSOSQUECAEN::pintar(){
    gotoxy(x,y);printf("*");
}

void COSOSQUECAEN::mover(){
    gotoxy(x,y);printf(" ");
    y++;
    if(y>32){
        x=rand()%76+2;
        y=2;
    }
    pintar();
}


void NAVE::dibujar(){
    gotoxy(x,y);printf(" %c", 94);
    gotoxy(x,y+1);printf("%c%c%c", 201,202,187);
};
void NAVE::borrar(){
    gotoxy(x,y);printf("   ");
    gotoxy(x,y+1);printf("   ");
};
void NAVE::mover(){
    if(kbhit()!=0){

            char tecla=getch();
            borrar();
            if((tecla=='a' || tecla==izquierda || tecla=='A')&&x>2){x--;}
            if((tecla=='d' || tecla==derecha || tecla=='D')&&x<75){x++;}
            if((tecla=='w' || tecla==arriba || tecla=='W')&&y>2){y--;}
            if((tecla=='s' || tecla==abajo || tecla=='S') &&y<31){y++;}
            if(tecla=='e' || tecla=='E')health--;
            dibujar();
            dibujar_vida();


        };
};
void pintar_bordes(){
    for(int i=2;i<78;i++){
        gotoxy(i,1); printf("%c",205);
        gotoxy(i,33); printf("%c",205);

    };
    for(int i=2;i<33;i++){
        gotoxy(1,i); printf("%c",186);
        gotoxy(78,i); printf("%c",186);
    };
    gotoxy(1,1); printf("%c",201);
    gotoxy(1,33); printf("%c",200);
    gotoxy(78,1); printf("%c",187);
    gotoxy(78,33); printf("%c",188);
};
void NAVE::perder_vida(){
    if(health==0){
       borrar();


        gotoxy(x-1,y);printf(" **");
        gotoxy(x-1,y+1);printf("****");
        Sleep(300);
Sleep(100);
        borrar();
        gotoxy(x-3,y);printf("   * * ");
        gotoxy(x-3,y+1);printf(" * * * * ");
Sleep(100);
        Sleep(300);
        gotoxy(x-3,y);printf("      ");
        gotoxy(x-3,y+1);printf("         ");
Sleep(100);
        gotoxy(x-3,y);printf("Te moriste");
        Sleep(300);
        gotoxy(x-3,y);printf("          ");
Sleep(100);
        lifes--;
        health=3;
        dibujar_vida();
        dibujar();
    }
}

void NAVE::dibujar_vida(){
    gotoxy(50,0);printf("Vidas: %d", lifes);
    gotoxy(65,0);printf("Health: ");
    gotoxy(73,0);printf("   ");
    for(int i=0;i<health;i++){
        gotoxy(72+i,0);printf("%c",229);
    }
}

int main(){
   // system("color 90");
    system("mode con: cols=80 lines=35");

    eliminarCosito();
    pintar_bordes();
    NAVE cosa1(38,27,3,3);
    cosa1.dibujar();
    cosa1.dibujar_vida();

    COSOSQUECAEN cosito1(10,4),cosito2(4,8),cosito3(15,10),cosito4(20,20),cosito5(10,10);

    bool game_over=false;
    while(!game_over){

            cosito1.mover();cosito1.chocar(cosa1);
            cosito2.mover();cosito2.chocar(cosa1);
            cosito3.mover();cosito3.chocar(cosa1);
            cosito4.mover();cosito4.chocar(cosa1);
        cosa1.perder_vida();
        cosa1.mover();

        Sleep(16);
    }

    return 0;
}
