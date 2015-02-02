//********************************************************************************
// * File Name          : Clampingarm_demo.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/16
// * Description        : Cycle through the basic functions of the RadioShack Make: it clamping arm robot.
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
  1st action  -> forward 1 second   <----------|
  2nd action  -> backward 1 second             | 
  3rd action  -> turn left 1 second            |
  4th action  -> turn right 1 second           |
  5th action  -> clamping arm up 1 second      |
  6th action  -> clamping arm down 1 second    |
  7th action  -> clamp 1 second                |
  8th action  -> release clamp 1 second--------|
*****************************************************************************/
#include <MakeItRobotics.h>  //include library
MakeItRobotics clampingarm;  //declare object
// **************************************************************************
// *                            Power Up Init.
// **************************************************************************
void setup() 
{
    Serial.begin(10420);     //tell the Arduino to communicate with Make: it PCB
    delay(500);              //delay 500ms
    clampingarm.all_stop();  //all motors stop
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{    
  clampingarm.go_forward(255);         //forward
  delay(1000);                         //delay 1000ms
  clampingarm.go_backward(255);        //backward
  delay(1000);                         //delay 1000ms       
  clampingarm.turn_left(255);          //turn left
  delay(1000);                         //delay 1000ms         
  clampingarm.turn_right(255);         //turn right
  delay(1000);                         //delay 1000ms
  clampingarm.all_stop();              //all motors stop
  clampingarm.clampingarm_up(80);      //clamping arm up
  delay(1000);                         //delay 1000ms
  clampingarm.clampingarm_down(80);    //clamping arm down
  delay(1000);                         //delay 1000ms
  clampingarm.all_stop();              //all motors stop
  clampingarm.clampingarm_clamp(80);   //clamp
  delay(1000);                         //delay 1000ms
  clampingarm.clampingarm_release(80); //release clamp
  delay(1000);                         //delay 1000ms
  clampingarm.all_stop();              //all motors stop
  delay(1000);                         //delay 1000ms    
}                                      //actions repeat continuously until you turn off battery compartments
