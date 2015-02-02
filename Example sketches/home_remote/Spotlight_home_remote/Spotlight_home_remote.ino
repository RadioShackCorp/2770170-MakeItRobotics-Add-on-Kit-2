//********************************************************************************
// * File Name          : Spotlight_home_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/21
// * Description        : Use your home IR remote control (for example, a TV remote) to cycle through the
// *                      RadioShack Make: it spotlight robot functions.
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
  
  STOP       <------------------------------------------------------|
  1st time  -> forward  1 second --> stop                           |
  2nd time  -> backward  1 second --> stop                          | 
  3rd time  -> turn left  1 second --> stop                         |
  4th time  -> turn right  1 second --> stop                        |
  5th time  -> rotate spotlight clockwise 1 second --> stop         |
  6th time  -> rotate spotlight counterclockwise 1 second --> stop  |
  7th time  -> move spotlight down 1 second --> stop                |
  8th time  -> move spotlight up 1 second --> stop                  |
  9th time  -> turn spotlight on                                    |
  10th time -> turn spotlight off  ---------------------------------|  
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics spotlight; //declare object
// ***************************************************************************
// * Pin definition
// ***************************************************************************
#define PIN_IR      10  //define IR input
// ***************************************************************************
// *                            Power Up Init.
// ***************************************************************************
void setup() 
{
  pinMode(PIN_IR, INPUT);        //set IO INPUT
  digitalWrite(PIN_IR,HIGH);     //set PULL HIGH  
  spotlight.spotlight_setup();   //setup spotlight IO 
  Serial.begin(10420);           //tell the Arduino to communicate with Make: it PCB
  delay(500);                    //delay 500ms
  spotlight.all_stop();          //stop all motors
}
// ***************************************************************************
// *                            Main Loop 
// ***************************************************************************
void loop() 
{  
  static int motoract = 0;       //action number
  static int count = 0;          //filter counter
  //----------------------------------------------------------------- 
  //GET IR & ACTION PROGRAM
  while(digitalRead(PIN_IR));     //during a low signal, wait for the IR remote recever signal
  while(digitalRead(PIN_IR)==0);  //wait for the signal to return to HIGH
  count++;                        //count +1 when count is greatere than 10, then go action (this makes a software filter))
  if(count>10)
  {
    count=0;                     //begin the count
    motoract++;                  //next action   
    if(motoract==11)             //total 11 action (0 to 10)
      motoract=1;          
    if(motoract==0)              //action 0  
      spotlight.all_stop();      //all motors stop
    else if(motoract==1)         //action 1
      spotlight.go_forward(255); //go forward       
    else if(motoract==2)         //action 2
      spotlight.go_backward(255);//go backward
    else if(motoract==3)         //action 3
      spotlight.turn_left(255);  //turn left        
    else if(motoract==4)         //action 4 
      spotlight.turn_right(255); //turn right         
    else if(motoract==5)         //action 5
    {
      spotlight.all_stop();      //stop all motors
      spotlight.spotlight_head_clockwise(80);  //rotate spotlight clockwise
    }  
    else if(motoract==6)         //action 6
      spotlight.spotlight_head_counterclockwise(80);  //rotate spotlight counterclockwise
    else if(motoract==7)         //action 7
    {
      spotlight.all_stop();      //stop all motors  
     spotlight.spotlight_head_down(80);  //move spotlight down
    }   
    else if(motoract==8)         //action 8
      spotlight.spotlight_head_up(80);  //move spotlight up
    else if(motoract==9)         //action 9
      spotlight.spotlight_on();  //spotlight on
    else if(motoract==10)        //action 10
      spotlight.spotlight_off(); //spotlight off      
      delay(1000);               //delay 1000ms
    if(motoract<=8)              //action 0 to 8 active 1000ms then stop
      spotlight.all_stop();
  }
}
