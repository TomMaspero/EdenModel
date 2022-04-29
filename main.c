#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <GL/gl.h>
#include "glut.h"
#include <unistd.h>

float frand()
{
    float k=1.0*rand()/RAND_MAX;
    while(k==1.0)
        k=1.0*rand()/RAND_MAX;
    return k;
}

int Nrand(int k)
{
    int pos=rand() % k;
    return pos;
}

int vecinos[4]={0,0,0,0};
int **matriz; //"vecinos" es una copia de la matriz que guarda un numero de 0 a 4, siendo este la cantidad de vecinos que ha llenado cada puesto
                        //la idea es que al llegar a 4 se "mate" a esa celda y no se vuelva a elegir
int *posX, *posY;  //vectores para guardar las posiciones donde hay unos
int extD = 0; //dimension de la matriz


int fvecinos(int x, int y)
{
    for(int l=0; l<4; l++){vecinos[l]=0;}

    if(matriz[x+1][y]==1){vecinos[0]=1;}
    if(matriz[x-1][y]){vecinos[1]=1;}
    if(matriz[x][y+1]){vecinos[2]=1;}
    if(matriz[x][y-1]){vecinos[3]=1;}
    return vecinos;
}



int main(int argc, const char **argv)
{
    float p=0;
    int d=0, N=0, x=0, y=0, centro=0, n=1, pos=0, intentos=0, k=1;
    //"N" el numero de unos a generar, "n" el numero actual de unos, "k" el numero de posiciones a elegir

    srand(time(NULL));
    for(int i=0; i<100; i++){rand();}

    printf("Introduzca el numero maximo de unos a generar\n");
    scanf("%d",&N);

    printf("Introduzca la dimension de la matriz\n");
    scanf("%d",&d);
    extD = d;

    centro=(d-1)/2;

    matriz=(int**) calloc(d, sizeof(int*));
    for(int i=0; i<d; i++){matriz[i]=(int*) calloc(d, sizeof(int));}

    posX=(int*) calloc(d*d, sizeof(int)); //falta chequear la asignacion de memoria
    posY=(int*) calloc(d*d, sizeof(int));

    matriz[centro][centro]=1;
    posX[0]=centro;
    posY[0]=centro;

    glutStuff(argc, argv);

    while(n<N)
    {
        pos=Nrand(k);
        p=frand();
        x=posX[pos];
        y=posY[pos];

        fvecinos(x,y);

        if(vecinos[0]==1 && vecinos[1]==1 && vecinos[2]==1 && vecinos[3]==1){
            posX[pos]=posX[k-1];
            posY[pos]=posY[k-1];
            k--;
        }

        else{
            p=frand();
            callGlut();

            if(p<0.25){
                if(matriz[x+1][y]==0){
                    posX[k]=x+1;
                    posY[k]=y;
                    matriz[x+1][y]=1;
                    n++;
                    printf("%d (%d)\n",n,intentos);
                    intentos=0;
                    k++;
                }
                else{intentos++;}
            }
            else if(p>=0.25 && p<0.5){
                if(matriz[x][y+1]==0){
                    posX[k]=x;
                    posY[k]=y+1;
                    matriz[x][y+1]=1;
                    n++;
                    printf("%d (%d)\n",n,intentos);
                    intentos=0;
                    k++;
                }
                else{intentos++;}
            }
            else if(p>=0.5 && p<0.75){
                if(matriz[x-1][y]==0){
                    posX[k]=x-1;
                    posY[k]=y;
                    matriz[x-1][y] = 1;
                    n++;
                    printf("%d (%d)\n",n,intentos);
                    intentos=0;
                    k++;
                }
                else{intentos++;}
            }
            else{
                if(matriz[x][y-1]==0){
                    posX[k]=x;
                    posY[k]=y-1;
                    matriz[x][y-1]=1;
                    n++;
                    printf("%d (%d)\n",n,intentos);
                    intentos=0;
                    k++;
                }
                else{intentos++;}
            }
        }

    } //fin del while

    for(int i=0; i<d; i++){free(matriz[i]);}
    free(matriz);

    free(posX);
    free(posY);

    sleep(5); //para ver el grafico

    return 0;
}






