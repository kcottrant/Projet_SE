#include "chiffresDroits.h"
#include "spi.h"
#include "usart.h"
#include <math.h>


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
uint16_t tab0posy[16]={135,185,235,285,335,385,435,485,535,585,635,685,735,785,835,885};
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
uint16_t tab15posy[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};


/*uint16_t tabPosy [16][16]={{135,185,235,285,335,385,435,485,535,585,635,685,735,785,835,885},
  {90,124,157,191,224,258,291,325,358,391,425,458,492,525,559,592},
  {85,116,148,179,211,242,274,305,337,368,400,431,463,494,526,557},
  {79,109,138,168,196,226,256,285,314,344,373,403,432,461,491,520},
  {74,108,128,155,182,210,237,264,291,319,346,373,400,428,455,482},
  {68,93,118,143,168,193,218,243,268,293,318,343,368,393,418,443},
  {61,84,107,129,152,175,197,220,243,265,288,311,334,356,379,402},
  {55,75,96,116,136,157,177,197,218,238,258,275,299,319,340,360},
  {48,66,84,102,120,138,156,174,192,201,228,245,263,281,299,317},
  {42,57,73,88,104,118,134,150,165,181,196,212,227,243,258,273},
  {35,48,61,74,87,100,113,126,138,151,164,172,190,203,216,229},
  {28,38,49,59,70,80,90,101,111,122,132,142,153,163,174,184},
  {21,29,37,45,52,60,68,76,84,92,99,107,115,123,131,138},
  {14,19,25,30,35,40,45,51,56,61,66,72,77,82,87,93},
  {7,10,12,15,18,20,23,25,28,31,33,36,38,41,44,46},
  {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
  };
*/

// definition des chiffres
uint16_t tabchiffreunx[12] = {35,245,385,385,485,485,135,135,250,250,110,35};
uint16_t tabchiffreuny[12] = {535,775,775,135,135,35,35,135,135,635,475,535};

/*uint16_t tabchiffreunx[12] = {135,245,385,435,435,400,145,135,135,135,135,135};
  uint16_t tabchiffreuny[12] = {535,535,535,535,185,185,185,185,335,475,500,535};*/

uint8_t coeffEstNull[11];
uint8_t *p;

int j=0;
//affiche le chiffre un
void chiffreun(uint8_t numero_cadran)
{
  int taba[11];
  int tabb[11];
  p=&coeffEstNull[0];
  if(j==0){
    for(int i=0;i<11;i++)
      {
	taba[i] = calculCoeffDirect(tabchiffreunx[i],tabchiffreunx[i+1],tabchiffreuny[i],tabchiffreuny[i+1],p);
	tabb[i] = calculOrdonOrigin(tabchiffreunx[i],tabchiffreuny[i],taba[i], p);
	p++;
      }
    j++;
  }
    
  uint8_t led[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  
  if(numero_cadran==0)
    {
      
	  for(int i=0;i<16;i++)
	    {
	      p=&coeffEstNull[0];
	      led[i]=calculLedAllume(taba, tabb,tab15posy[i], tab0posy[i],tabchiffreunx,tabchiffreuny,p);
	    }
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==1)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab14posy[i], tab1posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==2)
    {
      if(j==1){
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab13posy[i], tab2posy[i],tabchiffreunx,tabchiffreuny,p);
	  char buffer[16];
	      sprintf(buffer,"%i \n\r",led[i]);
	      USART_puts(buffer);
	}
      j++;
      }
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==3)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab12posy[i], tab3posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==4)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab11posy[i], tab4posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==5)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab10posy[i], tab5posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==6)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab9posy[i], tab6posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==7)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab8posy[i], tab7posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==8)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab7posy[i], tab8posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==9)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab6posy[i], tab9posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==10)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab5posy[i], tab10posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==11)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab4posy[i], tab11posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==12)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab3posy[i], tab12posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==13)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab2posy[i], tab13posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==14)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab1posy[i], tab14posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
  else if(numero_cadran==15)
    {
      for(int i=0;i<16;i++)
	{
	  p=&coeffEstNull[0];
	  led[i]=calculLedAllume(taba, tabb,tab0posy[i], tab15posy[i],tabchiffreunx,tabchiffreuny,p);
	}
      allumeLed(convertToDecimal(led));
    }
}


//calcule si une led doit etre alumee ou non
//pour cela, calcule si la position de la led se trouve a l'interieur du chiffre voulu
// taba : tableau contenant tous les coeffs dirrecteur du chiffre
// tabb : tableau contenant toutes les coordonnee a l'origine des droites du chiffre
// posLedx et posLedy : la position de la led en x et y que l'on souhaite allumer ou eteindre
// tabchiffrex tabchiffrey : tableau representant le chiffre que l'on veut afficher
// estNull :  pointeur vers le tableau représentant si le coeff des droites et null ou pas, donc si la droite est verticale ou pas
uint8_t calculLedAllume(int taba[11],int tabb[11], uint16_t posLedx, uint16_t posLedy,uint16_t tabchiffrex[12],uint16_t tabchiffrey[12], uint8_t *estNull)
{
  uint8_t nbDroiteTraverse = 0;
  uint16_t ycalcule;
  uint16_t plusGrandy;
  uint16_t plusPetity;
  uint16_t plusGrandx;
  uint16_t plusPetitx;
  for(int j=0;j<11;j++)
    {
      //calcule quelle sont les bornes max et min de la droite pour x et y
      if(tabchiffrey[j]>tabchiffrey[j+1])
	{
	  plusGrandy=tabchiffrey[j];
	  plusPetity=tabchiffrey[j+1];
	}
      else
	{
	  plusGrandy=tabchiffrey[j+1];
	  plusPetity=tabchiffrey[j];
	}
      if(tabchiffrex[j]>tabchiffrex[j+1])
	{
	  plusGrandx=tabchiffrex[j];
	  plusPetitx=tabchiffrex[j+1];
	}
      else
	{
	  plusGrandx=tabchiffrex[j+1];
	  plusPetitx=tabchiffrex[j];
	}
      
      //si le coeff de la droite est nul (la droite est vertivale)
      if(*estNull==1){
	if(tabb[j]==posLedx && posLedy<=plusGrandy && posLedy>=plusPetity )
	  {
	    return 1;
	  }
      }
      //sinon, on peut utiliser la formule y=ax+b et on compte combien de fois on traverse une droite en montant a partir de la led
      else{
	if(posLedx<=plusGrandx && posLedx>=plusPetitx)
	  {
	    ycalcule = posLedx*taba[j]+tabb[j];
	    if(ycalcule>=posLedy*10 )
	      {
		nbDroiteTraverse++;
	      }
	  }
      }
      estNull++;
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

int calculCoeffDirect(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2,uint8_t *estNull)
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
int calculOrdonOrigin(uint16_t x,uint16_t y,int a,uint8_t *estNull)
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




