//********************************************************************************
// * File Name          : Clampingarm_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/23
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the clamping arm robot.
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
  Press the following buttons (SW)or combinations of buttons (SW + SW) to control the robot.
  SW1 forward
  SW3 backward
  SW4 turn right
  SW2 turn left
  SW5 + SW1 move arm up
  SW5 + SW3 move arm down
  SW6 + SW1 close clamp
  SW6 + SW3 open clamp
  SW7 clamp hold
  SW8 release clamp
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics clampingarm; //declare object
// ***********************************************************************************************************
// *                            Power Up Init.
// ***********************************************************************************************************
void setup() 
{
    Serial.begin(10420);         //tell the Arduino to communicate with Make: it PCB
    clampingarm.remote_setup();  //remote control setup        
    delay(500);                  //delay500ms
    clampingarm.all_stop();      //stop all motors
}
// ***********************************************************************************************************
// *                            Main Loop 
// ***********************************************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  static boolean hold=false;  //flag to record the clamp status
  valuen=clampingarm.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;  //refresh the previous code       
    if(valueo==SW1)                       //SW1 action
    {
      clampingarm.clampingarm_up(0);      //stop arm
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_clamp(0); //release the clamp     
      clampingarm.go_forward(255);        //go forward
    }  
    else if(valueo==SW3)                  //SW3 action
    {
      clampingarm.clampingarm_up(0);      //stop arm
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_clamp(0); //release the clamp     
      clampingarm.go_backward(255);       //go backward
    }  
    else if(valueo==SW2)                  //SW2 action
    {
      clampingarm.clampingarm_up(0);      //stop arm
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_clamp(0); //release the clamping    
      clampingarm.turn_left(255);         //turn left   
    }  
    else if(valueo==SW4)                  //SW4 action
    {
      clampingarm.clampingarm_up(0);      //stop arm
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_clamp(0); //release the clamp     
      clampingarm.turn_right(255);        //turn right    
    }  
    else if(valueo==SW51)                 //SW5+SW1 action
    {
      clampingarm.move_stop();            //stop wheels
      clampingarm.clampingarm_up(80);     //move arm up
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_clamp(0); //release the clamp
    }  
    else if(valueo==SW53)                 //SW5+SW3 action
    {
      clampingarm.move_stop();            //stop wheels
      clampingarm.clampingarm_down(80);   //move arm down
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_clamp(0); //release the clamp
    }      
    else if(valueo==SW61)                 //SW6+SW1 action
    {
      clampingarm.move_stop();            //stop wheels
      clampingarm.clampingarm_up(0);      //stop arm
      clampingarm.clampingarm_clamp(80);  //close clamp
      hold=false;                         //clear hold status
    }  
    else if(valueo==SW63)                 //SW6+SW1 action
    {
      clampingarm.move_stop();            //stop wheels
      clampingarm.clampingarm_up(0);      //stop arm
      clampingarm.clampingarm_release(80);//release clamp 
      hold=false;                         //clear hold status
    }
    else if(valueo==SW7)                  //SW7 action
    {
      hold=true;                          //enable hold status
      clampingarm.clampingarm_clamp(80);  //hold clamp    
    }  
    else if(valueo==SW8)                  //SW7 action
    {
      hold=false;                         //clear hold status
      clampingarm.clampingarm_clamp(0);   //release clamp      
    }      
    else                                  //if no buttons are pushed
    {
      clampingarm.move_stop();            //stop all motors
      clampingarm.clampingarm_up(0);      //stop arm up down
      if(hold==false)                     //not hold status
        clampingarm.clampingarm_release(0);  //release clamp             
    }  
  }    
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)  //interrupt code
{
  clampingarm.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}
