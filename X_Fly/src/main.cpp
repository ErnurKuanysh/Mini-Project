/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\Айгуль                                           */
/*    Created:      Fri Apr 10 2020                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// Robot Configuration:
// [Name]               [Type]        [Port(s)]
// Controller1          controller                    
// Left1                motor         19              
// Right1               motor         13              
// Left2                motor         20              
// Right2               motor         11              
// Intake               motor         10              
// Indexer              motor         9               
// Flywheel             motor         16              
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"

using namespace vex;
void delay(float Time){
  task::sleep(Time);
}
void Reset(){
  Right1.setPosition(0,degrees);
  Right2.setPosition(0,degrees);
  Left1.setPosition(0,degrees);
  Left2.setPosition(0,degrees);
}
void Stop(){
  Right1.setVelocity(0,percent);
  Right2.setVelocity(0,percent);
  Left1.setVelocity(0,percent);
  Left2.setVelocity(0,percent);
  Right1.setStopping(hold);
  Right2.setStopping(hold);
  Left1.setStopping(hold);
  Left2.setStopping(hold);
}
void Spin(){
  Right1.spin(forward);
  Right2.spin(forward);
  Left1.spin(forward);
  Left2.spin(forward);
}
void Velocity(float Speed,int Heding){
    Right1.setVelocity(Speed*Heding,percent);
    Right2.setVelocity(Speed,percent);
    Left1.setVelocity(Speed,percent);
    Left2.setVelocity(Speed*Heding,percent);
}
void Rotate(float Speed){
    Right1.setVelocity(Speed,percent);
    Right2.setVelocity(Speed,percent);
    Left1.setVelocity(-Speed,percent);
    Left2.setVelocity(-Speed,percent);
}
void In(float Speed){
  Intake.spin(forward);
  Indexer.spin(forward);
  Intake.setVelocity(Speed,percent);
  Indexer.setVelocity(Speed,percent);
}
void InTake(float Speed){
  Intake.spin(forward);
  Intake.setVelocity(Speed,percent);
}
void InStop(){
  Indexer.setVelocity(0,percent);
  Intake.setVelocity(0,percent);
}
void Fly(){
  Flywheel.spin(forward);
  for(int i=1; i<=100;i++){
    Flywheel.setVelocity(i,percent);
    delay(15);
  }
}
void SideWays(float Distance,float MaxSpeed,float MinSpeed){
 float Now=0;
  Reset();
  delay(20);
  Spin();
  while(Distance-Now>0){
    Now=(abs(Right1.position(degrees))+abs(Right2.position(degrees))+abs(Left1.position(degrees))+abs(Left2.position(degrees)))*0.031;
    Velocity(/*Ускорение или замедление*/);
    //That's little secret (:
  }
  Stop();
}
void DriveCm(float Distance,float MaxSpeed,float MinSpeed){
  float Now=0;
  Reset();
  delay(20);
  Spin();
  while(Distance-Now>0){
    Now=(abs(Right1.position(degrees))+abs(Right2.position(degrees))+abs(Left1.position(degrees))+abs(Left2.position(degrees)))*0.031;
    Velocity(/*Ускорение или замедление*/);
    //That's little secret (:
  }
  Stop();
}
void TurnAngle(float Angle,float MaxSpeed,float MinSpeed){
  float Now=0;
  Reset();
  delay(20);
  Spin();
  while(Angle-Now>0){
    Now=(abs(Right1.position(degrees))+abs(Right2.position(degrees))+abs(Left1.position(degrees))+abs(Left2.position(degrees)))*0.07686567165;
    Rotate(/*PID*/);
    //That's little secret (:
  }
  Stop();
}
void Drive(float Distance, float MinSpeed,float MaxSpeed,bool Side){
  if(Side){
    SideWays(Distance/3,MinSpeed,MaxSpeed);
    SideWays(Distance/3*2,MaxSpeed,MinSpeed);
  }else{
    DriveCm(Distance/3,MinSpeed,MaxSpeed);
    DriveCm(Distance/3*2,MaxSpeed,MinSpeed);
  }
}
void Turn(float Angle, float MinSpeed,float MaxSpeed){
  TurnAngle(Angle/3,MinSpeed,MaxSpeed);
  TurnAngle(Angle/3*2,MaxSpeed,MinSpeed);
}
void Auton(){
  //:)
  delay(200);
  InTake(100);
  Drive(47,5,40,false);
  delay(300);
  In(100);
  delay(550);
  InStop();
  Drive(27,-5,-30,false);
  Drive(57,5,50,true);
  InTake(100);
  Drive(45,5,30,false);
  delay(200);
  Turn(37,5,25);
  In(100);
  delay(500);
  InStop();
  Turn(37,-5,-25);
  Drive(45,-5,-30,false);
  Drive(110,-5,-50,true);
  InTake(100);
  Drive(45,5,30,false);
  delay(200);
  Turn(37,-5,-25);
  In(100);
  delay(500);
  InStop();
  Right1.setStopping(coast);
  Right2.setStopping(coast);
  Left1.setStopping(coast);
  Left2.setStopping(coast);
}
int main() {
  vexcodeInit();
  Fly();
  while(true){
    if(Controller1.ButtonA.pressing()){
      delay(200);
      Auton();
    }else{
    Flywheel.setVelocity(100,percent);
    Right2.setVelocity((Controller1.Axis2.position(percent)+Controller1.Axis1.position(percent)-Controller1.Axis4.position(percent)/3)^3/18000,percent);
    Right1.setVelocity((Controller1.Axis2.position(percent)-Controller1.Axis1.position(percent)-Controller1.Axis4.position(percent)/3)^3/18000,percent);
    Left2.setVelocity((Controller1.Axis2.position(percent)-Controller1.Axis1.position(percent)+Controller1.Axis4.position(percent)/3)^3/18000,percent);
    Left1.setVelocity((Controller1.Axis2.position(percent)+Controller1.Axis1.position(percent)+Controller1.Axis4.position(percent)/3)^3/18000,percent);
    if(Controller1.ButtonL2.pressing()){
      InTake(100);
    }else if(Controller1.ButtonL1.pressing()){
      In(100);
    }else if(Controller1.ButtonR1.pressing()){
      In(-80);
    }else{
      Intake.setVelocity(0,percent);
      Indexer.setVelocity(0,percent);
      Intake.setStopping(coast);
      Indexer.setStopping(coast);
    }
      Right1.spin(forward);
      Right2.spin(forward);
      Left1.spin(forward);
      Left2.spin(forward);
      Indexer.spin(forward);
      Intake.spin(forward);
      Flywheel.spin(forward);
  }
}
}
//The End