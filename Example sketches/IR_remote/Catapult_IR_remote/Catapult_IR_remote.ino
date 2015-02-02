//********************************************************************************
// * File Name          : Catapult_IR_remote.ino
// * Author             : RadioShack Corporation
// * Version            : V1.0
// * Date               : 2014/01/23
// * Description        : Use the RadioShack Make: it Robotics Remote Control to control the catapult robot.
//********************************************************************************
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
  Press the following buttons (SW) or combinations of buttons (SW + SW) to control the robot.
  SW1 forward
  SW3 backward
  SW4 turn right
  SW2 turn left
  SW5 + SW1 rotate catapult base clockwise
  SW5 + SW3 rotate catapult base counterclockwise
  SW6 + SW1 move catapult arm back (pull)
  SW6 + SW3 move catapult arm foward (launch)
  SW7 launch
  SW8 stop launch
****************************************************************************/
#include <MakeItRobotics.h> //include library
MakeItRobotics catapult; //declare object
// *************************************************************************
// *                            Power Up Init.
// *************************************************************************
void setup() 
{
    Serial.begin(10420);     //tell the Arduino to communicate with Make: it PCB
    catapult.remote_setup(); //remote control setup       
    delay(500);              //delay 500ms
    catapult.all_stop();     //stop all motors
}
// **************************************************************************
// *                            Main Loop 
// **************************************************************************
void loop() 
{  
  static unsigned int valueo=0;  //old remote control code
  static unsigned int valuen=0;  //new remote control code
  static boolean hold=false;  //flag to record the throw status
  valuen=catapult.remote_value_read();  //read code from remote control
  if(valuen!=valueo)  //if the remote control code is different than the previous code, then change status
  {
    valueo=valuen;  //refresh the previous code          
    if(valueo==SW1)                         //SW1 action
    {
      catapult.catapult_head_clockwise(0);  //stop catapult base
      if(hold==false)                       //not hold status
        catapult.catapult_head_throw(0);    //stop catapult arm     
      catapult.go_forward(80);              //go forward
    }  
    else if(valueo==SW3)                    //SW3 action
    {
      catapult.catapult_head_clockwise(0);  //stop catapult base
      if(hold==false)                       //not hold status
        catapult.catapult_head_throw(0);    //stop catapult arm  
      catapult.go_backward(80);             //go backward
    }  
    else if(valueo==SW2)                    //SW2 action
    {
      catapult.catapult_head_clockwise(0);  //stop catapult base
      if(hold==false)                       //not hold status
        catapult.catapult_head_throw(0);    //stop catapult arm 
      catapult.turn_left(80);               //turn left
    }  
    else if(valueo==SW4)                    //SW4 action
    {
      catapult.catapult_head_clockwise(0);  //stop catapult base
      if(hold==false)                       //not hold status
        catapult.catapult_head_throw(0);    //stop catapult arm 
      catapult.turn_right(80);              //turn right
    }  
    else if(valueo==SW51)                   //SW5+SW1 action
    {
      catapult.move_stop();                 //stop wheels
      catapult.catapult_head_clockwise(80); //rotate catapult base clockwise
      if(hold==false)                       //not hold status 
        catapult.catapult_head_throw(0);    //stop catapult arm
    }  
    else if(valueo==SW53)                   //SW5+SW3 action
    {
      catapult.move_stop();                 //stop wheels
      catapult.catapult_head_counterclockwise(80);  //rotate catapult base counterclockwise
      if(hold==false)                       //not hold status
        catapult.catapult_head_throw(0);    //stop catapult arm
    }      
    else if(valueo==SW61)                   //SW6+SW1 action            
    {
      catapult.move_stop();                 //stop wheels
      catapult.catapult_head_clockwise(0);  //stop catapult base
      catapult.catapult_head_throw(80);     //move catapult arm forward
      hold=false;                           //clear hold status
    }  
    else if(valueo==SW63)                   //SW6+SW3 action            
    {
      catapult.move_stop();                 //stop wheels
      catapult.catapult_head_clockwise(0);  //stop catapult base
      catapult.catapult_head_pull(80);      //move catapult arm back
      hold=false;                           //clear hold status
    }
    else if(valueo==SW7)                    //SW7 action
    {
      hold=true;                            //hold status enable
      catapult.catapult_head_throw(255);    //throw (quickly accelerates catapult arm)
      delay(1000);                          //delay 1000ms      
    }  
    else if(valueo==SW8)                    //SW8 action     
    {
      hold=false;                           //clear hold status
      catapult.catapult_head_throw(0);      //stop catapult arm throw     
    }      
    else                                    //if no buttons are pushed
    {
      catapult.move_stop();                 //stop wheels
      catapult.catapult_head_clockwise(0);  //stop catapult base
      if(hold==false)                       //not hold status      
        catapult.catapult_head_throw(0);    //stop catapult arm              
    }  
  }    
}
/***********************************************************************
*    Remote Scan
************************************************************************/
ISR(PCINT0_vect)  //interrupt code
{
  catapult.remote_scan();  //analyze signal from RadioShack Make: it Robotics Remote Control
}
