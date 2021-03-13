 
 
 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <EEPROM.h>
#define EEP_ADRS1 0
long data_1;
long data_2;
#define EEP_ADRS2 EEP_ADRS1 + sizeof(data_1)
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
//int DIN_PIN = 12;
int RELAY1 = 7;
int RELAY2 = 6;
int RELAY3 = 5;
int RELAY4 = 4;
int RELAY5 = 11;
int RELAY6 = 10;
int RELAY7 = 9;
int RELAY8 = 8;
#define OLED_RESET 3
Adafruit_SSD1306 display(OLED_RESET);
#define RELAY_ON  LOW  //rirei
#define RELAY_OFF HIGH

#define CCW    LOW
#define CW     HIGH

#define BRAKE  HIGH
#define RUN    LOW
#define key1ValueMin     96
#define key1ValueMax     106
#define key2ValueMin     144
#define key2ValueMax     159
#define key3ValueMin     193
#define key3ValueMax     213
#define key4ValueMin     242
#define key4ValueMax     255
int adPin = A0;    // select the input pin for the potentiometer
int keyValue;
int keyValue_r;
int keyValue_rr;
int x = 28;
int Y = 80000UL;
//key scan
int key_scan(void)
{
  int adValue;
  int key;

  adValue = analogRead(adPin);//read ad Value

  adValue = adValue / 4;

  if (adValue >= key1ValueMin && adValue <= key1ValueMax) // k1
  {
    key = 1;
  }
  else if (adValue >= key2ValueMin && adValue <= key2ValueMax) // k2
  {
    key = 2;
  }
  else if (adValue >= key3ValueMin && adValue <= key3ValueMax) // k3
  {
    key = 3;
  }
  else if (adValue >= key4ValueMin) // k4
  {
    key = 4;
  }
  else //Invalid value
  {
    key = 0;
  }

  return key;

}

boolean A = false;
boolean running = false;
boolean wait = false;
#if (SSD1306_LCDHEIGHT != 64)
//#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif


void setup()   {

  Serial.begin(9600);
  EEPROM.get(EEP_ADRS1, data_1);
  EEPROM.get(EEP_ADRS2, data_2);
  Serial.println("DHTxx test!");
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)

  digitalWrite(RELAY1, RELAY_OFF);
  digitalWrite(RELAY2, RELAY_OFF);
  digitalWrite(RELAY3, RELAY_OFF);
  digitalWrite(RELAY4, RELAY_OFF);
  digitalWrite(RELAY5, RELAY_OFF);
  digitalWrite(RELAY6, RELAY_OFF);
  digitalWrite(RELAY7, RELAY_OFF);
  digitalWrite(RELAY8, RELAY_OFF);
  // pinMode( DIN_PIN, INPUT_PULLUP );
  pinMode(RELAY1, OUTPUT);
  pinMode(RELAY2, OUTPUT);
  pinMode(RELAY3, OUTPUT);
  pinMode(RELAY4, OUTPUT);
  pinMode(RELAY5, OUTPUT);
  pinMode(RELAY6, OUTPUT);
  pinMode(RELAY7, OUTPUT);
  pinMode(RELAY8, OUTPUT);
}
void timecount()
{
  //Save three key scan value
  keyValue_rr = keyValue_r;
  keyValue_r = keyValue;
  keyValue = key_scan();

  //Three scanned values are the same, indicating that key is valid
  if (keyValue > 0 && keyValue == keyValue_r && keyValue_r == keyValue_rr)
  {
    Serial.print("keyValue = ");
    Serial.println(keyValue);
  }
  if (keyValue == 3)
  {
    unsigned long time;//「time」をunsigned longで変数宣言
    rireyset1();
    time = millis() / 1000; //プログラム実行からの経過時間(us)をtimeに返す

    Serial.println("");

    Serial.print(time);//経過時間(us)を送信
    Serial.println("");//文字列「us」を送信、改行
    data_1 = time;

    Serial.println("");
    Serial.print(data_1);

    EEPROM.put(EEP_ADRS1, data_1);

    Serial.println("date 1=");
    Serial.print(data_1);


    delay(200); //Each scan interval 100-200MS
  //  A = !A ;
  }

  if (keyValue == 4)
  {
    unsigned long time;//「time」をunsigned longで変数宣言
  rireyset2();
    time = millis() / 1000; //プログラム実行からの経過時間(us)をtimeに返す

    Serial.println("");

    Serial.print(time);//経過時間(us)を送信
    Serial.println("");//文字列「us」を送信、改行
    data_2 = time;

    Serial.println("");
    Serial.print(data_2);


    EEPROM.put(EEP_ADRS2, data_2);
    // digitalWrite(motor1pin1,LOW );
    //   digitalWrite(motor1pin2, LOW);
    Serial.println("date 2=");
    Serial.print(data_2);


    delay(200); //Each scan interval 100-200MS
 //   digitalWrite(RELAY3, CCW );
 //   digitalWrite(RELAY4, CCW );

  //  digitalWrite(RELAY1, CCW );
  //  digitalWrite(RELAY2, CCW );
  }

}

void rireyset1()
{

  digitalWrite(RELAY3, CCW);
  digitalWrite(RELAY4, CCW);

  digitalWrite(RELAY1, CW  );
  digitalWrite(RELAY2, CW );

}
void rireyset2()
{
 digitalWrite(RELAY3, CCW );
  digitalWrite(RELAY4, CCW );

  digitalWrite(RELAY1, CCW );
  digitalWrite(RELAY2, CCW );

 
}
void rirey1up()
{
  digitalWrite(RELAY3, CCW);
  digitalWrite(RELAY4, CCW);

  digitalWrite(RELAY1, CW  );
  digitalWrite(RELAY2, CW );
  delay(data_1*1000);
  digitalWrite(RELAY1, CW  );
  digitalWrite(RELAY2, CCW);
  delay(1000);
  digitalWrite(RELAY3, CW);
  digitalWrite(RELAY4, CW);
  digitalWrite(RELAY2, CW );
  //running ==1;
  delay(1000);

}
void rirey2up()
{
  digitalWrite(RELAY7, CCW);
  digitalWrite(RELAY8, CCW);

  digitalWrite(RELAY5, CW  );
  digitalWrite(RELAY6, CW );
  delay(data_1*1000);

  digitalWrite(RELAY5, CW  );
  digitalWrite(RELAY6, CCW);
  delay(1000);
  digitalWrite(RELAY7, CW);
  digitalWrite(RELAY8, CW);
  //wait ==1;
  delay(1000);
}
void rirey1down()
{
  digitalWrite(RELAY3, CCW );
  digitalWrite(RELAY4, CCW );

  digitalWrite(RELAY1, CCW );
  digitalWrite(RELAY2, CCW );
  delay(data_2*1000);

  digitalWrite(RELAY1, CW  );
  digitalWrite(RELAY2, CCW);
  delay(1000);
  digitalWrite(RELAY3, CW);
  digitalWrite(RELAY4, CW);
  digitalWrite(RELAY2, CW);
  // running ==0;
  delay(1000);
}
void rirey2down()
{
  digitalWrite(RELAY7, CCW );
  digitalWrite(RELAY8, CCW );

  digitalWrite(RELAY5, CCW );
  digitalWrite(RELAY6, CCW );
  delay(data_2*1000);

  digitalWrite(RELAY5, CW  );
  digitalWrite(RELAY6, CCW);
  delay(1000);
  digitalWrite(RELAY7, CW);
  digitalWrite(RELAY8, CW);
  //  wait ==0;
  delay(1000);
}


void loop()
{
  
    timecount();
  


  EEPROM.get(EEP_ADRS1, data_1);
  EEPROM.get(EEP_ADRS2, data_2);
  display.display(); //I love Adafruit :D
  delay(1000);
  // int value;
  display.clearDisplay();   // Clear the buffer.

  Serial.begin(9600);
  Serial.print(data_1);
  Serial.print(data_2);
  Serial.println("DHT11 test!");
  dht.begin();

  //digitalWrite(RELAY1, RELAY_OFF);//rirei
  // digitalWrite(RELAY2, RELAY_OFF);

  //pinMode(RELAY1, OUTPUT);
  // pinMode(RELAY2, OUTPUT);
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  //Save three key scan value
  keyValue_rr = keyValue_r;
  keyValue_r = keyValue;
  keyValue = key_scan();

  //Three scanned values are the same, indicating that key is valid
  if (keyValue > 0 && keyValue == keyValue_r && keyValue_r == keyValue_rr)
  {
    Serial.print("keyValue = ");
    Serial.println(keyValue);
  
  if (keyValue == 1)
  {
    x = x + 1;
    Serial.print("x =");
    Serial.println(x);

    delay(200); //Each scan interval 100-200MS

  }
  if (keyValue == 2)
  {
    x = x - 1;
    Serial.print("x =");
    Serial.println(x);

    delay(200); //Each scan interval 100-200MS
  }
  if (keyValue == 3)
  {
    Y = Y + 1000;
    Serial.print("Y =");
    Serial.println(Y);

    delay(200); //Each scan interval 100-200MS

  }
  if (keyValue == 4)
  {
    Y = Y - 1000;
    Serial.print("Y =");
    Serial.println(Y);

    delay(200); //Each scan interva

  }
  }
  Serial.print("Humidity: ");
  Serial.print(h);
  Serial.println(" %\t");
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.println(" *C ");
  //  Serial.print(value) ;
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("tmp");
  display.setCursor(40, 0);
  display.println((int)t);
  display.setTextSize(1);
  display.setCursor(70, 0);
  display.println("o");
  display.setTextSize(2);
  display.setCursor(80, 0);

  display.println(running);
  display.setCursor(100, 0);
  display.println(x);
  display.setTextSize(1);
  display.setCursor(0, 18);
  display.println("ham");
  display.setCursor(20, 18);
  display.println((int)h);
  display.setTextSize(2);
  display.setCursor(40, 18);
  display.println(data_1);
  display.setCursor(90, 18);
  display.println(data_2);
  display.display();
  delay(1000);

  if (t >= x && running == 0) {
    //  digitalWrite(RELAY3, CCW);
    //  digitalWrite(RELAY4, CCW);

    //  digitalWrite(RELAY4, CW);

    //   delay(1000);
    rirey1up();
    rirey2up();
    running = !running;
  }

  /* (t >= 30 && wait == 0) {
    digitalWrite(RELAY3, RUN );
    digitalWrite(RELAY4, RUN );

    digitalWrite(RELAY1, CW  );
    digitalWrite(RELAY2, RUN );
    delay(3200000UL);

    digitalWrite(RELAY1, CW  );
    digitalWrite(RELAY2, BRAKE);
    delay(1000);

    wait = !wait;
    delay(1000);
    }

    if (t < 28 && wait == 1) {
    digitalWrite(RELAY1, CCW );
    digitalWrite(RELAY2, RUN );
    delay(1600000UL);

    digitalWrite(RELAY1, CCW  );
    digitalWrite(RELAY2, BRAKE);
    delay(1000);

    wait = !wait;
    delay(1000);
    }
  */
  if (t <= (x - 2) && running == 1) {
    // digitalWrite(RELAY3, CCW );
    //  digitalWrite(RELAY4, CCW );

    //  digitalWrite(RELAY1, CCW );
    //  digitalWrite(RELAY2, CCW );
    //  delay(130000UL);

    //  digitalWrite(RELAY1, CW  );
    //  digitalWrite(RELAY2, CCW);
    //   delay(1000);
    //   digitalWrite(RELAY3, CW);
    //  digitalWrite(RELAY4, CW);

    //   delay(1000);
    rirey1down();
    rirey2down();
    running = !running;
  }


}
