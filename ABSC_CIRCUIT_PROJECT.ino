#include <Adafruit_LiquidCrystal.h>

#include <Wire.h>
#include <hd44780.h>
#include <hd44780ioClass/hd44780_I2Cexp.h> // include i/o class header
hd44780_I2Cexp lcd; // declare lcd object: auto locate & config display for hd44780 chip

#include <LiquidCrystal_I2C.h>
const int RELAY_PIN1 = 3;  
const int RELAY_PIN2 = 5;
float voltageB;
float voltageA;
#define BAT1_MIN 7.0  // minimum battery voltage for 12V system
#define BAT1_MAX 7.0 // maximum battery voltage for 12V system
#define BAT2_MIN 3.0  // minimum battery voltage for 12V system
#define BAT2_MAX 7.5 // maximum battery voltage for 12V system
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  lcd.begin(20,4);
  lcd.init();
  lcd.backlight();
  lcd.clear();  
pinMode(RELAY_PIN1, OUTPUT);
pinMode(RELAY_PIN2, OUTPUT);
 
}
// the loop routine runs over and over again forever:
void loop() {
  int Battery1 = analogRead(A0);
  int Battery2 = analogRead(A1);
  //12V = ADC value 1024 => 1 ADC value = (7.5/1024)Volt= 0.00732Volt
    // Vout=Vin*R2/(R1+R2) => Vin = Vout*(R1+R2)/R2   R1=110 and R2=9
  float voltageA = Battery1 *0.008*(110/9);
  Serial.println("BATT 1 VOLTAGE : ");
  Serial.print(voltageA);
  float voltageB = Battery2 * 0.0076*(111/9);
  Serial.println("BATT 2 VOLTAGE : ");
  Serial.print(voltageB);
  lcd.setCursor(0,0);
  lcd.print(" BATT1 VOLTAGE:");
  lcd.print(voltageA);
  lcd.print("V");
  lcd.print(" ");
  lcd.setCursor(0,3);
  lcd.print(" BATT2 VOLTAGE:");
  lcd.print(voltageB);
  lcd.print("V");
  lcd.print(" ");
 lcd.setCursor(0, 1);
  lcd.print("AUTOMATIC BATT SHIFT");
digitalWrite(RELAY_PIN1,LOW);  // default value of pwm duty cycle
  digitalWrite(RELAY_PIN2,HIGH);  // default load state is OFFF
  lcd.setCursor(0,2);
  lcd.print(" BATTERY 1");
  delay(100);
 /* digitalWrite(RELAY_PIN1,HIGH);
  digitalWrite(RELAY_PIN2,LOW);
  lcd.setCursor(0,2);
  lcd.print(" BATTERY 2");*/
}
void system_voltage(void)
{
  if ((voltageB>45))
  {
  digitalWrite(RELAY_PIN1,HIGH);
  digitalWrite(RELAY_PIN2,LOW);
  lcd.setCursor(0,2);
  lcd.print(" BATTERY 2");
  }
}
