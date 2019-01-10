#include "chiffresDroits.h"
#include "spi.h"
#include "usart.h"


// premier element : sin(45) de moins 3 en moins 3 jusqu'à 0 (dernier élement) sin(0)
// pour le cosinus : inverse premier element cos(0) et dernier element cos(45)

//tableau de tableau representant les positions des leds en y pour chaque cadran (sin(angle)*dist(centre-led))
//une ligne represente la position des leds dans un cadran
//la premiere ligne represente la position des leds dans le cadran 0
//de gauche a droite se trouve la position des leds du plus proche du centre au plus eloigne du centre
//tabPosy[ligne][colonne]
//pour avoir les positions en x il suffis de lire le tableau de bas en haut car Sin(pi/2-theta)=cos(theta)
uint16_t tabPosy [16][16]={{135,185,235,285,335,385,435,485,535,585,635,685,735,785,835,885},			   {134,184,234,283,333,383,433,482,532,582,632,681,731,781,830,880},			   {132,181,230,279,328,377,425,474,523,572,621,670,719,768,817,866},			   {128,176,223,271,319,366,414,461,509,556,604,651,699,747,794,842},			   {123,169,215,260,306,352,397,443,489,534,580,626,671,717,763,808},			   {117,160,204,247,290,333,377,420,463,507,550,593,637,680,723,766},			   {109,150,190,231,271,311,352,392,433,473,514,554,595,635,676,716},			   {100,137,175,212,249,286,323,360,398,435,472,509,546,583,621,658},			   {90,124,157,191,224,258,291,325,358,391,425,458,492,525,559,592},			   {79,109,138,168,197,226,256,285,314,344,373,403,432,461,491,520},			   {68,93,118,143,168,193,218,243,268,293,318,343,368,393,418,443},			   {55,75,96,116,136,157,177,197,218,238,258,279,299,319,340,360},			   {42,57,73,88,104,119,134,150,165,181,196,212,227,243,258,273},	
{28,38,49,59,70,80,90,101,111,122,132,142,153,163,174,184},
{14,19,25,30,35,40,45,51,56,61,66,72,77,82,87,93},
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};


// definition du chiffre 1
int16_t tabchiffre1x[12] = {35,245,385,385,485,485,135,135,250,250,110,35};
int16_t tabchiffre1y[12] = {535,775,775,135,135,35,35,135,135,635,475,535};

// definition du chiffre 2
int16_t tabchiffre2x[25] = {135,185,245,335,390,460,505,510,485,435,255,535,535,135,135,235,345,385,390,375,330,275,235,205,135};
int16_t tabchiffre2y[25] = {635,710,735,735,730,685,635,535,450,360,185,185,85,85,185,285,435,490,585,605,635,635,610,565,635};

// definition du chiffre 3
int16_t tabchiffre3x[37] = {135,190,265,370,435,485,485,475, 410,480,505,535,535,485,385,285,210,160,235,285,335,385,125,435,430,395,325,325,370,385,385,360,335,285,235,195,135};
int16_t tabchiffre3y[37] = {635,710,735,735,710,635,535,485,435,405,335,285,185,95,50,35,50,120,185,145,140,145,185,235,285,335,385,440,485,535,585,605,630,630,605,560,635};

//definition du chiffre 4
int16_t tabchiffre4x[12]={245,335,195,335,335,460,460,335,335,85,85,245};
int16_t tabchiffre4y[12]={685,685,285,285,385,385,35,35,145,145,185,685};

//definition du chiffre 5
int16_t tabchiffre5x[21]={185,485,485,285,285,385,455,505,505,455,420,345,185,185,285,350,395,355,285,185,185};
int16_t tabchiffre5y[21]={685,685,585,585,435,435,365,290,110,145,90,80,80,180,180,190,255,330,335,335,685};

//definition du chiffre 6
int16_t tabchiffre6x[48]={235,285,355,455,525,555,565,485,445,385,325,285,255,250,255,275,290,310,355,440,490,490,455,390,335,290,275,255,335,430,495,610,585,585,555,490,425,335,255,220,185,175,155,155,160,185,195,235};
int16_t tabchiffre6y[48]={655,710,735,725,610,670,555,555,605,630,610,555,485,425,345,275,230,195,150,145,210,255,310,325,310,230,275,345,390,410,385,325,250,175,110,80,75,80,110,145,190,245,310,385,460,540,610,655};

//definition du chiffre 7
int16_t tabchiffre7x[15]={135,535,390,435,435,335,235,135,235,185,185,285,385,135,135};
int16_t tabchiffre7y[15]={635,635,335,335,235,235,35,35,235,235,335,335,535,535,635};

//definition du chiffre 8
int16_t tabchiffre8x[56]={260,235,185,175,180,195,235,285,385,445,465,470,465,405,485,505,535,540,535,505,485,435,385,285,235,185,145,135,135,145,175,205,260,335,305,285,305,335,360,435,360,335,260,335,385,430,435,430,385,335,285,260,275,285,335,260};
int16_t tabchiffre8y[56]={405,435,485,535,585,635,660,685,685,635,585,535,485,405,385,335,285,235,185,135,85,35,30,35,40,85,135,185,235,285,335,385,405,495,400,535,575,585,575,535,505,495,405,335,325,285,235,185,135,135,160,195,275,305,335,405};

//definition du chiffre 9
int16_t tabchiffre9x[41]={405,335,285,235,185,135,125,125,135,185,285,335,435,475,495,495,445,385,335,260,185,135,205,285,335,385,405,405,400,385,345,305,260,225,225,235,285,335,360,400,405};
int16_t tabchiffre9y[41]={425,390,385,390,405,485,535,585,635,705,740,740,685,635,585,235,135,85,80,85,135,185,260,185,180,205,285,425,535,505,485,485,495,535,585,635,645,635,585,535,425};

//definition du chiffre 0
int16_t tabchiffre0x[33]={385,385,375,335,305,285,245,235,235,245,285,305,345,375,385,485,485,460,435,385,335,285,205,165,135,135,165,235,305,385,460,485,385};
int16_t tabchiffre0y[33]={485,285,335,195,185,195,235,285,485,535,575,585,575,535,485,485,285,185,135,105,85,95,135,185,285,485,585,660,685,660,585,485,485};

//pointeurs vers le chiffre voulu
int16_t *pchiffrex1;
int16_t *pchiffrey1;
int16_t *pchiffrex2;
int16_t *pchiffrey2;

uint8_t heureDixaine=60;
uint8_t heureUnite=60;
uint8_t minuteDixaine=60;
uint8_t minuteUnite=60;

//tableau stockant tous les decimaux pour allumer les bonnes leds dans chaque cadran
uint16_t led[60];

//affiche l'heure voulue et met a jours le tableau de leds quand changement de l'heure
void afficheHeure(uint8_t numero_cadran,uint8_t heure,uint8_t minute,uint8_t sec)
{
    if(heureDixaine!=heure/10)
    {
      heureDixaine = heure/10;

      chiffre(heureDixaine,3);
    }
  if(heureUnite!=heure%10)
    {
      heureUnite = heure%10;
      chiffre(heureUnite,0);
    }
  if(minuteDixaine!=minute/10)
    {
      minuteDixaine = minute/10;
      chiffre(minuteDixaine,2);
    }
  if(minuteUnite!=minute%10)
    {
      minuteUnite = minute%10;
      chiffre(minuteUnite,1);
    }
  if(sec>=numero_cadran)
  {
    allumeLed(led[numero_cadran]+32768);
  }
  else
  {
    allumeLed(led[numero_cadran]);
  }
}

//calcule en decimal les leds a allumer dans chaque cadran pour le chiffre donne dans le bon quart d'horloge
//(quart=0: en haut a droite, quart=1: en bas a droite, quart=2: en bas a gauche, quart=3: en haut a gauche)
void chiffre(uint8_t chiffre,uint8_t quart)
{
  //alloue la memoire pour les tableaux contenant respectivement les coeff directeurs des droites et les ordonnees a l'origine
  //pointeur vers le debut des tableaux des droites
  int *ptabaSauvegarde =NULL;
  ptabaSauvegarde = malloc(56*sizeof(int));//on a max 56 coeffs (chiffre 8)
  int *ptabbSauvegarde = NULL;
  ptabbSauvegarde =  malloc(56*sizeof(int));
  //tableau contenant des 1 ou des 0 suivant si la droite est verticale ou non, donc suivant si le coeff directeur est infini ou non
  uint8_t *pcoeffEstNullSauvegarde = NULL;
  pcoeffEstNullSauvegarde = malloc(56*sizeof(uint8_t));
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
	      tempsLed[i]=calculLedAllume(ptaba, ptabb,tabPosy[45-h][i]*(-1), tabPosy[h-31][i]*(-1),pchiffrex1, pchiffrex2,pchiffrey1, pchiffrey2,pcoeffEstNull,tailleTableau,675,810);
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
  //libere la memoire allouee
  free(ptabaSauvegarde);
  free(ptabbSauvegarde);
  free(pcoeffEstNullSauvegarde);
}


//calcule si une led doit etre alumee ou non
//pour cela, calcule si la position de la led se trouve a l'interieur du chiffre voulu
// taba : tableau contenant tous les coeffs directeur du chiffre
// tabb : tableau contenant toutes les ordonnees a l'origine des droites du chiffre
// posLedx et posLedy : la position de la led en x et y que l'on souhaite allumer ou eteindre, donc dont on souhaite savoir si elle se trouve a l'interieur de la forme du chiffre a afficher
// tabchiffrex tabchiffrey : tableaux representant le chiffre que l'on veut afficher
// estNull :  pointeur vers le tableau représentant si le coeff directeur des droites et null ou pas, donc si la droite est verticale ou pas
// moinsX et moinsY : permet d'avoir les bonnes valeurs de position suivant le quart ou on veut afficher le chiffre
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
      
      //si le coeff de la droite est nul (la droite est verticale)
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
      
      taille = 11;
    }
  else if(chiffre==2)
    {
      pchiffrex1 = &tabchiffre2x[0];
      pchiffrey1 = &tabchiffre2y[0];
      pchiffrex2 = &tabchiffre2x[1];
      pchiffrey2 = &tabchiffre2y[1];

      taille = 24;
    }
  else if(chiffre==3)
    {
      pchiffrex1 = &tabchiffre3x[0];
      pchiffrey1 = &tabchiffre3y[0];
      pchiffrex2 = &tabchiffre3x[1];
      pchiffrey2 = &tabchiffre3y[1];

      taille = 36;
  }
  else if(chiffre==4)
  {
  pchiffrex1 = &tabchiffre4x[0];
      pchiffrey1 = &tabchiffre4y[0];
      pchiffrex2 = &tabchiffre4x[1];
      pchiffrey2 = &tabchiffre4y[1];

      taille = 11;
  }
  else if(chiffre==5)
  {
  pchiffrex1 = &tabchiffre5x[0];
      pchiffrey1 = &tabchiffre5y[0];
      pchiffrex2 = &tabchiffre5x[1];
      pchiffrey2 = &tabchiffre5y[1];

      taille = 20;
  }
  else if(chiffre==6)
  {
  pchiffrex1 = &tabchiffre6x[0];
      pchiffrey1 = &tabchiffre6y[0];
      pchiffrex2 = &tabchiffre6x[1];
      pchiffrey2 = &tabchiffre6y[1];

      taille = 47;
  }
  else if(chiffre==7)
  {
  pchiffrex1 = &tabchiffre7x[0];
      pchiffrey1 = &tabchiffre7y[0];
      pchiffrex2 = &tabchiffre7x[1];
      pchiffrey2 = &tabchiffre7y[1];

      taille = 14;
  }
  else if(chiffre==8)
  {
  pchiffrex1 = &tabchiffre8x[0];
      pchiffrey1 = &tabchiffre8y[0];
      pchiffrex2 = &tabchiffre8x[1];
      pchiffrey2 = &tabchiffre8y[1];

      taille = 55;
  }
  else if(chiffre==9)
  {
  pchiffrex1 = &tabchiffre9x[0];
      pchiffrey1 = &tabchiffre9y[0];
      pchiffrex2 = &tabchiffre9x[1];
      pchiffrey2 = &tabchiffre9y[1];

      taille = 40;
  }
  else if(chiffre==0)
  {
  pchiffrex1 = &tabchiffre0x[0];
      pchiffrey1 = &tabchiffre0y[0];
      pchiffrex2 = &tabchiffre0x[1];
      pchiffrey2 = &tabchiffre0y[1];

      taille = 32;
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

//calcule les tableaux de coeff directeur, d'ordonnees a l'origine et si la droite est verticale ou non
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




