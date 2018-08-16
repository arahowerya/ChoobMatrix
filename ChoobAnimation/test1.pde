// Particles, by Daniel Shiffman.

ParticleSystem ps;
PImage sprite;


import processing.serial.*;

int val = 0;

String outString;
byte[] outData = new byte[16*10];

Serial myPort;
  
PrintWriter output;
void setup() {
  size(100, 160, P2D);
  orientation(LANDSCAPE);
  sprite = loadImage("sprite.png");
  ps = new ParticleSystem(800);
  
  //output = createWriter("/dev/tty.usbserial-FTGVKO0C");
  
  
  printArray(Serial.list());
  myPort = new Serial(this, Serial.list()[1], 57600);

  // Writing to the depth buffer is disabled to avoid rendering
  // artifacts due to the fact that the particles are semi-transparent
  // but not z-sorted.
  hint(DISABLE_DEPTH_MASK);
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
    else outData[i] = byte(random(0x30,0x39));
    
    pixels[pixelPos] = pink;
    //print(str(outData[i]));
    pixelPos +=10;
    if(pixelPos % 100 == 0)
    {
      pixelPos += 800;
    }
  }
  updatePixels();
  outData[160-1] = '\n';
  myPort.write(outData);
}

void draw () {
  background(0);
  ps.update();
  ps.display();

  ps.setEmitter(mouseX, mouseY);
  outputData();

  fill(255);
  delay(50);
}