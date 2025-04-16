#include <PS2X_lib.h>
#include <Servo.h>

Servo myservo; // Classe Servo motor 

PS2X ps2x; // Classe PS2 Controller

#define PS2_CLK  51
#define PS2_CMD  52
#define PS2_ATT  50
#define PS2_DAT  53
#define IN1 40
#define IN2 38
#define DCR 47

void Setup_controller(){
    Serial.begin(9600);
    int error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_ATT, PS2_DAT, true, false);
    
    if (error != 0) {
        Serial.println("⚠️ PS2 Controller NOT found! Check wiring.");
        while (true); // Stop execution if no controller is found
    }

    byte type = ps2x.readType();
    Serial.print("PS2 Controller Type: ");
    if (type == 0) Serial.println("Unknown");
    else if (type == 1) Serial.println("DualShock");
    else Serial.println("Other");
}

void Setup_servo() {
  myservo.attach(9);
}

void Setup_DCpince () {
  pinMode(IN1, OUTPUT); 
  pinMode(IN2, OUTPUT);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

}

void Setup_DCressort () {
  pinMode(DCR, OUTPUT);

  digitalWrite(DCR, LOW);
}



