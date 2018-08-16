float x, y, speedX, speedY;
float diam = 10;
float rectSize = 35;

import processing.serial.*;
byte[] outData = new byte[16*10];
Serial myPort;


int score = 0;

void setup() {
  
  size(100, 80); 
  reset();
  
  myPort = new Serial(this, Serial.list()[1], 57600);
}
void outputData()
{
  loadPixels();
  color pink = color(255, 102, 204);
  int pixelPos = 800;
  for (int i = 0; i < (height/10)*(width/10); i++)
  { 
    int sum = 0;
    for(int j = 0; j<10; j++)
    {
      color c = pixels[pixelPos];
      sum += (brightness(c) > 100)?0:1;
    }
    if(sum >5) outData[i] = byte('X');
    else outData[i] = byte('8');
    
    pixels[pixelPos] = pink;
    //print(str(outData[i]));
    pixelPos +=10;
    if(pixelPos % 100 == 0)
    {
      pixelPos += 800;
    }
  }
  updatePixels();
  outData[75] = byte(score + '0');
  outData[160-1] = '\n';
  myPort.write(outData);
}

int scorereset = 0;

void reset() {
  x = width/2;
  y = height/2;
  scorereset = 0;
  speedX = random(1, 3)*-1;
  speedY = random(1, 3)*-1;
}
void draw() { 
  background(0);
  
  ellipse(x, y, diam, diam);

  rect(width-15, mouseY-rectSize/2, 15, rectSize);

  x += speedX;
  y += speedY;

  // if ball hits movable bar, invert X direction
  if ( x > width-20 && x < width -10 && y > mouseY-rectSize/2 && y < mouseY+rectSize/2 ) {
    speedX = speedX * -1;
  } 

  // if ball hits wall, change direction of X
  if (x < 1) {
    speedX *= -1.1;
    speedY *= 1.1;
    x += speedX;
  }

  if(x>width && scorereset ==0)
  {
    score++;
    scorereset = 1;
  }

  // if ball hits up or down, change direction of Y   
  if ( y > height || y < 0 ) {
    speedY *= -1;
  }
  
  outputData();
  delay(50);
}

void mousePressed() {
  reset();
}