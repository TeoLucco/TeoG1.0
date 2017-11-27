#define timePerAnsw 50000
#define maxQuestionsPerEx 10
#define maxAnswersPerEx 4
#define maxScenariosPerEx 10
#define GamesNumber 10

int currentQuestionI = 0;
int currentCorrectAnswers = 0;
//int currentAnswers = 0;
bool currentGivenAnswers[N_HEAD_SENSORS]  = {false, false, false, false};

struct Scenario {
  int n_questions;
  int audio_indices[maxQuestionsPerEx] ;
  bool correct_answers[maxQuestionsPerEx][N_HEAD_SENSORS];
  String Id;
};

typedef struct Scenario t_Scenario;

struct Game {
  int n_senarios;
  t_Scenario scenarios[maxScenariosPerEx];
};

typedef struct Game t_Game;

t_Game games[] =
{ { // game 0
    6, //numero scenari
    {
      { // scenario 0
        4,//Number questions
        {    91,         91,       91,        91},
        { {true, false, false, false} , {false, false, false, true}, {false, true, false, false}, {false, false, true, false}},
        "SCENARIO1"
      },
      { // scenario 1
        4,//Number questions
        {    91,         91,       91,        91},
        { {false, false, false, true} , {false, false, true, false}, {false, true, false, false}, {true, false, false, false}},
        "SCENARIO2"
      },
      { // scenario 2
        4,//Number questions
        {    91,         91,       91,        91},
        { {false, false, true, false} , {false, true, false, false}, {true, false, false, false}, {false, false, false, true}},
        "SCENARIO3"
      },
      { // scenario 3
        4,//Number questions
        {    92,         92,       92,        92},
        { {true, false, false, false} , {false, false, false, true}, {false, true, false, false}, {false, false, true, false}},
        "SCENARIO4"
      },
      { // scenario 4
        4,//Number questions
        {    92,         92,       92,        92},
        { {false, false, false, true} , {false, false, true, false}, {false, true, false, false}, {true, false, false, false}},
        "SCENARIO5"
      },
      { // scenario 5
        4,//Number questions
        {    92,         92,       92,        92},
        { {false, false, true, false} , {false, true, false, false}, {true, false, false, false}, {false, false, false, true}},
        "SCENARIO6"
      }
    }
  },
  { 8,//numero scenari gioco 1
    { { 4,
        {    94,         96,       97,        98},
        { {false, true, true, true} , {false, false, true, false}, {true, false, false, true}, {false, true, false, false}},
        "SCENARIO1"
      },
      { 4,
        {    95,          96,       100,        99},
        { {false, true, false, true} , {false, true, false, true}, {false, false, true, false}, {true, false, false, false}},
        "SCENARIO2"
      },
      { 4,
        {    94,          103,       99,        101},
        { {true, true, false, true} , {true, true, false, false}, {false, false, false, true}, {false, true, false, false}},
        "SCENARIO3"
      },
      { 4,
        {    95,          99,       97,        102},
        { {false, false, true, true} , {false, false, false, true}, {false, true, false, false}, {true, false, false, false}},
        "SCENARIO4"
      },
      { 5,
        {    94,          95,       101,        96,        98},
        { {false, true, false, true} , {false, false, true, true}, {false, true, true, false}, {false, true, false, false}, {true, false, false, false}},
        "SCENARIO5"
      },
      { 5,
        {    94,          95,       99,        102,        98},
        { {false, true, false, true} , {false, false, true, true}, {false, false, false, true}, {true, true, false, false}, {true, false, false, false}},
        "SCENARIO6"
      },
      { 5,
        {    94,          95,       100,        103,        102},
        { {true, true, false, false} , {false, true, false, true}, {false, false, true, false}, {false, false, false, true}, {true, true, false, false}},
        "SCENARIO7"
      },
      { 5,
        {    94,          95,       101,        100,        103},
        { {false, false, true, true} , {true, true, false, true}, {true, false, false, false}, {false, false, false, true}, {false, false, true, false}},
        "SCENARIO8"
      }
    }
  },
  { 6,//numero scenari gioco 2
    { { 4,
        {    105,         106,       107,        108},
        { {true, false, false, false} , {false, false, true, false}, {false, true, false, false}, {false, false, false, true}},
        "SCENARIO1"
      },
      { 4,
        {    109,          110,       111,        112},
        { {false, true, false, false} , {false, false, true, false}, {false, false, false, true}, {true, false, false, false}},
        "SCENARIO2"
      },
      { 4,
        {    113,          114,       115,        116},
        { {false, false, false, true} , {false, true, false, false}, {true, false, false, false}, {false, false, true, false}},
        "SCENARIO3"
      },
      { 3,
        {    117,          118,       119},
        { {true, false, false, true} , {false, false, true, false}, {false, true, false, false}},
        "SCENARIO4"
      },
      { 3,
        {    120,          121,       122},
        { {false, true, false, false} , {true, true, false, false}, {false, false, false, true}},
        "SCENARIO5"
      },
      { 4,
        {    135,          122,       123,      124},
        { {false, false, true, false} , {true, true, false, true}, {false, true, false, false}, {false, false, false, true}},
        "SCENARIO6"
      }
    }
  },
  { 3,//numero scenari gioco 3
    { { 5,
        {    126,         127,       128,        129,        130},
        { {true, false, false, false} , {false, false, false, true}, {false, false, true, false}, {false, false, true, false}, {false, true, false, false}},
        "SCENARIO1"
      },
      { 5,
        {    131,         132,       133,        134,       127},
        { {false, false, false, true} , {true, false, true, true}, {false, false, false, true}, {false, false, false, true}, {false, true, false, false}},
        "SCENARIO2"
      },
      { 4,
        {    131,          135,       134,        133},
        { {false, false, false, true} , {false, true, true, false}, {false, false, false, true}, {true, false, false, false}},
        "SCENARIO3"
      }
    }
  }
}
;

int answerTillNow[maxAnswersPerEx];
int answerI = 0;

//struct Scenario & getCurrentScenario() {
//  t_Game & g = games[currentGameI].scenarios[currentScenarioI];
//  t_Scenario & s = games[currentGameI].scenarios[currentScenarioI];
//  return s;
//}

int n_answers[maxQuestionsPerEx];
unsigned long int questionResponseTime[maxQuestionsPerEx];
boolean givenAnswersReport[maxQuestionsPerEx];

void setupScenario(struct Scenario &s) {
  //Serial3.println(s.Id);
  for (int i = 0; i < s.n_questions; i++) {
    n_answers[i] = 0;
  }
  for (int i = 0; i < s.n_questions; i++) {
    questionResponseTime[i] = 5;
    givenAnswersReport[i] = true;
    for (int j = 0; j < N_HEAD_SENSORS; j++) {
      if (s.correct_answers[i][j]) {
        n_answers[i]++;
      }
    }
    //Serial3.println( s.n_answers[i]);
  }
}

void settingGame() {
  t_Scenario &s = games[currentGameI].scenarios[currentScenarioI];
  setupScenario(s);
  currentQuestionI = 0;
  gameState = make_question;
}

void turnOnLed() {
  t_Scenario &s = games[currentGameI].scenarios[currentScenarioI];
  if (currentGameI == 0) {
    for (int i = 0; i < N_HEAD_SENSORS; i++) {
      if (s.correct_answers[currentQuestionI][i]) {
        switch (i) {
          case 0: bodyLedUpdate(color_wipe, redC); headLedUpdate(red, color_wipe); break;
          case 1: bodyLedUpdate(color_wipe, greenC); headLedUpdate(green, color_wipe); break;
          case 2: bodyLedUpdate(color_wipe, yellowC); headLedUpdate(yellow, color_wipe); break;
          case 3: bodyLedUpdate(color_wipe, blueC); headLedUpdate(blue, color_wipe); break;
        }
      }
    }
  }
}

void makeQuestion() {
  t_Scenario &s = games[currentGameI].scenarios[currentScenarioI];
  //Serial3.print("currentQuestionI:  "); Serial3.println(currentQuestionI);
  //Serial3.print("s.n_questions: "); Serial3.println(s.n_questions);
  turnOnLed();
  if (currentQuestionI < s.n_questions) {                                   //se devo fare ancora domande
    //Serial3.println("currentQuestionI < s.n_questions");
    //Serial3.print("played audio: "); Serial3.println(s.audio_indices[currentQuestionI]);
    playS(s.audio_indices[currentQuestionI]);                                 //faccio la domanda I
    //Serial3.println("Reset del vettore risposte fino ad ora");
    //Serial3.println("currentGivenAnswers: ");
    for (int i = 0; i < N_HEAD_SENSORS; i++) {
      currentGivenAnswers[i] = false;                                         //azzero il vettore delle risposte date fino ad ora
      //Serial3.print(currentGivenAnswers[i]);Serial3.print(" ");
    }
    //Serial3.println();
    currentCorrectAnswers = 0;                                               //azzero il contatore delle risposte corrette date fino ad ora
    gameState = wait_answer;                                                  //vado in stato wait answer
    startWaitingTime = millis();
    //Serial3.println("startWaitingTime: " + String(startWaitingTime));
    //Serial3.println("wait answer begin");
  } else {                                                                   //se invece ho finito le domande
    gameState = end_game;                                                     //vado a stato end game
  }
}

void waitAnswer() {
  if (workingCapacitives != head) {
    //Serial3.println("Attivo capacitivi Testa");
    //CapacitivesUpdate(head);
  }
  t_Scenario &s = games[currentGameI].scenarios[currentScenarioI];
  if (currentCorrectAnswers < n_answers[currentQuestionI]) {    //se ci sono ancora risposte da dare
    turnOnLed();
    if (currentCorrectAnswers > 0) {                                //se ho già dato una risposta
      //Serial3.println("E poi???");                                    //say:e poi??
      timedPlayS(ALTRA_RISPOSTA_AUDIO, 15000);
    }
    if (pressedButton != -1) {                                        //se viene premuto un bottone
      int a = pressedButton;
      if (currentGivenAnswers[a]) {                                     //se il bottone è già stato premuto per questa domanda
        if (s.correct_answers[currentQuestionI][a]) {                     //se il bottone premuto è una risposta corretta
          headLedUpdate(green, color_wipe);
        } else {
          headLedUpdate(red, color_wipe);
          // wrong
        }
        //Serial3.println("Bottone Gia premuto per questa domanda!");
        playS(RISPOSTA_GIA_DATA_AUDIO);                                                        // say: hai già dato questa risposta, provane un'altra
      } else {                                                          //se invece è la prima volta che prova un bottone
        //Serial3.println("Prima volta che premi il bottone!");
        currentGivenAnswers[a] = true;                                    //mi salvo il bottone che ha premuto
        if (s.correct_answers[currentQuestionI][a]) {                     //se il bottone premuto è una risposta corretta
          //Serial3.print("s.correct_answers[currentQuestionI][a]: ");
          //Serial3.println("risposta corretta");                             // correct
          currentCorrectAnswers++;                                          //incremento il contatore delle risposte corrette
          rightAnswer();                                                    //eseguo movimento right answer
        } else {                                                          //se invece la riposta è sbagliata
          //Serial3.println("risposta scorretta");
          givenAnswersReport[currentQuestionI] = false;
          wrongAnswer();                                                    //say risposta sbagliata  ed esegui movimento
          // wrong
        }
        gameState = mov;                //TODO da testare############################################################
      }

    }
  } else {                                                        //se non ci sono più risposte da dare
    questionResponseTime[currentQuestionI] = (millis() - startWaitingTime);
    //Serial3.println("Millis: " + String(millis()));
    //Serial3.println("startWaitingTime: " + String(startWaitingTime));
    //Serial3.println("Response Time question number " + String(currentQuestionI) + ": " + String(questionResponseTime[currentQuestionI]));
    //Serial3.println("Report question number " + String(currentQuestionI) + ": " + String(givenAnswersReport[currentQuestionI]));

    currentQuestionI++;                                                                       //incrementa l'indice della domanda
    gameState = make_question;                                                                //vado in stato make question
    //Serial3.println("wait answer end");
  }
}

void rightAnswer() {
  int randNumber = rand() % 4 + make_happy0;
  int randNumber2 = rand() % 3;
  ////Serial3.println("Disattivo Capacitivi");
  previousWorkingCapacitives = workingCapacitives;
  if (interpreterState == game_modality)workingCapacitives = noOne;
  else if (interpreterState == fam_modality)workingCapacitives = body;
  if (randNumber2 == 0)
    playS(RIGHT_ANSWER_AUDIO1);
  else if (randNumber2 == 1)
    playS(RIGHT_ANSWER_AUDIO2);
  else
    playS(RIGHT_ANSWER_AUDIO3);
  //  setLedTimer(2000);
  //  bodyLedUpdate(color_wipe, greenC, 2000);
  //  headLedUpdate(green, color_wipe);
  //  startMovement(randNumber); //at the end of makeHappy function there's the gameStateChange
  startMovement(randNumber, greenC, color_pulse);
}
void wrongAnswer() {
  int randNumber2 = rand() % 3;
  //Serial3.println("Disattivo Capacitivi");
  previousWorkingCapacitives = workingCapacitives;
  if (interpreterState == game_modality)workingCapacitives = noOne;
  else if (interpreterState == fam_modality)workingCapacitives = body;
  if (randNumber2 == 0)
    playS(WRONG_ANSWER_AUDIO1);
  else if (randNumber2 == 1)
    playS(WRONG_ANSWER_AUDIO2);
  else
    playS(WRONG_ANSWER_AUDIO3);
  dir = rand() % 2;
  //  bodyLedUpdate(color_wipe, redC, 2000);
  //  headLedUpdate(red, color_wipe);
  //  startMovement(make_sad1);
  startMovement(make_sad1, redC, color_pulse);
}

void endGame() {
  //Serial3.print("End Game");
  int nRightAns = countResult();
  playS(END_GAME);
  delay(4000);
  if (nRightAns == 0)
    playS(64);
  else if (nRightAns == 1)
    playS(63);
  else if (nRightAns == 2)
    playS(62);
  else if (nRightAns > 2)
    playS(61); // gioco finito
  if(digitalRead(BUSY_PIN) == HIGH)
  gameState = dance;

  //Serial3.print("Correct answers number:"); Serial3.println(nRightAns);
  t_Scenario &s = games[currentGameI].scenarios[currentScenarioI];

  Serial3.print("*G");
  for (int i = 0; i < s.n_questions - 1; i++) {
    Serial3.print(questionResponseTime[i]); Serial3.print(",");
  }
  Serial3.print(questionResponseTime[s.n_questions - 1]); Serial3.println("*");

  Serial3.print("*H");
  for (int i = 0; i < s.n_questions - 1; i++) {
    if (givenAnswersReport[i]) Serial3.print("t");
    else Serial3.print("f");
    Serial3.print(",");
  }
  if (givenAnswersReport[s.n_questions - 1]) Serial3.print("t");
  else Serial3.print("f");
  Serial3.println("*");
  currentGameI=-1;
  currentScenarioI=-1;
}

int countResult() {
  int n = 0;
  t_Scenario s = games[currentGameI].scenarios[currentScenarioI];
  for (int i = 0; i < maxQuestionsPerEx; i++) {
    if (givenAnswersReport[i])n++;
  }
  return n;
  //  int n = 0;
  //  for (int i = 0; i < maxQuestionsPerEx; i++) {
  //    if (questionResult[i]) n++;
  //    Serial3.print(questionResult[i]);
  //    if (i != maxQuestionsPerEx - 1) Serial3.print(",");
  //    else Serial3.print(";");
  //  }
  //  return n;
}
boolean color_Game = false;

//void colorGameSetup() {
//  if (!color_Game) {
//    color_Game = true;
//    int color = rand() % 4;
//    playS(DOMANDA_COLORE_LED_AUDIO);
//    switch (color) {
//      case 0: headLedUpdate(red, color_wipe); break;
//      case 1: headLedUpdate(green, color_wipe); break;
//      case 2: headLedUpdate(blue, color_wipe); break;
//      case 3: headLedUpdate(yellow, color_wipe); break;
//    }
//    buttonToTouch = color;
//    //CapacitivesUpdate(head);
//  }
//}

void makeDance(){
  startMovement(make_dance,greenC,color_pulse,136 + rand()%3);
//  interpreterState = choose_game;
//  gameState=no_game;
}

void gameModality() {
  switch (gameState) {
    case no_game:         break;
    case setting:         settingGame(); break;
    case make_question:   makeQuestion(); break;
    case wait_answer:     waitAnswer(); break;
    case mov:             break;
    case end_game:        endGame(); break;
    case dance:           makeDance();break;
  }
}


