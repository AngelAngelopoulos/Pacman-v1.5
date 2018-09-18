
/*
 * Fecha: 28/Agosto/2018
 *
 * Autor: Luis Angel Alvarado Hernandez
 *
 * Versión: 1.2
 *
 * Descripcion de la aplicación: Pacman que se mueve mediante flechas del teclado y
 * fantasma que funciona autonomamente
 *
 * Fecha de Revision:
 *
 * Encargado de revisión: Francisco Eduardo Matrinez Perez
 *
 * Materia: Lenguajes de Programación
 */

#include <graphics.h>  //Libreria basica de los graficos MS_DOS
#include <stdio.h>
#include <conio.h>
#include "LIB01.h"  //Libreria que contiene la funcion de los bordes con sombra
//#include "Interface.h"
#include <time.h>
#include "interfaz.h"

/*typedef struct{
    int iCx; //Variable para capturar la posición inicial en coordenada en X
    int iCy; //Variable para capturar la posición inicial en coordenada en Y
    int iCFx; //Variable para capturar la posición final en coordenada en X
    int iCFy; //Variable para capturar la posición final en coordenada en Y
    int iColorF; //Variable para capturar el color de fondo de los objetos
    int iColorL; //Variable para capturar el color del contorno de los objetos
    int iCualBoton;
}BOTONES;
*/

void SpaceFree(int x1, int y1, int x2, int y2);  //genera el espacio de trabajo del juego
void PacmanOp(int x, int y, int color);  //Genera a pacman con la boca cerrada
void PacmanCl(int x, int y, int color);  //Genera a pacman con la boca abierta
void PacmanLef(int x ,int y, int color);  //gira a pacman a la izquierda
void PacmanDwn(int x ,int y, int color);  //gira a pacman a la derecha
void PacmanUp(int x, int y, int color);  //gira a pacman hacia arriba
void MovePacman();  //Programa generl para mover a pacman


void fantasma(int *iCorxF, int *iCoryF, int color);  //funcion que genera un fantasma
void aleatorio(int option, int *iCorxF, int *iCoryF);  //funcion que mueve aleatoriamente un fantasma
void toRight(int *iCorxF);  //Fantasma hacia la derecha
void toLeft(int *iCorxF);  //Fantasma hacia la izquierda
void toUp(int *iCoryF);  //Fanstasma hacia arriba
void toDown(int *iCoryF);  //Fantasma hacia abajo
void refreshPac(int iCorxU, int iCoryU);
void tiempoF(int *iCorxF, int *iCoryF);



int main()
{
    int res = 0;
    //int radx = 30;  //radio de pacman

    initwindow(800, 600, "PACMAN:V");  //pantalla incial de tamaño 800x600
    //SpaceFree(0, 0, 800, 600);  //espacio de trabajo 800x600
    res = menu();
    //if (res == 1)
    if(res == 1)
        MovePacman();
    //MovePacman();  //funcion para mover a pacman
    //tiempoF();

    getch();

}

//Funcion para generar un espacio con bordes
void SpaceFree(int x1, int y1, int x2, int y2)
{
    rectangle(x1+5, y1+5, x2-5, y2-5);  //rectangulo intermedio
    interior(x1, y1, x2, y2, 15);
    exterior(x1 +20, y1 +20, x2 -20, y2 -20, 0);
}


//Funcion para generar a pacman abierto
void PacmanOp(int x, int y, int color)
{
    int radx = 15;  //radio de pacman
//Cuerpo de pacman

   setfillstyle(1,color);
   setcolor(color);
   fillellipse(x, y, radx, radx);

//Boca de pacman
  /* setcolor(7);
   arc(x, y, 0, 45, radx);
   setcolor(YELLOW);
   line(x, y, x+radx, y);
   line(x, y, x+(.70*radx), y-(.70*radx));*/


//Boca de pacman alternativa

    setcolor(color);
    setfillstyle(1,0);
    pieslice(x,y, -10, 50, radx);
    setcolor(7);
    arc(x, y, 0, 45, radx);

//Ojo de pacman
   setcolor(0);
   setfillstyle(1,0);
   fillellipse(x, y-(radx/2), radx/10, radx/10);
}

void PacmanCl(int x, int y, int color)  //pacman cerrado
{
    int radx = 15;
    //Cuerpo de pacman

   setfillstyle(1,color);
   setcolor(color);
   fillellipse(x, y, radx, radx);

   //Ojo de pacman
   setcolor(0);
   setfillstyle(1,0);
   fillellipse(x, y-(radx/2), radx/10, radx/10);
}

void fantasma(int *iCorxF, int *iCoryF, int color)  //Funcion que imprime el fantasma en la pantalla
{
    int radx = 10;

    setcolor(color);
    setfillstyle(1, color);
    arc(*iCorxF, *iCoryF, 0, 180, radx);
    line(*iCorxF+radx, *iCoryF, *iCorxF+radx, *iCoryF+radx*2);  //Cuerpo del fantasma
    line(*iCorxF-radx, *iCoryF, *iCorxF-radx, *iCoryF+radx*2);
    line(*iCorxF+radx, *iCoryF+radx*2, *iCorxF+(radx/2), *iCoryF+(radx));
    line(*iCorxF+(radx/2), *iCoryF+(radx), *iCorxF,  *iCoryF+radx*2);
    line(*iCorxF, *iCoryF+radx*2, *iCorxF-(radx/2), *iCoryF+radx);
    line(*iCorxF-(radx/2), *iCoryF+radx, *iCorxF-radx, *iCoryF+radx*2);
    floodfill(*iCorxF, *iCoryF, color);
    setcolor(BLACK);
    setfillstyle(1, BLACK);
    fillellipse(*iCorxF+radx/2, *iCoryF, radx/6, radx/4);  //ojos del fantasma
    fillellipse(*iCorxF-radx/2, *iCoryF, radx/6, radx/4);

}

void MovePacman()
{
    //iCorxU = variable para mover el objeto del usuario
    //iCorxF = Variable del fantasma que se mueve autonomamente
    int iOp, iCorxU=350, iCoryU=50, iCorxF = 400, iCoryF=300;
    //interfaz();
    PacmanOp(iCorxU, 250,YELLOW);
    //fantasma(iCorxF, 250, YELLOW); //fantasma

    do {
        if (kbhit())
            { //espera que alguna tecla sa presionada
                iOp=getch();  //gurada en una variable wl avlr ascii
                switch(iOp)
                {
                    case 77: //Valor de la flecha derecha
                        refreshPac(iCorxU, iCoryU);  //refresca la imagen de pacman

                        if(iCorxU<=750)  //Si el pacman se encuentra dentro de los limites
                        {
                            iCorxU+=10;
                            PacmanOp(iCorxU, iCoryU, YELLOW);  //Camina hacia adelante
                        }

                        else
                        {
                            iCorxU=50;
                            PacmanOp(iCorxU, iCoryU, YELLOW);  //Regresa al inicio
                        }
                    break;

                    case 75:  //Valor de la flecha izquierda
                        refreshPac(iCorxU, iCoryU);

                        if(iCorxU>=50)
                        {
                            iCorxU-=10;
                            PacmanLef(iCorxU, iCoryU, YELLOW);
                        }

                        else
                        {
                            iCorxU=750;
                            PacmanLef(iCorxU, iCoryU, YELLOW);
                        }
                    break;

                    case 72:  //Valor de la flecha arriba
                        refreshPac(iCorxU, iCoryU);

                        if(iCoryU>=50)
                        {
                            iCoryU-=10;
                            PacmanUp(iCorxU, iCoryU, YELLOW);
                        }

                        else
                        {
                            iCoryU=550;
                            PacmanUp(iCorxU, iCoryU, YELLOW);
                        }
                    break;

                    case 80: //Valor de la flecha abajo
                        refreshPac(iCorxU, iCoryU);

                        if(iCoryU<=550)
                        {
                            iCoryU+=10;
                            PacmanDwn(iCorxU, iCoryU, YELLOW);
                        }
                        else
                        {
                            iCoryU=50;
                            PacmanDwn(iCorxU, iCoryU, YELLOW);
                        }
                    break;
                }
        }
        //int azar = rand() % 4;  //Cuatro estados posibles al azar
        tiempoF(&iCorxF, &iCoryF);
        //aleatorio(azar, &iCorxF, &iCoryF); //Se genera el movimiento aleatorio del fantasma
    }while(iOp!=27);  //Mientras no se presione ESC
}

void PacmanLef(int x, int y, int color){
    int radx = 15;  //radio de pacman
//Cuerpo de pacman

   setfillstyle(1,color);
   setcolor(color);
   fillellipse(x, y, radx, radx);


//Boca de pacman alternativa

    setcolor(color);
    setfillstyle(1,0);
    pieslice(x,y, 130, 190, radx);
    setcolor(7);
    arc(x, y, 130, 190, radx);

//Ojo de pacman
   setcolor(0);
   setfillstyle(1,0);
   fillellipse(x, y-(radx/2), radx/10, radx/10);
}

void PacmanDwn(int  x, int y, int color)
{
    int radx = 15;  //radio de pacman

//Cuerpo de pacman

   setfillstyle(1,color);
   setcolor(color);
   fillellipse(x, y, radx, radx);


//Boca de pacman alternativa

    setcolor(color);
    setfillstyle(1,0);
    pieslice(x,y, 260, 320, radx);
    setcolor(7);
    arc(x, y, 260, 320, radx);

//Ojo de pacman
   setcolor(0);
   setfillstyle(1,0);
   fillellipse(x, y-(radx/2), radx/10, radx/10);
}

void PacmanUp(int x, int y, int color)
{
     int radx = 15;  //radio de pacman

//Cuerpo de pacman

   setfillstyle(1,color);
   setcolor(color);
   fillellipse(x, y, radx, radx);


//Boca de pacman alternativa

    setcolor(color);
    setfillstyle(1,0);
    pieslice(x,y, 80, 140, radx);
    setcolor(7);
    arc(x, y, 80, 140, radx);

//Ojo de pacman
   setcolor(0);
   setfillstyle(1,0);
   fillellipse(x, y-(radx/2), radx/10, radx/10);
}

void aleatorio(int option, int *iCorxF, int *iCoryF)
{

    switch(option)
    {
        case 0:  //Opcion 0, hacia la derecha
            fantasma(iCorxF, iCoryF, 0);
            toRight(iCorxF);  //Funcion que mueve al fantasma a la derecha
            fantasma(iCorxF, iCoryF, YELLOW);
            //fantasma(iCorxF, iCoryF, BLACK);
        break;

        case 1:  //opcion 1, hacia abajo
            fantasma(iCorxF, iCoryF, 0);
            toDown(iCoryF);  //Funcion que mueve al fantasma hacia abajo
            fantasma(iCorxF, iCoryF, YELLOW);
            //fantasma(iCorxF, iCoryF, BLACK);
        break;

        case 2:  //opcion 2, hacia arriba
            fantasma(iCorxF, iCoryF, 0);
            toUp(iCoryF);  //Funcion que mueve al fantasma hacia arriba
            fantasma(iCorxF, iCoryF, YELLOW);
            //fantasma(iCorxF, iCoryF, BLACK);
        break;

        case 3:  //opcion 3, hacia la izquierda
            fantasma(iCorxF, iCoryF, 0);
            toLeft(iCorxF);  //Funcion que mueve al fantasma a la izquierda
            fantasma(iCorxF, iCoryF, YELLOW);
            //fantasma(iCorxF, iCoryF, BLACK);
        break;
    }
}

void toRight(int *iCorxF)  //Funcion que mueve al fantasma a la derecha
{
    if(*iCorxF <= 750)
        *iCorxF += 20;
    else
        *iCorxF =50;
}

void toLeft(int *iCorxF)  //Funcion que mueve al fantasma a la izquierda
{
    if(*iCorxF >= 50)
        *iCorxF -= 20;
    else
        *iCorxF =750;
}

void toUp(int *iCoryF)  //Funcion que mueve al fantasma hacia arriba
{
    if(*iCoryF >= 50)
        *iCoryF -= 20;
    else
        *iCoryF =550;
}

void toDown(int *iCoryF)  //Funcion que mueve al fantasma hacia abajo
{
    if(*iCoryF <= 550)
        *iCoryF += 20;
    else
        *iCoryF =50;
}

void refreshPac(int iCorxU, int iCoryU)  //Refresca la imagen de Pacman
{
    PacmanOp(iCorxU, iCoryU, YELLOW);//aparece abierto
    PacmanCl(iCorxU, iCoryU, YELLOW);  //aparece cerrado
    PacmanOp(iCorxU, iCoryU, BLACK);    //desaparece abierto
    PacmanCl(iCorxU, iCoryU, YELLOW);  //aparece cerrado
    PacmanCl(iCorxU, iCoryU, BLACK);  //desaparece cerrado
}

void tiempoF(int *iCorxF, int *iCoryF)
{
    //initwindow(800, 600,"aaa");
//    int iCorxF = 400, iCoryF = 300;
    int iAle;
    char cTecla;
    clock_t ini, fin, aux1, aux2;
    aux1 = clock();
    srand(time(NULL));
    ini = clock();
    printf("Entro");

    do
    {
        fin = clock();
        iAle = rand() % 4;

        if(kbhit())
        {
            fflush(stdin);
            cTecla = getch();
        }

        if(((fin-ini)/CLOCKS_PER_SEC) == 2)
        {
            //MovePacman();
            aleatorio(iAle, iCorxF, iCoryF);
            printf(" %d ",iAle );
            ini = fin;
        }
    } while(cTecla!=27 );
}
