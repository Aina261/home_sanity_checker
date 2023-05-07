#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_CCS811.h>


#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BME280 bme;
Adafruit_CCS811 ccs;
Adafruit_SSD1306 display = Adafruit_SSD1306(128, 64, &Wire);

void setup() {
  Serial.begin(115200);
  Wire.begin();
   
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x64)
  display.display();
  delay(100);
  display.clearDisplay();
  display.display();
  display.setTextSize(2.3);
  display.setTextColor(WHITE);
  
  bool bme_status = bme.begin(0x76);
  bool ccs811_status = ccs.begin(0x5A);

  if (!bme_status) {
    Serial.println("Could not find a valid BME280 sensor");
    while (1);
  }

  if(!ccs811_status){
    Serial.println("Could not find a valid CCS811 sensor");
    while(1);
  }
}

void loop() { 
  
  display.setCursor(0,0);
  display.clearDisplay();
  
  display.print(bme.readTemperature()); display.println(" C");
  display.print(bme.readHumidity()); display.println(" %");
  if(ccs.available()){
    if(!ccs.readData()){
      display.print(ccs.geteCO2()); display.println(" PPM");
      display.print(ccs.getTVOC()); display.println(" PPB");
    } else {
      display.print("Waiting CCS811 data");
    }
  } else {
    display.print("Waiting CCS811 data");
  }

  display.display();
  delay(1000);
  
}