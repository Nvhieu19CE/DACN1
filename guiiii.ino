#include <Wire.h>
#include <SPI.h>
#include <LoRa.h>
#include <DHT.h>

#define SS 15
#define RST 16
#define DIO0 2
 
int DHTPIN = D3;//pin where the dht11 is connected
const int DHTTYPE = DHT11;
//DHT dht(DHTPIN, DHTTYPE);
String data = "Subscribe Tech Vegan";
DHT dht(DHTPIN, DHT11);
 
String LoRaMessage = ""; 
 
void setup()
{
  pinMode(A0, INPUT);
  dht.begin();
  Serial.begin(9600);
  while (!Serial);
  Serial.println(F("LoRa Sender"));
  LoRa.setPins(SS, RST, DIO0);
//  LoRa.setTxPower(TX_P);
//  LoRa.setSyncWord(ENCRYPT);
if (!LoRa.begin(433E6)) {
    Serial.println(F("Starting LoRa failed!"));
    delay(100);
    while (1);
  }
}
 
void loop()
{
  float temperature = dht.readTemperature();
  float humidity = dht.readHumidity();
  int as = digitalRead(D4);
  int value = analogRead(A0); 
  value = map(value, 0, 1023, 100, 0);
  
//  if (value < 20) digitalWrite(D2, 1);
//  else digitalWrite(D2, 0); 
  
  Serial.print(F("Temperature = "));
  Serial.print(temperature);
  Serial.println(F("*C"));
 
  Serial.print(F("Humidity = "));
  Serial.print(humidity);
  Serial.println(F("%"));

  Serial.print(F("Value = "));
  Serial.print(value);
  Serial.println(F("%"));

  Serial.print("as: ");
  Serial.println(digitalRead(D4));
//  if (digitalRead(D4) == 1) digitalWrite(D2, 1);
//  else digitalWrite(D2, 0);

  Serial.println();
 
  LoRaMessage =  String(temperature) + "/" + String(value) + "&" + String(humidity) +"@"+ String(as) ;
               
  // send packet
  LoRa.beginPacket();
  LoRa.print(LoRaMessage);
  LoRa.endPacket();
  delay(5000);
}
