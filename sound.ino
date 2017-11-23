void dfPlayerSetup() {
  Serial2.begin(9600);

  Serial3.println();
  Serial3.println(F("DFRobot DFPlayer Mini Demo"));
  Serial3.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(Serial2)) {  //Use Serial2 to communicate with mp3.
    Serial3.println(F("Unable to begin:"));
    Serial3.println(F("1.Please recheck the connection!"));
    Serial3.println(F("2.Please insert the SD card!"));
    while (true);
  }
  Serial3.println(F("DFPlayer Mini online."));

  myDFPlayer.volume(28);  //Set volume value. From 0 to 30

}



void playS(int Index) {
  if (speakers) {
    myDFPlayer.play(Index);
    startPlayTime = millis();
    lastPlayed = Index;
  }
}
void timedPlayS(int Index, int millisec) {
  if ((millis() - startPlayTime > millisec && Index == lastPlayed) || (Index != lastPlayed)) playS(Index);
}

void stopS() {
  if (digitalRead(BUSY_PIN) == LOW) {
    myDFPlayer.stop();
  }
}

void updateSong() {
  switch (actual_movement) {
    case no_movement:         break;
    case follow:              break;
    case make_eight:          break;
    case make_circle:         break;
    case turn180r:            break;
    case turn180l:            break;
    case makeOnemF:            break;
    case makeOnemB:            break;
    case scared_round:        break;
    case dontwonna:           break;
    case angrymov:            break;
    case scared_behind:       break;
    case autonomous_movement: break;
    case make_happy0:         break;
    case make_happy1:         break;
    case make_happy2:         break;
    case make_happy3:         break;
    //      case make_happy4:         /*playS(16);break;
    case make_sad0:           break;
    case make_sad1:           break;
    case make_sad2:           break;
  }

}

void FirstSound() {
  if (!firstSound) {
    playS(BEEP_AUDIO);
    delay(5000);
    playS(CIAO_SONO_TEOAUDIO);
    delay(10000);
    playS(CHOOSE_MOD_AUDIO);
    firstSoundFinishTime = millis();
    firstSound = true;
  }
}

void playAudioTutorial() {
  if ((millis() - headInterpreterActivatedTime > 7000) && interpreterState == choose_modality && !tutorial && headInterpreter) {
    playS(scelta_tutorial_audio);
    tutorial = true;
  }
}




