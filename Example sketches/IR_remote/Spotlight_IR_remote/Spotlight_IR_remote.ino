//********************************************************************************
// * File Name          : Spotlight_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/24
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the spotlight robot.
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
  SW5 + SW1 rotate spotlight clockwise
  SW5 + SW3 rotate spotlight counterclockwise
  SW6 + SW1 move spotlight up
  SW6 + SW3 move spotlight down
  SW7 spotlight on
  SW8 spotlight off
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics spotlight; //declare object
// ***************************************************************************
// *                            Power Up Init.
// ***************************************************************************
void setup() 
{
  spotlight.spotlight_setup();  //Spolight IO setup
  Serial.begin(10420);          //tell the Arduino to communicate with Make: it PCB
  spotlight.remote_setup();     //remote control setup   
  delay(500);                   //delay 500ms
  spotlight.all_stop();         //stop all motors
}
// ***************************************************************************
// *                            Main Loop 
// ***************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  valuen=spotlight.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;  //refresh the previous code            
    if(valueo==SW1)                             //SW1 action
    {
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation
      spotlight.spotlight_head_up(0);           //stop spotlight up/down    
      spotlight.go_forward(255);                //go forward
    }  
    else if(valueo==SW3)                        //SW3 action
    {
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation
      spotlight.spotlight_head_up(0);           //stop spotlight up/down
      spotlight.go_backward(255);               //go backward
    }  
    else if(valueo==SW2)                        //SW3 action
    {
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation
      spotlight.spotlight_head_up(0);           //stop spotlight up/down
      spotlight.turn_left(255);                 //turn left
    }  
    else if(valueo==SW4)                        //SW4 action
    {
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation 
      spotlight.spotlight_head_up(0);           //stop spotlight up/down
      spotlight.turn_right(255);                //turn right
    }   
    else if(valueo==SW51)                       //SW5 + SW1 action
    {
      spotlight.move_stop();                    //stop wheels
      spotlight.spotlight_head_up(0);           //stop spotlight up/down
      spotlight.spotlight_head_clockwise(80);   //rotate spotlight clockwise
    }  
    else if(valueo==SW53)                       //SW5 + SW3 action
    {
      spotlight.move_stop();                    //stop wheels
      spotlight.spotlight_head_up(0);           //stop spotlight up/down
      spotlight.spotlight_head_counterclockwise(80);  //rotate spotlight counterclockwise
    }      
    else if(valueo==SW61)                       //SW6 + SW1 action
    {
      spotlight.move_stop();                    //stop wheels
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation  
      spotlight.spotlight_head_up(80);          //move spotlight up
    }  
    else if(valueo==SW63)                       //SW6 + SW3 action
    {
      spotlight.move_stop();                    //stop wheels
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation    
      spotlight.spotlight_head_down(80);        //move spotlight head down
    }
    else if(valueo==SW7)                        //SW7 action
      spotlight.spotlight_on();                 //turn spotlight on
    else if(valueo==SW8)                        //SW8 action
      spotlight.spotlight_off();                //turn spotlight off 
    else                                        //if no buttons are pushed
    {
      spotlight.move_stop();                    //stop wheels
      spotlight.spotlight_head_clockwise(0);    //stop spotlight rotation 
      spotlight.spotlight_head_up(0);           //stop spotlight up/down   
    }  
  }    
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect) //interrupt code
{
  spotlight.remote_scan(); //analyze signal from RadioShack Make: it Robotics Remote Control
}
