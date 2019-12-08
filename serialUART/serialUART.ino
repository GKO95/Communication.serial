
#include <Wire.h>               /* Allow I2C/TWI serial communication */
#include <LiquidCrystal_I2C.h>  /* LiquidCrystal I2C (ver.1.1.2) by Frank de Brabander*/

int RESET = 4;

unsigned long count = 0;
char received;

LiquidCrystal_I2C lcd(0x3F, 16, 2); // Declare LiquidCrystal_I2C instance as lcd as 0x27 address and 16x2 display.

void setup() {

    // UNTRIGGER RESET.
    /*digitalWrite(RESET, HIGH); delay(200);
    pinMode(RESET, OUTPUT);*/
  
    // INITIALIZE LCD AND SHOW THAT IT IS READY FOR 1 SECOND.
    lcd.init();
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("INITIALIZED!");
    delay(500);

    // INITIALIZE SERIAL COMMUNICATION.
    Serial.begin(115200);
    while (!Serial){
        ;   // 
    }
    lcd.setCursor(0,1);
    lcd.print("CONNECTED!");
    delay(500);

    // STAND-BY FOR INCOMING SERIAL DATA...
    while(!Serial.available()){
        ;  
    }
}

void loop() {
    // CLEAR EXISING TEXT.
    lcd.clear();

    // IF THERE IS A NUMBER OF BYTE AVAILABLE FOR READING (SERIAL BUFFER: 64 BYTES).
    if(Serial.available() > 0){
        // READ RECEIVED DATA.
        received = Serial.read();
    }

    // PRINT THE RECEIVED SIGNAL.
    lcd.setCursor(0,0);
    lcd.print(received);  // BINARY, THUS CAN RECEIVE NUMBER 0 ~ 255 (8 BITS; 1 BYTE) ONLY.

    // PRINT THE COUNTER.
    lcd.setCursor(0,1);
    String counter = "CNT: " + String(count);
    lcd.print(counter);
    count += 1;

    displayBuffer();

}

// SHOW Serial.available() RETURN VALUE.
void displayBuffer() {

    lcd.setCursor(12,1); lcd.print("[");
    if (Serial.available()< 10) {
        lcd.setCursor(13,1); lcd.print("0");
        lcd.setCursor(14,1); lcd.print(Serial.available());
    }
    else {
        lcd.setCursor(13,1); lcd.print(Serial.available());
    }
    lcd.setCursor(15,1); lcd.print(']');

    delay(100);
}
