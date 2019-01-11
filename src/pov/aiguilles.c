  #include "aiguilles.h"
  #include "spi.h"

  //mode d'affichage aiguille
  void aiguilles(uint8_t numero_cadran, uint8_t compteur_h,uint8_t compteur_min,uint8_t compteur_sec){
    uint8_t heure12;

      if(compteur_h>=12){
        heure12=compteur_h-12;
      }
      else{
        heure12=compteur_h;
      }
      //sec min pas h
      if(numero_cadran==compteur_sec && numero_cadran==compteur_min)// &&  numero_cadran/5!=heure12)
      {
         allumeLed(49151);
      }
      //sec min h
      else if(numero_cadran==compteur_sec && numero_cadran==compteur_min &&  numero_cadran/5==heure12 && numero_cadran%5==0)
      {
         allumeLed(48895);
      }
      //sec pas min pas h
      else if (numero_cadran==compteur_sec && numero_cadran!=compteur_min)//&& numero_cadran/5!=heure12)
      {
        allumeLed(32768);
      }
      //sec pas min h
      else if (numero_cadran==compteur_sec && numero_cadran!=compteur_min && numero_cadran/5==heure12 &&  numero_cadran%5==0)
      {
        allumeLed(33023);
      }
      //pas sec min pas h
      else if(numero_cadran!=compteur_sec && numero_cadran==compteur_min)// && numero_cadran/5!=heure12)
      {
        allumeLed(16383);
      }
      //pas sec min h
      else if(numero_cadran!=compteur_sec && numero_cadran==compteur_min && numero_cadran/5==heure12 &&  numero_cadran%5==0)
      {
        allumeLed(16127);
      }
      //pas sec pas min h
      else if(numero_cadran!=compteur_sec && numero_cadran!=compteur_min && numero_cadran/5==heure12 &&  numero_cadran%5==0)
      {
        allumeLed(255);

      }
      else
      {
         allumeLed(0);
      }
  }
