#include <EnableInterrupt.h>  // Permet realitzar interrupcions en un pin concret

// Es defineixen els pins
#define BUSY 3
#define RD_ 4     // RD_+CS_ units
#define RST 5
#define CONVST 6  // CONVSTA+CONVSTB units
#define OS0 8
#define OS1 9
#define OS2 10

#define DB0 14
#define DB1 15
#define DB2 16
#define DB3 17
#define DB4 18
#define DB5 19 
#define DB6 20
#define DB7 21
#define DB8 22
#define DB9 23
#define DB10 24
#define DB11 25
#define DB12 26
#define DB13 27
#define DB14 28
#define DB15 29

// Es declara un array de 16 enters
int rawData[16];

void setup() {

  // Es defineix la funció a realitzar durant la interrupció (ISR_)
  enableInterrupt(BUSY, ISR_, FALLING);

  // Es defineixen les entrades i sortides
  pinMode(RD_, OUTPUT);
  pinMode(RST, OUTPUT);
  pinMode(CONVST, OUTPUT);
  pinMode(BUSY, INPUT);

  pinMode(OS0, OUTPUT);
  pinMode(OS1, OUTPUT);
  pinMode(OS2, OUTPUT);

  // Es defineix la velocitat de transmisió de dades
  Serial.begin(115200);

  // Es reseteja l'ADC per a començar la conversió 
  digitalWrite(RST, HIGH);
  delayMicroseconds(10);
  digitalWrite(RST, LOW);

  // S'estableixen els pins de l'oversampling a zero
  digitalWrite(OS0, LOW);
  digitalWrite(OS1, LOW);
  digitalWrite(OS2, LOW);

  // S'estableixen els estats inicials de la resta de pins
  digitalWrite(CONVST, LOW);  
  digitalWrite(RD_, HIGH);
  digitalWrite(BUSY, LOW);  

  delayMicroseconds(1000);

}

void loop() {

  // S'atura la interrupció
  disableInterrupt(BUSY);

//  delayMicroseconds(40000);

 // S'inicialitza la conversió i es produeix la interrupció
  digitalWrite(CONVST, LOW);
  delayMicroseconds(10); 
  digitalWrite(CONVST, HIGH);
  enableInterrupt(BUSY, ISR_, FALLING);

}

// Es defineix la funció a realitzar durant la interrupció del pin BUSY
void ISR_ ()  {

  delayMicroseconds(1);
  digitalWrite(RD_, LOW); // Per a poder fer la lectura el pin RD_ (negat) ha d'estar actiu
  delayMicroseconds(1);
  lecturaDBpins();        // Es crida la funció que realitza la conversió
  digitalWrite(RD_, HIGH);

  Serial.println(" ");

}

// Es defineix la funció encarregada de fer la conversió a partir de l'array rawData
void lecturaDBpins()
{
  rawData[0] = digitalRead(DB15);

  if (rawData[0] > 0) {rawData[0] = 32768;} 
  rawData[1] = digitalRead(DB14);  

  if (rawData[1] > 0) {rawData[1] = 16384;}
  rawData[2] = digitalRead(DB13);

  if (rawData[2] > 0) {rawData[2] = 8192;}
  rawData[3] = digitalRead(DB12);

  if (rawData[3] > 0) {rawData[3] = 4096;}
  rawData[4] = digitalRead(DB11);

  if (rawData[4] > 0) {rawData[4] = 2048;}
  rawData[5] = digitalRead(DB10);

  if (rawData[5] > 0) {rawData[5] = 1024;}
  rawData[6] = digitalRead(DB9);

  if (rawData[6] > 0) {rawData[6] = 512;}
  rawData[7] = digitalRead(DB8);

  if (rawData[7] > 0) {rawData[7] = 256;}
  rawData[8] = digitalRead(DB7);

  if (rawData[8] > 0) {rawData[8] = 128;}
  rawData[9] = digitalRead(DB6);

  if (rawData[9] > 0) {rawData[9] = 64;}
  rawData[10] = digitalRead(DB5);

  if (rawData[10] > 0) {rawData[10] = 32;}
  rawData[11] = digitalRead(DB4);

  if (rawData[11] > 0) {rawData[11] = 16;}
  rawData[12] = digitalRead(DB3);

  if (rawData[12] > 0) {rawData[12] = 8;}
  rawData[13] = digitalRead(DB2);

  if (rawData[13] > 0) {rawData[13] = 4;}
  rawData[14] = digitalRead(DB1);

  if (rawData[14] > 0) {rawData[14] = 2;}
  rawData[15] = digitalRead(DB0);

  if (rawData[15] > 0) {rawData[15] = 1;}
  
  // S'imprimeix temps i lectura per a poder graficar els resultats
  Serial.print (millis());
  Serial.print (",");
  Serial.print (rawData[0]+rawData[1]+rawData[2]+rawData[3]+rawData[4]+rawData[5]+rawData[6]+rawData[7]+rawData[8]+rawData[9]+rawData[10]+rawData[11]+rawData[12]+rawData[13]+rawData[14]+rawData[15]-16365);
}
