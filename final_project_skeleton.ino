#include <Servo.h>

Servo gripper; 
Servo ax1;
Servo ax2;

//Variables to store the servo angle associated with the gripper open and closed positions
int gr_open = 30;
int gr_close = 160;

//Variables to store the servo angles associated with the home location
float ax1_home = 10;
float ax2_home = 80;

//Variables to store the servo angles associated with the current location - only needed for moveToposFunction
float ax1_current;
float ax2_current;

//3x2 array of servo angles for each position 1,2, and 3
int pos[3][2] = {
      {76,54},
      {100,73},
      {121,92},
    };

// communication pins
int sendPin1 = 5;
int sendPin2 = 6;
int recievePin1 = 7;
int recievePin2 = 8;

//current position var
int curr=3;

void moveTopos(float ax1s, float ax1e, float ax2s, float ax2e) {
  /*
   This function taskes the starting and ending angles for both axes and
   divides them into an even number of steps. This ensures that the movement
   from both motors occurs simultaneously. It also reduces the speed of
   movement to help protect the mechanism. This is a workable but sub-optimal
   way of moving the mechanism.

   ax1s -> Axis 1 Start Position
   ax1e -> Axis 1 End Position
   ax2s -> Axis 2 Start Position
   ax2e -> Axis 2 End Position
   */
  float num_steps_1 = ax1e - ax1s;
  float num_steps_2 = ax2e - ax2s;
  float num_steps = 0;

  if (abs(num_steps_1) >= abs(num_steps_2)){
    num_steps = abs(num_steps_1);
  }
  else {
     num_steps = abs(num_steps_2);
  }
  float inc1 = num_steps_1 / num_steps;
  float inc2 = num_steps_2 / num_steps;
  float stp = 0;
  for(stp = 0; stp<=num_steps; stp += 1){
    ax1_current += inc1;
    ax1.write(ax1_current);
    ax2_current += inc2;
    ax2.write(ax2_current);
    delay(25);
  }
  ax1_current = ax1e;
  ax1.write(ax1_current);
  ax2_current = ax2e;
  ax2.write(ax2_current);
  delay(25);
}

void setup() {
  //start serial
  Serial.begin(9600);
  //initialize servos with associated pins
  gripper.attach(12); 
  ax1.attach(11);
  ax2.attach(10);
  //initialize communication through pins
  pinMode(sendPin1, OUTPUT);
  pinMode(sendPin2, OUTPUT);
  pinMode(recievePin1, INPUT_PULLUP);
  pinMode(recievePin2, INPUT_PULLUP);
  //Setting the axes to the home position
  ax1.write(ax1_home);
  ax2.write(ax2_home);
}

void picknplace(int pick, int place){
  //move: home -> pick pos
  moveTopos(ax1_home, pos[pick-1][1], ax2_home, pos[pick-1][0]);
  //close grip to grab payload
  gripper.write(gr_close);
  delay(2000);
  //move: pick pos -> place pos
  moveTopos(pos[pick-1][1], pos[place-1][1], pos[pick-1][0], pos[place-1][0]);
  //open grip to release payload
  gripper.write(gr_open);
  delay(2000);
  //move: place pos -> home
  moveTopos(pos[place-1][1], ax1_home, pos[place-1][0], ax2_home);
  //set current pos to place pos + 10
  curr = place + 10;
}

void loop() {
  //repeating code
  //get input from serial monitor
  int num = Serial.parseInt();
  //if pick and place was run prior, send position value instead of reading first
  if (curr >=10){
    curr = curr-10;
    digitalWrite(sendPin1, curr%2);
    digitalWrite(sendPin2, curr/2);
  }
  else{
    //if pick and place wasn't run, read values sent by other device
    curr = 2*digitalRead(recievePin2)+ digitalRead(recievePin1);
  }
  //write new values to other device
  digitalWrite(sendPin1, curr%2);
  digitalWrite(sendPin2, curr/2);
  //run pick and place if a number was enterred into serial monitor, assume input inclusively between 1 to 3
  if (num != 0){
    picknplace(curr, num);
  }
  delay(10);
}
