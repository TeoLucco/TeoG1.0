#define SENDSTATETIME 1000
unsigned long int lastSendState = 0;
double prev_posX = 0;
double actual_posX = 0;
double prev_posY = 0;
double actual_posY = 0;
double prev_posTh = 0;
double actual_posTh = 0;


#define SCARED_SPD 47.0
#define HAPPY_SPD 39.0
#define SAD_SPD 15.0

void btInterpreter() {
  switch (interpreterState) {
    case choose_modality: chooseModality();timedSwitchToGameMod(); playAudioTutorial(); break;
    case choose_game:     chooseGame(); break;
    case choose_scenario: chooseScenario(); break;
    case sg_waiting:      sgWaiting(); break;
    case game_modality:   gameMod(); break;
    case fam_modality:    famMod(); break;
    case discharge:       disCharge(); break;
//    case test_modality:   hardwareTests(); break;
  }
}

void chooseModality() {
  if (Serial3.available()) {
    b = Serial3.read();
    settings();
    switch (b) {
      case'(':
        interpreterState = choose_game;
        playS(game_mod_audio);
        delay(2000);
        //Serial3.println();
        //Serial3.println("Selezionare Gioco");
        playS(CHOOSE_GAME_AUDIO);
        break;
      case')':
        interpreterState = fam_modality;
        playS(Familiarization_mod_audio);
        fam_modality_start_time=millis();
        //CapacitivesUpdate(body);
        movementFinishTime = millis();
        break;
      default:
        break;
    }
  }
  sendState();
}

#define GAME_MODE_SWITCH_TIME 420000
#define TIME_TO_ANSWER_SWITCH_GAME_MOD 60000
unsigned long int switchToGameMod_time=0;

boolean switchToGameMod=false;
void timedSwitchToGameMod(){
  if(millis()-fam_modality_start_time>GAME_MODE_SWITCH_TIME){
    fam_modality_start_time=millis();
    switchToGameMod=true;
    playS(MAKEAGAME_AUDIO);//facciamo un gioco?
    switchToGameMod_time=millis();
  }
  if(switchToGameMod && millis()-switchToGameMod_time>TIME_TO_ANSWER_SWITCH_GAME_MOD){
    switchToGameMod=false;
    fam_modality_start_time=millis();
  }
}

void famMod() {
  if (Serial3.available()) {
    b = Serial3.read();
    movementPanel();
    startMovementBT();
    settings();
    playAudio();
    headButtonsControl();
    switch (b) {
      case '.': interpreterState = choose_modality;loopStartTime=millis(); break;
      case'(': interpreterState = choose_game; playS(game_mod_audio); delay(2000);playS(CHOOSE_GAME_AUDIO);
        delay(2000);break;

    }
  }
  sendState();
}

void headButtonsControl() {
  if (b == '!') {
    buttonToTouch = Serial3.parseInt();
    CapacitivesUpdate(both);
    //Serial3.print("buttonToTouch: ");Serial3.println(buttonToTouch);
  }
}

void movementPanel() {
  switch (b) {
    case '0':
      //resetButtons();
      if (actual_movement == no_movement) {
        if (prev_movement != autonomous_capa && prev_movement != follow && prev_movement != autonomous_movement) {
          triskar.stop3();
          //triskar.stop2();
          move = false;
        } else if (prev_movement == follow) {
          actual_movement = follow;
          prev_movement = no_movement;
          prev_movement2 = no_movement;
          prev_movement3 = no_movement;
        }
        else if (prev_movement == autonomous_movement) {
          actual_movement = autonomous_movement;
          prev_movement = no_movement;
          prev_movement2 = no_movement;
          prev_movement3 = no_movement;
        }
        else if (prev_movement == autonomous_capa) {
          //startMovement(idle, rainbow_cycle);
          actual_movement = autonomous_capa;
          prev_movement = no_movement;
          prev_movement2 = no_movement;
          prev_movement3 = no_movement;
        }
      }
      //}
      break;

    case '1':
      //Serial3.println("1-SU");
      if (front_obstacle!=veryCloseOb && actual_movement != dontwonna) {
        move = true;
        movementFinishTime = millis();
        triskar.run(speed_trg, 0.0);
      } else if (f_front<=30 && actual_movement != dontwonna)  startMovement(dontwonna, yellowC, color_pulse, DONT_WONNA_AUDIO1 + rand()%3);
      break;
    case '2':
      //Serial3.println("2-GIU'");
      if (back_obstacle!=veryCloseOb && actual_movement != dontwonna) {
        move = true;
        triskar.run(-speed_trg, 0.0);
        movementFinishTime = millis();
      } else if (f_back<30 && actual_movement != dontwonna)  startMovement(dontwonna, yellowC, color_pulse, DONT_WONNA_AUDIO1 + rand()%3);
      break;

    case '3':
      //Serial3.println("3-SINISTRA");
      move = true;
      if (actual_movement == no_movement) {
        triskar.run(0.0, speed_trg / robot_radius);
        movementFinishTime = millis();
      } else if (actual_movement == autonomous_movement || actual_movement == follow || actual_movement == autonomous_capa) {
        prev_movement3 = prev_movement2;
        prev_movement2 = prev_movement;
        prev_movement = actual_movement;
        actual_movement = no_movement;
        movementFinishTime = millis();
        triskar.run(0.0, speed_trg / robot_radius);
      }

      break;

    case '4':
      //Serial3.println("4-DESTRA");
      move = true;
      if (actual_movement == no_movement) {
        triskar.run(0.0, -speed_trg / robot_radius);
        movementFinishTime = millis();
      } else if (actual_movement == autonomous_movement || actual_movement == follow || actual_movement == autonomous_capa) {
        prev_movement3 = prev_movement2;
        prev_movement2 = prev_movement;
        prev_movement = actual_movement;
        actual_movement = no_movement;
        movementFinishTime = millis();
        triskar.run(0.0, -speed_trg / robot_radius);
      }
      break;
    //Code when RIGHT key is pressed

    case '5':
      speed_trg -= 3;
      if (speed_trg < 0)     speed_trg = 0;
      break;

    case '6':
      speed_trg += 3;
      if (speed_trg > 51)   speed_trg = 51;
      break;

//    case 'f':
//      triskar.setKi(triskar.getKi() + 0.02);
//      Serial3.println("*I" + String(triskar.getKi()) + "*");
//      break;
//    case 'g':
//      triskar.setKi(triskar.getKi() - 0.02);
//      Serial3.println("*I" + String(triskar.getKi()) + "*");
//      break;
//    case 'h':
//      triskar.setKp(triskar.getKp() + 0.02);
//      Serial3.println("*P" + String(triskar.getKp()) + "*");
//      break;
//    case 'i':
//      triskar.setKi(triskar.getKp() - 0.02);
//      Serial3.println("*P" + String(triskar.getKp()) + "*");
//      break;
  }
}

void settings() {
  switch (b) {
    case 'L': bodyCapacitor = true; //CapacitivesUpdate(body); break;
    case 'M': CapacitivesUpdate(noOne); bodyCapacitor = false; break;
    case 'N': speakers = true; break;
    case 'O': speakers = false; break;
    case 'P': headLedSetColor(red); break;
    case 'Q': headLedSetColor(yellow); break;
    case 'R': headLedSetColor(blue); break;
    case 'S': headLedSetColor(green); break;
    case 'T': headLedUpdate(led_off); head_leds = false; break;
    case 'U': head_leds = true; headLedUpdate(rainbow_cycle); break;
    case 'V': head_leds = true; headLedUpdate(color_wipe);  break;
    case 'W': head_leds = true; headLedUpdate(color_pulse); break;
    case 'X': bodyLedUpdate(redC); break;
    case 'Y': bodyLedUpdate(yellowC); break;
    case 'Z': bodyLedUpdate(blueC); break;
    case '[': bodyLedUpdate(greenC); break;
    case ']': bodyLedUpdate(led_off); body_leds = false; break;
    case '^': body_leds = true; bodyLedUpdate(rainbow_cycle); break;
    case '_': body_leds = true; bodyLedUpdate(color_wipe); break;
    case 'a': body_leds = true; bodyLedUpdate(color_pulse); break;
    case 'b': fotoresistor = true; break;
    case 'c': fotoresistor = false; break;
    case 'd': micro = true; break;
    case 'e': micro = false; break;
    case 'f': microSoglia=Serial3.parseInt();EEPROM.put(microEEPROMADDR, microSoglia); break;
    case 'g': FAR_DISTANCE=Serial3.parseInt();EEPROM.put(farDistanceEEPROMADDR, FAR_DISTANCE); break;
    case 'h': volume=Serial3.parseInt(); myDFPlayer.volume(volume);break;
    case 'i': bodyLedUpdate(color_pulse, orangeC); speed_trg = SCARED_SPD; break;
    case 'j': bodyLedUpdate(color_pulse, greenC); speed_trg = HAPPY_SPD; break;
    case 'k': bodyLedUpdate(color_pulse, blueC); speed_trg = SAD_SPD; break;
    case 'l': bodyLedUpdate(led_off); speed_trg =35; break;
   
  }
}



void startMovementBT() {
  switch (b) {
    case '#': stopMovement2();break;
    case '9': startMovement(make_circle); break;
    case ':': startMovement(scared_round); break;
    case ';': startMovement(dontwonna); break;
    case '<': startMovement(scared_behind); break;
    case '=': startMovement(make_happy0); break;
    case '>': startMovement(make_happy1); break;
    case '?': startMovement(make_happy2); break;
    case '@': startMovement(make_happy3); break;
    case 'A': startMovement(make_sad0); break;
    case 'B': startMovement(make_sad1); break;
    case 'C': startMovement(scared_hit); break;
    case 'D': startMovement(make_sad2); break;
    case 'E': startMovement(angrymov); break;
    case 'F': stopMovement(); startMovement(follow); actual_obstacle = none; last_obstacle = none; break;
    case 'G': stopMovement(); startMovement(autonomous_movement); break;
    case 'H': stopMovement(); startMovement(autonomous_capa); break; //START DI MOSCACIECA
//    case 'I': stopMovement(); startMovement(brokeIce); break;
//    case 'J': stopMovement(); startMovement(dance_mov); break;
//    case 'K': stopMovement(); startMovement(colorGame); break;
  }
}


void playAudio() {
  if (b == '%') {
    playS(Serial3.parseInt());
  }
}


void sendState() {//send data from arduino to App
  Serial3.println("*A" + String(interpreterState) + "*");
  battery_indicator = constrain(mapfloat(voltage, MIN_INDICATOR_VOLTAGE, MAX_INDICATOR_VOLTAGE, MIN_INDICATOR_VALUE, MAX_INDICATOR_VALUE), MIN_INDICATOR_VALUE, MAX_INDICATOR_VALUE);
  Serial3.println("*B" + String(battery_indicator) + "*");
  Serial3.println("*C" + String(speed_trg) + "*");
  Serial3.println("*D" + String(f_front) + "*");
  Serial3.println("*L" + String(f_left) + "*");
  Serial3.println("*R" + String(f_right) + "*");
  Serial3.println("*S" + String(f_back) + "*");
  Serial3.println("*M" + String(micro_f) + "*");
  Serial3.println("*g" + String(microSoglia) + "*");
  Serial3.println("*s" + String(FAR_DISTANCE) + "*");
  Serial3.println("*t" + String(volume) + "*");
//  Serial3.println("*F" + String(fotores_value) + "*");
//  Serial3.println("*Q" + String(triskar.getSpeedX()) + "*");
//  Serial3.println("*N" + String(actual_movement) + "*");
//  Serial3.println("*O" + String(prev_movement) + "*");
//  Serial3.println("*h" + String(actual_obstacle) + "*");
//  Serial3.println("*i" + String(last_obstacle) + "*");
//  Serial3.println("*l" + String(targetPos) + "*");
//  Serial3.println("*m" + String(right_obstacle) + "*");
//  Serial3.println("*n" + String(left_obstacle) + "*");
//  Serial3.println("*o" + String(front_obstacle) + "*");
//  Serial3.println("*p" + String(previous_distance) + "*");
//  Serial3.println("*q" + String(actual_distance) + "*");
//  Serial3.println("*r" + String(touched) + "*");
//  prev_posX = actual_posX;
//  actual_posX = triskar.getPosX();
//  prev_posY = actual_posY;
//  actual_posY = triskar.getPosY();
//  prev_posTh = actual_posTh;
//  actual_posTh = triskar.getPosTh();
//  if (actual_posX != prev_posX) {
//    Serial3.println("*X" + String(actual_posX) + "*");
//  }
//  if (actual_posY != prev_posY) {
//    Serial3.println("*Y" + String(actual_posY) + "*");
//  }
//  if (actual_posTh != prev_posTh) {
//    Serial3.println("*T" + String(actual_posTh) + "*");
//  }

}


void chooseGame() {
  if (Serial3.available()) {
    b = Serial3.read();
    settings();
    switch (b) {
      case '0':
        interpreterState = choose_scenario;
        currentGameI = 0;
        playS(you_choosed_game_audio);
        delay(2000);
        playS(currentGameI+1);
        //        }
        break;
      case '1':
        interpreterState = choose_scenario;
        currentGameI = 1;
        playS(you_choosed_game_audio);
        delay(2000);
        playS(currentGameI+1);
        //        }
        break;

      case '2':
        interpreterState = choose_scenario;
        currentGameI = 2;
        playS(you_choosed_game_audio);
        delay(2000);
        playS(currentGameI+1);

        break;
      case '3':
        interpreterState = choose_scenario;
        currentGameI = 3;
        playS(you_choosed_game_audio);
        delay(2000);
        playS(currentGameI+1);

        break;
       case '4':
        interpreterState = choose_scenario;
        currentGameI = 4;
        playS(you_choosed_game_audio);
        delay(2000);
        playS(currentGameI+1);

        break;
      case')':
        interpreterState = fam_modality;
        playS(Familiarization_mod_audio);
        fam_modality_start_time=millis();
        //CapacitivesUpdate(body);
        movementFinishTime = millis();
        break;
      case '.':
        interpreterState = choose_modality;
        loopStartTime=millis();
        //CapacitivesUpdate(noOne);
        break;

    }

  }
  sendState();
}

void chooseScenario() {
  if (Serial3.available()) {
    b = Serial3.read();
    switch (b) {
      case '0':
        interpreterState = sg_waiting;
        currentScenarioI = 0;
        playS(currentScenarioI+1);
        //        }
        break;
      case '1':
        interpreterState = sg_waiting;
        currentScenarioI = 1;
        playS(currentScenarioI+1);
        //        }
        break;

      case '2':
        interpreterState = sg_waiting;
        currentScenarioI = 2;
        playS(currentScenarioI+1);
        break;
      case '3':
        interpreterState = sg_waiting;
        currentScenarioI = 3;
        playS(currentScenarioI+1);
        //        }
        break;
      case '4':
        interpreterState = sg_waiting;
        currentScenarioI = 4;
        playS(currentScenarioI+1);
        //        }
        break;
      case '5':
        interpreterState = sg_waiting;
        currentScenarioI = 5;
        playS(currentScenarioI+1);
        //        }
        break;
      case '6':
        interpreterState = sg_waiting;
        currentScenarioI = 6;
        playS(currentScenarioI+1);
        //        }
        break;
      case '7':
        interpreterState = sg_waiting;
        currentScenarioI = 7;
        playS(currentScenarioI+1);
        //        }
        break;
      case '(': interpreterState = choose_game;playS(game_mod_audio); delay(2000);playS(CHOOSE_GAME_AUDIO); break;
      default:
        // default code (should never run)
        break;
    }
  }
  sendState();
}

void sgWaiting() {
  if (Serial3.available()) {
    b = Serial3.read();
    settings();
    switch (b) {
      //      case '0':
      //        resetButtons();
      //        break;

      case '1':
        //        Serial3.println("9-X");
        //        if (!croce) {
        //          croce = true;
        interpreterState = game_modality;
        gameState = setting;
        //CapacitivesUpdate(head);
        //        }
        break;

      default:
        // default code (should never run)
        break;
    }

  }
  sendState();
}

void gameMod() {
  if (Serial3.available()) {
    b = Serial3.read();
    settings();
    switch (b) {
      case '.':
        interpreterState = choose_modality;
        loopStartTime=millis();
        break;
    }

  }
  sendState();
}

void disCharge() {
  sendState();
}

//void resetButtons() {
//  triangolo = false;
//  quadrato = false;
//  cerchio = false;
//  croce = false;
//  startbutton = false;
//  select = false;
//}
//




