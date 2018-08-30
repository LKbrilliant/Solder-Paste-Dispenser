/* Project       : Solder Paste dispenser
 * Code by       : LKBrilliant
 * Date          : 26.08.2018
 * Components    : 24BYJ-48 5V unipolar stepper motor
 *                 ATtiny85 microcontroller
 *                 ULN2003A Stepper driver
 *                
 * Description : > By pressing the external button once, the motor will turn 
 *                 preset number of steps. 
 *               > The screw mechanism will convert the rotational motion into linear 
 *                 motion thus compressing the plunge of the Syringe. 
 *               > changing the "forwardStp" and "idleBkStp", the amount of solder coming 
 *                 out of the container can be controlled.
 *               > Forward and backward direction may vary due to different wiring 
 *                 configurations of the stepper motor
 */

// Connections between Attiny85 and ULN2003A
#define in1 0
#define in2 1
#define in3 2
#define in4 3

#define forwardStp   2       // Number of steps per button press
#define idleBkStp   20      

#define del 2

long t = 0;
bool backed = false;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(4, INPUT);
  backward(5);
  motor_steps(4);           // Stepper off
}

void loop() {
  if(digitalRead(4) == HIGH){
    forward(forwardStp);
    t = millis();
    backed = false;
    delay(500);                 // Reaction delay
  }
  if((millis() - t) > 10000 && backed == false){     // release the inside pressure after 10s of idle
    backward(idleBkStp);
    motor_steps(4);             // Stepper off
    backed = true;
  }
}

void motor_steps(int i) {       // Full stepping
  if (i == 0) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
    delay(del);
  } 
  else if (i == 1) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, HIGH);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, LOW);
    delay(del);
  }
  else if (i == 2) {
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, HIGH);
    digitalWrite(in4, HIGH);
    delay(del);
  } 
  else if (i == 3) {
    digitalWrite(in1, HIGH);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, HIGH);
    delay(del);
  }
  else if (i == 4) {      // stepper off
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
  }
}

void backward(int count) {
  for (int c = 0; c < count; c++) {
    motor_steps(0);
    motor_steps(1);
    motor_steps(2);
    motor_steps(3);
  }
}

void forward(int count) {
  for (int c = 0; c < count; c++) {
    motor_steps(3);
    motor_steps(2);
    motor_steps(1);
    motor_steps(0);
  }
}
