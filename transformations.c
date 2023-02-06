#include <stdio.h>
#include <math.h>
#include "surface.h"

#define X_AXIS 0
#define Y_AXIS 1

void axe_symetrie(double p_x, double p_y, double value, int axis, double ret[2]){
    if(axis == X_AXIS){
        p_x = value + value-p_x;
    }
    if(axis == Y_AXIS){
        p_y = value + value-p_y;
    }
    ret[0] = p_x;
    ret[1] = p_y;
}

void rotation(double p_x, double p_y, double a_x, double a_y, double angle, double ret[2]){
    double c = cos(angle);
    double s = sin(angle);
    double diffx = p_x - a_x;
    double diffy = p_y - a_y;
    ret[0] = a_x + c*diffx+s*diffy;
    ret[1] = a_y + c*diffy-s*diffx;
}

void translation(double p_x, double p_y, double dx, double dy, double ret[2]){
    ret[0] = p_x + dx;
    ret[1] = p_y + dy;
}

void scale(double p_x, double p_y, double scaling, double ret[2]){
    ret[0] = scaling*p_x;
    ret[1] = scaling*p_y;
}

void augmentation_hauteur(double p_x, double p_y, double scaling, double ret[2]){
    ret[0] = p_x;
    ret[1] = scaling*p_y;
}