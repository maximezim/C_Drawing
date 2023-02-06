#include <stdlib.h>
#include <stdio.h>
#include "surface.h"
#include "items.h"
#include "time.h"

#define SURF_W 600
#define SURF_H 450

//double s,m,p;
//int sym;

void move_herbe(double x, double y, double r[2], double param[]){
    scale(x,y,param[0],r);
    translation(r[0],r[1],param[1],(SURF_H-1)*(1-param[0]),r);
    if(param[3]>0) axe_symetrie(r[0],r[1],1,y,r);
    rotation(r[0],r[1],param[1],SURF_H-1,param[2],r);
}

void move_herbebg(double x, double y, double r[2], double param[]){
    scale(x,y,param[0],r);
    translation(r[0],r[1],param[1],(SURF_H-6)*(1-param[0]),r);
    if(param[3]>0) axe_symetrie(r[0],r[1],1,y,r);
    rotation(r[0],r[1],param[1],SURF_H-4,param[2],r);
}

void transfo_fleur(double x, double y, double r[2], double param[]){
    scale(x,y,param[0],r);
    
    translation(r[0],r[1],param[1],(SURF_H)*(1-param[0]),r);
    rotation(r[0],r[1],param[1],SURF_H-10,param[2],r);
}

int main(){
    srand((unsigned int) time(NULL));
    SURFACE surf;
    double white[] = {1,1,1};
    double yellow[] = {1,0.5,0.2};
    //double blue[] = {0,0,1};
    //double red[] = {1,0,0};
    //double green[] = {0,1,0};
    //double black[] = {0,0,0};
    double color[] = {0,0,0};
    double orange_sunset[] = {0.7,0.3,0.1};
    double cyan_sky[] = {0.4,0.4,1};
    double gris[3] = {0.85,0.8,1};
    double gris_orange[3] = {1,0.7,0.5};
    double gris_orange_2[3] = {9.5,0.7,0.6};
    double tr[4] = {0};
    if(init_surf(&surf,SURF_W, SURF_H, 255)){
        fill(&surf,white);

        rectangle_tah_le_degrade(&surf,0,0,SURF_W,SURF_H,cyan_sky,orange_sunset,NULL,NULL);
        cercle(&surf, 100,300,SURF_H-50,yellow,NULL,NULL);
        fill_item(&surf,300,SURF_H-110,yellow); 

        oval_epicycloide(&surf,50,8,1,1,2.5,125,130,gris,NULL,NULL);
        fill_item(&surf,125,130,gris);

        oval(&surf,15,1,10,180,370,gris_orange,NULL,NULL);
        fill_item(&surf,180,370,gris_orange);

        oval_epicycloide(&surf,30,4,1,1,5,410,320,gris_orange_2,NULL,NULL);
        fill_item(&surf,410,320,gris_orange_2);

        for(int m=3;m<SURF_W;m+=4){
            color[1] = ((double)(rand()%35))/100 + 0.3;
            tr[0] = (((double) (rand()%50))/100 + 0.7);
            tr[1] = (double) m;
            tr[2] /*p*/ = (0.5 - ((double) (rand()%100))/100)*0.5;
            tr[3]/*sym*/ = (double) (rand()%2);
            herbe(&surf,0,SURF_H-4,color,&move_herbebg, tr);
            fill_item(&surf,m,SURF_H-5,color);
        } 

        arbre(&surf,SURF_W-150,SURF_H-1);

        double param[3], colorf[3];
        for(int i=0;i<10; i++){
            param[0] = (((double) (rand()%30))/100 + 0.6);
            param[1] = 40 + i*57 + (rand()%10) - 5;
            param[2] =  (0.5 - ((double) (rand()%100))/100)*0.2;
            colorf[0] = (double)(rand()%90) /100 + 0.05;
            colorf[1] = (double)(rand()%90) /100 + 0.05;
            colorf[2] = (double)(rand()%90) /100 + 0.05;
            fleur(&surf,1,SURF_H-10,rand()%8+3,colorf,&transfo_fleur,param);
        }
        
        for(int m=0;m<SURF_W;m+=4){
            color[1] = ((double)(rand()%35))/100 + 0.6;
            tr[0] /*s*/ = (((double) (rand()%40))/100 + 0.5);
            tr[1] /*m*/ = (double) m;
            tr[2] /*p*/ = (0.5 - ((double) (rand()%100))/100)*0.5;
            tr[3] /*sym*/ = (double)(rand()%2);
            herbe(&surf,0,SURF_H-1,color,&move_herbe, tr);
            fill_item(&surf,m,SURF_H-2,color);
        }

        FILE *o = fopen("test.ppm","w");
        ppm_write(&surf,o);
        fclose(o);
        #ifndef _WIN32
            system("eog test.ppm");
        #endif
    }
}
