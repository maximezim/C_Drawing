#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "surface.h"

double linear_interpolation_x(double x1, double x2, double t){
    return x1 + (x2-x1)*t;
}

double linear_interpolation_y(double x1, double y1, double x2, double y2, double t){
    if((x2-x1)==0) return y1;
    return y1 + ((x2-x1)*t)*((y2-y1)/(x2-x1));
}

void bezier(SURFACE *s,double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, double col[3], void (*func)(double, double, double*, double *), double param[]){
    double A1x,A1y,A2x,A2y,A3x,A3y,B1x,B1y,B2x,B2y,C1x,C1y,tempx,tempy;
    double holder[2];
    for(double t=0; t < 1; t += 0.01){
        A1x = linear_interpolation_x(Ax,Bx,t);
        A1y = linear_interpolation_y(Ax,Ay,Bx,By,t);
        B1x = linear_interpolation_x(Bx,Cx,t);
        B1y = linear_interpolation_y(Bx,By,Cx,Cy,t);
        C1x = linear_interpolation_x(Cx,Dx,t);
        C1y = linear_interpolation_y(Cx,Cy,Dx,Dy,t);
        A2x = linear_interpolation_x(A1x,B1x,t);
        A2y = linear_interpolation_y(A1x,A1y,B1x,B1y,t);
        B2x = linear_interpolation_x(B1x,C1x,t);
        B2y = linear_interpolation_y(B1x,B1y,C1x,C1y,t);
        A3x = linear_interpolation_x(A2x,B2x,t);
        A3y = linear_interpolation_y(A2x,A2y,B2x,B2y,t);
        if(func != NULL)(*func)(A3x,A3y,holder,param);
        else{
            holder[0] = A3x;
            holder[1] = A3y;
        }
        if(t != 0) segment(s,tempx,holder[0],tempy,holder[1],col);
        tempx = holder[0];
        tempy = holder[1];
    }
    if(tempx != Dx && tempy != Dy){
        if(func != NULL)(*func)(Dx,Dy,holder,param);
        else{
            holder[0] = Dx;
            holder[1] = Dy;
        }
        segment(s,tempx,holder[0],tempy,holder[1],col);
    }
}

void epicycloide(SURFACE *s,double rm, double n_petal, double  n_tour, double cx, double cy,double color[3], void (*func)(double,double,double *, double *), double param[]){
    double ra = (rm*n_petal)/(n_petal+2*n_tour);
    double rb = (ra*n_tour)/n_petal;
    double rc = (ra+rb)/rb;
    double x,y,old_x,old_y,holder[2];
    for(double t=0;t<=n_tour*6.283;t += 0.01){
        x = cx + (ra+rb)*cos(t)+rb*cos(rc*t);
        y = cy + (ra+rb)*sin(t)+rb*sin(rc*t);
        if(func != NULL)(*func)(x,y,holder,param);
        else{
            holder[0] = x;
            holder[1] = y;
        }
        if(t != 0) segment(s,old_x,holder[0],old_y,holder[1],color);
        old_x = holder[0];
        old_y = holder[1];
    }
}

void cercle(SURFACE *s, double r, double cx, double cy, double color[3], void (*func)(double, double, double*, double*), double param[]){
    double x,y,old_x,old_y, holder[2];
    for(double t=0;t<=6.283;t += 0.01){
        x = cx + r*cos(t);
        y =  cy + r*sin(t);
        if(func != NULL)(*func)(x,y,holder,param);
        else{
            holder[0] = x;
            holder[1] = y;
        }
        if(t != 0) segment(s,old_x,holder[0],old_y,holder[1],color);
        old_x = holder[0];
        old_y = holder[1];
    }
}

void oval_epicycloide(SURFACE *s,double rm, double n_petal, double  n_tour, double h, double w,double cx, double cy,double color[3], void (*func)(double,double,double *, double *), double param[]){
    double ra = (rm*n_petal)/(n_petal+2*n_tour);
    double rb = (ra*n_tour)/n_petal;
    double rc = (ra+rb)/rb;
    double x,y,old_x,old_y,holder[2];
    for(double t=0;t<=n_tour*6.283;t += 0.01){
        x = cx + w*(ra+rb)*cos(t)+rb*cos(rc*t);
        y = cy + h*(ra+rb)*sin(t)+rb*sin(rc*t);
        if(func != NULL)(*func)(x,y,holder,param);
        else{
            holder[0] = x;
            holder[1] = y;
        }
        if(t != 0) segment(s,old_x,holder[0],old_y,holder[1],color);
        old_x = holder[0];
        old_y = holder[1];
    }
}

void oval(SURFACE *s, double r, double h, double w, double cx, double cy, double color[3], void (*func)(double, double, double*, double*), double param[]){
    double x,y,old_x,old_y, holder[2];
    for(double t=0;t<=6.283;t += 0.01){
        x = cx + w*r*cos(t);
        y =  cy + h*r*sin(t);
        if(func != NULL)(*func)(x,y,holder,param);
        else{
            holder[0] = x;
            holder[1] = y;
        }
        if(t != 0) segment(s,old_x,holder[0],old_y,holder[1],color);
        old_x = holder[0];
        old_y = holder[1];
    }
}
