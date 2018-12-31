#include "chiffresDroits.h"
#include "spi.h"
#include "usart.h"


// on fait un tableau de cosinus et de sinus pour chaque LED
// Sin(pi/2-theta)=cos(theta) => 

// premier element : sin(45) de moins 3 en moins 3 jusqu'à 0 (dernier élement) sin(0)
// pour le cosinus : inverse premier element cos(0) et dernier element cos(45)
/*
  uint16_t tab1posy[16]={135,90,85,79,74,68,61,55,48,42,35,28,21,14,7,0};
  uint16_t tab2posy[16]={185,124,116,109,108,93,84,75,66,57,48,38,29,19,10,0};
  uint16_t tab3posy[16]={235,157,148,138,128,118,107,96,84,73,61,49,37,25,12,0};
  uint16_t tab4posy[16]={285,191,179,168,155,143,129,116,102,88,74,59,45,30,15,0};
  uint16_t tab5posy[16]={335,224,211,197,182,168,152,136,120,104,87,70,52,35,18,0};
  uint16_t tab6posy[16]={385,258,242,226,210,193,175,157,138,118,100,80,60,40,20,0};
  uint16_t tab7posy[16]={435,291,274,256,237,218,197,177,156,134,113,90,68,45,23,0};
  uint16_t tab8posy[16]={485,325,305,285,264,243,220,197,174,150,126,101,76,51,25,0};
  uint16_t tab9posy[16]={535,358,337,314,291,268,243,218,192,165,138,111,84,56,28,0};
  uint16_t tab10posy[16]={585,391,368,344,319,293,265,238,201,181,151,122,92,61,31,0};
  uint16_t tab11posy[16]={635,425,400,373,346,318,288,258,228,196,164,132,99,66,33,0};
  uint16_t tab12posy[16]={685,458,431,403,373,343,311,275,245,212,172,142,107,72,36,0};
  uint16_t tab13posy[16]={735,492,463,432,400,368,334,299,263,227,190,153,115,77,38,0};
  uint16_t tab14posy[16]={785,525,494,461,428,393,356,319,281,243,203,163,123,82,41,0};
  uint16_t tab15posy[16]={835,559,526,491,455,418,379,340,299,258,216,174,131,87,44,0};
  uint16_t tab16posy[16]={885,592,557,520,482,443,402,360,317,273,229,184,138,93,46,0};
*/

// numero tab correspond au numéro du cadran
// de gauche à droite correspond au LED de la plus petite distance à la plus grande distance
/*
  uint16_t tab0posy[16]={135,185,235,285,335,385,435,485,535,585,635,685,735,785,835,885};
  uint16_t tab1posy[16]={90,124,157,191,224,258,291,325,358,391,425,458,492,525,559,592};
  uint16_t tab2posy[16]={85,116,148,179,211,242,274,305,337,368,400,431,463,494,526,557};
  uint16_t tab3posy[16]={79,109,138,168,196,226,256,285,314,344,373,403,432,461,491,520};
  uint16_t tab4posy[16]={74,108,128,155,182,210,237,264,291,319,346,373,400,428,455,482};
  uint16_t tab5posy[16]={68,93,118,143,168,193,218,243,268,293,318,343,368,393,418,443};
  uint16_t tab6posy[16]={61,84,107,129,152,175,197,220,243,265,288,311,334,356,379,402};
  uint16_t tab7posy[16]={55,75,96,116,136,157,177,197,218,238,258,275,299,319,340,360};
  uint16_t tab8posy[16]={48,66,84,102,120,138,156,174,192,201,228,245,263,281,299,317};
  uint16_t tab9posy[16]={42,57,73,88,104,118,134,150,165,181,196,212,227,243,258,273};
  uint16_t tab10posy[16]={35,48,61,74,87,100,113,126,138,151,164,172,190,203,216,229};
  uint16_t tab11posy[16]={28,38,49,59,70,80,90,101,111,122,132,142,153,163,174,184};
  uint16_t tab12posy[16]={21,29,37,45,52,60,68,76,84,92,99,107,115,123,131,138};
  uint16_t tab13posy[16]={14,19,25,30,35,40,45,51,56,61,66,72,77,82,87,93};
  uint16_t tab14posy[16]={7,10,12,15,18,20,23,25,28,31,33,36,38,41,44,46};
  uint16_t tab15posy[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
*/

//bons numeros
/*uint16_t tab0posy[16]={135,185,235,285,335,385,435,485,535,585,635,685,735,785,835,885};
  uint16_t tab1posy[16]={134,184,234,283,333,383,433,482,532,582,632,681,731,781,830,880};
  uint16_t tab2posy[16]={132,181,230,279,328,377,425,474,523,572,621,670,719,768,817,866};
  uint16_t tab3posy[16]={128,176,223,271,319,366,414,461,509,556,604,651,699,747,794,842};
  uint16_t tab4posy[16]={123,169,215,260,306,352,397,443,489,534,580,626,671,717,763,808};
  uint16_t tab5posy[16]={117,160,204,247,290,333,377,420,463,507,550,593,637,680,723,766};
  uint16_t tab6posy[16]={109,150,190,231,271,311,352,392,433,473,514,554,595,635,676,716};
  uint16_t tab7posy[16]={100,137,175,212,249,286,323,360,398,435,472,509,546,583,621,658};
  uint16_t tab8posy[16]={90,124,157,191,224,258,291,325,358,391,425,458,492,525,559,592};
  uint16_t tab9posy[16]={79,109,138,168,197,226,256,285,314,344,373,403,432,461,491,520};
  uint16_t tab10posy[16]={68,93,118,143,168,193,218,243,268,293,318,343,368,393,418,443};
  uint16_t tab11posy[16]={55,75,96,116,136,157,177,197,218,238,258,279,299,319,340,360};
  uint16_t tab12posy[16]={42,57,73,88,104,119,134,150,165,181,196,212,227,243,258,273};
  uint16_t tab13posy[16]={28,38,49,59,70,80,90,101,111,122,132,142,153,163,174,184};
  uint16_t tab14posy[16]={14,19,25,30,35,40,45,51,56,61,66,72,77,82,87,93};
  uint16_t tab15posy[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};*/

//tableau de tableau representant les positions des leds en y poue chaque cadran
//une ligne represente la position des leds dans un cadran
//la premiere ligne represente la position des leds dans le cadran 0
//de gauche a droite se trouve la position des leds du plus proche du centre au plus eloigne du centre
//tabPosy[ligne][colonne]
//pour avoir les positions en x il suffis de lire 
uint16_t tabPosy [16][16]={{135,185,235,285,335,385,435,485,535,585,635,685,735,785,835,885},
			   {134,184,234,283,333,383,433,482,532,582,632,681,731,781,830,880},
			   {132,181,230,279,328,377,425,474,523,572,621,670,719,768,817,866},
			   {128,176,223,271,319,366,414,461,509,556,604,651,699,747,794,842},
			   {123,169,215,260,306,352,397,443,489,534,580,626,671,717,763,808},
			   {117,160,204,247,290,333,377,420,463,507,550,593,637,680,723,766},
			   {109,150,190,231,271,311,352,392,433,473,514,554,595,635,676,716},
			   {100,137,175,212,249,286,323,360,398,435,472,509,546,583,621,658},
			   {90,124,157,191,224,258,291,325,358,391,425,458,492,525,559,592},
			   {79,109,138,168,197,226,256,285,314,344,373,403,432,461,491,520},
			   {68,93,118,143,168,193,218,243,268,293,318,343,368,393,418,443},
			   {55,75,96,116,136,157,177,197,218,238,258,279,299,319,340,360},
			   {42,57,73,88,104,119,134,150,165,181,196,212,227,243,258,273},
			   {28,38,49,59,70,80,90,101,111,122,132,142,153,163,174,184},
			   {14,19,25,30,35,40,45,51,56,61,66,72,77,82,87,93},
			   {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

//int16_t tabchiffreunx[12] = {135,245,385,435,435,400,145,135,135,135,135,135};
//int16_t tabchiffreuny[12] = {535,535,535,535,185,185,185,185,335,475,500,535};

// definition du chiffre 1
//positifs
int16_t tabchiffre1x[12] = {35,245,385,385,485,485,135,135,250,250,110,35};
int16_t tabchiffre1y[12] = {535,775,775,135,135,35,35,135,135,635,475,535};
//negatifs
//int16_t tabchiffre1xneg[12] = {-565,-355,-215,-215,-115,-115,-465,-465,-350,-350,-490,-565};
//int16_t tabchiffre1yneg[12] = {-365,-125,-125,-765,-765,-865,-865,-765,-765,-265,-425,-365};

// definition du chiffre 2
//positifs
int16_t tabchiffre2x[25] = {135,185,245,335,390,460,505,510,485,435,255,535,535,135,135,235,345,385,390,375,330,275,235,205,135};
int16_t tabchiffre2y[25] = {635,710,735,735,730,685,635,535,450,360,185,185,85,85,185,285,435,490,585,605,635,635,610,565,635};
//negatifs
//int16_t tabchiffre2xneg[25] = {-540,-490,-430,-340,-285,-215,-170,-165,-190,-240,-420,-140,-140,-540,-540,-440,-330,-290,-285,-300,-345,-400,-440,-470,-540};//-675
//int16_t tabchiffre2yneg[25] = {-165,-90,-65,-65,-70,-115,-165,-265,-350,-440,-615,-615,-715,-715,-615,-515,-365,-310,-215,-195,-165,-165,-190,-235,-165};//-800

// definition du chiffre 3
//positifs
int16_t tabchiffre3x[37] = {135,190,265,370,435,485,485,475, 410,480,505,535,535,485,385,285,210,160,235,285,335,385,125,435,430,395,325,325,370,385,385,360,335,285,235,195,135};
int16_t tabchiffre3y[37] = {635,710,735,735,710,635,535,485,435,405,335,285,185,95,50,35,50,120,185,145,140,145,185,235,285,335,385,440,485,535,585,605,630,630,605,560,635};
//negatifs
//int16_t tabchiffre3xneg[37] = {};//-675
//int16_t tabchiffre3yneg[37] = {};//-800

//pointeurs vers le chiffre voulu
int16_t *pchiffrex1;
int16_t *pchiffrey1;
int16_t *pchiffrex2;
int16_t *pchiffrey2;

/*int16_t *pchiffrex1neg;
int16_t *pchiffrey1neg;
int16_t *pchiffrex2neg;
int16_t *pchiffrey2neg;*/

int j=0;

uint16_t led[60];

void afficheHeure(uint8_t numero_cadran)
{
  if(j==0)
    {
      chiffre(2,3);
      j++;
    }
  allumeLed(led[numero_cadran]);
}

//calcule en decimal les leds a allumer dans chaque cadran pour le chiffre donnee dans le bon quart d'horloge
//(quart=0: en haut a droite, quart=1: en bas a droite, quart=2: en bas a gauche, quart=3: en haut a gauche)
void chiffre(uint8_t chiffre,uint8_t quart)
{
  //alloue la memoire pour les tableaux contenant respectivement les coeff directeurs des droites et les ordonnees a l'origine
  //int taba[tailleTableau];
  //int tabb[tailleTableau];
  //pointeur vers le debut des tableaux des droites
  int *ptabaSauvegarde =NULL;
  ptabaSauvegarde = malloc(24*sizeof(int));
  int *ptabbSauvegarde = NULL;
  ptabbSauvegarde =  malloc(24*sizeof(int));
  //tableau contenant des 1 ou des 0 suivant si la droite est verticale ou non, donc suivant si le coeff directeur est infini ou non
  //uint8_t coeffEstNull[tailleTableau];
  uint8_t *pcoeffEstNullSauvegarde = NULL;
  pcoeffEstNullSauvegarde = malloc(24*sizeof(uint8_t));
  //pointeurs vers les tableaux qui vont être modifiés au cours du programme pour parcourir le tableau
  int *ptaba = ptabaSauvegarde;
  int *ptabb = ptabbSauvegarde;
  uint8_t *pcoeffEstNull = pcoeffEstNullSauvegarde;
  
  uint8_t tailleTableau;
  tailleTableau = miseAZeroPointeurs(chiffre,ptaba, ptabb, pcoeffEstNull,ptabaSauvegarde,ptabbSauvegarde,pcoeffEstNullSauvegarde);

  uint8_t tempsLed[16];
  
  if(quart==0)
    {
      calculDroites(pchiffrex1,pchiffrex2, pchiffrey1,pchiffrey2,pcoeffEstNull, ptaba, ptabb,tailleTableau,0,0);
      for(int h=0;h<=15;h++)//pour tous les cadrans
	{
	  for(int i=0;i<16;i++)//pour toutes les leds
	    {
	      miseAZeroPointeurs(chiffre,ptaba, ptabb, pcoeffEstNull,ptabaSauvegarde,ptabbSauvegarde,pcoeffEstNullSauvegarde);
	      tempsLed[i]=calculLedAllume(ptaba, ptabb,tabPosy[15-h][i], tabPosy[h][i],pchiffrex1,pchiffrex2 ,pchiffrey1, pchiffrey2,pcoeffEstNull,tailleTableau,0,0);
	    }
	  led[h]=convertToDecimal(tempsLed);
	}
    }
  else if(quart==1)
    {
      calculDroites(pchiffrex1,pchiffrex2, pchiffrey1,pchiffrey2,pcoeffEstNull, ptaba, ptabb,tailleTableau,0,800);
      for(int h=16;h<=30;h++)
	{
	  for(int i=0;i<16;i++)
	    {
	      miseAZeroPointeurs(chiffre,ptaba, ptabb, pcoeffEstNull,ptabaSauvegarde,ptabbSauvegarde,pcoeffEstNullSauvegarde);
	      tempsLed[i]=calculLedAllume(ptaba, ptabb,tabPosy[h-16][i],tabPosy[30-h][i]*(-1),pchiffrex1, pchiffrex2,pchiffrey1, pchiffrey2,pcoeffEstNull,tailleTableau,0,810);
	    }
	  led[h]=convertToDecimal(tempsLed);
	}
    }
  else if (quart==2)
    {
      calculDroites(pchiffrex1,pchiffrex2, pchiffrey1,pchiffrey2,pcoeffEstNull, ptaba, ptabb,tailleTableau,675,800);
      for(int h=31;h<=45;h++)
	{
	  for(int i=0;i<16;i++)
	    {
	      miseAZeroPointeurs(chiffre,ptaba, ptabb, pcoeffEstNull,ptabaSauvegarde,ptabbSauvegarde,pcoeffEstNullSauvegarde);
	      tempsLed[i]=calculLedAllume(ptaba, ptabb,tabPosy[45-h][i]*(-1), tabPosy[h-31][i]*(-1),pchiffrex1, pchiffrex2,pchiffrey1, pchiffrey2,pcoeffEstNull,tailleTableau,675,800);
	    }
	  led[h]=convertToDecimal(tempsLed);
	}
    }
  else if(quart==3)
    {
      calculDroites(pchiffrex1,pchiffrex2, pchiffrey1,pchiffrey2,pcoeffEstNull, ptaba, ptabb,tailleTableau,675,0);
      for(int h= 46;h<=59;h++)
	{
	  for(int i=0;i<16;i++)
	    {
	      miseAZeroPointeurs(chiffre,ptaba, ptabb, pcoeffEstNull,ptabaSauvegarde,ptabbSauvegarde,pcoeffEstNullSauvegarde);
	      tempsLed[i]=calculLedAllume(ptaba, ptabb, tabPosy[h-46][i]*(-1), tabPosy[59-h][i],pchiffrex1,pchiffrex2, pchiffrey1, pchiffrey2,pcoeffEstNull,tailleTableau,675,0);
	    }
	  led[h]=convertToDecimal(tempsLed);
	}
    }
  free(ptabaSauvegarde);
  free(ptabbSauvegarde);
  free(pcoeffEstNullSauvegarde);
}


//calcule si une led doit etre alumee ou non
//pour cela, calcule si la position de la led se trouve a l'interieur du chiffre voulu
// taba : tableau contenant tous les coeffs dirrecteur du chiffre
// tabb : tableau contenant toutes les coordonnee a l'origine des droites du chiffre
// posLedx et posLedy : la position de la led en x et y que l'on souhaite allumer ou eteindre
// tabchiffrex tabchiffrey : tableau representant le chiffre que l'on veut afficher
// estNull :  pointeur vers le tableau représentant si le coeff des droites et null ou pas, donc si la droite est verticale ou pas
uint8_t calculLedAllume(int *taba,int *tabb, uint16_t posLedx, uint16_t posLedy,int16_t *tabchiffrex1,int16_t *tabchiffrex2 ,int16_t *tabchiffrey1, int16_t *tabchiffrey2, uint8_t *estNull, uint8_t tailleTabDroite, uint16_t moinsX, uint16_t moinsY)
{
  uint8_t nbDroiteTraverse = 0;
  uint16_t ycalcule;
  uint16_t plusGrandy;
  uint16_t plusPetity;
  uint16_t plusGrandx;
  uint16_t plusPetitx;
  for(int j=0;j<tailleTabDroite;j++)
    {
      //calcule quelle sont les bornes max et min de la droite pour x et y
      if(*tabchiffrey1-moinsY > *tabchiffrey2-moinsY)
	{
	  plusGrandy=*tabchiffrey1-moinsY;
	  plusPetity=*tabchiffrey2-moinsY;
	}
      else
	{
	  plusGrandy=*tabchiffrey2-moinsY;
	  plusPetity=*tabchiffrey1-moinsY;
	}
      if(*tabchiffrex1-moinsX >*tabchiffrex2-moinsX)
	{
	  plusGrandx=*tabchiffrex1-moinsX;
	  plusPetitx=*tabchiffrex2-moinsX;
	}
      else
	{
	  plusGrandx=*tabchiffrex2-moinsX;
	  plusPetitx=*tabchiffrex1-moinsX;
	}
      
      //si le coeff de la droite est nul (la droite est vertivale)
      if(*estNull==1){
	if(*tabb==posLedx && posLedy<=plusGrandy && posLedy>=plusPetity )
	  {
	    return 1;
	  }
      }
      //sinon, on peut utiliser la formule y=ax+b et on compte combien de fois on traverse une droite en montant a partir de la led
      else{
	if(posLedx<=plusGrandx && posLedx>=plusPetitx)
	  {
	    ycalcule = posLedx*(*taba)+*tabb;
	    if(ycalcule>=posLedy*10 )
	      {
		nbDroiteTraverse++;
	      }
	  }
      }
      estNull++;
      taba++;
      tabb++;
      tabchiffrex1++;
      tabchiffrex2++;
      tabchiffrey1++;
      tabchiffrey2++;
    }
  //si le nombre de droites traversees est pair, la led n'est pas dans la forme du chiffre
  if(nbDroiteTraverse%2==0)
    {
      return 0;
    }
  //sinon le nombre de droites traversees est impair, la led est dans la forme du chiffre
  else
    {
      return 1;
    }
}

//initialise les pointeurs vers les bons tabeaux et renvoie la taille que le tableau des droites doit avoir
uint8_t miseAZeroPointeurs(uint8_t chiffre,int *ptaba, int *ptabb, uint8_t * pcoeffEstNull, int *ptabaSauv, int *ptabbSauv, uint8_t *pcoeffEstNullSauv)
{

  ptaba = ptabaSauv;
  ptabb = ptabbSauv;
  pcoeffEstNull = pcoeffEstNullSauv;

  uint8_t taille=0;
  
  if(chiffre==1)
    {
      pchiffrex1 = &tabchiffre1x[0];
      pchiffrey1 = &tabchiffre1y[0];
      pchiffrex2 = &tabchiffre1x[1];
      pchiffrey2 = &tabchiffre1y[1];

      /* pchiffrex1neg = &tabchiffre1xneg[0];
      pchiffrey1neg = &tabchiffre1yneg[0];
      pchiffrex2neg = &tabchiffre1xneg[1];
      pchiffrey2neg = &tabchiffre1yneg[1];*/
      
      taille = 11;
    }
  else if(chiffre==2)
    {
      pchiffrex1 = &tabchiffre2x[0];
      pchiffrey1 = &tabchiffre2y[0];
      pchiffrex2 = &tabchiffre2x[1];
      pchiffrey2 = &tabchiffre2y[1];

      /*pchiffrex1neg = &tabchiffre2xneg[0];
      pchiffrey1neg = &tabchiffre2yneg[0];
      pchiffrex2neg = &tabchiffre2xneg[1];
      pchiffrey2neg = &tabchiffre2yneg[1];*/
      taille = 24;
    }
  else if(chiffre==3)
    {
      pchiffrex1 = &tabchiffre3x[0];
      pchiffrey1 = &tabchiffre3y[0];
      pchiffrex2 = &tabchiffre3x[1];
      pchiffrey2 = &tabchiffre3y[1];

      /*pchiffrex1neg = &tabchiffre2xneg[0];
      pchiffrey1neg = &tabchiffre2yneg[0];
      pchiffrex2neg = &tabchiffre2xneg[1];
      pchiffrey2neg = &tabchiffre2yneg[1];*/
      taille = 36;
  }
  return taille;
}

//convertit en décimal un tableau de taille 16 remplis de 1 et de 0
uint16_t convertToDecimal(uint8_t tabled[16])
{
  uint16_t decimal=0;
  for(int i = 0;i<16;i++)
    {
      if(tabled[i]==1){
	decimal |= (1<<i);
      }
    }
  return decimal;
}

void calculDroites(int16_t *pchiffrex1,int16_t *pchiffrex2,int16_t *pchiffrey1,int16_t *pchiffrey2,uint8_t *pCoeffNull, int *ptaba, int *ptabb, uint8_t tailleTabDroite, uint16_t moinsX, uint16_t moinsY)
{
  for(int i=0;i<tailleTabDroite;i++)
    {	
      *ptaba = calculCoeffDirect(*pchiffrex1-moinsX,*pchiffrex2-moinsX,*pchiffrey1-moinsY,*pchiffrey2-moinsY,pCoeffNull);
      *ptabb = calculOrdonOrigin(*pchiffrex1-moinsX,*pchiffrey1-moinsY,*ptaba, pCoeffNull);
         
      pCoeffNull++;
      ptaba++;
      ptabb++;
      pchiffrex1++;
      pchiffrey1++;
      pchiffrex2++;
      pchiffrey2++;
    }
}

int calculCoeffDirect(int16_t x1,int16_t x2,int16_t y1,int16_t y2,uint8_t *estNull)
{
  int a;
  int denominateur;
  int numerateur;
  if(x1!=x2)
    {
      *estNull = 0;
      numerateur = (y1-y2)*10;
      denominateur = x1-x2;
      a = numerateur/denominateur;
    }
  else
    {
      *estNull = 1;
      a=1000;
    }
  return a;
}
int calculOrdonOrigin(int16_t x,int16_t y,int a,uint8_t *estNull)
{
  int b;
  if(*estNull==0){
    b=y*10-a*x;
  }
  else{
    b= x;
  }
  return b;
}




