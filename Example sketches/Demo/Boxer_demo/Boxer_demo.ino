//********************************************************************************
// * File Name          : Boxer_demo.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/16
// * Description        : Cycle through the basic functions of the RadioShack Make: it boxer robot
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
  1st action  -> forward 1 second   <-------|
  2nd action  -> backward 1 second          | 
  3rd action  -> go left 1 second           |
  4th action  -> go right 1 second          |
  5th action  -> left arm up 1 second       |
  6th action  -> left arm down 1 second     |
  7th action  -> right arm up 1 second      |
  8th action  -> right arm down 1 second ---|  
*****************************************************************************/
#include <MakeItRobotics.h>  //include library
MakeItRobotics boxer;        //declare object
// **************************************************************************
// *                            Power Up Init.
// **************************************************************************
void setup() 
{  
  Serial.begin(10420);    //tells the Arduino where to send data
  delay(500);            //delay 1000ms
  boxer.all_stop();      //all motors stop
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{             
    boxer.go_forward(80);             //forward
    delay(1000);                      //delay 1000ms
    boxer.go_backward(80);            //backward
    delay(1000);                      //delay 1000ms           
    boxer.turn_left(80);              //turn left
    delay(1000);                      //delay 1000ms      
    boxer.turn_right(80);             //turn right
    delay(1000);                      //delay 1000ms   
    boxer.all_stop();                 //all motors stop
    boxer.boxer_left_hand_up(80);     //left arm up
    delay(1000);                      //delay 1000ms   
    boxer.boxer_left_hand_down(80);   //left arm down
    delay(1000);                      //delay 1000ms   
    boxer.all_stop();                 //all motors stop
    boxer.boxer_right_hand_up(80);    //right arm up
    delay(1000);                      //delay 1000ms   
    boxer.boxer_right_hand_down(80);  //right arm down       
    delay(1000);                      //delay 1000ms
    boxer.all_stop();                 //all motors stop
    delay(1000);                      //delay 1000ms     
                                      //actions repeat continuously until you turn off battery compartments
}
