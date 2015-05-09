typedef struct S_point T_point; 
void insererEnTete(int x, int y ,T_point** tete);
void insererEnQueue(int x, int y, T_point** tete);
void afficherListe(T_point* tete);
int getX(T_point* tete, int i);
int getY(T_point* tete, int i);