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

// definition des chiffres
uint16_t tabchiffreunx[5] = {100,380,380,500,260};
uint16_t tabchiffreuny[5] = {460,740,100,100,100};

//affiche le chiffre un
void chiffreun(uint8_t numero_cadran)
{
  int taba[4];
  int tabb[4];
  for(int i=0;i<4;i++)
    {
      taba[i] = calculCoeffDirect(tabchiffreunx[i],tabchiffreunx[i+1],tabchiffreuny[i],tabchiffreuny[i+1]);
      tabb[i] = calculOrdonOrigin(tabchiffreunx[i],tabchiffreuny[i],taba[i]);
    }

  uint8_t led[16]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  
  // on parcourt pour chaque LED sa position pour un cadran donné

      
  if(numero_cadran==0)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab0posy[15-i], tab0posy[i]);
	  uint8_t test[16] = {0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0};
	  allumeLed(convertToDecimal(test));
	  //allumeLed(0);
	}
    }
  else if(numero_cadran==1)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab1posy[15-i], tab1posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(2);
	}
    }
  else if(numero_cadran==2)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab2posy[15-i], tab2posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(4);
	}
    }
  else if(numero_cadran==3)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab3posy[15-i], tab3posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(6);
	}
    }
  else if(numero_cadran==4)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab4posy[15-i], tab4posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==5)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab5posy[15-i], tab5posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==6)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab6posy[15-i], tab6posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==7)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab7posy[15-i], tab7posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==8)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab8posy[15-i], tab8posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==9)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab9posy[15-i], tab9posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==10)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab10posy[15-i], tab10posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==11)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab11posy[15-i], tab11posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==12)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab12posy[15-i], tab12posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==13)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab13posy[15-i], tab13posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==14)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab14posy[15-i], tab14posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
  else if(numero_cadran==15)
    {
      for (int i =0;i<16;i++)
	{
	  led[i]=0;
	}
      for(int i=0;i<16;i++)
	{
	  led[i]=calculLedAllume(taba, tabb,tab15posy[15-i], tab15posy[i]);
	  //allumeLed(convertToDecimal(led));
	  //allumeLed(32768);
	}
    }
}


//calcule si une led doit etre alumee ou non
//pour cela, calcule si la position de la led se trouve sur une des droites que composent le chiffre
// taba : tableau contenant tous les coeffs dirrecteur du chiffre
// tabb : tableau contenant toutes les coordonnee a l'origine des droites du chiffre
// posLed : la position de la led que l'on souhaite allumer ou eteindre
uint8_t calculLedAllume(int taba[16],int tabb[16], uint16_t posLedx, uint16_t posLedy)
{
  uint16_t ycalcule;
  for(int j=0;j<4;j++)
    {
      ycalcule = posLedx*taba[j]+tabb[j];
      if(ycalcule == posLedy)
	{
	  return 1;
	}
    }
  return 0;
}

//convertit en décimal un tableau de taille 16 remplis de 1 et de 0
uint16_t convertToDecimal(uint8_t tabled[16])
{
  uint16_t decimal=0;
  for(int i = 0;i<16;i++)
    {
      decimal = decimal + pow(2,i)*tabled[i];
    }
  char buffer[16];
  sprintf(buffer,"%i\r\n",decimal);
  USART_puts(buffer);
  return decimal;
}

int calculCoeffDirect(uint16_t x1,uint16_t x2,uint16_t y1,uint16_t y2)
{
  int a;
  if(y1!=y2)
  {
    a = (x1-x2)/(y1-y2);
  }
  else
  {
    a=0;
  }
  
  return a;
}
int calculOrdonOrigin(uint16_t x,uint16_t y,int a)
{
  int b = y-a*x;
  return b;
}




