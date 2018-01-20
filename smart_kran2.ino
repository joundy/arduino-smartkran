
#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

int count = 0;
int countWudhu = 3;
int state = 0;

int menu = 0;

int btnHome = 2;
int btnMenu1 = 11;
int btnMenu2 = 12;

//ultrasonic
const int trigPin = 9;
const int echoPin = 10;
// defines variables
long duration;
int distance;

//lcd
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);

//led
int ledgreen = 3;
int ledred = 6;
int ledblue = 1;

//buzzer
int buzzer = 4;

//servo
int pin_servo = 5;
Servo myservo;

void setup() {
  //lcd
  lcd.begin(16, 2);
  lcd.clear();

  //servo
  myservo.attach(pin_servo);

  //ultrasonic
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  Serial.begin(9600); // Starts the serial communication

  //led
  pinMode( ledgreen, OUTPUT);
  pinMode( ledred, OUTPUT);

  //buzzer
  pinMode(buzzer, OUTPUT);

  //btn
  pinMode(btnHome, INPUT);
  pinMode(btnMenu1, INPUT);
  pinMode(btnMenu2, INPUT);
}

void showLcd(String top, String bottom, int countWudhu) {
  lcd.clear();
  lcd.print(top);
  lcd.setCursor(0, 1);
  lcd.print(bottom);
  if (bottom != "Selesai")
  {
    lcd.print(countWudhu);
    lcd.print("X");
  }
  //   Serial.print(countWudhu);
}

void loop() {

  if (menu == 0)
  {
    lcd.clear();
    lcd.print("STEAMTEL SMART");
    lcd.setCursor(0, 1);
    lcd.print("1 KRAN | 2 WUDHU");
    digitalWrite(ledred, LOW);
    digitalWrite(ledgreen, LOW);
    noTone(buzzer);
    myservo.write(20);
  }

  if (menu > 0) {

    //ultrasonic
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin on HIGH state for 10 micro seconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2;
    // Prints the distance on the Serial Monitor
    //Serial.print("Distance: ");
    //  Serial.println(distance);

    if (distance < 30) {
      if (state == 1) {
        count = count + 1;
        countWudhu =  countWudhu - 1;
        state = 0;
      }
      digitalWrite(ledgreen, HIGH);
      digitalWrite(ledred, LOW);
      tone(buzzer, 1000);

      myservo.write(115);
    }

    else {

      digitalWrite(ledred, HIGH);
      digitalWrite(ledgreen, LOW);
      noTone(buzzer);
      myservo.write(20);
      state = 1;

      if (countWudhu == 0)
      {
        countWudhu = 3;
      }

      if (menu == 1) {
        showLcd("STEMATEL KRAN", "Terbuka ", count);
      }

      if (menu == 2) {

        if (count >= 0 && count < 3) {
          showLcd("STEMATEL WUDHU", "Berkumur ", countWudhu);
        }
        else if (count >= 3 && count < 6) {
          showLcd("STEMATEL WUDHU", "Hidung ", countWudhu);
        }
        else if (count >= 6 && count < 9) {
          showLcd("STEMATEL WUDHU", "Muka ", countWudhu);
        }
        else if (count >= 9 && count < 12) {
          showLcd("STEMATEL WUDHU", "Tangan Kanan ", countWudhu);
        }
        else if (count >= 12 && count < 15) {
          showLcd("STEMATEL WUDHU", "Tangan Kiri ", countWudhu);
        }
        else if (count >= 15 && count < 18) {
          showLcd("STEMATEL WUDHU", "Rambut ", countWudhu);
        }
        else if (count >= 18 && count < 21) {
          showLcd("STEMATEL WUDHU", "Kedua Telinga ", countWudhu);
        }
        else if (count >= 21 && count < 24) {
          showLcd("STEMATEL WUDHU", "Kaki Kanan ", countWudhu);
        }
        else if (count >= 24 && count < 27) {
          showLcd("STEMATEL WUDHU", "Kaki Kiri ", countWudhu);
        }
        else if (count >= 27) {
          showLcd("STEMATEL WUDHU", "Selesai", countWudhu);
        }
      }
    }
  }
  
   if (digitalRead(btnHome) == HIGH) {
    Serial.println("MenuHome");
    menu = 0;
  }
  
  if (digitalRead(btnMenu1) == HIGH) {
    Serial.println("Menu1");
    menu = 1;
    count = 0;
    countWudhu = 3;
    state = 0;
  }
  if (digitalRead(btnMenu2) == HIGH) {
    Serial.println("Menu2");
    menu = 2;
    count = 0;
    countWudhu = 3;
    state = 0;
  }

  delay(200);
}
