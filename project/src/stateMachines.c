#include <msp430.h>
#include "stateMachines.h"
#include "led.h"
#include "switches.h"
#include "buzzer.h"

int song_H[] = {220,196,147,220,196,147,220,196,147,131,147,220,196,0};
int song_W[] = {392,294,370,330,294,261,392,247,440,294};
int i = 0;
int j = 0;

void test_toggle()
{
  if (switch_state == 2) {
    green_on = 1;
    red_on = 0;
    switch_state = 0;
  } else {
    red_on = 1;
    green_on = 0;
    switch_state = 0;
  }
}

void state_advance()/* alternate between toggling red & green */
{
  switch(switch_state)
    {
    case 1:
      //Does not play song continuously
      buzzer_set_period(song_W[j++]);
      break;
    case 2:
      test_toggle();
      break;
    case 3:
      //This will stop any of the actions going on regardless of action
      buzzer_off();
      lights_off();
      break;
    case 4:
      //Does not play song continuously
      buzzer_set_period(song_H[i++]);
      break;
    }
  switch_state = 0;
}
