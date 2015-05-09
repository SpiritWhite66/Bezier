#include <stdio.h>
#include <iostream>
#include "CImg/CImg.h"
#include <math.h>
#include "ListeChaine.hpp"
using namespace std; 
using namespace cimg_library;

typedef struct S_point T_point; 
void minMax( int N, float * t, float * min, float * max );
void calcCourbe(float * x, float * y, T_point* tete);
void initImg( CImg<unsigned char> * img, int imgL, int imgC );
int triangleP(int n, int k);
float bezierx(float t,T_point* wkt);
float beziery(float t,T_point* wkt);
void traceB(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx);
void traceU(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx);
void traceD(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx);
void traceE(CImg<unsigned char>* lettre,unsigned char* couleur,int coeffx);
void dessinBezier(float * zoom, CImg<unsigned char>* img, int N,int imgL, int imgC, int* imgC2, int* imgL2,float * x, float * y, float * t);
void ControlPointPrint(CImg<unsigned char>* img, T_point *adress);
void event(CImgDisplay* fenetre, float * zoom, CImg<unsigned char>* img, int N,int imgL, int imgC, int* imgC2, int* imgL2,
float * x, float * y, float * t, T_point** tete);
