//********************************************************************************
// * File Name          : Boxer_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/24
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the boxer robot.
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
/****************************************************************************
  Press the following buttons (SW) or combinations of buttons (SW + SW) to control the robot.
  SW1 forward
  SW3 backward
  SW4 turn right
  SW2 turn left
  SW5 + SW1 left arm up
  SW5 + SW3 left arm down
  SW6 + SW1 right arm up
  SW6 + SW3 right arm down
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics boxer; //declare object
// ****************************************************************************
// *                            Power Up Init.
// ****************************************************************************
void setup() 
{
  Serial.begin(10420);   //tell the Arduino to communicate with Make: it PCB
  boxer.remote_setup();  //remote control setup      
  delay(500);            //delay 500ms 
  boxer.all_stop();      //stop all motors
}
// ****************************************************************************
// *                            Main Loop 
// ****************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  valuen=boxer.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;  //refresh the previous code              
    if(valueo==SW1)                    //SW1 action
    {
      boxer.boxer_left_hand_up(0);     //stop boxer left arm
      boxer.boxer_right_hand_up(0);    //stop boxer right arm  
      boxer.go_forward(80);            //go forward
    }  
    else if(valueo==SW3)               //SW3 action
    {
      boxer.boxer_left_hand_up(0);     //stop boxer left arm   
      boxer.boxer_right_hand_up(0);    //stop boxer right arm    
      boxer.go_backward(80);           //go backward
    }  
    else if(valueo==SW2)               //SW2 action
    {
      boxer.boxer_left_hand_up(0);     //stop boxer left arm 
      boxer.boxer_right_hand_up(0);    //stop boxer right arm     
      boxer.turn_left(80);             //turn left
    }  
    else if(valueo==SW4)               //SW4 action
    {
      boxer.boxer_left_hand_up(0);     //stop boxer left arm  
      boxer.boxer_right_hand_up(0);    //stop boxer right arm     
      boxer.turn_right(80);            //turn right
    }  
    else if(valueo==SW51)              //SW5 + SW1 action
    {
      boxer.move_stop();               //stop wheels
      boxer.boxer_right_hand_up(0);    //stop boxer right arm  
      boxer.boxer_left_hand_up(80);    //boxer left arm up
    }  
    else if(valueo==SW53)              //SW5 + SW3 action
    {
      boxer.move_stop();               //stop wheels
      boxer.boxer_right_hand_up(0);    //stop boxer right arm   
      boxer.boxer_left_hand_down(80);  //boxer left arm down
    }      
    else if(valueo==SW61)              //SW6 + SW1 action
    {
      boxer.move_stop();               //stop wheels
      boxer.boxer_left_hand_down(0);   //stop boxer left arm     
      boxer.boxer_right_hand_up(80);   //boxer right arm up
    }  
    else if(valueo==SW63)              //SW6 + SW3 action
    {
      boxer.move_stop();               //stop wheels
      boxer.boxer_left_hand_down(0);   //stop boxer left arm    
      boxer.boxer_right_hand_down(80); //boxer right arm down 
    }     
    else                               //if no buttons are pushed
      boxer.all_stop();                //stop all motors
  }    
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)  //interrupt code
{
  boxer.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}
