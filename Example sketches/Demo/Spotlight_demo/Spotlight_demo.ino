
//********************************************************************************
// * File Name          : Spotlight_demo.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/16
// * Description        : Cycle through the basic functions of the RadioShack Make: it spotlight robot
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
  1st action  -> forward 1 second           <------------------|
  2nd action  -> backward 1 second                             | 
  3rd action  -> turn left 1 second                            |
  4th action  -> turn right 1 second                           |
  5th action  -> rotate spotlight clockwise 1 second           |
  6th action  -> rotate spotlight counterclockwise 1 second    |
  7th action  -> move spotlight down 1 second                  |
  8th action  -> move spotlight up 1 second                    |  
  9th action  -> turn spotlight on 1 second                    |
  10th action -> turn spotlight off 1 second       ------------|    
*****************************************************************************/
#include <MakeItRobotics.h>  //include library
MakeItRobotics spotlight;    //declare object
// **************************************************************************
// *                            Power Up Init.
// **************************************************************************
void setup() 
{
  spotlight.spotlight_setup();  //setup the status of spotlight
  Serial.begin(10420);          //tell the Arduino to communicate with Make: it PCB
  delay(500);                   //delay 500ms
  spotlight.all_stop();         //all motors stop
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{       
  spotlight.go_forward(255);     //forward
  delay(1000);                   //delay 1000ms
  spotlight.go_backward(255);    //backward
  delay(1000);                   //delay 1000ms          
  spotlight.turn_left(255);      //turn left
  delay(1000);                   //delay 1000ms        
  spotlight.turn_right(255);     //turn right     
  delay(1000);                   //delay 1000ms
  spotlight.all_stop();          //all motors stop
  spotlight.spotlight_head_clockwise(80);  //rotate spotlight clockwise
  delay(1000);                   //delay 1000ms
  spotlight.spotlight_head_counterclockwise(80);  //rotate spotlight counterclockwise
  delay(1000);                   //delay 1000ms
  spotlight.all_stop();          //all motors stop
  spotlight.spotlight_head_down(80);  //move spotlight down
  delay(1000);                   //delay 1000ms
  spotlight.spotlight_head_up(80);  //move spotlight up
  delay(1000);                   //delay 1000ms
  spotlight.all_stop();          //stop all motors
  spotlight.spotlight_on();      //spotlight on
  delay(1000);                   //delay 1000ms
  spotlight.spotlight_off();     //spotlight off   
  delay(1000);                   //delay 1000ms
}                                //actions repeat continuously until you turn off battery compartments
