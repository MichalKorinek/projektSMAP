int senzor = A1; // analogový pin A1 připojený k pinu fotorezistoru


// piny pro připojení Trig a Echo z modulu
int pTrig = 4;
int pEcho = 5;
// inicializace proměnných, do kterých se uloží data
long odezva, vzdalenost;



#include <Servo.h>     //zahrnutí knihovny pro ovládání servo motoru
Servo myservoOn;         //každý motor má svou instanci třídy Servo
int posOn = 0;           //proměnná obsahující pozici motoru (úhel natočení)
Servo myservoOff;
int posOff = 0;



int rangeTimeStamp = 0; // proměnná inkrementující se pokud uživatel odejde od stolu
int onOff = 0;         //proměnná pro uchovávání informace, zda je lampička zapnutá

 
void setup () {
  pinMode(pTrig, OUTPUT);
  pinMode(pEcho, INPUT);
  myservoOn.attach(9);   //motor je připojen na pin č. 9
  myservoOff.attach(10);
  Serial.begin (9600); // inicializace sériového monitoru
}
 
void loop () {


  //Fotorezistor
  int war = analogRead (senzor); // přečíst hodnotu z A1
  delay(500); // prodleva mezi po sobě následujícími odečty

  // podmínka citlivosti světla
  if(war > 750){ 
    if(onOff == 1){
      for(posOff = 0; posOff <= 180; posOff += 1) 
    {
      myservoOff.write(posOff);  
      delay(15);           
    }
    for(posOff = 180; posOff >= 0; posOff -= 1) 
    {
      myservoOff.write(posOff);  
      delay(15);           
    }
    onOff = 0; //identifikační proměnná zda je lampička
               //zapnutá nebo ne
    }    
  }

  else {
  digitalWrite(pTrig, LOW);
  delayMicroseconds(2);
  digitalWrite(pTrig, HIGH);
  delayMicroseconds(5);
  digitalWrite(pTrig, LOW);
  // ultrazvukový senzor
  // pomocí funkce pulseIn získáme následně
  // délku pulzu v mikrosekundách (us)
  odezva = pulseIn(pEcho, HIGH);
  // přepočet získaného času na vzdálenost v cm
  vzdalenost = odezva / 58.31;
  
 
  if(onOff == 0 && rangeTimeStamp < 15){
    for(posOn = 0; posOn <= 180; posOn += 1) 
    {
      myservoOn.write(posOn);  
      delay(15);           
    }
    for(posOn = 180; posOn >= 0; posOn -= 1) 
    {
      myservoOn.write(posOn);  
      delay(15);           
    }
    onOff = 1;
         
  }

  // kontrola uživatele u stolu
  if(vzdalenost > 63){
    rangeTimeStamp += 1;
  } else rangeTimeStamp = 0;
  if(rangeTimeStamp >= 15 && onOff == 1){
    for(posOff = 0; posOff <= 180; posOff += 1)
    {
      myservoOff.write(posOff); 
      delay(15);           
    }
    for(posOff = 180; posOff >= 0; posOff -= 1) 
    {
      myservoOff.write(posOff);  
      delay(15);           
    }
    onOff = 0;
  }
  }
  
  












    
    
  

  
  


  



  
}
