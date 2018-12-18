#include "chiffres.h"
#include "spi.h"

// inverser 1,2,4,5,6,7
void AfficheHeures(uint8_t heures,uint8_t secondes,uint8_t numero_cadran)
{
  if(heures/10 ==1)
    {
      Afficheun(50,numero_cadran,secondes);
    }
  else if(heures/10 ==0)
    {
      Affichezero(50,numero_cadran,secondes);
    }
  if(heures%10 ==1)
    {
      Afficheun(1,numero_cadran,secondes);
    }
  else if(heures%10 ==2)
    {
      Affichedeux(1,numero_cadran,secondes);
    }
  else if(heures%10 ==3)
    {
      Affichetrois(1,numero_cadran,secondes);
    }
  else if(heures%10 ==4)
    {
      Affichequatre(1,numero_cadran,secondes);
    }
  else if(heures%10 ==5)
    {
      Affichecinq(1,numero_cadran,secondes);
    }
  else if(heures%10 ==6)
    {
      Affichesix(1,numero_cadran,secondes);
    }
  else if(heures%10 ==7)
    {
      Affichesept(1,numero_cadran,secondes);
    }
  else if(heures%10 ==8)
    {
      Affichehuit(1,numero_cadran,secondes);
    }
  else if(heures%10 ==9)
    {
      Afficheneuf(1,numero_cadran,secondes,0);
    }
 
}

void AfficheMinutes(uint8_t minutes,uint8_t secondes,uint8_t numero_cadran)
{
  if(minutes/10 ==0)
    {
      Affichezero(31,numero_cadran,secondes);
    }
  else if(minutes/10 ==1)
    {
      Afficheun(31,numero_cadran,secondes);
    }
  else if(minutes/10 ==2)
    {
      Affichedeux(31,numero_cadran,secondes);
    }
  else if(minutes/10 ==3)
    {
      Affichetrois(31,numero_cadran,secondes);
    }
  else if(minutes/10 ==4)
    {
      Affichequatre(31,numero_cadran,secondes);
    }
  else if(minutes/10 ==5)
    {
      Affichecinq(31,numero_cadran,secondes);
    }
  
  if(minutes%10 ==0)
    {
      Affichezero(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==1)
    {
      Afficheun(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==2)
    {
      Affichedeux(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==3)
    {
      Affichetrois(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==4)
    {
      Affichequatre(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==5)
    {
      Affichecinq(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==6)
    {
      Affichesix(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==7)
    {
      Affichesept(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==8)
    {
      Affichehuit(20,numero_cadran,secondes);
    }
  else if(minutes%10 ==9)
    {
      Afficheneuf(20,numero_cadran,secondes,1);
    }
 
}

void Afficheun(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(512+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(1024+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(2048+valeur_sec);
    }
  else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(4096+valeur_sec);
    }
  else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(8188+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichedeux(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(1036+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(2068+valeur_sec);
    }
  else if(cadrandesire+2== numero_cadran)
    {
      allumeLed(4132+valeur_sec);
    }
  else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(4164+valeur_sec);
    }
  else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(3972+valeur_sec);
    }
  else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(4+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichetrois(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(3080+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(4100+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran || cadrandesire+3==numero_cadran)
    {
      allumeLed(4228+valeur_sec);
    }
  else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(2184+valeur_sec);
    }
  else if(cadrandesire+5== numero_cadran)
    {
      allumeLed(1904+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichequatre(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(224+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(416+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(1568+valeur_sec);
    }
  else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(3324+valeur_sec);
    }
  else if(cadrandesire+4== numero_cadran || cadrandesire+5==numero_cadran)
    {
      allumeLed(32+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichecinq(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(7940+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran || cadrandesire+2==numero_cadran || cadrandesire+3==numero_cadran)
    {
      allumeLed(4356+valeur_sec);
    }
  else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(4232+valeur_sec);
    }
  else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(112+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichesix(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(496+valeur_sec);
    }
  else if(cadrandesire+1== numero_cadran)
    {
      allumeLed(1608+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(2180+valeur_sec);
    }
  else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(4228+valeur_sec);
    }
  else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(4168+valeur_sec);
    }
  else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(48+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichesept(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(4100+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(4248+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(4320+valeur_sec);
    }
  else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(4480+valeur_sec);
    }
  else if(cadrandesire+4== numero_cadran)
    {
      allumeLed(5760+valeur_sec);
    }
  else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(6144+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Affichehuit(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire== numero_cadran)
    {
      allumeLed(1584+valeur_sec);
    }
  else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(2376+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran || cadrandesire+3 == numero_cadran)
    {
      allumeLed(4228+valeur_sec);
    }
  else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(2376+valeur_sec);
    }
  else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(1584+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}

void Afficheneuf(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(estbas==0)
    {
      if(cadrandesire == numero_cadran)
	{
	  allumeLed(1536+valeur_sec); // inverse : 4064
	}
      else if(cadrandesire+1 == numero_cadran)
	{
	  allumeLed(2312+valeur_sec); // inverse : 4024
	}
      else if(cadrandesire+2 == numero_cadran || cadrandesire+3 == numero_cadran)
	{
	  allumeLed(4228+valeur_sec);
	}
      else if(cadrandesire+4== numero_cadran)
	{
	  allumeLed(2312+valeur_sec);
	}
      else if(cadrandesire+5 == numero_cadran)
	{
	  allumeLed(2032+valeur_sec);
	}
      else
	{
	  allumeLed(valeur_sec);
	}
    }
  else
    {
      if(cadrandesire == numero_cadran)
	{
	  allumeLed(4064+valeur_sec);
	}
      else if(cadrandesire+1== numero_cadran)
	{
	  allumeLed(4240+valeur_sec);
	}
      else if(cadrandesire+2 == numero_cadran || cadrandesire+3 == numero_cadran)
	{
	  allumeLed(8456+valeur_sec);
	}
      else if(cadrandesire+4 == numero_cadran)
	{
	  allumeLed(4240+valeur_sec);
	}
      else if(cadrandesire+5 == numero_cadran)
	{
	  allumeLed(96+valeur_sec);
	}
      else
	{
	  allumeLed(valeur_sec);
	}
    }
}


void Affichezero(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
    {
      valeur_sec=32768;
    }
  if(cadrandesire == numero_cadran)
    {
      allumeLed(2032+valeur_sec);
    }
  else if(cadrandesire+1== numero_cadran)
    {
      allumeLed(2056+valeur_sec);
    }
  else if(cadrandesire+2 == numero_cadran || cadrandesire+3 == numero_cadran)
    {
      allumeLed(4100+valeur_sec);
    }
  else if(cadrandesire+4== numero_cadran)
    {
      allumeLed(2056+valeur_sec);
    }
  else if(cadrandesire+5== numero_cadran)
    {
      allumeLed(2032+valeur_sec);
    }
  else
    {
      allumeLed(valeur_sec);
    }
}