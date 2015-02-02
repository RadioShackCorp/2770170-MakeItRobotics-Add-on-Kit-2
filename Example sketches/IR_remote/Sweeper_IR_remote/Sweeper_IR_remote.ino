//********************************************************************************
// * File Name          : Sweeper_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/24
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the street sweeper robot.
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
  Press the following buttons (SW)or combinations of buttons (SW + SW) to control the robot.
  SW1 forward
  SW3 backward
  SW4 turn right
  SW2 turn left
  SW5 rotate sweeper plates inward
  SW6 rotate sweeper plates outward
  SW7 sweep continously
  SW8 stop sweeping
******************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics street_sweeper; //declare object
// ***************************************************************************
// *                            Power Up Init.
// ***************************************************************************
void setup() 
{
  Serial.begin(10420);            //tell the Arduino to communicate with Make: it PCB
  street_sweeper.remote_setup();  //remote control setup    
  delay(500);                     //delay 500ms
  street_sweeper.all_stop();      //stop all motors
}
// ***************************************************************************
// *                            Main Loop 
// ***************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  static boolean sweep=false;  //flag to record the sweep status
  valuen=street_sweeper.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;  //refresh the previous code
    if(valueo==SW1)                               //SW1 action
    {
      if(sweep==false)                            //not sweep status
        street_sweeper.street_sweeper_inward(0);  //stop the sweeper plates
      street_sweeper.go_forward(120);             //go forward    
    }
    else if(valueo==SW3)                          //SW3 action
    {
      if(sweep==false)                            //not sweep status
        street_sweeper.street_sweeper_inward(0);  //stop the sweeper plates    
      street_sweeper.go_backward(120);            //go backward
    }    
    else if(valueo==SW2)                          //SW2 action
    {
      if(sweep==false)                            //not sweep status
        street_sweeper.street_sweeper_inward(0);  //stop the sweeper plates  
      street_sweeper.turn_front_left(120);        //turn left  
    }
    else if(valueo==SW4)                          //SW4 action
    {    
      if(sweep==false)                            //not sweep status
        street_sweeper.street_sweeper_inward(0);  //stop the sweeper plates
      street_sweeper.turn_front_right(120);       //turn right   
    }
    else if(valueo==SW5)                          //SW5 action
    {
      street_sweeper.move_stop();                 //stop wheels
      street_sweeper.street_sweeper_inward(80);   //rotate sweeper plates inward
    }  
    else if(valueo==SW6)                          //SW6 action
    {
      street_sweeper.move_stop();                 //stop wheels
      street_sweeper.street_sweeper_outward(80);  //rotate sweeper plates outward
    } 
    else if(valueo==SW7)                          //SW7 action
    {          
      street_sweeper.street_sweeper_inward(80);   //continuously rotate sweeper plates inward 
      sweep=true;                                 //sweeper status enable
    } 
    else if(valueo==SW8)                          //SW8 action
    {          
      street_sweeper.street_sweeper_inward(0);    //stop rotating sweeper plates
      sweep=false;                                //clear sweeper status
    }    
    else                                          //if no buttons are pushed
    {
      street_sweeper.move_stop();                 //stop wheels
      if(sweep==true)                             //if sweeper plates are rotating
        street_sweeper.street_sweeper_inward(80); //continue rotating sweeper plates inward      
      else                                        //if sweeper plates are not rotating
        street_sweeper.street_sweeper_inward(0);  //stop street sweeper          
    }  
  }  
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)  //interrupt code
{
  street_sweeper.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}
