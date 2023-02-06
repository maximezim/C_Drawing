#include <stdlib.h>
#include <stdio.h>
#include "surface.h"

void herbe(SURFACE *s,double x, double y,double color[3], void (*transfo)(double, double, double*, double*), double param[]){
    bezier(s,x-3,y,x-5,y-10,x+2,y-20,x,y-50,color,transfo,param);
    bezier(s,x+3,y,x-2,y-10,x+5,y-20,x,y-50,color,transfo,param);
    double r1[2],r2[2];
    if(transfo != NULL){
        (*transfo)(x-3,y,r1,param);
        (*transfo)(x+3,y,r2,param);
        segment(s,r1[0],r2[0],r1[1],r2[1],color);
    }
    else{
        segment(s,x-3,x+3,y,y,color);
    }
}

void rectangle(SURFACE *s, double x1, double y1, double w, double h, double color[3], void (*transfo)(double, double, double*, double*),double param[]){
    if(transfo != NULL){
        double a[2],b[2],c[2],d[2];
        (*transfo)(x1,y1,a,param);
        (*transfo)(x1+w,y1,b,param);
        (*transfo)(x1,y1+h,d,param);
        (*transfo)(x1+w,y1+h,c,param);
        segment(s,a[0],b[0],a[1],b[1],color);
        segment(s,b[0],c[0],b[1],c[1],color);
        segment(s,c[0],d[0],c[1],d[1],color);
        segment(s,a[0],d[0],a[1],d[1],color);
    }
    else{
        segment(s,x1,x1+w,y1,y1,color);
        segment(s,x1+w,x1+w,y1,y1+h,color);
        segment(s,x1+w,x1,y1+h,y1+h,color);
        segment(s,x1,x1,y1,y1+h,color);
    }
}

void rotation_feuile(double x, double y, double r[2], double param[]){
    rotation(x,y,param[0],param[1],param[2],r);
}

void arbre(SURFACE *s, double x, double y){
    double brun[] = {0.336,0.191,0};
    double vert[] = {0.4,0.7,0};
    //double vert_clair[] = {0.4,0.9,0};;
    double vert_fonce[] = {0.2,0.5,0};
    rectangle(s,x-30,y,60,-220,brun,NULL,NULL);
    fill_item(s,x,y-1,brun);
    bezier(s,x+30,y-150,x+40,y-180,x+110,y-190,x+120,y-205,brun,NULL,NULL);
    bezier(s,x+30,y-180,x+40,y-190,x+110,y-200,x+120,y-205,brun,NULL,NULL);
    fill_item(s, x+31,y-155,brun);
    double tr[3]; 
    oval_epicycloide(s,100,15,1,1,1.5,x,y-290,vert_fonce,NULL,NULL);
    fill_item(s,x,y-290,vert_fonce);
    tr[0] = x-68; tr[1] = y-245; tr[2] = -0.3;
    oval_epicycloide(s,43,5,1,1,1.5,x-68,y-245,vert,&rotation_feuile,tr);
    fill_item(s,x-68,y-245,vert);
    tr[0] = x+120; tr[1] = y-200; tr[2] = -0.1;
    oval_epicycloide(s,40,10,1,1,2,x+120,y-200,vert,&rotation_feuile,tr);
    fill_item(s,x+125,y-210,vert);
    
}

//fleur
void fleur(SURFACE *s, double x1, double y1, int nbpetales, double color[3], void (*transfo)(double, double, double*, double*), double param[]){
    //courbe de bezier pour la tige
    double vert[] = {0.4,0.7,0};
    double jaune[] = {1,1,0};
    double vert_fonce[] = {0.1,0.5,0};
    //double rouge[] = {1,0,0};
    double r[2];
    bezier(s,x1,y1,x1-10,y1-20,x1+10,y1-40,x1,y1-100,vert_fonce,transfo,param);
    //epycicloide pour la fleur
    epicycloide(s,20,nbpetales,1,x1,y1-100,color,transfo,param);
    if(transfo != NULL)(*transfo)(x1,y1-100,r,param);
    else{
        r[0] = x1;
        r[1] = y1-100;
    }
    fill_item(s,r[0],r[1],color);
    cercle(s, 5, x1, y1-100, jaune, transfo, param);
    fill_item(s,r[0],r[1],jaune);

    //feuilles
    bezier(s,x1-30,y1-60,x1-20,y1-20,x1-10,y1-50,x1,y1-40,vert,transfo,param);
    bezier(s,x1-30,y1-60,x1-20,y1-50,x1-10,y1-50,x1,y1-40,vert,transfo,param);
    if(transfo!=NULL)(*transfo)(x1-20,y1-41,r,param);
    else{
        r[0] = x1-20;
        r[1] = y1-41;
    }
    fill_item(s,r[0],r[1],vert);

    bezier(s,x1+30,y1-50,x1+20,y1-10,x1+10,y1-40,x1,y1-30,vert,transfo,param);
    bezier(s,x1+30,y1-50,x1+20,y1-40,x1+10,y1-50,x1,y1-30,vert,transfo,param);
    if(transfo!=NULL)(*transfo)(x1+20,y1-30,r,param);
    else{
        r[0] = x1+20;
        r[1] = y1-30;
    }
    fill_item(s,r[0],r[1],vert);

    //ligne verte au centre
    bezier(s,x1-20,y1-51,x1-10,y1-45,x1-5,y1-45,x1,y1-40,vert_fonce,transfo,param);
    bezier(s,x1+20,y1-40,x1+10,y1-32,x1+5,y1-40,x1,y1-30,vert_fonce,transfo,param);
}

void rectangle_tah_le_degrade(SURFACE *s, double x1, double y1,double w, double h, double color1[3], double color2[3],void (*transfo)(double, double, double*, double*), double param[]){
        double a[2],b[2],color[3],fac;
        int max = approx(y1+h);
        for(int i=approx(y1); i<max;i++){
            fac = (((double)i )- approx(y1))/(h);
            for(int j = 0;j<3;j++){
                color[j] = fac*color2[j] + (1-fac)*color1[j];
            }
            if(transfo != NULL){
                (*transfo)(x1,i,a,param);
                (*transfo)(x1+w,i,b,param);
                segment(s,a[0],b[0],a[1],b[1],color);
            }
            else{
                segment(s,x1,x1+w,i,i,color);
            }
            
        }
}
