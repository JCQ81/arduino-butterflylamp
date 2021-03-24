/*  Switch 1: power on/off
 *  Switch 2: Mode (dimm/constant)
 *  Button  : power on with timer
 */

#define pRAND 0

#define pLED1 3
#define pLED2 5
#define pLED3 6
#define pLED4 9
#define pLED5 10
#define pLED6 11

#define pPower   2
#define pBtnMode 12

#define ldir  0
#define lcur  1
#define ltrn  2

byte ledArr[6][3];  // [direction,current,turningpoint]
byte lstep;
long cycle;

void setup() {  
  pinMode(pPower, OUTPUT);
  digitalWrite(pPower, HIGH);
  pinMode(pBtnMode, INPUT_PULLUP);
  pinMode(pLED1, OUTPUT);
  pinMode(pLED2, OUTPUT);
  pinMode(pLED3, OUTPUT);   
  pinMode(pLED4, OUTPUT);   
  pinMode(pLED5, OUTPUT);   
  pinMode(pLED6, OUTPUT);   
  randomSeed(analogRead(pRAND));
  for (byte i = 0; i < 6; i = i + 1) {
    for (byte j = 0; j < 3; j = j + 1)
      ledArr[i][j] = 0;    
    ledArr[i][ltrn] = 20+5*i;
  } 
  cycle = 1;

  // If mode = on never activate loop()
  if (digitalRead(pBtnMode) == LOW) {
    analogWrite(pLED1, 250);
    analogWrite(pLED2, 250);
    analogWrite(pLED3, 250);
    analogWrite(pLED4, 250);
    analogWrite(pLED5, 250);
    analogWrite(pLED6, 250);
    delay(600000);
    digitalWrite(pPower, LOW);
    while (true) {
      delay(1000);
    }
  }
}

void loop() {    
  for (byte i = 0; i < 6; i = i+ 1) { 
    lstep = 1;
    if ( ledArr[i][lcur] > 20) {
      lstep = 2;
    }      
    if ( ledArr[i][ldir] == 0 ) {            
      if ( ledArr[i][lcur] <= ledArr[i][ltrn] ) {
        ledArr[i][lcur] = ledArr[i][lcur] + lstep;
      } else {
        ledArr[i][ldir] = 1;
      }
    } else {
      if ( ledArr[i][lcur] >= 2 ) {
        ledArr[i][lcur] = ledArr[i][lcur] - lstep;
      } else {
        ledArr[i][ldir] = 0;
        ledArr[i][ltrn] = random(10,50);
      }
    }
  }  
  analogWrite(pLED1, ledArr[0][lcur]*5);
  analogWrite(pLED2, ledArr[2][lcur]*5);
  analogWrite(pLED3, ledArr[4][lcur]*5);
  analogWrite(pLED4, ledArr[3][lcur]*5);
  analogWrite(pLED5, ledArr[1][lcur]*5);
  analogWrite(pLED6, ledArr[5][lcur]*5); 
  
  delay(80);

  cycle = cycle + 1;
  if (cycle > 7500) // (1min = approx. 60000 / delay)
    digitalWrite(pPower, LOW);  
}
