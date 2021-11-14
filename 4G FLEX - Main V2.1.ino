
//*****************TRANSMETTEUR 4G à base SIM7600*******************
// Controleur ATMEGA2560
// Version V2.0 - 13/11/2021
// XTA - Dabi_creator
//******************************************************************

#include <SoftwareSerial.h>

//*****************Configuation TX/RX (10/8)************************

SoftwareSerial SIM7600(10, 8); 

//*****************DECLARATION DES VARIABLES ************************

// Pin ATMEGA2560 à personnaliser ***

const int E_MES_TOTAL       = 3;
const int E_MES_PARTIEL     = 4;
const int E_MHS             = 5;
const int E_AUTOPROTECTION  = 6;
const int E_DEFAUT_SECTEUR  = 7;
const int E_DEFAUT          = 14;
const int E_INCENDIE        = 15;
const int E_INTRUSION       = 2;

const int S_TOTAL           = 17;
const int S_PARTIEL         = 16;

//***********************************

// Etat des Entrées
boolean etat_E_MES_TOTAL        = 0;
boolean etat_E_MES_PARTIEL      = 0;
boolean etat_E_MHS              = 0;
boolean etat_E_AUTOPROTECTION   = 0;
boolean etat_E_DEFAUT_SECTEUR   = 0;
boolean etat_E_DEFAUT           = 0;
boolean etat_E_INCENDIE         = 0;
boolean etat_E_INTRUSION        = 0;
boolean etat_S_TOTAL            = 0;
boolean etat_S_PARTIEL          = 0;

boolean b_etat_E_MES_TOTAL      = 0;
boolean b_etat_E_MES_PARTIEL    = 0;
boolean b_etat_E_MHS            = 0;
boolean b_etat_E_DEFAUT_SECTEUR = 0;
boolean b_etat_E_DEFAUT         = 0;

//***********************************
String textMessage;

int etat_centrale           = 0;

int nbre_appel_alarm        = 2;
boolean acquit_alarm        = 0;

char OPERATEUR[20];
char SIGNAL[20];

char ess[30];
char temp_strg_2[100];
char temp_strg_1[100];

char var_Extraction_Char[20];
char strg_3[30];

int temp_nbre_appel = nbre_appel_alarm ;
uint8_t answer = 0;

//********* enregistrement des N° de telephone***********

char phone_1[] = "+33123456789";      
char phone_2[] = "+33123456789";

//********* code d'accés ********************************

char code_phone_1[] = "0000";
char code_phone_2[] = "0000";  

//=======================================================

void setup() {

  // Configuration des Entrées
  
  pinMode(E_MES_TOTAL, INPUT);
  pinMode(E_MES_PARTIEL, INPUT);
  pinMode(E_MHS, INPUT);
  pinMode(E_AUTOPROTECTION, INPUT);
  pinMode(E_DEFAUT_SECTEUR, INPUT);
  pinMode(E_DEFAUT, INPUT);
  pinMode(E_INCENDIE, INPUT);
  pinMode(E_INTRUSION, INPUT);

  // Configuration des Sorties
  
  pinMode(S_TOTAL, OUTPUT);
  pinMode(S_PARTIEL, OUTPUT);
 
  digitalWrite(S_TOTAL, LOW);
  digitalWrite(S_PARTIEL, LOW);
 
  delay(2000);

  // Configuration SIM7600 4G
 
  SIM7600.begin(19200);   //initialisation Vitesse SIM7600 = 19200
  Serial.begin(19200);    //initialisation Console = 19200

  Serial.println("Initialisation SIM7600");
  
  while (envoyer_Commande_AT("AT", "OK", 2000) == 0){
    delay(1000);
    Serial.print("."); 
  }

  delay(5000);
  
  Serial.println("SIM7600 Code PIN");
  
  envoyer_Commande_AT("AT+CPIN=1234", "+CPIN: READY", 2000);
  
  while (envoyer_Commande_AT("AT+CPIN?", "+CPIN: READY", 2000) == 0){
    delay(1000);
    Serial.print(".");
  }

  Serial.println("SIM7600 PIN OK");
 
  delay(1000);
  
  while ((envoyer_Commande_AT("AT+CREG?", "+CREG: 0,5", 5000) || envoyer_Commande_AT("AT+CREG?", "+CREG: 0,1",5000) || envoyer_Commande_AT("AT+CREG?", "+CREG: 0,2",5000)) == 0 ); 

  delay(2000); 
  
  Serial.println("SIM7600 Connecté OPERATEUR");

  //initialisation Mode SMS
  while (envoyer_Commande_AT("AT+CMGF=1", "OK", 5000) == 0);
  Serial.println("SIM7600 CMGF"); 
  //while (envoyer_Commande_AT("AT+CSCS=GSM", "OK", 5000) == 0);
  //Serial.println("SIM7600 CSCS"); 
  while (envoyer_Commande_AT("AT+CSMP=17,167,0,0", "OK", 5000) == 0); 
  Serial.println("SIM7600 CSMP");
  while (envoyer_Commande_AT("AT+CNMI=2,2,0,0,0", "OK", 5000) == 0); 
  Serial.println("SIM7600 CNMI");
  
  Serial.println("SIM7600 Mode SMS");

  send_SMS(phone_1,"Honeywell 4G Flex : Fonctionnel");
   
  delay(2000);
    
  lecture_ES();
  etat_flex();
  
  Serial.println("SIM7600 Prêt");
  
  }
//*******************************************************
//********* Programme principal *************************
//*******************************************************

void loop() { 

  lecture_ES();
  etat_flex();

//********* Envoi des Etats par SMS suivant commandes CLAVIER FLEX **********

//********* Envoi des Etats par SMS  - TOTAL **********

  if (etat_E_MES_TOTAL == 1 & b_etat_E_MES_TOTAL == 0 & etat_E_MES_PARTIEL == 0 & etat_E_MHS == 0){

    b_etat_E_MES_TOTAL = 1;
    b_etat_E_MES_PARTIEL = 0;
    b_etat_E_MHS = 0;
    
    send_SMS(phone_1,"ALARME EN SERVICE - TOTAL");   
    send_SMS(phone_2,"ALARME EN SERVICE - TOTAL");
    
  }

//********* Envoi des Etats par SMS  - PARTIEL **********

  if (etat_E_MES_PARTIEL == 1 & b_etat_E_MES_PARTIEL == 0 & etat_E_MES_TOTAL == 0 & etat_E_MHS == 0){

    b_etat_E_MES_TOTAL = 0;
    b_etat_E_MES_PARTIEL = 1;
    b_etat_E_MHS = 0;
    
    send_SMS(phone_1,"ALARME EN SERVICE - PARTIEL");   
    send_SMS(phone_2,"ALARME EN SERVICE - PARTIEL");
    
  }

//********* Envoi des Etats par SMS  - ARRET **********

  if (etat_E_MHS == 1 & b_etat_E_MHS == 0 & etat_E_MES_TOTAL == 0 & etat_E_MES_PARTIEL == 0){
    
    b_etat_E_MES_TOTAL = 0;
    b_etat_E_MES_PARTIEL = 0;
    b_etat_E_MHS = 1;
    
    send_SMS(phone_1,"ALARME HORS SERVICE");   
    send_SMS(phone_2,"ALARME HORS SERVICE");
    
  }

//********* Envoi des Etats par SMS  - COUPURE EDF **********

  if (etat_E_DEFAUT_SECTEUR == 1 & b_etat_E_DEFAUT_SECTEUR == 0){

    b_etat_E_DEFAUT_SECTEUR = 1;
    
    send_SMS(phone_1,"COUPURE EDF");   
    send_SMS(phone_2,"COUPURE EDF");
    
  }

if (etat_E_DEFAUT_SECTEUR == 0 & b_etat_E_DEFAUT_SECTEUR == 1){

    b_etat_E_DEFAUT_SECTEUR = 0;
    
    send_SMS(phone_1,"RETABLISSEMENT EDF");   
    send_SMS(phone_2,"RETABLISSEMENT EDF");
    
  }

//********* Envoi des Etats par SMS  - DEFAUT **********

  if (etat_E_DEFAUT == 1 & b_etat_E_DEFAUT == 0){

    b_etat_E_DEFAUT = 1;
    
    send_SMS(phone_1,"DEFAUT SYSTEME");   
    send_SMS(phone_2,"DEFAUT SYSTEME");
    
  }

if (etat_E_DEFAUT == 0 & b_etat_E_DEFAUT == 1){

    b_etat_E_DEFAUT = 0;
    
    send_SMS(phone_1,"RETABLISSEMENT DEFAUT SYSTEME");   
    send_SMS(phone_2,"RETABLISSEMENT DEFAUT SYSTEME");
    
  }

//********* Mode Alarm - INTRUSION / AUTOPROTECTION / INCENDIE **********
 
  while (etat_centrale == 1 & temp_nbre_appel != 0){

   lecture_ES();
   etat_flex();
    
   if (etat_E_AUTOPROTECTION == 1){

      Serial.println("MODE ALARM - AUTOPROTECTION");
      send_SMS(phone_1,"ALARME EN COURS !!! - AUTOPROTECTION");   
      send_SMS(phone_2,"ALARME EN COURS !!! - AUTOPROTECTION");            
   }

   if (etat_E_INCENDIE == 1){

      Serial.println("MODE ALARM - INCENDIE");
      send_SMS(phone_1,"ALARME EN COURS !!! - INCENDIE");   
      send_SMS(phone_2,"ALARME EN COURS !!! - INCENDIE");            
   }

   if (etat_E_INTRUSION == 1){

      Serial.println("MODE ALARM - INTRUSION");
      send_SMS(phone_1,"ALARME EN COURS !!! - INTRUSION");   
      send_SMS(phone_2,"ALARME EN COURS !!! - INTRUSION");            
   }
      
    appel_vocal(phone_1);
    appel_vocal(phone_2);  
    
    if (acquit_alarm == 1){
      temp_nbre_appel = 0;
      break;
    }
       
    temp_nbre_appel-- ;
    
    Serial.println(temp_nbre_appel);
    
  }   

//********* Lecture des données **********
  if(SIM7600.available()>0){
      textMessage = SIM7600.readString();
      Serial.println(textMessage);  
      delay(10);  
      lecture_ES();
      etat_flex();

      if(textMessage.indexOf(phone_1)>=0){
      menu(phone_1,code_phone_1);
      }

      if(textMessage.indexOf(phone_2)>=0){
      menu(phone_2,code_phone_2);
      }
  }
}
//*******************************************************
//*******************************************************

void menu(const char* tel_user, const char* code_user) {

  String code_T = String (code_user) + "t";
  String code_P = String (code_user) + "p";
  String code_A = String (code_user) + "a";
  String code_E = String (code_user) + "e";
 
//********* Code Valide  **********
  if(textMessage.indexOf(code_user)>=0 & textMessage.length() <= 56){

    lecture_ES();
    etat_flex();
    etat_systeme_simplifie();
    
    sprintf(temp_strg_1,"%s \rt = TOTAL\rp = PARTIEL\ra = ARRET\re = ETAT\r", ess);    
    send_SMS(tel_user,temp_strg_1);
    textMessage = " ";
   }

 //********* Menu Utilisateur 1 **********  

  if (textMessage.indexOf(code_T)>=0 & textMessage.length() <= 57){  
        Serial.println("Menu T");
        textMessage = " ";
        
        lecture_ES();
        etat_flex();
        
        if (etat_centrale == 0){
        
        digitalWrite(S_TOTAL, HIGH);
        delay(2000);
        digitalWrite(S_TOTAL, LOW);
        delay(2000);
        
      /*lecture_ES();
        etat_flex();
        
          if(etat_E_MES_TOTAL == 1){
            //send_SMS(tel_user,"ALARME EN SERVICE - TOTAL");
          }
          else {
              send_SMS(tel_user,"ECHEC - MISE EN ALARME");         
          }*/   
        }
        else if(etat_centrale == 1) {
        send_SMS(tel_user,"ALARME EN COURS !!!"); 
        }
        else if(etat_centrale == 2) {
        send_SMS(tel_user,"ALARME EN SERVICE - TOTAL"); 
        }
        else if(etat_centrale == 3) {
        send_SMS(tel_user,"ALARME EN SERVICE - PARTIEL"); 
        }
  }
 
  if (textMessage.indexOf(code_P)>=0 & textMessage.length() <= 57){  
          Serial.println("Menu P");
          textMessage = " ";
          
          lecture_ES();
          etat_flex();
          
          Serial.println(etat_centrale);
          
          if (etat_centrale == 0){

          digitalWrite(S_PARTIEL, HIGH);
          delay(2000);
          digitalWrite(S_PARTIEL, LOW);
          delay(2000);
          
        /*lecture_ES();
          etat_flex();
          
            if(etat_E_MES_PARTIEL == 1){
              //send_SMS(tel_user,"ALARME EN SERVICE - PARTIEL");
            } 
            else {
              send_SMS(tel_user,"ECHEC - MISE EN ALARME");         
            }*/
          }
          else if(etat_centrale == 1) {
          send_SMS(tel_user,"ALARME EN COURS !!!"); 
          }
          else if(etat_centrale == 2) {
          send_SMS(tel_user,"ALARME EN SERVICE - TOTAL"); 
          }
          else if(etat_centrale == 3) {
          send_SMS(tel_user,"ALARME EN SERVICE - PARTIEL"); 
          }
    }

  if (textMessage.indexOf(code_A)>=0 & textMessage.length() <= 57){  
          Serial.println("Menu A");
          textMessage = " ";
          
          lecture_ES();
          etat_flex();
          
          if (etat_centrale == 2){

          digitalWrite(S_TOTAL, HIGH);
          delay(2000);
          digitalWrite(S_TOTAL, LOW);
          delay(2000);
          
        /*lecture_ES();
          etat_flex();
          
            if(etat_E_MHS == 1){
              //send_SMS(tel_user,"ALARME HORS SERVICE");
            }
            else {
              send_SMS(tel_user,"ECHEC - ARRET ALARME");         
            }*/
         }
          else if(etat_centrale == 3) {
         
          digitalWrite(S_PARTIEL, HIGH);
          delay(1000);
          digitalWrite(S_PARTIEL, LOW);
          delay(5000);
          
         /*lecture_ES();
          etat_flex();
          
            if(etat_E_MHS == 1){
              //send_SMS(tel_user,"ALARME HORS SERVICE");
            }         
            else if (etat_E_MHS == 1) {
            send_SMS(tel_user,"ALARME HORS SERVICE");      
            }*/
          }   
    }
   
  if (textMessage.indexOf(code_E)>=0 & textMessage.length() <= 57){  
            Serial.println("Menu E");
            textMessage = " ";
            lecture_ES();
            etat_flex();
            operateur();
            ssri();
            etat_systeme_complet();
            send_SMS(tel_user,temp_strg_2);
  }     
  
}

//*****************Lecture des Entrées / Sorties  *************************

void lecture_ES(){

  etat_E_MES_TOTAL = digitalRead(E_MES_TOTAL);
  etat_E_MES_PARTIEL = digitalRead(E_MES_PARTIEL);
  etat_E_MHS = digitalRead(E_MHS);
  etat_E_AUTOPROTECTION = digitalRead(E_AUTOPROTECTION);
  etat_E_DEFAUT_SECTEUR = digitalRead(E_DEFAUT_SECTEUR);
  etat_E_DEFAUT = digitalRead(E_DEFAUT);
  etat_E_INCENDIE = digitalRead(E_INCENDIE);
  etat_E_INTRUSION = digitalRead(E_INTRUSION);
    
}
    
//*****************Fonction Centrale en attente de mise en service  *************************

void etat_flex() {

  if (etat_E_MHS == 1 & etat_E_AUTOPROTECTION  == 0 & etat_E_INCENDIE == 0 & etat_E_INTRUSION == 0)
  {
    etat_centrale = 0;
    acquit_alarm = 0;
    temp_nbre_appel = nbre_appel_alarm;    
  }
  else if (etat_E_AUTOPROTECTION  == 1 || etat_E_INCENDIE == 1 || etat_E_INTRUSION == 1)
  {
    etat_centrale = 1;
  }
  else if (etat_E_MES_TOTAL  == 1)
  {
    etat_centrale = 2;
  }
   else if (etat_E_MES_PARTIEL  == 1)
  {
    etat_centrale = 3;
  }
     
}

//*****************Etat du Systeme Simplifié  *************************

void etat_systeme_simplifie() {
         
    if (etat_E_AUTOPROTECTION  == 1 || etat_E_INCENDIE == 1 || etat_E_INTRUSION == 1){

    sprintf(ess,"ALARME EN COURS !!!\r");
      
    }
    else if (etat_E_MES_TOTAL  == 1){

    sprintf(ess,"ALARME EN SERVICE - TOTAL \r");
    
    }
    else if (etat_E_MES_PARTIEL  == 1){

    sprintf(ess,"ALARME EN SERVICE - PARTIEL \r");
     
    }
    
    else if (etat_E_MHS  == 1){

    sprintf(ess,"ALARME HORS SERVICE \r");

    }
}

 //*****************Etat du Systeme Complet  *************************

void etat_systeme_complet() {
 
   sprintf(temp_strg_2,"%d = TOTAL\r%d = PARTIEL\r%d = MHS\r%d = AUTOPROTECT.\r%d = SECTEUR\r%d = DEFAUT\r%d = INCENDIE\r%d = INTRUSION\r%d = S TOTAL\r%d = S PARTIEL\r\r%s\r%s", etat_E_MES_TOTAL, etat_E_MES_PARTIEL, etat_E_MHS, etat_E_AUTOPROTECTION, etat_E_DEFAUT_SECTEUR, etat_E_DEFAUT, etat_E_INCENDIE, etat_E_INTRUSION, etat_S_TOTAL, etat_S_PARTIEL, OPERATEUR, SIGNAL);
   
}

// Information Opérateur Téléphonique
void operateur(){

     if (Extraction_Char("AT+COPS?","OK", 10000,23 ,33 ) == 1){
  
      sprintf(OPERATEUR,var_Extraction_Char);    
    }
    
    else {
  
      sprintf(OPERATEUR,"-");   
    }
   
}

// Information SSRI Operateur
void ssri(){

    if (Extraction_Char("AT+CSQ","OK", 10000,15 ,21 ) == 1){
      
        sprintf(SIGNAL,var_Extraction_Char);    
    }
    
    else {
      
        sprintf(SIGNAL,"-");   
    }
   
}
/**************************SMS sending and receiving message **************************/
//SMS sending short message

bool send_SMS(const char* PhoneNumber,const char* Message){
  
  uint8_t answer = 0;
  char aux_string[100];

  Serial.print("Configuration SMS mode...\n");
  envoyer_Commande_AT("AT+CMGF=1", "OK", 1000);    // sets the SMS mode to text
  Serial.print("Envoie SMS\n");
    
  sprintf(aux_string,"AT+CMGS=\"%s\"", PhoneNumber);

  answer = envoyer_Commande_AT(aux_string, ">", 3000);    // send the SMS number
  if (answer == 1)
  {
      SIM7600.println(Message);
      SIM7600.write(0x1A);
      answer = envoyer_Commande_AT("", "OK", 25000);
      if (answer == 1)
      {
          Serial.print("Envoie OK \n"); 
          return true;   
      }
      else
      {
          Serial.print("Erreur \n");
          return false;
      }
  }
  else
  {
      Serial.print(" Erreur.\n");
      return false;
  }
}

//*****************Fonction Appel Vocal *************************

void appel_vocal(const char* PhoneNumber){

  char aux_str[30];
  sprintf(aux_str, "ATD%s;", PhoneNumber);

  // Appui de la touche "1" pendant a communication pour acquiter l'alarme
  if (envoyer_Commande_AT(aux_str, "+RXDTMF: 1", 20000) == 1){

    acquit_alarm = 1 ;
    SIM7600.println("AT+CHUP");            // Déconnecte l'appel en cours
    delay(5000);
    Serial.print("Fin d'appel\n");
    
  }
  
  else {

    SIM7600.println("AT+CHUP");             // Déconnecte l'appel en cours
    delay(5000);
    Serial.print("Fin d'appel\n");
  }
}

//*************** MISE EN MEMOIRE COMMANDE AT********************************

uint8_t envoyer_Commande_AT(const char* commande_AT, const char* reponse_Esperee, unsigned int timeout)
{

  uint8_t x = 0,  answer = 0;
  char reponse[100];
  unsigned long previous;

  // Initialisation de la chaine de caractère (string).
  memset(reponse, '\0', 100);

  delay(100);

  // Initialisation du tampon d'entrée (input buffer).
  while ( SIM7600.available() > 0)
  {
    SIM7600.read();
  }
  // Envoi de la commande AT.
  SIM7600.println(commande_AT);

  // Réponse du SIM7600.
  // Cette boucle vérifie s'il y a des données disponibles dans le tampon.
  // Ces données sont comparées avec la réponse attendue.

  x = 0;
  previous = millis();

  do
  {
    if (SIM7600.available() != 0)
    {
      reponse[x] = SIM7600.read();
      x++;
      // Comparaison des données
      if (strstr(reponse, reponse_Esperee) != NULL)
      {
        answer = 1;
      }
    }
  } while ((answer == 0) && ((millis() - previous) < timeout));

 return answer;

}

//*************** MISE EN MEMOIRE COMMANDE AT********************************

uint8_t Extraction_Char(const char* commande_AT, const char* reponse_Esperee, unsigned int timeout,unsigned int index_debut, unsigned int index_fin)
{
  uint8_t x = 0,  answer = 0;
  char reponse[100];
  String extract_1, extract_2;
  unsigned long previous;

  // Initialisation de la chaine de caractère (string).
  memset(reponse, '\0', 100);

  delay(100);

  // Initialisation du tampon d'entrée (input buffer).
  while ( SIM7600.available() > 0)
  {
    SIM7600.read();
  }
  // Envoi de la commande AT.
  SIM7600.println(commande_AT);

  // Réponse du SIM7600.
  // Cette boucle vérifie s'il y a des données disponibles dans le tampon.
  // Ces données sont comparées avec la réponse attendue.

  x = 0;
  previous = millis();

  do
  {
    if (SIM7600.available() != 0)
    {
      reponse[x] = SIM7600.read();
      x++;
      // Comparaison des données
      if (strstr(reponse, reponse_Esperee) != NULL)
      {
        answer = 1;
        
        extract_1 = String(reponse);      
        extract_2 = extract_1.substring(index_debut,index_fin);
        extract_2.toCharArray(var_Extraction_Char,index_fin - index_debut);
             
      }       
    }
  
  } while ((answer == 0) && ((millis() - previous) < timeout));

  return answer;

}
