typedef struct{
    double r,g,b;
} PIXEL;

typedef struct{
    int width; // largeur
    int height; // hauteur
    int scale; //echelle de conversion
    PIXEL* data; // Liste de pixels
} SURFACE;

/*
*  Initialise la surface.
*  Utilise la fonction malloc pour initialiser le tableau data en de taille width*height
*  @param s le pointeur vers la surface
*  @param width la largeur de la surface en pixel
*  @param height la hauteur de la surface en pixel
*  @param scale l'echelle de conversion des valeurs de couleur entre double et int
*  @return 1 si la surface est correctement initialisée, 0 sinon
*/
int init_surf(SURFACE *s, int width, int height, int scale);


/*
*  Libère la mémoire occupée par la surface passé par adresse et pointe data vers le pointeur NULL
*  @param s le pointeur vers la surface
*/
void _SURFACE(SURFACE *s);

/*
* Retourne l'adresse mémoire du PIXEL de coordonée (x,y) de la surface passée par adresse
*
* @param s le pointeur vers la surface
* @param x coordonée horizontale
* @param y coordonée verticale
* @return l'adresse mémoire du pixel
 */
PIXEL *at(SURFACE *s, int x, int y);

/*
 * Attribue la couleur au pixel (x,y) de la surface s
 */
void point(SURFACE *s,int x, int y,double value[3]);

/*
* Remplis l'integralitée de la surface avec la couleur passée en paramètre
*
* @param s le pointeur vers la surface
* @param value tableau de trois valeur représentant une couleur sour la forme {r,g,b}
*/
void fill(SURFACE *s, double value[3]);

/*
* Lis le fichier passé en paramètre et si c'est un .ppm P3, le charge dans la surface passée en paramètre
*
* @param s le pointeur vers la surface
* @param f l'adresse mémoire du fichier
* @return 1 si la lecture a reussi, 0 sinon
*/
int ppm_read(SURFACE *s,FILE *f);

/*
* Ecrit le contenu de la surface dans le fichier passé en paramètre.
*
* @param s le pointeur vers la surface
* @param f l'adresse mémoire du fichier
* @return le nombre d'appel de la fonction fprintf.
*/
int ppm_write(SURFACE *s,FILE *f);

/* ------------------------------------------------------ */

/* 
*   Approxime un flottant en nombre entier
* 
*   @param value nombre décimal a approximer
*   @return valeur entière approximative
*/
int approx(double value);

/*
*   retourne la valeur minimale entre a et b
*
*   @param a valeur décimale
*   @param b valeur décimale
*   @return la plus petite valeur entre a et b
*/
double min(double a, double b);

/*
*   Trace le segment [AB] sur la surface avec la couleur donné en paramètre.
*
*   @param s le pointeur vers la surface
*   @param x1 coordonée x du point A
*   @param x2 coordonée x du point B
*   @param y1 coordonée y du point A
*   @param y2 coordonée y du point B
*   @param color couleur des pétales représentée sous la forme (r,g,b) avec des valeurs entre 0 et 1
*/
void segment(SURFACE *s,double x1, double x2, double y1, double y2, double color[3]);


void bezier(SURFACE *s,double Ax, double Ay, double Bx, double By, double Cx, double Cy, double Dx, double Dy, double col[3], void (*func)(double, double, double*, double*), double param[]);

/*
*   Remplis par innondation une forme du dessin
*
*   s'appelle reccursivement sur les pixels voisins de celui selectionné a l'appel
*   precedent jusqu'a rencontrer la couleur du bord
*   
*   @param s le pointeur vers la surface
*   @param Ix cordonée x d'un point à l'interieur de la forme a remplir
*   @param Iy cordonée y d'un point à l'interieur de la forme a remplir
*   @param la couleur du bord de la forme (et la couleur de remplissage)
*/
void fill_item(SURFACE *s, double Ix, double Iy, double border_color[3]);

void epicycloide(SURFACE *s,double rm, double n_petal, double  n_tour, double cx, double cy,double color[3], void (*func)(double,double,double *, double*), double param[]);

void oval_epicycloide(SURFACE *s,double rm, double n_petal, double  n_tour, double h, double w,double cx, double cy,double color[3], void (*func)(double,double,double *, double *), double param[]);

void cercle(SURFACE *s, double r, double cx, double cy, double color[3], void (*func)(double, double, double*, double*), double param[]);

void oval(SURFACE *s, double r, double h, double w, double cx, double cy, double color[3], void (*func)(double, double, double*, double*), double param[]);

/* ------------------------------------------------------ */

void axe_symetrie(double p_x, double p_y, double value, int axis, double ret[2]);

void rotation(double p_x, double p_y, double a_x, double a_y, double angle, double ret[2]);

void translation(double p_x, double p_y, double dx, double dy, double ret[2]);

void scale(double p_x, double p_y, double scaling, double ret[2]);