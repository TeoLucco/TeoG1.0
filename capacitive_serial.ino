void capacitiveSerialLoop() {
  reciveSerial();
  sendSerial();
}


void reciveSerial() {
  resetPatCountTimer();
  resetHitCountTimer();
  resetHugsCountTimer();
  if (pressedButton != -1) pressedButton = -1;
  if (touched != noWhere) touched = noWhere;
  if (touch_type != nothing) touch_type = nothing;
  if (Serial.available()) {
    int b = Serial.read();
    //Serial3.print("FROM NANO TO MEGA:'");
    //Serial3.print(b);
    //Serial3.println("'");
    if (workingCapacitives != noOne) {
      switch (b) {
        case 9: hugRecived(); break;
        case 2: patRecived(); break;
        case 3: hitRecived(); break;
        case 4: pressedButton = Serial.read(); /*Serial3.print("Pressed button n "); Serial3.println(pressedButton);*/ break;
        default : /*Serial3.println("Stringa ricevuta non coincide!");*/ break;
      }
    }
  }
}

void hugRecived() {
  if (bodyCapacitor) {
    abbraccioN++;
    lastHugRecivedTime = millis();
    touch_type = hugT;
    //Serial3.print("Abbraccio durata "); Serial3.println(abbraccioN);
    if(actual_movement!=autonomous_capa && prev_movement!=autonomous_capa && prev_movement2!=autonomous_capa && prev_movement3!=autonomous_capa){
    timedPlayS(HUG_AUDIO, 10000);
    bodyLedUpdate(color_pulse, redC, 4000);
    //    setLedTimer(4000);
    //    bodyLedUpdate(color_pulse, redC);
    resetPats();
    resetHits();
    }
  }
}

void patRecived() {
  if (bodyCapacitor) {
    resetHits();
    touch_type = patT;
    int i = Serial.read();
    //if (i == -1) break;
    lastPatTime[i] = millis();
    //Serial3.print("pat at "); Serial3.println(i);
    setTouched(i);
    if (switchToGameMod && i == 2) {
      switchToGameMod = false;
      interpreterState = game_modality;
    } else  if(actual_movement!=autonomous_capa && prev_movement!=autonomous_capa && prev_movement2!=autonomous_capa && prev_movement3!=autonomous_capa){
      if (pats >= N_PATS) {
        //resetPats();
        timedPlayS(N_PATS_AUDIO, 5000);
        bodyLedUpdate(color_wipe, lightBlueC, 2000);
        //        setLedTimer(2000);
        //        bodyLedUpdate(color_wipe, lightBlueC);
      } else {
        if (millis() - lastPatTime[i] > 1000) {
          pat[i]++;
          pats++;
        }
        timedPlayS(PATS_AUDIO1 + rand() % 2, 5000);
        bodyLedUpdate(color_wipe, lightBlueC, 2000);
        //        setLedTimer(2000);
        //        bodyLedUpdate(color_wipe, lightBlueC);
        //playS(23);
      }
    }
  }
}

void hitRecived() {
  if (bodyCapacitor) {
    resetPats();
    touch_type = hitT;
    int i = Serial.read();
    //if (i == -1) break;
    lastHitTime[i] = millis();
    //Serial3.print("hit at "); Serial3.println(i);
    setTouched(i);
    if (hits >= N_HITS) {
      resetHits();
      nhits(i);
    } else {
      hit[i]++;
      hits++;
      hitRecived(i);
    }
  }
}

void setTouched(int i) {
  switch (i) {
    case 0: touched = leftT; break;
    case 1: touched = rightT; break;
    case 2: touched = frontT; break;
    default: touched = noWhere; break;
  }
  //Serial3.println("*r" + String(touched) + "*");
}

void sendSerial() {
  defineWorkingCapacitives();
  if (workingCapacitives != previousWorkingCapacitives) {
    switch (workingCapacitives) {
      case noOne: Serial.write(0); break;
      case head: Serial.write(1); break;
      case body: Serial.write(2); if(actual_movement==autonomous_capa)Serial.write(4);else Serial.write(5); break;
      case both: Serial.write(3); break;
    }
    Serial3.println("*E" + String(workingCapacitives) + "*");
    previousWorkingCapacitives = workingCapacitives;
  }
}

void defineWorkingCapacitives() {
  if (interpreterState == fam_modality) {
    if (actual_movement != autonomous_capa || switchToGameMod) {
      if (triskar.isStopped() && actual_movement == no_movement) CapacitivesUpdate(body);
      else CapacitivesUpdate(noOne);
    } else CapacitivesUpdate(body);
  } else if (interpreterState == choose_game || interpreterState == choose_scenario || interpreterState == choose_modality || interpreterState == sg_waiting) {
    if (headInterpreter) CapacitivesUpdate(head);
    else CapacitivesUpdate(noOne);
  } else if (interpreterState == game_modality) {
    if (gameState == wait_answer) CapacitivesUpdate(head);
    else CapacitivesUpdate(noOne);
  }
}

void nhits(int i) {
  CapacitivesUpdate(noOne); //DA TESTARE(DOVREBBE ESSERE RIDONDANTE)
  if(actual_movement!=autonomous_capa && prev_movement!=autonomous_capa && prev_movement2!=autonomous_capa && prev_movement3!=autonomous_capa){
    switch (i) {
      case 0: alpha = 0.70 * PI; startMovement(make_sad2L, redCrazy, color_wipe, N_HIT_AUDIO); break;
      case 1: alpha = 0.70 * PI; startMovement(make_sad2R, redCrazy, color_wipe, N_HIT_AUDIO); break;
      case 2: startMovement(make_sad2, redCrazy, color_wipe, N_HIT_AUDIO); break;
      case 3: startMovement(angrymov, redCrazy, color_wipe, N_HIT_AUDIO); break;
    }
  }
}

void hitRecived(int i) {
  CapacitivesUpdate(noOne); //DA TESTARE(DOVREBBE ESSERE RIDONDANTE)
  if(actual_movement!=autonomous_capa && prev_movement!=autonomous_capa && prev_movement2!=autonomous_capa && prev_movement3!=autonomous_capa){
    switch (i) {
      case 0: alpha = 0.70 * PI; startMovement(scared_hitL, orangeC, color_wipe, HIT_AUDIO); break;
      case 1: alpha = 0.70 * PI; startMovement(scared_hitR, orangeC, color_wipe, HIT_AUDIO); break;
      case 2: startMovement(scared_hit, orangeC, color_wipe, HIT_AUDIO); break;
      case 3: startMovement(scared_round, orangeC, color_wipe, HIT_AUDIO); break;
    }
  }
}

void resetPatCountTimer() {
  pats = 0;
  for (int i = 0; i < N_BODY_SENSORS; i++) {
    if (millis() - lastPatTime[i] > RESET_PAT_TIME /*&& capacitiveState[i] == no_touch*/) {
      pat[i] = 0;
    }
    pats += pat[i];
  }
}

void resetHitCountTimer() {
  hits = 0;
  for (int i = 0; i < N_BODY_SENSORS; i++) {
    if (millis() - lastHitTime[i] > RESET_HIT_TIME /*&& capacitiveState[i] == no_touch*/) {
      hit[i] = 0;
    }
    hits = hit[i];
  }
}

void resetHugsCountTimer() {
  if (millis() - lastHugRecivedTime > RESET_HUG_TIME) {
    abbraccioN = 0;
  }
}

void resetPats() {
  for (int j = 0; j < N_BODY_SENSORS; j++) pat[j] = 0;
  pats = 0;
}
void resetHits() {
  for (int j = 0; j < N_BODY_SENSORS; j++) hit[j] = 0;
  hits = 0;
}
void CapacitivesUpdate(warKingsCapacitives c) {
  previousWorkingCapacitives = workingCapacitives;
  workingCapacitives = c;
}

