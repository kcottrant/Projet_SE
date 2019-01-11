#include "chiffres.h"
#include "spi.h"

// Affiche dans les bons cadrans les heures
void AfficheHeures(uint8_t heures,uint8_t secondes,uint8_t numero_cadran)
{
  if(heures/10 ==1)
  {
    Afficheun(54,numero_cadran,secondes,0);
  }
  else if(heures/10 ==0)
  {
    Affichezero(54,numero_cadran,secondes);
  }
  if(heures%10 ==1)
  {
    Afficheun(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==2)
  {
    Affichedeux(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==3)
  {
    Affichetrois(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==4)
  {
    Affichequatre(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==5)
  {
    Affichecinq(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==6)
  {
    Affichesix(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==7)
  {
    Affichesept(2,numero_cadran,secondes,0);
  }
  else if(heures%10 ==8)
  {
    Affichehuit(2,numero_cadran,secondes);
  }
  else if(heures%10 ==9)
  {
    Afficheneuf(2,numero_cadran,secondes,0);
  }

}

// Affiche dans les bons cadrans les minutes
void AfficheMinutes(uint8_t minutes,uint8_t secondes,uint8_t numero_cadran)
{
  if(minutes/10 ==0)
  {
    Affichezero(32,numero_cadran,secondes);
  }
  else if(minutes/10 ==1)
  {
    Afficheun(32,numero_cadran,secondes,1);
  }
  else if(minutes/10 ==2)
  {
    Affichedeux(32,numero_cadran,secondes,1);
  }
  else if(minutes/10 ==3)
  {
    Affichetrois(32,numero_cadran,secondes,1);
  }
  else if(minutes/10 ==4)
  {
    Affichequatre(32,numero_cadran,secondes,1);
  }
  else if(minutes/10 ==5)
  {
    Affichecinq(32,numero_cadran,secondes,1);
  }

  if(minutes%10 ==0)
  {
    Affichezero(24,numero_cadran,secondes);
  }
  else if(minutes%10 ==1)
  {
    Afficheun(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==2)
  {
    Affichedeux(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==3)
  {
    Affichetrois(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==4)
  {
    Affichequatre(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==5)
  {
    Affichecinq(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==6)
  {
    Affichesix(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==7)
  {
    Affichesept(24,numero_cadran,secondes,1);
  }
  else if(minutes%10 ==8)
  {
    Affichehuit(24,numero_cadran,secondes);
  }
  else if(minutes%10 ==9)
  {
    Afficheneuf(24,numero_cadran,secondes,1);
  }

}

// les fonctions suivantes permettent d'afficher respectivement les chiffres de 0 à 9 dans le bon cadran

void Afficheun(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
{
  uint16_t valeur_sec=0;
  if(numero_cadran<=secondes)
  {
    valeur_sec=32768;
  }
  if (estbas==0)
  {

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
  else
  {
    if(cadrandesire == numero_cadran)
    {
      allumeLed(16376+valeur_sec);
    }
    else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(8+valeur_sec);
    }
    else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(16+valeur_sec);
    }
    else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(32+valeur_sec);
    }
    else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(64+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
  }
}

void Affichedeux(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
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
  else
  {
    if(cadrandesire == numero_cadran)
    {
      allumeLed(8192+valeur_sec);
    }
    else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(8688+valeur_sec);
    }
    else if(cadrandesire+2== numero_cadran)
    {
      allumeLed(8712+valeur_sec);
    }
    else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(9224+valeur_sec);
    }
    else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(10256+valeur_sec);
    }
    else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(12320+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
  }
}

void Affichetrois(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
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
  else
  {
    if(cadrandesire == numero_cadran)
    {
      allumeLed(3808+valeur_sec);
    }
    else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(4368+valeur_sec);
    }
    else if(cadrandesire+2 == numero_cadran || cadrandesire+3==numero_cadran)
    {
      allumeLed(8456+valeur_sec);
    }
    else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(8200+valeur_sec);
    }
    else if(cadrandesire+5== numero_cadran)
    {
      allumeLed(4144+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
  }
}

void Affichequatre(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
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
  else
  {
    if(cadrandesire == numero_cadran || cadrandesire+1 == numero_cadran)
    {
      allumeLed(1024+valeur_sec);
    }
    else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(16176+valeur_sec);
    }
    else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(1120+valeur_sec);
    }
    else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(1408+valeur_sec);
    }
    else if(cadrandesire+5== numero_cadran)
    {
      allumeLed(1792+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
  }
}

void Affichecinq(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
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
  else
  {
    if(cadrandesire == numero_cadran)
    {
      allumeLed(3584+valeur_sec);
    }
    else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(4360+valeur_sec);
    }
    else if( cadrandesire+2==numero_cadran || cadrandesire+3==numero_cadran || cadrandesire+4 == numero_cadran)
    {
      allumeLed(8328+valeur_sec);
    }
    else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(8440+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
  }
}

void Affichesix(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
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
  else
  {
    if(cadrandesire == numero_cadran)
    {
      allumeLed(3072+valeur_sec);
    }
    else if(cadrandesire+1== numero_cadran)
    {
      allumeLed(4616+valeur_sec);
    }
    else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(8456+valeur_sec);
    }
    else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(8464+valeur_sec);
    }
    else if(cadrandesire+4 == numero_cadran)
    {
      allumeLed(4704+valeur_sec);
    }
    else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(3968+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
  }
}

void Affichesept(uint8_t cadrandesire,uint8_t numero_cadran,uint8_t secondes,uint8_t estbas)
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
  else
  {
    if(cadrandesire == numero_cadran)
    {
      allumeLed(24+valeur_sec);
    }
    else if(cadrandesire+1 == numero_cadran)
    {
      allumeLed(360+valeur_sec);
    }
    else if(cadrandesire+2 == numero_cadran)
    {
      allumeLed(392+valeur_sec);
    }
    else if(cadrandesire+3 == numero_cadran)
    {
      allumeLed(16136+valeur_sec);
    }
    else if(cadrandesire+4== numero_cadran)
    {
      allumeLed(264+valeur_sec);
    }
    else if(cadrandesire+5 == numero_cadran)
    {
      allumeLed(8+valeur_sec);
    }
    else
    {
      allumeLed(valeur_sec);
    }
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
