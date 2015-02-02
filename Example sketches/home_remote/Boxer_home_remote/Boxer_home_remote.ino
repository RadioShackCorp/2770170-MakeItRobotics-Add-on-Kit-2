//********************************************************************************
// * File Name          : Boxer_home_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/21
// * Description        : Use your home IR remote control (for example, a TV remote) to cycle through the
// *                      RadioShack Make: it boxer robot functions.
// ********************************************************************************
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, see http://www.gnu.org/licenses/
//
/*****************************************************************************
  Point one of your home IR remote controls (for example, TV, DVD player)
  and press any button to cycle through the following commands. If you 
  press and hold the button, the robot will continuously repeat the cycle. 
  
  STOP       <--------------------|
  1st time  -> forward            |
  2nd time  -> backward           | 
  3rd time  -> turn left          |
  4th time  -> turn right         |
  5th time  -> left arm up        |
  6th time  -> left arm down      |
  7th time  -> right arm up       |
  8th time  -> right arm down ----|  
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics boxer; //declare object
// ****************************************************************************
// * Pin definition
// ****************************************************************************
#define PIN_IR      10  //define IR input
// ****************************************************************************
// *                            Power Up Init.
// ****************************************************************************
void setup() 
{
  pinMode(PIN_IR, INPUT);       //set IO INPUT
  digitalWrite(PIN_IR,HIGH);    //set PULL HIGH
  Serial.begin(10420);          //tell the Arduino to communicate with Make: it PCB
  delay(500);                   //delay 500ms
  boxer.all_stop();             //stop all motors
}
// ****************************************************************************
// *                            Main Loop 
// ****************************************************************************
void loop() 
{  
  static int motoract = 0;  //action number
  static int count = 0;     //filter counter
  //----------------------------------------------------------------- 
  //GET IR & ACTION PROGRAM
  while(digitalRead(PIN_IR));     //during a low signal, wait for the IR remote recever signal
  while(digitalRead(PIN_IR)==0);  //wait the signal return to HIGH
  count++;                        //count +1 when count greater than 10, then go action (this makes a software filter)
  if(count>10)
  {
    count=0;                      //begin the count
    motoract++;                   //next action 
    if(motoract==9)               //total 9 action (0 to 8)
      motoract=0;                 
    if(motoract==0)               //action 0
      boxer.all_stop();           //all motors stop
    else if(motoract==1)          //action 1
      boxer.go_forward(80);       //go forward 
    else if(motoract==2)          //action 2 
      boxer.go_backward(80);      //go backward
    else if(motoract==3)          //action 3
      boxer.turn_left(80);        //turn left  
    else if(motoract==4)          //action 4
      boxer.turn_right(80);       //turn right    
    else if(motoract==5)          //action 5
    {
      boxer.all_stop();           //all motors stop
      boxer.boxer_left_hand_up(80);  //left arm up
    }  
    else if(motoract==6)          //action 6
      boxer.boxer_left_hand_down(80);  //left arm down
    else if(motoract==7)          //action 6
    {
      boxer.all_stop();           //all motors stop 
      boxer.boxer_right_hand_up(80);  //right arm up
    }  
    else if(motoract==8)          //action 8
      boxer.boxer_right_hand_down(80); //right arm down
    delay(500);   //delay 500ms (to next action at least 500ms)
  }
}
