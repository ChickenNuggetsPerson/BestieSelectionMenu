/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       C:\Users\24hsteele                                        */
/*    Created:      Mon Nov 21 2022                                           */
/*    Description:  V5 project                                                */
/*                                                                            */
/*----------------------------------------------------------------------------*/

// ---- START VEXCODE CONFIGURED DEVICES ----
// ---- END VEXCODE CONFIGURED DEVICES ----

#include "vex.h"



using namespace vex;

bool running = true;


int team = 0;
int rollers = 0;
int launch = 0;
int pickup = 0;

unsigned int readFile(const char* fileName) {
  unsigned int ival = 0;
  unsigned char readBuff[4];
  Brain.SDcard.loadfile(fileName, readBuff, 4);
	ival = *(unsigned int*)(readBuff);
  return ival;
};

void writeFile(const char* fileName, unsigned int numToWrite) {
  unsigned int ival = numToWrite;
  unsigned char writeBuff[4];
  memcpy(writeBuff, (char*)&ival,sizeof(unsigned int));
  Brain.SDcard.savefile(fileName, writeBuff, 4);
};


void writeAllFiles() {
  writeFile("team", team);
  writeFile("rollers", rollers);
  writeFile("launch", launch);
  writeFile("pickup", pickup);
};


void screenPressed() {
  int checkX = 20;
  int checkY = 20;

  // Team Button
  if (Brain.Screen.xPosition() > checkX && Brain.Screen.xPosition() < checkX + 100 && Brain.Screen.yPosition() > checkY && Brain.Screen.yPosition() < checkY + 100) {
    if (team == 1) {
      team = -1;
    } else {
      team = 1;
    }
  } 


  // Save Button
  checkX = 20;
  checkY = 170;
  if (Brain.Screen.xPosition() > checkX && Brain.Screen.xPosition() < checkX + 100 && Brain.Screen.yPosition() > checkY && Brain.Screen.yPosition() < checkY + 40) {
    running = false;
  }


  // Rollers Button
  checkX = 350;
  checkY = 40;
  if (Brain.Screen.xPosition() > checkX && Brain.Screen.xPosition() < checkX + 100 && Brain.Screen.yPosition() > checkY && Brain.Screen.yPosition() < checkY + 40) {
    if ( rollers == 0 ) {
      rollers = 1;
    } else {
      rollers = 0;
    }
  }

  // Launch Button
  checkX = 350;
  checkY = 80;
  if (Brain.Screen.xPosition() > checkX && Brain.Screen.xPosition() < checkX + 100 && Brain.Screen.yPosition() > checkY && Brain.Screen.yPosition() < checkY + 40) {
    if ( launch == 0 ) {
      launch = 1;
    } else {
      launch = 0;
    }
  }


  // Pickup Button
  checkX = 350;
  checkY = 140;
  if (Brain.Screen.xPosition() > checkX && Brain.Screen.xPosition() < checkX + 100 && Brain.Screen.yPosition() > checkY && Brain.Screen.yPosition() < checkY + 40) {
    if ( pickup == 0 ) {
      pickup = 1;
    } else {
      pickup = 0;
    }
  }

  writeAllFiles();
  
}

void screenReleased() {
  
};


int main() {
  // Initializing Robot Configuration. DO NOT REMOVE!
  vexcodeInit();

  Brain.Screen.pressed(screenPressed);
  Brain.Screen.released(screenReleased);
  
  

  if (Brain.SDcard.exists("team")) {  
    team = readFile("team");
    rollers = readFile("rollers");
    launch = readFile("launch");
    pickup = readFile("pickup");
  } else {
    team = 1;
    rollers = 0;
    launch = 0;
  }

  int drawX = 0;
  int drawY = 0;

  while(running){
  
    Brain.Screen.clearScreen();

    drawX = 20;
    drawY = 20;
    if (team == 1) { Brain.Screen.drawRectangle(drawX, drawY, 100, 100, vex::color::blue);}
    if (team == -1) { Brain.Screen.drawRectangle(drawX, drawY, 100, 100, vex::color::red);}
    Brain.Screen.printAt(drawX, drawY + 120, true, "Team Color");


    drawX = 20;
    drawY = 170;
    Brain.Screen.drawRectangle(drawX, drawY, 100, 40);
    Brain.Screen.printAt(drawX + 30, drawY + 30, true, "Save");


    drawX = 350;
    drawY = 20;
    if (rollers == 1) { Brain.Screen.drawRectangle(drawX, drawY, 100, 40, vex::color::green);}
    if (rollers == 0) { Brain.Screen.drawRectangle(drawX, drawY, 100, 40, vex::color::red);}
    Brain.Screen.printAt(drawX + 20, drawY + 30, true, "Rollers");

    drawX = 350;
    drawY = 80;
    if (launch == 1) { Brain.Screen.drawRectangle(drawX, drawY, 100, 40, vex::color::green);}
    if (launch == 0) { Brain.Screen.drawRectangle(drawX, drawY, 100, 40, vex::color::red);}
    Brain.Screen.printAt(drawX + 20, drawY + 30, true, "Launch");

    drawX = 350;
    drawY = 140;
    if (pickup == 1) { Brain.Screen.drawRectangle(drawX, drawY, 100, 40, vex::color::green);}
    if (pickup == 0) { Brain.Screen.drawRectangle(drawX, drawY, 100, 40, vex::color::red);}
    Brain.Screen.printAt(drawX + 20, drawY + 30, true, "Pickup");

    wait(0.1, seconds);

  }

  Brain.Screen.clearScreen();
  Brain.Screen.setCursor(1, 1);

  

  Brain.Screen.print("You can close the program now");
  //Brain.Screen.drawRectangle(360, 90, 100, 20, vex::color::white);
  Brain.Screen.setPenWidth(5);
  Brain.Screen.drawLine(360, 100, 460, 100);
  Brain.Screen.drawLine(460, 100, 440, 80);
  Brain.Screen.drawLine(460, 100, 440, 120);
 // Brain.Screen.drawLine(440, 80,  440, 120);
  
  //Brain.Screen.drawRectangle(420, 70, 20, 60, vex::color::white);
  

  return 1;
  
}