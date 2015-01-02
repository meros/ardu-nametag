// include the library code:
#include <SerialLCD.h>
#include <SoftwareSerial.h> //this is a must

// initialize the library
SerialLCD slcd(1,2);//this is a must, assign soft serial pins

char* name = "Alexander R. Schrab";

char* titles[] = {"Master", "Amateur", "Hobby", "Senior", "Junior", "Certified"};
int numTitles = 6;
char* roles[] = {"Programmer", "Coffee Maker", "Carpenter", "Hacker", "Whiner"};
int numRoles = 5;


void setup() {
  slcd.begin();
  slcd.backlight();
}

int nameState = 0;
int titleState = 0;
int titleIndex = 0;
int roleIndex = 0;

void loop() {
  
  int nameStartX = 16 - nameState;
  int nameLen = strlen(name);
  
  int titleStartX = 16 - titleState;
         
  char* title = titles[titleIndex];
  char* role = roles[roleIndex];
        
  int titleLen = strlen(title);
  int roleLen = strlen(role);
   
  for (int y = 0; y < 2; y++) {
    for (int x = 0; x < 16; x++) {
      slcd.setCursor(x,y);
      
      if (y == 0) {
        // print name
        if (x >= nameStartX && x < nameStartX+nameLen) {
          slcd.print(name[x-nameStartX]);
        } else {
          slcd.print(' ');
        }
      }
      
      if (y == 1) {
        // print title & role
        int titleChar = x - titleStartX;
        
        if (titleChar >= 0 && titleChar < titleLen + roleLen + 1) {
          if (titleChar < titleLen) {
            slcd.print(title[titleChar]);
          } else if (titleChar == titleLen) {
            slcd.print(' ');
          } else {
            slcd.print(role[titleChar-titleLen-1]);
          } 
        } else {
          slcd.print(' ');
        }
      }
    }
  }
  
  // Reset states  
  if (nameStartX <= -nameLen) {
    nameState = -1;
  }
  
  if (titleStartX <= -(titleLen + roleLen + 1)) {
    titleState = -1;
    titleIndex = random(0, numTitles);
    roleIndex = random(0, numRoles);
  }


  nameState++;
  titleState++;
 
  delay(150);
}
