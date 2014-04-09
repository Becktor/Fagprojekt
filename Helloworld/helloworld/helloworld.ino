#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

void setup()
{
  GD.begin();
}

void loop()

{

  GD.Clear();
   for (int rand = 0; rand < 100; rand++) {
      GD.cmd_number(240,136, 31, OPT_CENTER, rand); 
     if(rand == 0){
        GD.play(PIANO, 24);  //c
         delay(500);
      }else if(rand == 1) {
        GD.play(PIANO, 26);  //d
         delay(500);
      }else if(rand == 2) {
        GD.play(PIANO, 28);  //e
         delay(700);
      }else if(rand == 3) {
        GD.play(PIANO, 29);  //f
         delay(800);
      }else if(rand == 4) {
        GD.play(PIANO, 31);  //g
         delay(400);
      }else if(rand == 5) {
        GD.play(PIANO, 33);  //a
         delay(400);
      }else if(rand == 6) {
        GD.play(PIANO, 35);  //b
         delay(300);
      }else if(rand == 7) {
        GD.play(PIANO, 24);  //c
         delay(600);
      }else if(rand == 8) {
        GD.play(PIANO, 24);  //c
         delay(800);
      }else if(rand == 9) {
        GD.play(PIANO, 26);  //d
         delay(700);
      }else if(rand == 10) {
        GD.play(PIANO, 28);  //e
         delay(500);
      }else if(rand == 11) {
        GD.play(PIANO, 26);  //d
         delay(800);
      }else if(rand == 12) {
        GD.play(PIANO, 33);  //a
         delay(900);
      }else if(rand == 13) {
        GD.play(PIANO, 35);  //b
         delay(700);
      }else if(rand == 14) {
        GD.play(PIANO, 35);  //b
         delay(300);
      }else if(rand == 15) {
        GD.play(PIANO, 33);  //a
         delay(400);
      }else if(rand == 16) {
        GD.play(PIANO, 31);  //g
         delay(600);
      }else if(rand == 17) {
        GD.play(PIANO, 29);  //f
         delay(500);
      }else if(rand == 18) {
        GD.play(PIANO, 24);  //c
         delay(400);
      }else if(rand == 19) {
        GD.play(PIANO, 26);  //d
         delay(800);
      }else if(rand == 20) {
        GD.play(PIANO, 26);  //d
         delay(200);
      }else if(rand == 21) {
        GD.play(PIANO, 28);  //e
         delay(200);
      }else if(rand == 22) {
        GD.play(PIANO, 24);  //c
         delay(900);
      }else if(rand == 23) {
        GD.play(PIANO, 33);  //a
         delay(800);
      }else if(rand == 24) {
        GD.play(PIANO, 35);  //b
         delay(700);
      }else if(rand == 25) {
        GD.play(PIANO, 29);  //f
         delay(700);
      }else if(rand == 26) {
        GD.play(PIANO, 29);  //f
         delay(500);
      }else if(rand == 27) {
        GD.play(PIANO, 31);  //g 
        delay(700); 
      }else if(rand == 28) {
        GD.play(PIANO, 24);  //c
         delay(600);
      }else if(rand == 29) {
        GD.play(PIANO, 26);  //d
         delay(800);
      }else if(rand == 30) {
        GD.play(PIANO, 28);  //e
         delay(300);
      }else if(rand == 31) {
        GD.play(PIANO, 29);  //f
         delay(500);
      }else if(rand == 32) {
        GD.play(PIANO, 31);  //g
         delay(400);
      }else if(rand == 33) {
        GD.play(PIANO, 33);  //a
         delay(400);
      }else if(rand == 34) {
        GD.play(PIANO, 35);  //b
         delay(400);
      }else if(rand == 35) {
        GD.play(PIANO, 24);  //c
         delay(800);
      }else if(rand == 36) {
        GD.play(PIANO, 24);  //c
         delay(500);
      }else if(rand == 37) {
        GD.play(PIANO, 26);  //d
         delay(300);
      }else if(rand == 38) {
        GD.play(PIANO, 28);  //e
         delay(300);
      }else if(rand == 39) {
        GD.play(PIANO, 26);  //d
         delay(900);
      }else if(rand == 40) {
        GD.play(PIANO, 33);  //a
         delay(300);
      }
       if (rand == 40){
         rand=0;
     }
   }

 

  GD.Begin(POINTS);
  for (int i = 0; i < 100; i++) {
    
    GD.PointSize(GD.random(16 * 50));
    GD.ColorRGB(GD.random(256),
                GD.random(256),  
                GD.random(256));
    GD.ColorA(GD.random(256));
    GD.Vertex2ii(GD.random(480), GD.random(272));
  }

GD.swap();

}

