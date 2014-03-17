/*
 *  The main sketch file, the root of all evil.
 *  Instead of using a separate file for the main game logic, updates and lists,
 *  use this.
 */

#include <EEPROM.h>
#include <SPI.h>
#include <GD2.h>

#include "Director.h"

void setup() {
  GD.begin();
}

void loop() {
}

//Should be in a separate scene generation library.
/*
void shellScene() {
  for(int i = 0; i < SCENE_WIDTH; i++) {
    _scene.setTile(i, 0, Rock);
    _scene.setTile(i, SCENE_HEIGHT - 1, Rock);
  }
  for(int i = 1; i < SCENE_HEIGHT - 1; i++) {
    _scene.setTile(0, i, Rock);
    _scene.setTile(SCENE_WIDTH - 1, i, Rock);
  }
}
*/
