#ifndef ITEMS_H

#define ITEMS_H

/*
*  Crée un brun d'herbe a l'aide de deux courbes de bezier et un segment de taille et de forme prédéfinie
*  Peut etre modifiée en passant en paramètre une fonction de transformation.
*
*   @param s pointeur vers la SURFACE
*   @param x coordonée x centre de la base du brin
*   @param y coordonée y de la base du brin
*   @param color couleur de l'herbe représentée sous la forme (r,g,b) avec des valeurs entre 0 et 1
*   @param transfo fonction de transformation
*   @param param dernier paramètre de la fonctio de transformation
*/
void herbe(SURFACE *s,double x, double y,double color[3], void (*transfo)(double, double, double*, double*), double param[]);

/*
*   Crée un rectangle (non remplis)
*   
*   @param s pointeur vers la SURFACE
*   @param x1 coordonnée x du point haut gauche
*   @param y1 coordonnée y du point haut gauche
*   @param w la largeur du rectangle
*   @param h la hauteur du rectangle
*   @param color couleur des coté du rectangle représentée sous la forme (r,g,b) avec des valeurs entre 0 et 1
*   @param transfo fonction de transformation
*   @param param dernier paramètre de la fonctio de transformation
*/
void rectangle(SURFACE *s, double x1, double y1, double w, double h, double color[3], void (*transfo)(double, double, double*, double*), double param[]);

/*
*   Crée un arbre aux coordonées indiquées
*   
*   @param s pointeur vers la SURFACE
*   @param x1 coordonée x du centre de la base de l'arbre
*   @param x2 coordonée y du centre de la base de l'arbre
*/
void arbre(SURFACE *s, double x1, double y1);

/*
*   Crée une fleur a l'aide de courbe de bezier et d'epicycloides.
*
*   @param s pointeur vers la SURFACE
*   @param x1 coordonée x de la base de la tige
*   @param y1 coordonée y de la base de la tige
*   @param nbpetales le nombre de pétales de la fleur
*   @param color couleur des pétales représentée sous la forme (r,g,b) avec des valeurs entre 0 et 1
*   @param transfo fonction de transformation
*   @param param dernier paramètre de la fonctio de transformation
*/
void fleur(SURFACE *s, double x1, double y1, int nbpetales, double color[3], void (*transfo)(double, double, double*, double*), double param[]);

/* 
*   Crée un recangle remplis avec un dégradé vertical de couleur
*
*   @param s pointeur vers la SURFACE
*   @param x1 coordonnée x du point haut gauche
*   @param y1 coordonnée y du point haut gauche
*   @param w la largeur du rectangle
*   @param h la hauteur du rectangle
*   @param color1 la couleur du haut du rectangle
*   @param color2 la couleur du bas du rectangle
*   @param transfo fonction de transformation
*   @param param dernier paramètre de la fonctio de transformation
*/
void rectangle_tah_le_degrade(SURFACE *s, double x1, double y1, double w, double h, double color1[3], double color2[3],void (*transfo)(double, double, double*, double*), double param[]);

#endif