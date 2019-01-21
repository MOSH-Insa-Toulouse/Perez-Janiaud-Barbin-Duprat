/*
pin 11 : moteur
pin 6 : servo
pin 3 : rxPin arduino => TX module BT
pin 5 : txPin arduino => RX module BT
*/


#include <SoftwareSerial.h>
//#include <TimerOne.h>
#include <Servo.h>
#include "Wire.h"

#define rxPin 3
#define txPin 5

Servo myservo ; //création objet "servo"
int serialA=0; // variable de reception de donnée via rxPin
const int speed_serial = 9600; // vitesse communication Bluetooth
SoftwareSerial mySerial(rxPin,txPin); //creation serial BT
int pinMoteur = 11; // moteur pin 11 (PWM)

bool go=false; // variable contrôle start/stop
int vitesse=40; //vitesse moteur (entre 0 et 100)
int pos=90 ; //position servo (angle entre 0 et 180°)

/*  
 *   Configuration du module bluetooth
 */
 /*
void setupBlueToothConnection() // fonction de configuration du module bluetooth
{
  Serial.begin(speed_serial); //vitesse de bluetooth
                              //initialisation de la connexion série (avec le module bluetooth)
//  Serial.print("\r\n+STBD=115200\r\n"); // fixe la vitesse du bluetooth
  Serial.print("\r\n+STBD=9600\r\n"); // fixe la vitesse du bluetooth
  Serial.print("\r\n+STWMOD=0\r\n"); //bluetooth en mode esclave
  Serial.print("\r\n+STNA=Arduino"); //nom de l'appareil
  Serial.print("\r\n+STPIN=0000\r\n");//code pin "0000"
  Serial.print("\r\n+STOAUT=1\r\n"); // Permit Paired device to connect me
  Serial.print("\r\n+STAUTO=0\r\n"); // Auto-connection should be forbidden here
  delay(2000); // This delay is required.
  Serial.print("\r\n+INQ=1\r\n"); //make the slave bluetooth inquirable 
  delay(2000); // This delay is required.
  Serial.flush();
}*/

 
/*
 * setup
 */
 
void setup()
{
  // define pin modes for tx, rx pins:
  pinMode(rxPin,INPUT);
  pinMode(txPin,OUTPUT);
  // ouverture serial
  mySerial.begin(speed_serial);
  //Serial.begin(speed_serial);
  
  myservo.attach(6); //Pin Servo
}


/*
 * main
 */
void loop() {

  //lecture BT uniquement si donnée disponible
  if(mySerial.available()>0) {

    //lecture variable
    serialA=mySerial.read();
    //affichage valeur
    //Serial.print("value : ");
    //Serial.println(serialA);
    
    if (serialA<=100 && serialA>=0){
         // slider vitesse
         vitesse = serialA*255/100;
         //Serial.print("VITESSE :");
         //Serial.println(vitesse);
      }
    else if (serialA>=101 and serialA<=200){
        //slider position
        pos=map(serialA, 101, 200, 70, 110);
        //Serial.print("pos :");
        //Serial.println(pos);
        dir(pos);
      }
    else if (serialA==201){
        //clic_avancer => changement état go to start/stop
        /*if (go==true){
          go=false;
          Serial.println("stop");
        }
        else if (go==false){
          go=true;
          Serial.println("start");
        }*/
        go= (!go);
      }
    /* ancien bouton  
    else if (serialA==202){
        //clicl_reculer
        go=false;
        Serial.println("STOP !!");
      }
    else if (serialA==203){
        //clic_gauche   
        pos-=30;   
        Serial.println("gauche");   
      }
    else if (serialA==204){
        //clic_droit
        pos+=30;
        Serial.println("droite");
      }
    */
    }     

  if (go==true){
    //Serial.print("et c'est parti à ");
    //Serial.print(vitesse);
    //Serial.println(" milliard de km/h");
    avancer(vitesse);
    //dir(pos);
  }
  else {
    avancer(0);
    //dir(pos);
  }
  

 //Serial.print("AT+INQ?\r\n");  
 delay(100);
}



/*
 * Fonction avancer (changement de vitesse moteur)
 */
void avancer(int vitesse)
{
  analogWrite(pinMoteur, vitesse); // réglage vitesse moteur  
}


/*
 * contrôle direction (servo entre 0 et 180°)
 */ 
void dir(int pos)
{
  int pos_act = myservo.read();
  int i=0;
  if (pos_act<pos) {
    for(i = pos_act; i<pos ; i++)  // goes from 0 degrees to 180 degrees
    {                                  // in steps of 1 degree
      myservo.write(i);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
  else if (pos_act>pos) {    
    for(i = pos_act; i>=pos ; i--)  // goes from 0 degrees to 180 degrees
    {                                  // in steps of 1 degree
      myservo.write(i);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
  }
}
  
/*fonction acceleration/decceleration pour un contrôle plus fin de la vitesse
  void accelerer(int vitesse)
  {
    int vitesse_conv = vitesse*255/100 ; //conversion vitesse
    for( int i = 30; i = vitesse_conv; i++ ){
      analogWrite( pinMoteur, i );
      delay(50); // delay pour avoir un progression
    }
  }

void decelerer(int vitesse)
{
  int vitesse_conv = vitesse*255/100 ; //conversion vitesse
  for( int i = vitesse_conv; i > 0; i-- ){
    analogWrite( pinMoteur, i );
    delay(50); // delay pour avoir un progression
  }
}

}*/
