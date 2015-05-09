#include <iostream>
using namespace std;

typedef struct S_point
{
	int x;
	int y;
	struct S_point *suivant;
}T_point; 

void insererEnTete(int x, int y,T_point** tete) //avec tete qui est l'adresse du bloc d'entête
{
	T_point *cell = new T_point;
	cell->x=x;
	cell->y=y;
	cell->suivant = *tete;
	*tete = cell; 	
}

void insererEnQueue(int x, int y, T_point** tete)
{
	T_point* adress = *tete;
	if(*tete != NULL)
	{
		while(adress->suivant != NULL)
		{			
			adress = adress->suivant;
		}
		T_point *cell = new T_point;
		cell->x=x;
		cell->y=y;
		cell->suivant = NULL;
		adress->suivant = cell;
	} 
	else
	{
		insererEnTete(x,y ,tete);
	}
}

void afficherListe(T_point* tete)
{
	while(tete != NULL)
	{
		cout<<"->"<<tete->x<< " | "<<tete->y;
		tete = tete->suivant;
	}
}

int getX(T_point* tete, int i)
{
	int j = 0;
	while(tete != NULL and j!=i)
	{
		tete = tete->suivant;
		j++;
	}
	if(j==i)
	{
		return tete->x;
	}
	else
	{
		return -1;
	}
}
int getY(T_point* tete, int i)
{
	int j = 0;
	while(tete != NULL and j!=i)
	{
		tete = tete->suivant;
		j++;
	}
	if(j==i)
	{
		return tete->y;
	}
	else
	{
		return -1;
	}
	
}