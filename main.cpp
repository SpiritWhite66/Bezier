#include <iostream>
#include <math.h>
#include "ListeChaine.hpp"
#include "Draw.hpp"
#include "CImg/CImg.h"

using namespace std; 
using namespace cimg_library;

#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

int main( void ){

	/* Paramètre pour l'image courbe dynamique */
	int imgL = 512, imgC = 512 ; //Dimension de l'image
    int imgL2 = imgL / 2, imgC2 = imgC / 2 ; //moitié de l'image
    int N = 2001 ;
    float * t = new float [N];
    float * x = new float [N];
    float * y = new float [N];
    float xMin, xMax, yMin, yMax, dx, dy, xMil, yMil ;
    float diff ;
    float zoom = 1; // valeur du zoom

    /* Déclaration des différentes images */
	CImg<unsigned char> presentation(512,512,1,3,255); //n=1
	CImg<unsigned char> accueil(512,512,1,3,255); //n=2
	CImg<unsigned char> dynamique(512,512,1,3,255); //n=3
	CImg<unsigned char> lettreB(512,512,1,3,255); //n=4
	CImg<unsigned char> lettreU(512,512,1,3,255); //n=5
	CImg<unsigned char> lettreD(512,512,1,3,255); //n=6
	CImg<unsigned char> lettreE(512,512,1,3,255); //n=7
	CImg<unsigned char> lettre(512,512,1,3,255); //n=8
	CImg<unsigned char> img( imgL, imgC ,1 ,3,255); // initialisation de l'image dynamique

	/* Déclaration et définition des couleurs */
	unsigned char noir[]={0,0,0};
	unsigned char blanc[]={255,255,255};
	unsigned char rouge[]={255,0,0};
	unsigned char vert[]={0,255,0};
	unsigned char bleu[]={0,0,255};
	unsigned char marron[]={86,48,44};
	unsigned char jaune[]={255,255,0};
	unsigned char rose[]={255,0,255};
	unsigned char cyan[]={0,255,255};
	unsigned char vertmenu[]={0,128,64};

	/* Mise en couleur */
	for(int i=0;i<512;i++){
		for(int j=0;j<512;j++){
			presentation.draw_point(i,j,marron);
			accueil.draw_point(i,j,marron);
			dynamique.draw_point(i,j,marron);
			lettreB.draw_point(i,j,marron);
			lettreU.draw_point(i,j,marron);
			lettreD.draw_point(i,j,marron);
			lettreE.draw_point(i,j,marron);
			lettre.draw_point(i,j,marron);

		}
	}
	/*Création de l'image presentation et accueil*/
	presentation.draw_text(70,60,"Bezier's Corporate",blanc,marron,1,50).draw_text(55,150,"Presente",blanc,marron,1,120).draw_rectangle(128,350,384,420,noir,1).draw_text(135,360,"COMMENCER",blanc,noir,1,50);

    accueil.draw_rectangle(254,0,258,512,blanc).draw_rectangle(21,25,235,64,blanc).draw_text(26,30,"Mode Dynamique",blanc,marron,1,30).draw_rectangle(305,25,461,64,blanc).draw_text(310,30,"Mode Lettre",blanc,marron,1,30).draw_text(41,150,"Demarrer avec :",blanc,marron,1,25).draw_text(310,150,"Choisir Lettre :",blanc,marron,1,25).draw_rectangle(91,228,166,256,blanc).draw_text(93,230,"1 Point",blanc,marron,1,25).draw_rectangle(83,268,170,296,blanc).draw_text(85,270,"2 Points",blanc,marron,1,25).draw_rectangle(83,308,170,336,blanc).draw_text(85,310,"3 Points",blanc,marron,1,25).draw_rectangle(83,348,170,376,blanc).draw_text(85,350,"4 Points",blanc,marron,1,25).draw_rectangle(83,388,170,416,blanc).draw_text(85,390,"5 Points",blanc,marron,1,25).draw_rectangle(83,428,169,456,blanc).draw_text(85,430,"6 Points",blanc,marron,1,25).draw_text(339,230,"B",blanc,marron,1,50).draw_text(338,290,"U",blanc,marron,1,50).draw_text(337,350,"D",blanc,marron,1,50).draw_text(340,410,"E",blanc,marron,1,50).draw_rectangle(332,229,334,277,blanc).draw_rectangle(334,229,367,231,blanc).draw_rectangle(367,229,369,277,blanc).draw_rectangle(334,275,367,277,blanc).draw_rectangle(332,289,334,337,blanc).draw_rectangle(334,289,367,291,blanc).draw_rectangle(367,289,369,337,blanc).draw_rectangle(334,335,367,337,blanc).draw_rectangle(332,349,334,397,blanc).draw_rectangle(334,349,367,351,blanc).draw_rectangle(367,349,369,397,blanc).draw_rectangle(334,395,367,397,blanc).draw_rectangle(332,409,334,457,blanc).draw_rectangle(334,409,367,411,blanc).draw_rectangle(367,409,369,457,blanc).draw_rectangle(334,455,367,457,blanc).draw_rectangle(206,482,298,512,vertmenu).draw_text(211,482,"Quitter",blanc,vertmenu,1,30).draw_rectangle(430,220,467,476,blanc).draw_rectangle(433,223,464,473,marron).draw_text(436,223,"S",blanc,marron,1,50).draw_text(433,263,"A",blanc,marron,1,50).draw_text(445,303,"I",blanc,marron,1,50).draw_text(436,343,"S",blanc,marron,1,50).draw_text(445,383,"I",blanc,marron,1,50).draw_text(437,423,"E",blanc,marron,1,50);

    lettreB.draw_text(110,10,"Mode Lettre",blanc,marron,1,40).draw_rectangle(438,58,494,478,noir).draw_rectangle(440,60,492,476,blanc).draw_rectangle(441,61,491,111,noir).draw_rectangle(441,113,491,163,noir).draw_rectangle(441,166,491,215,noir).draw_rectangle(441,217,491,267,noir).draw_rectangle(441,269,491,319,noir).draw_rectangle(441,321,491,371,noir).draw_rectangle(441,373,491,423,noir).draw_rectangle(441,425,491,475,noir).draw_rectangle(443,115,489,161,blanc).draw_rectangle(443,168,489,213,rouge).draw_rectangle(443,219,489,265,vert).draw_rectangle(443,271,489,317,bleu).draw_rectangle(443,323,489,369,jaune).draw_rectangle(443,375,489,421,rose).draw_rectangle(443,427,489,473,cyan).draw_rectangle(410,10,490,40,vertmenu).draw_text(420,10,"Menu",blanc,vertmenu,1,30);

    lettreU.draw_text(110,10,"Mode Lettre",blanc,marron,1,40).draw_rectangle(438,58,494,478,noir).draw_rectangle(440,60,492,476,blanc).draw_rectangle(441,61,491,111,noir).draw_rectangle(441,113,491,163,noir).draw_rectangle(441,166,491,215,noir).draw_rectangle(441,217,491,267,noir).draw_rectangle(441,269,491,319,noir).draw_rectangle(441,321,491,371,noir).draw_rectangle(441,373,491,423,noir).draw_rectangle(441,425,491,475,noir).draw_rectangle(443,115,489,161,blanc).draw_rectangle(443,168,489,213,rouge).draw_rectangle(443,219,489,265,vert).draw_rectangle(443,271,489,317,bleu).draw_rectangle(443,323,489,369,jaune).draw_rectangle(443,375,489,421,rose).draw_rectangle(443,427,489,473,cyan).draw_rectangle(410,10,490,40,vertmenu).draw_text(420,10,"Menu",blanc,vertmenu,1,30);

    lettreD.draw_text(110,10,"Mode Lettre",blanc,marron,1,40).draw_rectangle(438,58,494,478,noir).draw_rectangle(440,60,492,476,blanc).draw_rectangle(441,61,491,111,noir).draw_rectangle(441,113,491,163,noir).draw_rectangle(441,166,491,215,noir).draw_rectangle(441,217,491,267,noir).draw_rectangle(441,269,491,319,noir).draw_rectangle(441,321,491,371,noir).draw_rectangle(441,373,491,423,noir).draw_rectangle(441,425,491,475,noir).draw_rectangle(443,115,489,161,blanc).draw_rectangle(443,168,489,213,rouge).draw_rectangle(443,219,489,265,vert).draw_rectangle(443,271,489,317,bleu).draw_rectangle(443,323,489,369,jaune).draw_rectangle(443,375,489,421,rose).draw_rectangle(443,427,489,473,cyan).draw_rectangle(410,10,490,40,vertmenu).draw_text(420,10,"Menu",blanc,vertmenu,1,30);

    lettreE.draw_text(110,10,"Mode Lettre",blanc,marron,1,40).draw_rectangle(438,58,494,478,noir).draw_rectangle(440,60,492,476,blanc).draw_rectangle(441,61,491,111,noir).draw_rectangle(441,113,491,163,noir).draw_rectangle(441,166,491,215,noir).draw_rectangle(441,217,491,267,noir).draw_rectangle(441,269,491,319,noir).draw_rectangle(441,321,491,371,noir).draw_rectangle(441,373,491,423,noir).draw_rectangle(441,425,491,475,noir).draw_rectangle(443,115,489,161,blanc).draw_rectangle(443,168,489,213,rouge).draw_rectangle(443,219,489,265,vert).draw_rectangle(443,271,489,317,bleu).draw_rectangle(443,323,489,369,jaune).draw_rectangle(443,375,489,421,rose).draw_rectangle(443,427,489,473,cyan).draw_rectangle(410,10,490,40,vertmenu).draw_text(420,10,"Menu",blanc,vertmenu,1,30);
	lettre.draw_text(50,10,"Mode Saisie Lettre",blanc,marron,1,40).draw_rectangle(410,10,490,40,vertmenu).draw_text(420,10,"Menu",blanc,vertmenu,1,30);
    /*Création de la fenetre*/
    CImgDisplay fenetre(presentation, "Courbe de Bezier"); 


    minMax( N, x, & xMin, & xMax ) ;
    minMax( N, y, & yMin, & yMax ) ;
    dx = xMax - xMin ;
    dy = yMax - yMin ;
    
    float max_x, max_y, min_x, min_y;
    initImg(&img, imgL, imgC ) ;

    //Nos point de controle sous forme de liste chainée 
    
    /* Boucle infini */
    int n=1;
	while(!fenetre.is_closed()){
		fenetre.wait();
		if(n==1 && fenetre.button() && fenetre.mouse_y()>=350 && fenetre.mouse_y()<=420 && fenetre.mouse_x()>=128 && fenetre.mouse_x()<=384){
			fenetre.display(accueil);
			n=2;			
		}
		if(n==2){
			if(fenetre.button() && fenetre.mouse_y()>=228 && fenetre.mouse_y()<=256 && fenetre.mouse_x()>=91 && fenetre.mouse_x()<=166){//1
				n=3;
				zoom = 1;
				T_point* tete = NULL;
				insererEnQueue(256,256,&tete);
				fenetre.display(img);
				ControlPointPrint(&img, tete);
				calcCourbe(x, y, tete);
				dessinBezier(&zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t);
				fenetre.display(img);
				while(!fenetre.is_closed() and n==3){	
					event(&fenetre, &zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t, &tete);
					if(n==3 && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
						fenetre.display(accueil);
						initImg(&img, imgL, imgC ) ;
						n=2;
					}
				}
			}
			if(fenetre.button() && fenetre.mouse_y()>=268 && fenetre.mouse_y()<=296 && fenetre.mouse_x()>=83 && fenetre.mouse_x()<=170){//2
				n=3;
				T_point* tete = NULL;
				insererEnQueue(170,256,&tete);
				insererEnQueue(340,256,&tete);
				fenetre.display(img);
				ControlPointPrint(&img, tete);
				calcCourbe(x, y, tete);
				dessinBezier(&zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t);
				fenetre.display(img);
				while(!fenetre.is_closed() and n==3){	
					event(&fenetre, &zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t, &tete);
					if(n==3 && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
						fenetre.display(accueil);
						initImg(&img, imgL, imgC ) ;
						n=2;
					}
				}
			}
			if(fenetre.button() && fenetre.mouse_y()>=308 && fenetre.mouse_y()<=336 && fenetre.mouse_x()>=83 && fenetre.mouse_x()<=170){//3
				n=3;
				T_point* tete = NULL;
				insererEnQueue(256,170,&tete);
				insererEnQueue(170,340,&tete);
				insererEnQueue(340,340,&tete);
				fenetre.display(img);
				ControlPointPrint(&img, tete);
				calcCourbe(x, y, tete);
				dessinBezier(&zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t);
				fenetre.display(img);
				while(!fenetre.is_closed() and n==3){
					event(&fenetre, &zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t, &tete);
					if(n==3 && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
						fenetre.display(accueil);
						initImg(&img, imgL, imgC ) ;
						n=2;
					}
				}
			}
			if(fenetre.button() && fenetre.mouse_y()>=348 && fenetre.mouse_y()<=376 && fenetre.mouse_x()>=83 && fenetre.mouse_x()<=170){//4
				n=3;
				T_point* tete = NULL;
				insererEnQueue(170,170,&tete);
				insererEnQueue(170,340,&tete);
				insererEnQueue(340,340,&tete);
				insererEnQueue(340,170,&tete);
				fenetre.display(img);
				ControlPointPrint(&img, tete);
				calcCourbe(x, y, tete);
				dessinBezier(&zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t);
				fenetre.display(img);
				while(!fenetre.is_closed() and n==3){	
					event(&fenetre, &zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t, &tete);
					if(n==3 && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
						fenetre.display(accueil);
						initImg(&img, imgL, imgC ) ;
						n=2;
					}
				}
			}
			if(fenetre.button() && fenetre.mouse_y()>=388 && fenetre.mouse_y()<=416 && fenetre.mouse_x()>=83 && fenetre.mouse_x()<=170){//5
				n=3;
				T_point* tete = NULL;
				insererEnQueue(170,170,&tete);
				insererEnQueue(170,340,&tete);
				insererEnQueue(256,256,&tete);
				insererEnQueue(340,340,&tete);
				insererEnQueue(340,170,&tete);
				fenetre.display(img);
				ControlPointPrint(&img, tete);
				calcCourbe(x, y, tete);
				dessinBezier(&zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t);
				fenetre.display(img);
				while(!fenetre.is_closed() and n==3){	
					event(&fenetre, &zoom, &img, N, imgL, imgC, &imgC2, &imgL2,x, y, t, &tete);
					if(n==3 && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
						fenetre.display(accueil);
						initImg(&img, imgL, imgC ) ;
						n=2;
					}
				}
			}
			if(fenetre.button() && fenetre.mouse_y()>=428 && fenetre.mouse_y()<=486 && fenetre.mouse_x()>=83 && fenetre.mouse_x()<=169){//6
				n=3;
				T_point* tete = NULL;
				insererEnQueue(170,170,&tete);
				insererEnQueue(170,340,&tete);
				insererEnQueue(256,340,&tete);
				insererEnQueue(340,340,&tete);
				insererEnQueue(340,170,&tete);
				insererEnQueue(256,170,&tete);
				fenetre.display(img);
				ControlPointPrint(&img, tete);
				calcCourbe(x, y, tete);
				dessinBezier(&zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t);
				fenetre.display(img);
				while(!fenetre.is_closed() and n==3){	
					event(&fenetre, &zoom, &img, N, imgL, imgC, &imgC2, &imgL2, x, y, t, &tete);
					if(n==3 && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
						fenetre.display(accueil);
						initImg(&img, imgL, imgC ) ;
						n=2;
					}
				}
			}
			if(fenetre.button() && fenetre.mouse_y()>=229 && fenetre.mouse_y()<=277 && fenetre.mouse_x()>=332 && fenetre.mouse_x()<=369){//B
				traceB(&lettreB,noir,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=289 && fenetre.mouse_y()<=337 && fenetre.mouse_x()>=332 && fenetre.mouse_x()<=369){//U
				traceU(&lettreU,noir,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=349 && fenetre.mouse_y()<=397 && fenetre.mouse_x()>=332 && fenetre.mouse_x()<=369){//D
				traceD(&lettreD,noir,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=409 && fenetre.mouse_y()<=457 && fenetre.mouse_x()>=332 && fenetre.mouse_x()<=369){//E
				traceE(&lettreE,noir,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=482 && fenetre.mouse_y()<=512 && fenetre.mouse_x()>=206 && fenetre.mouse_x()<=298){
				fenetre.close();
			}
			if(fenetre.button() && fenetre.mouse_y()>=220 && fenetre.mouse_y()<=476 && fenetre.mouse_x()>=430 && fenetre.mouse_x()<=467){
				lettre.draw_text(90,200,"Veuillez saisir le mot",blanc,marron,1,40).draw_text(125,300,"dans la console.",blanc,marron,1,40);
				fenetre.display(lettre);
				cout<<"Veuillez saisir le mot dans la console : ";
				string mot;
				int coeff = 0;
				cin>>mot;
				lettre.draw_rectangle(0,100,512,512,marron);
				for(int i=0;i<=mot.size();i++){
					if(mot[i]=='b'){
						if(mot[i+1]=='b'){
							traceB(&lettre,blanc,coeff);coeff+=48;
						}
						else if(mot[i+1]=='u'){
							traceB(&lettre,blanc,coeff);coeff+=47;
						}
						else if(mot[i+1]=='d'){
							traceB(&lettre,blanc,coeff);coeff+=47;
						}
						else if(mot[i+1]=='e'){
							traceB(&lettre,blanc,coeff);coeff+=35;
						}else{
							traceB(&lettre,blanc,coeff);
						}
					}
					if(mot[i]=='u'){
						if(mot[i+1]=='b'){
							traceU(&lettre,blanc,coeff);coeff+=85;
						}
						else if(mot[i+1]=='u'){
							traceU(&lettre,blanc,coeff);coeff+=84;
						}
						else if(mot[i+1]=='d'){
							traceU(&lettre,blanc,coeff);coeff+=85;
						}
						else if(mot[i+1]=='e'){
							traceU(&lettre,blanc,coeff);coeff+=74;
						}else{
							traceU(&lettre,blanc,coeff);
						}
					}
					if(mot[i]=='d'){
						if(mot[i+1]=='b'){
							traceD(&lettre,blanc,coeff);coeff+=42;
						}
						else if(mot[i+1]=='u'){
							traceD(&lettre,blanc,coeff);coeff+=40;
						}
						else if(mot[i+1]=='d'){
							traceD(&lettre,blanc,coeff);coeff+=37;
						}
						else if(mot[i+1]=='e'){
							traceD(&lettre,blanc,coeff);coeff+=31;
						}else{
							traceD(&lettre,blanc,coeff);
						}
					}
					if(mot[i]=='e'){
						if(mot[i+1]=='b'){
							traceE(&lettre,blanc,coeff);coeff+=85;
						}
						else if(mot[i+1]=='u'){
							traceE(&lettre,blanc,coeff);coeff+=85;
						}
						else if(mot[i+1]=='d'){
							traceE(&lettre,blanc,coeff);coeff+=80;
						}
						else if(mot[i+1]=='e'){
							traceE(&lettre,blanc,coeff);coeff+=74;
						}else{
							traceE(&lettre,blanc,coeff);
						}
					}
				}
				fenetre.display(lettre);
				n=8;
			}
		}
		if(n==4){
			if(fenetre.button() && fenetre.mouse_y()>=63 && fenetre.mouse_y()<=109 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,noir,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=115 && fenetre.mouse_y()<=161 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,blanc,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=168 && fenetre.mouse_y()<=213 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,rouge,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=219 && fenetre.mouse_y()<=265 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,vert,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=271 && fenetre.mouse_y()<=317 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,bleu,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=323 && fenetre.mouse_y()<=369 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,jaune,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=375 && fenetre.mouse_y()<=421 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,rose,200);
				fenetre.display(lettreB);
				n=4;
			}
			if(fenetre.button() && fenetre.mouse_y()>=427 && fenetre.mouse_y()<=473 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceB(&lettreB,cyan,200);
				fenetre.display(lettreB);
				n=4;
			}
		}
		if(n==5){
			if(fenetre.button() && fenetre.mouse_y()>=63 && fenetre.mouse_y()<=109 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,noir,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=115 && fenetre.mouse_y()<=161 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,blanc,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=168 && fenetre.mouse_y()<=213 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,rouge,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=219 && fenetre.mouse_y()<=265 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,vert,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=271 && fenetre.mouse_y()<=317 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,bleu,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=323 && fenetre.mouse_y()<=369 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,jaune,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=375 && fenetre.mouse_y()<=421 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,rose,200);
				fenetre.display(lettreU);
				n=5;
			}
			if(fenetre.button() && fenetre.mouse_y()>=427 && fenetre.mouse_y()<=473 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceU(&lettreU,cyan,200);
				fenetre.display(lettreU);
				n=5;
			}
		}
		if(n==6){
			if(fenetre.button() && fenetre.mouse_y()>=63 && fenetre.mouse_y()<=109 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,noir,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=115 && fenetre.mouse_y()<=161 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,blanc,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=168 && fenetre.mouse_y()<=213 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,rouge,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=219 && fenetre.mouse_y()<=265 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,vert,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=271 && fenetre.mouse_y()<=317 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,bleu,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=323 && fenetre.mouse_y()<=369 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,jaune,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=375 && fenetre.mouse_y()<=421 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,rose,200);
				fenetre.display(lettreD);
				n=6;
			}
			if(fenetre.button() && fenetre.mouse_y()>=427 && fenetre.mouse_y()<=473 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceD(&lettreD,cyan,200);
				fenetre.display(lettreD);
				n=6;
			}
		}
		if(n==7){
			if(fenetre.button() && fenetre.mouse_y()>=63 && fenetre.mouse_y()<=109 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,noir,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=115 && fenetre.mouse_y()<=161 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,blanc,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=168 && fenetre.mouse_y()<=213 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,rouge,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=219 && fenetre.mouse_y()<=265 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,vert,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=271 && fenetre.mouse_y()<=317 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,bleu,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=323 && fenetre.mouse_y()<=369 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,jaune,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=375 && fenetre.mouse_y()<=421 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,rose,200);
				fenetre.display(lettreE);
				n=7;
			}
			if(fenetre.button() && fenetre.mouse_y()>=427 && fenetre.mouse_y()<=473 && fenetre.mouse_x()>=443 && fenetre.mouse_x()<=489){
				traceE(&lettreE,cyan,200);
				fenetre.display(lettreE);
				n=7;
			}
		}
		if((n==4 or n==5 or n==6 or n==7 or n==8) && fenetre.button() && fenetre.mouse_y()>=10 && fenetre.mouse_y()<=40 && fenetre.mouse_x()>=410 && fenetre.mouse_x()<=490){
			fenetre.display(accueil);
			lettre.draw_rectangle(0,100,512,512,marron);
			n=2;
		}		
	}
}