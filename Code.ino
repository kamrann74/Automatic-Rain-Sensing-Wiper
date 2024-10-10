#include <Servo.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); // Creating an object of LiquidCrsytal named lcd

Servo myservo; // Creating an object of Servo Motor
float Vout;    // Ctreating a float variable for calculating Voltage Drop

int pos = 0;         // Setting the initial position of servo motor at 0 degree
int sensorValue = 0; // Setting the initial SensorValue to 0;

void setup()
{                       //
    Serial.begin(9600); // Setting up the Serial Montior with baud rate set to 9600
    lcd.init();         // Initialising the LCD panel
    myservo.attach(9);  // Informing Arduino that Servo Motor is attached to pin number 9
}

void loop()
{
    myservo.write(pos);                // Initially setting the Servo motor to 0 degree
    sensorValue = analogRead(A0);      // Reading the Voltage drop coming from Rain Drop senor and Storing it in variable named sensorValue
    Vout = (5. / 1023.) * sensorValue; // Calculating the actual voltage drop using the given formula, as the Voltage that arduino reads
                                       // ranges from 0-1023, where 0 represents 0 volts and 1023 represents 5 volts
    Serial.println(Vout);              // Printing the voltage on Serial Monitor

    // Condition for No Rain
    if (sensorValue > 800)
    {
        myservo.write(180);   // Initially set the wiper at 180 degree
        lcd.clear();          // Clear the LCD
        lcd.setCursor(0, 0);  // (Column no, row no)
        lcd.print("NO RAIN"); // Display "No Rain" on lCD Panel
        delay(1000);          // Keep a dealy of 1000 ms = 1 sec and then check for different conditions again
    }

    // Condition for LOW Rain
    if (sensorValue <= 800 && sensorValue > 300)
    {
        lcd.setCursor(0, 0);
        lcd.print("IT IS RAINING"); // Display It's Raining
        lcd.setCursor(0, 1);
        lcd.print("AMOUNT: LOW"); // Display "Amount: Low"
        // For Controlling the Speed of Wiper based on Voltage readings recieved from Rain Drop Sensor
        for (pos = 180; pos >= 0; pos -= 1)
        { // Rotations from 180 degree to 0 degree
            myservo.write(pos);
            delay(12); // For each degree decrement set a dealy of 12 ms
        }
        for (pos = 0; pos <= 180; pos += 1)
        { // Rotations from 0 degree to 180 degree
            myservo.write(pos);
            delay(12); // For each degree decrement set a dealy of 12 ms
        }
        delay(1000); // Keep a dealy of 1000 ms = 1 sec and then check for different conditions again
    }
    lcd.clear(); // Clear the LCD Panel

    // Condition when Amount of Rain is Medium
    if (sensorValue <= 300 && sensorValue > 200)
    {
        lcd.setCursor(0, 0);
        lcd.print("IT IS RAINING"); // Display It's Raining
        lcd.setCursor(0, 1);
        lcd.print("AMOUNT: MEDIUM"); // Display "Amount: Medium"
        // For Controlling the Speed of Wiper based on Voltage readings recieved from Rain Drop Sensor
        for (pos = 180; pos >= 0; pos -= 1)
        { // Rotations from 180 degree to 0 degree
            myservo.write(pos);
            delay(8); // For each degree decrement set a dealy of 8 ms
        }
        for (pos = 0; pos <= 180; pos += 1)
        { // Rotations from 0 degree to 180 degree
            myservo.write(pos);
            delay(8); // For each degree decrement set a dealy of 8 ms
        }
        delay(1000); // Keep a dealy of 1000 ms = 1 sec and then check for different conditions again
    }
    lcd.clear();

    // Condtion for High Rain
    if (sensorValue < 200)
    {
        lcd.setCursor(0, 0);
        lcd.print("IT IS RAINING"); // Display It's Raining
        lcd.setCursor(0, 1);
        lcd.print("AMOUNT: HIGH"); // Display "Amount: High"
                                   // For Controlling the Speed of Wiper based on Voltage readings recieved from Rain Drop Sensor
        for (pos = 180; pos >= 0; pos -= 1)
        { // Rotations from 180 degree to 0 degree
            myservo.write(pos);
            delay(3); // For each degree decrement set a dealy of 3 ms
        }
        for (pos = 0; pos <= 180; pos += 1)
        { // Rotations from 180 degree to 0 degree
            myservo.write(pos);
            delay(3); // For each degree decrement set a dealy of 3 ms
        }
        delay(1000); // Keep a dealy of 1000 ms = 1 sec and then check for different conditions again
    }
    lcd.clear(); // Clearing the LCD Panel
}
