#include <stdlib.h>
#include <stdio.h>
#include "surface.h"

int iclamp(double val, int min , int max){
    int val_parsed = (int)val;
    if(val_parsed < 0) return 0;
    if(val_parsed > max) return 255;
    return val_parsed;
}

int approx(double value){
    double a =(double) ((int) value);
    if(a==value) return a;
    if( a-value < -0.5){
        return (int) a + 1;
    }
    return (int) a;
}

double min(double a, double b){
    if(a<b)return a;
    return b;
}

int init_surf(SURFACE *s, int width, int height, int scale){
    s->data = (PIXEL *) malloc(width*height*sizeof(PIXEL));
    if(s->data != NULL){
        s->width = width;
        s->height = height;
        s->scale = scale;
        return 1;
    }
    return 0;
}

void _SURFACE(SURFACE *s){
    free(s->data);
    s->data = NULL;
}

PIXEL *at(SURFACE *s,int x, int y){
    if(x < 0 || x >= s->width)return NULL;
    if(y < 0 || y >= s->height)return NULL;
    return s->data+(y*s->width)+x;
}

void point(SURFACE *s,int x, int y,double value[3]){
    PIXEL* pos = at(s,x,y);
    if(pos != NULL){
        pos->r = value[0];
        pos->g = value[1];
        pos->b = value[2];
    }
}

void fill(SURFACE *s, double value[3]){
    PIXEL* e = s->data + s->width*s->height;
    for(PIXEL* i = s->data; i != e; i++){
        i->r = value[0];
        i->g = value[1];
        i->b = value[2];
    }
}

int ppm_write(SURFACE *s,FILE *f){
    int count = fprintf(f,"P3\n# ppm_write\n%d %d\n%d\n",s->width,s->height,s->scale);
    int cr = s->width;
    PIXEL* e = s->data + s->height*s->width;
    for(PIXEL* i = s->data; i != e; i++){
        count += fprintf(f,"%d %d %d", iclamp(i->r * s->scale, 0, s->scale-1),iclamp(i->g * s->scale, 0, s->scale-1),iclamp(i->b * s->scale, 0, s->scale-1));
        if(--cr)count += fprintf(f," ");
        else{
            cr = s->width;
            count += fprintf(f,"\n");
        }
    }
    return count;
}

int ppm_read(SURFACE *s,FILE *f){
    if(fgetc(f) != 'P') return 0;
    if(fgetc(f) != '3') return 0;
    if(fgetc(f) != '\n') return 0;

    char c;
    while( (c = fgetc(f))== '#'){
        while(fgetc(f) != '\n');
    }
    ungetc(c,f);

    int w,h,m;
    if(fscanf(f,"%d%d%d",&w,&h,&m) != 3) return 0;
    
    _SURFACE(s);
    s->data = (PIXEL *) malloc(w*h*sizeof(PIXEL));
    if(s->data != NULL){
        s->width = w;
        s->height = h;
        PIXEL *e = s->data + h*w;
        for(PIXEL *i = s->data; i != e; i++){
            int r,g,b;
            if( fscanf(f, "%d %d %d", &r, &g, &b) != 3){
                _SURFACE(s);
                return 0;
            }
            i->r = (double) r/m;
            i->g = (double) g/m;
            i->b = (double) b/m;
        }
        s->scale = m;
        return 1;
    }
    return 0;
}

void segment(SURFACE *s,double x1, double x2, double y1, double y2, double color[3]){
    double dx = x2-x1;
    double dy = y2-y1;
    double increment,ix,ygrek;
    if(dx*dx > dy*dy){
        ygrek = y1;
        ix = x1;
        if(min(x1,x2) == x1){
            increment = 1;
            
        }
        else{
            increment = -1;
        }
        point(s,approx(ix),approx(ygrek),color);
        while( increment*(x2-ix) >= 1){
            ix += increment;
            ygrek += increment*(dy/dx);
            point(s,approx(ix),approx(ygrek),color);
        }
    }
    else{
        ygrek = y1;
        ix = x1;
        if(min(y1,y2) == y1){
            increment = 1;
        }
        else{
            increment = -1;
        }
        point(s,approx(ix),approx(ygrek),color);
        while( increment*(y2-ygrek) >= 1){
            ygrek += increment;
            ix += increment*(dx/dy);
            point(s,approx(ix),approx(ygrek),color);
        }
    }
}

int IsColor(PIXEL *c, double color[3]){
    return c->r == color[0] && c->g == color[1] && c->b == color[2];
}


void fill_item(SURFACE *s, double Ix, double Iy, double border_color[3]){
    //PIXEL **c = (PIXEL **) malloc(sizeof(PIXEL **));
    //if(c != NULL) *c = at(s,Ix,Iy);
    if(at(s,Ix,Iy) == NULL){
        return;
    }
    else if(IsColor(at(s,Ix,Iy),border_color)){
        return;
    }
    else{
        at(s,Ix,Iy)->r = border_color[0];
        at(s,Ix,Iy)->g = border_color[1];
        at(s,Ix,Iy)->b = border_color[2];
        if(Ix < s->width-1) fill_item(s,Ix+1,Iy,border_color);
        if(Iy < s->width-1) fill_item(s,Ix,Iy+1,border_color);
        if(Ix > 0) fill_item(s,Ix-1,Iy,border_color);
        if(Iy > 0) fill_item(s,Ix,Iy-1,border_color);
    }
    //free(c);
}