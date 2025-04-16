#include <AFMotor.h>
#include <PS2X_lib.h>
#include <Servo.h>
#include "setup.h";


#define IN1 40
#define IN2 38
#define DCR 47


// Define motors
AF_DCMotor motor_FL(2);  // Front Left
AF_DCMotor motor_FR(1);  // Front Right
AF_DCMotor motor_BL(3);  // Back Left
AF_DCMotor motor_BR(4);  // Back Right



int speed = 200;
int position = 125;



void setup() {
  // put your setup code here, to run once:
  Setup_controller();  // Connexion à la manette

  Setup_servo();

  Setup_DCpince();

  Setup_DCressort();

  // Set all motors to stop initially
  motor_FL.run(RELEASE);
  motor_FR.run(RELEASE);
  motor_BL.run(RELEASE);
  motor_BR.run(RELEASE);

  // Set all motors to speed
  motor_FL.setSpeed(speed);
  motor_FR.setSpeed(speed);
  motor_BL.setSpeed(speed);
  motor_BR.setSpeed(speed);
}

void loop() {
  // put your main code here, to run repeatedly:
  ps2x.read_gamepad(false, false);  // Lire le signal de la manette


  //Servo motor for claw

  if (ps2x.Button(PSB_PAD_LEFT)) {
    Serial.println("OPENING CLAW");
    position = constrain(position + 3, 10, 180);
    
    Serial.println(position);

  } else if (ps2x.Button(PSB_PAD_RIGHT)) {
    Serial.println("CLOSING CLAW");
    position = constrain(position - 3, 10, 180);
    Serial.println(position);

  }

  myservo.write(position);


  if (ps2x.Button(PSB_PAD_UP)) {
    Serial.println("CLAW UPWARD");
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
  } else if (ps2x.Button(PSB_PAD_DOWN)) {
    Serial.println("CLAW DOWNWARD");
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  } else {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, LOW);
  }

  if (ps2x.Button(PSB_R3)){
    digitalWrite(DCR, HIGH);
  }

  


  if (ps2x.Button(PSB_GREEN)) {
    Serial.println("SPEED UP");
    speed = constrain(speed + 5, 0, 255);  // Prevent speed from going below 0
    motor_FL.setSpeed(speed);
    motor_FR.setSpeed(speed);
    motor_BL.setSpeed(speed);
    motor_BR.setSpeed(speed);
    Serial.println(speed);
  } else if (ps2x.Button(PSB_BLUE)) {
    Serial.println("SPEED DOWN");
    speed = constrain(speed - 5, 0, 255);  // Prevent speed from exceeding 255
    motor_FL.setSpeed(speed);
    motor_FR.setSpeed(speed);
    motor_BL.setSpeed(speed);
    motor_BR.setSpeed(speed);
    Serial.println(speed);
  }

  bool moving = false;

  if (ps2x.Button(PSB_L1)) {
    moveForward();
    moving = true;
  } else if (ps2x.Button(PSB_R1)) {
    moveBackward();
    moving = true;
  } else if (ps2x.Button(PSB_L2)) {
    strafeLeft();
    moving = true;
  } else if (ps2x.Button(PSB_R2)) {
    strafeRight();
    moving = true;
  } else if (ps2x.Button(PSB_CIRCLE)) {
    rotateRight();
    moving = true;
  } else if (ps2x.Button(PSB_SQUARE)) {
    rotateLeft();
    moving = true;
  }

  if (!moving) {  // Stop motors ONLY if no movement button is pressed
    motor_FL.run(RELEASE);
    motor_FR.run(RELEASE);
    motor_BL.run(RELEASE);
    motor_BR.run(RELEASE);
  }

  delay(50);
}

// ---- Movement Functions ---- //
void moveForward() {
  Serial.println("Moving Forward");
  motor_FL.run(FORWARD);
  motor_FR.run(FORWARD);
  motor_BL.run(FORWARD);
  motor_BR.run(FORWARD);
}

void moveBackward() {
  Serial.println("Moving Backward");
  motor_FL.run(BACKWARD);
  motor_FR.run(BACKWARD);
  motor_BL.run(BACKWARD);
  motor_BR.run(BACKWARD);
}

void strafeRight() {
  Serial.println("Strafing Right");
  motor_FL.run(FORWARD);
  motor_FR.run(BACKWARD);
  motor_BL.run(BACKWARD);
  motor_BR.run(FORWARD);
}

void strafeLeft() {
  Serial.println("Strafing Left");
  motor_FL.run(BACKWARD);
  motor_FR.run(FORWARD);
  motor_BL.run(FORWARD);
  motor_BR.run(BACKWARD);
}

void rotateRight() {
  Serial.println("Rotating Right");
  motor_FL.run(FORWARD);
  motor_FR.run(BACKWARD);
  motor_BL.run(FORWARD);
  motor_BR.run(BACKWARD);
}

void rotateLeft() {
  Serial.println("Rotating Left");
  motor_FL.run(BACKWARD);
  motor_FR.run(FORWARD);
  motor_BL.run(BACKWARD);
  motor_BR.run(FORWARD);
}
