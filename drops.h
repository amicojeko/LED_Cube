
unsigned char dropcolor[8][4] = {{0,0,0,0},{0,0,0,255},{0,0,255,64},{0,255,64,32},{255,64,32,0},{64,32,0,0},{32,0,0,0},{0,0,0,0}};  
char x0,y0,x1,y1,x2,y2,x3,y3,x4,y4,x5,y5,x6,y6,x7,y7;
char dropsframe;

void drops(){

  for(char z=0; z<4; z++){
    Rb.setPixelZXY(z,x0,y0,dropcolor[dropsframe][z],dropcolor[dropsframe][z],dropcolor[dropsframe][z]);
    Rb.setPixelZXY(z,x1,y1,dropcolor[(dropsframe+1)%8][z],dropcolor[(dropsframe+1)%8][z],dropcolor[(dropsframe+1)%8][z]);
    Rb.setPixelZXY(z,x2,y2,dropcolor[(dropsframe+2)%8][z],dropcolor[(dropsframe+2)%8][z],dropcolor[(dropsframe+2)%8][z]);
    Rb.setPixelZXY(z,x3,y3,dropcolor[(dropsframe+3)%8][z],dropcolor[(dropsframe+3)%8][z],dropcolor[(dropsframe+3)%8][z]);
    Rb.setPixelZXY(z,x4,y4,dropcolor[(dropsframe+4)%8][z],dropcolor[(dropsframe+4)%8][z],dropcolor[(dropsframe+4)%8][z]);
    Rb.setPixelZXY(z,x5,y5,dropcolor[(dropsframe+5)%8][z],dropcolor[(dropsframe+5)%8][z],dropcolor[(dropsframe+5)%8][z]);
    Rb.setPixelZXY(z,x6,y6,dropcolor[(dropsframe+6)%8][z],dropcolor[(dropsframe+6)%8][z],dropcolor[(dropsframe+6)%8][z]);    
    Rb.setPixelZXY(z,x7,y7,dropcolor[(dropsframe+7)%8][z],dropcolor[(dropsframe+7)%8][z],dropcolor[(dropsframe+7)%8][z]);
    


    delay(33);
  }

  dropsframe++;

  if (dropsframe == 8) {
    dropsframe=0; 
    x0= random(4);
    y0= random(4);
  }
  if (dropsframe == 7) {

    x1= random(4);
    y1= random(4);
  }

  if (dropsframe == 6) {
    x2= random(4);
    y2= random(4);
  }

  if (dropsframe == 5) {
    x3= random(4);
    y3= random(4);
  }
  if (dropsframe == 4) {

    x4= random(4);
    y4= random(4);
  }
  if (dropsframe == 3) {

    x5= random(4);
    y5= random(4);
  }

  if (dropsframe == 2) {
    x6= random(4);
    y6= random(4);
  }

  if (dropsframe == 1) {
    x7= random(4);
    y7= random(4);
  }
}

















