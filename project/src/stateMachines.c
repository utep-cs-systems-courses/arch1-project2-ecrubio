#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

char toggle_red()/* always toggle! */
{
  static char state = 0;
  
  switch (state) {
  case 0:
    red_on = 1;
    state = 1;
    break;
  case 1:
    red_on = 0;
    state = 0;
    break;
  }
  return 1;/* always changes an led */
}

char toggle_green()/* only toggle green if red is on!  */
{
  char changed = 0;
  if (red_on) {
    green_on ^= 1;
    changed = 1;
  }
  return changed;
}

int song[] = {220,196,147,220,196,147,220,196,147,131,147,220,196,0};
int i = 0;

void state_advance()/* alternate between toggling red & green */
{
  switch(switch_state)
    {
    case 1:
      // buzzer_set_period(200);
      switch_state = 0;

      break;
    case 2:
      //buzzer_set_period(1000);
      switch_state = 0;
      break;
    case 3:
      buzzer_off();
      break;
    case 4:
      /*for(int i = 0; i < 14; i++) {
	buzzer_set_period(song[i++]);
	switch_state = 0;
	}*/
      buzzer_set_period(song[i++]);
      break;
    }
  switch_state = 0;
  /*char changed = 0;

  static enum {R=0, G=1} color = G;
  switch (color) {
  case R: changed = toggle_red(); color = G; break;
  case G: changed = toggle_green(); color = R; break;
  }

  switch_state = changed;
  led_update();*/
}
