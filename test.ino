//ultrason---
int pinTrig = 2;
int pinEcho = 3;
long temps;
float distance;
//------
//buzzeur---
#include "pitches.h"

// notes in the melody:
int melody[] = {
  NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
  4, 8, 8, 4, 4, 4, 4, 4
};
//------
const int led = 4;
// ============================
void setup() {  // put your setup code here, to run once:
    Serial.begin(9600);  
   pinMode (led , OUTPUT);
  pinMode(pinTrig, OUTPUT);
  pinMode(pinEcho, INPUT);
  digitalWrite(pinTrig, LOW);  
}
void loop() {// put your main code here, to run repeatedly:
//affichage du distance
  digitalWrite(pinTrig, HIGH);        
  delayMicroseconds(10);
  digitalWrite(pinTrig, LOW);
  temps = pulseIn(pinEcho, HIGH); //On lit la durée d'état haut sur la broche "Echo"   
  if (temps > 25000) { //si la durée est supérieure à 25ms, l'onde est perdue             
    Serial.println("Echec de la mesure");
  }
  else {
    temps = temps/2; // On divise cette durée par deux pour n'avoir qu'un trajet
    distance = (temps*340)/10000.0; //On calcul la distance avec la formule d=v*t                
    Serial.print("Distance: ");
    Serial.print(distance);
    Serial.println(" cm");
  }
  delay(2000);
//----buzzeur et LED
if ( distance < 3){
    // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {

    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(8, melody[thisNote], noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
  }
  digitalWrite (led , HIGH); delay(1000);
  }else{digitalWrite (led , LOW);delay(1000);}    
}
