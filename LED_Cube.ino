#include <Rainbowduino.h>
#include "rgbfunctions.h"
#include "drops.h"

/*
EFFECTS:
 crrr,ggg,bbb = color (rgb in 8 bit format)
 usage:
 c255,33,234 
 
 p = plasma
 
 m = moodlamp
 
 d = drops
 
 srrr,ggg,bbb = stars (rgb in 8 bit format)
 usage:
 s255,33,234 
 
 r = random pixel
 
 hrrr,ggg,bbb = heartbeat (rgb in 8 bit format)
 usage:
 h255,33,234 
 
 ln,rrr,ggg,bbb = layer (n [int]: number of layers  rgb in 8 bit format)
 
  usage:
  l2,255,33,234 
 
 
 */

unsigned char RED[64] = {
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,171,154,137,119,102,85,
  68,51,34,17,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,17,35,52};

unsigned char GREEN[64] = {
  0,17,34,51,68,85,102,119,136,153,170,187,204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,
  255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,238,221,204,188,170,154,136,120,102,86,68,52,34,18,0,0,0,0};

unsigned char BLUE[64] = {
  0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,18,34,52,68,86,102,120,136,154,170,188,
  204,221,238,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255,255};


unsigned char plasma[4][4][4];
int red, green, blue;
char command, layers;
unsigned char x,y,z,colorshift=0;

void setup()
{
  Serial.begin(2400);
  Serial.println("ready");
  Rb.init(); //initialize Rainbowduino driver

  setCubeColor(255, 255, 255);
  randomSeed(analogRead(0));
}



void loop()
{

  if (Serial.available() > 0){

    switch (Serial.read()){
    case 'c':
      command = 'c';
      Serial.println("Set Color");
      getcolor();
      break;
    case 'p':
      Serial.println("Plasma");
      command = 'p';  
      for(unsigned char x = 0; x < 4; x++)
      {
        for(unsigned char y = 0; y < 4; y++)
        {
          for(unsigned char z = 0; z < 4; z++)
          {
            int color = int(32.0 + (32.0 * sin(x / 4.0))+ 32.0 + (32.0 * sin(y / 4.0)) + 32.0 + (32.0 * sin(z / 4.0))) / 3;
            plasma[x][y][z] = color;      
          }   
        }
      }
      break;
    case 'm':
      Serial.println("Moodlamp");
      command = 'm';  
      break;
    case 'd':
      Serial.println("drops");
      z=x=y=0;
      setCubeColor(0,0,0);
      dropsframe=0;
      command = 'd';  
      break;
    case 's':
      Serial.println("stars");
      getcolor();
      setCubeColor(0,0,0);
      command = 's';  
      break;      
    case 'r':
      Serial.println("random pixel");      
      setCubeColor(0,0,0);
      command = 'r';  
      break;
    case 'h':
      Serial.println("heart");      
      getcolor();
      setCubeColor(0,0,0);
      command = 'h';  
      break;
    case 'b':
      Serial.println("cube");   
      getcolor();  
      setCubeColor(0,0,0);
      command = 'b';  
      break;
    case 'l':
      Serial.println("layer");   
      layers = Serial.parseInt();
      getcolor();  
      setCubeColor(0,0,0);
      command = 'l';  
      break;    
    default:
      Serial.println("comando sconosciuto");
    }

    Serial.read();
  }


  switch (command){
  case 'c':
    setCubeColor(red,green,blue);
    break;
  case 'p':
    setPlasma();
    break;
  case 'm':
    moodLamp();
    break;
  case 'd':
    drops();
    break; 
  case 's':
    stars();
    break;    
  case 'r':
    randompixel();
    break; 
  case 'b':
    cube();
    break;       
  case 'h':
    hearth();
    break;  
  case 'l':
    layer();
    break;  
  default:
    setCubeColor(0,0,0);
  }
}



void setPlasma(){
  for(x=0;x<4;x++)  
  {
    for(y=0;y<4;y++)  
    {
      for(z=0;z<4;z++)
      {
        Rb.setPixelZXY(z,x,y,(RED[plasma[x][y][z] + colorshift]) % 256,(GREEN[plasma[x][y][z] + colorshift]) % 256,(BLUE[plasma[x][y][z] + colorshift]) % 256); //uses R, G and B color bytes
      }
    }
  }
  delay(100);
  colorshift=  colorshift + 1;
}


void setCubeColor(char r, char g, char b){
  {
    for(z=0;z<4;z++)
    {
      for(x=0;x<4;x++)
      {
        for(y=0;y<4;y++)
        {
          //Paint random colors
          Rb.setPixelZXY(z,x,y,r,g,b); //uses R, G and B color bytes
          delay(5);
        }
      }
    }
  }
}


void moodLamp(){
  for(z=0; z<64 ;z++)
  {
    for(x=0;x<8;x++)
    {
      for(y=0;y<8;y++)
      {

        Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
      }
    }
    delay(100);
  }
  for(z=63; z > 0 ;z--)
  {
    for(x=0;x<8;x++)
    {
      for(y=0;y<8;y++)
      {

        Rb.setPixelXY(x,y,RED[z],GREEN[z],BLUE[z]); //uses R, G and B color bytes
      }
    }
    delay(100);
  }
}


void randompixel() {
  Rb.setPixelZXY(random(4),random(4),random(4),random(255),random(255),random(255)); //uses R, G and B color bytes
  delay(25);
}

float pixelfade[9] = {
  0, 0.2, 0.4, 0.8, 1, 0.8, 0.4, 0.2, 0};

void randompixel_color() {
  x=random(4);
  y=random(4);
  z=random(4);

  float hue = random(255)/255.0;
  for (char i=0; i<9; i++){
    RGB rgb = hsb2rgb(hue, 0, pixelfade[i]);
    Rb.setPixelZXY(z,x,y,rgb.r,rgb.g,rgb.b); //uses R, G and B color bytes
    delay(50);  
  }
  delay(random(1000));
}

char starsfade[9] = {
  0,32,64,128,255,128,64,32,0};

void stars() {
  x=random(4);
  y=random(4);
  z=random(4);
  HSB hsb = rgb2hsb(red, green, blue);  
  for (char i=0; i<9; i++){
    RGB rgb = hsb2rgb(hsb.h, hsb.s, pixelfade[i]);
    Rb.setPixelZXY(z,x,y,rgb.r,rgb.g,rgb.b); //uses R, G and B color bytes
    delay(50);  
  }
  delay(random(500));
}

void layer(){
  {
    for(z=0;z<layers;z++)
    {
      for(x=0;x<4;x++)
      {
        for(y=0;y<4;y++)
        {
          //Paint random colors
          Rb.setPixelZXY(z,x,y,red,green,blue); //uses R, G and B color bytes
          delay(5);
        }
      }
    }
  }
}


void cube(){
  for (int i = 0; i<4; i++){
    {
      for(z=0;z<4;z++)
      {
        for(x=0;x<4;x++)
        {
          for(y=0;y<4;y++)
          {
            //Paint random colors
            Rb.setPixelZXY(z,x,y,0,0,0); //uses R, G and B color byte
          }
        }
      }
    }

    for (z=0; z<4; z++){
      for (y=0; y<4; y++){
        Rb.setPixelZXY(z,i,y,red,green,blue); 
      }
    }
    delay(100);
  }
}

float hearthbeat[21] = {
  0,0.1,0.2,0.3,0.8,1,1,0.6,0.2,0,0,0.1,0.2,0.3,0.8,1,1,0.6,0.2,0}; 

void hearth(){
  HSB hsb = rgb2hsb(red, green, blue); 
  for (int i = 0; i<21; i++){
    RGB rgb = hsb2rgb(hsb.h+0.5, hsb.s, hearthbeat[i]/10);
    for(z=0;z<4;z++)
    {
      for(x=0;x<4;x++)
      {
        for(y=0;y<4;y++)
        {

          //Paint random colors
          Rb.setPixelZXY(z,x,y,rgb.r,rgb.g,rgb.b); //uses R, G and B color byte

        }
      }
    }
    rgb = hsb2rgb(hsb.h, hsb.s, hearthbeat[i]);
    for(z=1;z<3;z++)
    {
      for(x=1;x<3;x++)
      {
        for(y=1;y<3;y++)
        {



          //Paint random colors
          Rb.setPixelZXY(z,x,y,rgb.r,rgb.g,rgb.b); //uses R, G and B color byte


        }
      }
    }

    delay(50);
  }
  delay(400);
}


void getcolor(){
  red = Serial.parseInt();
  green = Serial.parseInt();
  blue = Serial.parseInt();
  red = constrain(red, 0, 255);
  green = constrain(green, 0, 255);
  blue = constrain(blue, 0, 255);

}







