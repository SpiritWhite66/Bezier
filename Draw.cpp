#include "Draw.hpp"

typedef struct S_point
{
  int x;
  int y;
  struct S_point *suivant;
}T_point;


void minMax( int N, float * t, float * min, float * max ){
    *min = t[0] ;
    *max = t[0] ;
    for( int i = 1 ; i < N ; i ++ ){
        if( t[ i ] < *min ) *min = t[ i ] ;
        if( t[ i ] > *max ) *max = t[ i ] ;
    }
}

void calcCourbe(float * x, float * y, T_point* tete){
	float i = 0;
	int k = 0;
    while(i<=1){
		x[k]=bezierx(i,tete);
		y[k]=beziery(i,tete);
		i=i+0.0005;
		k++;
	}

}

void initImg( CImg<unsigned char> * img, int imgL, int imgC ){
  
    unsigned char marron[]={86,48,44};
    unsigned char blanc[]={255,255,255};
    unsigned char vertmenu[]={0,128,64};    
    for(int i=0;i<imgL;i++){
	for(int j=0;j<imgC;j++){
	    img->draw_point(i,j,marron);
	}
    }
    img->draw_rectangle(410,10,490,40,vertmenu);
    img->draw_text(420,10,"Menu",blanc,vertmenu,1,30);
    img->draw_text(110,10,"Mode Dynamique",blanc,marron,1,40);
}


void ControlPointPrint(CImg<unsigned char>* img, T_point *adress)
{
    unsigned char noir[] = { 0, 0, 0 } ;
    unsigned char blanc[] = {255,255,255};
     while((adress)!= NULL)
        {
            img->draw_circle (adress->x, adress->y,5, noir, 1);
	    img->draw_circle(adress->x,adress->y,3,blanc,1);
	    img->draw_circle(adress->x,adress->y,1,noir,1);
            adress= adress->suivant;
        }
}

int triangleP(int n, int k){
	int liste[n][n+1];
	liste[0][0] = 1;
	for(int i=1; i<n; i++){
		liste[i][0] = 1;
			for(int j=1; j<i; j++){
				liste[i][j]=liste[i-1][j-1] + liste[i-1][j];
			}
		liste[i][i] = 1;
	}
	return liste[n-1][k];
}

float bezierx(float t,T_point* wkt){
	T_point* start = wkt;
	float coor=0;
	int n=0;int i=0;
	while(start!=NULL){
		start=start->suivant;
		n++;
	}
	start = wkt;
	while(start!=NULL){
		int coeff=triangleP(n,i);
		//cout<<coeff<<endl;
		coor=coor+pow((1-t),(n-1)-i)*start->x*pow(t,i)*coeff;
		//cout<<"(1-t)^"<<(n-1)-i<<" * "<<start->x<<" * t^"<<i<<" * "<<coeff<<" + ";
		start=start->suivant;
		i++;
	}
	return coor;
}

float beziery(float t,T_point* wkt){
	T_point* start = wkt;
	float coor=0;
	int n=0;int i=0;
	while(start!=NULL){
		start=start->suivant;
		n++;
	}
	start = wkt;
	while(start!=NULL){
		int coeff = triangleP(n,i);
		coor=coor+pow((1-t),(n-1)-i)*start->y*pow(t,i)*coeff;
		start=start->suivant;
		i++;
	}
	return coor;
}

void traceB(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx){
  T_point* lettreB = NULL;
  insererEnQueue(8+coeffx,307,&lettreB);
  insererEnQueue(126+coeffx,107,&lettreB);
  insererEnQueue(-34+coeffx,117,&lettreB);
  insererEnQueue(-7+coeffx,378,&lettreB);
  insererEnQueue(-2+coeffx,337,&lettreB);
  insererEnQueue(49+coeffx,344,&lettreB);
  insererEnQueue(86+coeffx,230,&lettreB);
  insererEnQueue(-31+coeffx,305,&lettreB);
  insererEnQueue(56+coeffx,290,&lettreB);
  float x,y;
  float i=0;
  while(i<=1){
    x=bezierx(i,lettreB);
    y=beziery(i,lettreB);
    lettre->draw_point(x,y,couleur);
    //cout<<"x = "<<x<<" et y = "<<y<<endl;
    i=i+0.0005;
  }
}

void traceU(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx){
  T_point* lettreU = NULL;
  insererEnQueue(93+coeffx,287,&lettreU);
  insererEnQueue(65+coeffx,393,&lettreU);
  insererEnQueue(77+coeffx,156,&lettreU);
  insererEnQueue(41+coeffx,-1,&lettreU);
  insererEnQueue(189+coeffx,452,&lettreU);
  insererEnQueue(-33+coeffx,408,&lettreU);
  insererEnQueue(14+coeffx,362,&lettreU);
  insererEnQueue(27+coeffx,67,&lettreU);
  insererEnQueue(8+coeffx,305,&lettreU);
  float x,y;
  float i=0;
  while(i<=1){
    x=bezierx(i,lettreU);
    y=beziery(i,lettreU);
    lettre->draw_point(x,y,couleur);
    i=i+0.0005;
  }

}

void traceD(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx){
  T_point* lettreD = NULL;
  insererEnQueue(30+coeffx,270,&lettreD);
  insererEnQueue(-27+coeffx,265,&lettreD);
  insererEnQueue(31+coeffx,338,&lettreD);
  insererEnQueue(59+coeffx,510,&lettreD);
  insererEnQueue(36+coeffx,15,&lettreD);
  insererEnQueue(26+coeffx,15,&lettreD);
  insererEnQueue(47+coeffx,166,&lettreD);
  insererEnQueue(47+coeffx,138,&lettreD);
  insererEnQueue(17+coeffx,364,&lettreD);
  insererEnQueue(50+coeffx,305,&lettreD);

  float x,y;
  float i=0;
  while(i<=1){
    x=bezierx(i,lettreD);
    y=beziery(i,lettreD);
    lettre->draw_point(x,y,couleur);
    i=i+0.0005;
  }
}

void traceE(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx){
  T_point* lettreE = NULL;
  insererEnQueue(20+coeffx,289,&lettreE);
  insererEnQueue(185+coeffx,275,&lettreE);
  insererEnQueue(46+coeffx,192,&lettreE);
  insererEnQueue(-43+coeffx,323,&lettreE);
  insererEnQueue(94+coeffx,305,&lettreE);
  float x,y;
  float i=0;
  while(i<=1){
    x=bezierx(i,lettreE);
    y=beziery(i,lettreE);
    lettre->draw_point(x,y,couleur);
    i=i+0.0005;
  }
}


void event(CImgDisplay* fenetre, float * zoom, CImg<unsigned char>* img, int N,int imgL, int imgC, int* imgC2, int* imgL2,
float * x, float * y, float * t, T_point** tete)
{
/******************
La fonction event permet la gestion des événements pour les actions de zoom et de déplacement
******************/

    unsigned char noir[] = { 0, 0, 0 } ; // on sauvegarde la couleur noir

    if(fenetre->is_keyA()) // Si le bouton "A" est appuyé on zoom de 10% 
    { 
      float max_x; 
      float min_x;
      float max_y; 
      float min_y;
      minMax(1000, x, &max_x , &min_x);
      minMax(1000, y, &max_y , &min_y);
      float diff_x = (max_x-min_x)/2;
      float diff_y = (max_y-min_y)/2;  
      T_point * start = *tete;
      
      /* Correction déplacement du zoom */
      int save_x; 
      int save_y;
      if((start->y)>diff_y)
      {
        save_y=start->y - (start->y)/0.9;
      }
      if((start->x)<diff_x)
      {
        save_x=start->x -((start->x))*0.9;
      }
      if((start->y)<diff_y)
      {
        save_y=start->y -(start->y)*0.9;
      }
      if((start->x)>diff_x)
      {
       save_x=start->x -(start->x)/0.9;
      }
      /* Fin Correction déplacement du zoom */

      /* Boucle de zoom */
      while(start!=NULL)
      { 
        if((start->y)>diff_y)
        {
          start->y =  (start->y)/0.9 + save_y;
        }
        if((start->x)<diff_x)
        {
          start->x = ((start->x))*0.9 +save_x ;
        }
        if((start->y)<diff_y)
        {
          start->y = (start->y)*0.9 + save_y;
        }
        
        if((start->x)>diff_x)
        {
          start->x = (start->x)/0.9 +save_x;
        }
        
        start=start->suivant;
      }
      

      initImg( img, imgL, imgC ) ; // Réinitialisation de l'image en marron
      calcCourbe(x, y, *tete); //Calcul des nouveaux points
      ControlPointPrint(img, *tete); // Dessine les points de contrôle
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t); // Dessine la courbe de bézier
      fenetre->display(*img); //Affiche les points de contrôle et la courbe

    }
    else if(fenetre->is_keyZ()) // Si le bouton "Z" est appuyé on dézoom de 10%
    {
      float max_x; 
      float min_x;
      float max_y; 
      float min_y;
      minMax(1000, x, &max_x , &min_x);
      minMax(1000, y, &max_y , &min_y);
      float diff_x = (max_x-min_x)/2;
      float diff_y = (max_y-min_y)/2;  
      T_point * start = *tete;

      /* Correction déplacement du zoom */
      int save_x; 
      int save_y;
      if((start->y)>diff_y)
      {
        save_y=start->y - (start->y)/1.1;
      }
      if((start->x)<diff_x)
      {
        save_x=start->x -((start->x))*1.1;
      }
      if((start->y)<diff_y)
      {
        save_y=start->y -(start->y)*1.1;
      }
      if((start->x)>diff_x)
      {
       save_x=start->x -(start->x)/1.1;
      }
      /* Fin Correction déplacement du zoom */

      while(start!=NULL)
      { 
         if((start->y)>diff_y)
        {
          start->y =  (start->y)/1.1 + save_y;
        }
        if((start->x)<diff_x)
        {
          start->x = ((start->x))*1.1 + save_x;
        }
        if((start->y)<diff_y)
        {
          start->y = (start->y)*1.1 + save_y;
        }
        
        if((start->x)>diff_x)
        {
          start->x = (start->x)/1.1 + save_x;
        }
        start=start->suivant;
      }

      initImg( img, imgL, imgC ) ;
      calcCourbe(x, y, *tete);
      ControlPointPrint(img, *tete);
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);
    }
    else if(fenetre->button() and fenetre->is_keyCTRLLEFT()) // Permet le déplacement lorsqu'il y a un clic de la souris et la touche "Ctrl" gauche enclenché
    {
      T_point * start = *tete;
      int mousex = fenetre->mouse_x(); // on récupére la position de la souris  
      int mousey = fenetre->mouse_y(); 
      //cout<< "x : "<<fenetre->mouse_x()<<" | y : "<< fenetre->mouse_y();
      mousex = mousex- (start->x); //on replace les points du centre du graph
      mousey = mousey - (start->y);

      while(start!=NULL)
      { 
        start->x = (start->x)+mousex; 
        start->y = (start->y)+mousey;
        start=start->suivant;
      } 

      initImg( img, imgL, imgC ) ;
      calcCourbe(x, y, *tete);
      ControlPointPrint(img, *tete);
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);

    }
    //Gestion des mouvements par les "flèches"
    else if(fenetre->is_keyARROWRIGHT())
    {	
      T_point * start = *tete;

      while(start!=NULL)
      { 
        start->x = (start->x)+10; 
        start=start->suivant;
      } 

      initImg( img, imgL, imgC ) ;
      calcCourbe(x, y, *tete);
      ControlPointPrint(img, *tete);
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);
    }
    else if(fenetre->is_keyARROWLEFT())
    {
      T_point * start = *tete;

      while(start!=NULL)
      { 
        start->x = (start->x)-10; 
        start=start->suivant;
      } 

      initImg( img, imgL, imgC ) ;
      calcCourbe(x, y, *tete);
      ControlPointPrint(img, *tete);
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);
    }
    else if(fenetre->is_keyARROWUP())
    {
     	 T_point * start = *tete;

      while(start!=NULL)
      { 
        start->y = (start->y)-10;
        start=start->suivant;
      } 

      initImg( img, imgL, imgC ) ;
      calcCourbe(x, y, *tete);
      ControlPointPrint(img, *tete);
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);
    }
    else if(fenetre->is_keyARROWDOWN())
    {
     	T_point * start = *tete;

      while(start!=NULL)
      { 
        start->y = (start->y)+10;
        start=start->suivant;
      } 

      initImg( img, imgL, imgC ) ;
      calcCourbe(x, y, *tete);
      ControlPointPrint(img, *tete);
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);
    }
    else if(fenetre->is_keyC() and fenetre->button()) // Créer un nouveau point de controle  
    {
      insererEnQueue(fenetre->mouse_x(),fenetre->mouse_y(), tete);
      ControlPointPrint(img, *tete);
     	calcCourbe(x, y, *tete);
     	initImg(img, imgL, imgC ) ;
     	dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
     	fenetre->display(*img);
	    fenetre->wait(500);
    }
     else if(fenetre->is_keyD() and fenetre->button()) // Supprime le dernier point de controle créé 
    {
      T_point * start = *tete;
      T_point * prec = start;
      while(start->suivant!=NULL)
      {
        prec=start;
        start=start->suivant;

      }
      delete[] prec->suivant;
      prec->suivant=NULL;
      start = *tete;
      while(start!=NULL)
      {
        cout<<" -> "<<start->x;
        start=start->suivant;
      }
      cout<<endl;
      ControlPointPrint(img, *tete);
      calcCourbe(x, y, *tete);
      initImg(img, imgL, imgC ) ;
      dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
      fenetre->display(*img);
    }
    else if(fenetre->button())
      {
        int mousex = fenetre->mouse_x(); // on récupére la position de la souris
        int mousey = fenetre->mouse_y();
        int mousex_min = mousex - 15; // on créer une zone "d'erreur" de 10x10px
        int mousex_max = mousex + 15;
        int mousey_min = mousey -15;
        int mousey_max = mousey +15;
        T_point* adress = *tete;

        initImg(img, imgL, imgC ) ;
        fenetre->display(*img);
        while(adress!= NULL)
        { // on compare à nos points de controle
          if(((adress->x)>mousex_min and (adress->x)<mousex_max)and ((adress->y)>mousey_min and (adress->y)<mousey_max))
          {
            adress->x = fenetre->mouse_x();
            adress->y = fenetre->mouse_y();         
          }
          adress= adress->suivant;
          
        }
        ControlPointPrint(img, *tete);
        calcCourbe(x, y, *tete);
        dessinBezier(zoom, img, N, imgL, imgC, imgC2, imgL2, x, y, t);
        fenetre->display(*img);
        
      }

}

void dessinBezier(float * zoom, CImg<unsigned char>* img, int N,int imgL, int imgC, int* imgC2, int* imgL2,
  float * x, float * y, float * t)
{
    unsigned char noir[] = { 0, 0, 0 } ;
    for( int i = 0 ; i < N ; i ++ )
      {
        img->draw_point(x[i] , y[i],noir);
        //cout<<x[i]<<endl;
      }
}
