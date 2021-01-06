#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27, 16, 3);

float distance = 0;
int section = 0;
int add_button = 0;
float Counter = 0;
int button = 0;
int reset_button = 0;
const int buzzer = 3;


void setup() {
  lcd.init();
  lcd.backlight();
  pinMode(buzzer, OUTPUT);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print("activated");
  lcd.setCursor(2, 0);
  lcd.print("HELLO!");
  lcd.setCursor(2, 1);
  lcd.print("By Sam Howell");
  delay(1500);
  lcd.clear();
}

void loop() {
  //reset_button = digitalRead(8);
  //button = digitalRead(7);
  look_for_reed();
}

void reed_detected(){
  reset_button = digitalRead(8);
  button = digitalRead(7);
  Counter = Counter +0.5;
  Serial.print("count: ");
  Serial.println(Counter);
  lcd.setCursor(2, 0);
  lcd.print("Distance: ");
  lcd.setCursor(12, 0);
  lcd.print(Counter);
  lcd.setCursor(2, 1);
  lcd.print("Alarm at: ");
  lcd.setCursor(12, 1);
  lcd.print(distance);

  
  //delay(500);
  if (reset_button == 0) reset_count();
  else if (button == 0) still_active();
  else if(button == 1) look_for_reed(); 
  
}

void still_active(){
  reset_button = digitalRead(8);
  button = digitalRead(7);
  if (reset_button == 0) reset_count();
  else if (button == 0) still_active();
  else if (button == 1) look_for_reed(); 
}

void look_for_reed(){
  //lcd.clear();
  add_button = digitalRead(9);
  reset_button = digitalRead(8);
  button = digitalRead(7);

  if ((reset_button == 0) && (add_button == 0)) reset_all();
  else if (reset_button == 0) reset_count();
  else if (button == 0) reed_detected();
  else if (add_button == 0) add_dist();
  else if ((distance > 1) && (distance <= Counter)) alarm();
  else if(button == 1){
    Serial.print("count: ");
    Serial.println(Counter);
    lcd.setCursor(2, 0);
    lcd.print("Distance: ");
    lcd.setCursor(12, 0);
    lcd.print(Counter);
    lcd.setCursor(2, 1);
    lcd.print("Alarm at: ");
    lcd.setCursor(12, 1);
    lcd.print(distance);
    lcd.setCursor(2, 3);
    lcd.print("Sections: ");
    lcd.setCursor(12, 3);
    lcd.print(section);
    
   // lcd.setCursor(5, 1);
   // lcd.print("m");
  }
  delay(90);
}

void reset_count(){
  Counter = 0;
  lcd.clear();
  Serial.print("Distance: ");
  Serial.println(Counter);
  
  delay(90);
  make_noise();
  look_for_reed();
}

void make_noise(){
  tone(buzzer, 900, 200);
  delay(100);
  noTone;
  delay(100);
}

void alarm(){
  loud();
  loud();
  loud();
  loud();
  loud();
  loud();
  Counter = 0;
  section = section + 1;
  
}

void loud(){
  tone(buzzer, 800, 900);
  delay(500);
  noTone(buzzer);
  tone(buzzer, 400, 900);
  delay(500);
  noTone(buzzer);

}

void add_dist(){
  distance = distance + 0.5;
  lcd.setCursor(2, 1);
  lcd.print("Alarm at: ");
  lcd.setCursor(12, 1);
  lcd.print(distance);
  make_noise();
  delay(500);
}

void reset_all(){
  Counter = 0;
  distance = 0;
  lcd.clear();
  make_noise();
  delay(300);
  tone(buzzer, 500, 200);
  delay(200);
  tone(buzzer, 800, 200);
  delay(200);
  tone(buzzer, 500, 200);
  delay(200);
  tone(buzzer, 1200, 200);
  delay(1000);
}
