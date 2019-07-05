long roundTime = 10000; // Time for player to find the color

// include the library code:
#include <LiquidCrystal_I2C.h>

// define pins for color sensor
#define S0 6
#define S1 7
#define S2 9
#define S3 8
#define sensorOut 10

long currentTime; //elapsed time in round

long startTime = millis(); //start time of round

// values of each color from color sensor
int frequencyR = 0;
int frequencyG = 0;
int frequencyB = 0;

int color = 0;

// player points
int pointsPlayer1 = 0;
int pointsPlayer2 = 0;

int newGame = 0; 
int keyRead = 0; 

int playerOnTurn = 2; 

int rightColorFound = 0; 

LiquidCrystal_I2C lcd(0x27, 20, 4); //Hier wird festgelegt um was für einen Display es sich handelt. In diesem Fall eines mit 16 Zeichen in 2 Zeilen und der HEX-Adresse 0x27. Für ein vierzeiliges I2C-LCD verwendet man den Code "LiquidCrystal_I2C lcd(0x27, 20, 4)" 

void setup() {
  
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);

  pinMode(2, INPUT); //RED
  pinMode(3, INPUT); //YELLOW
  pinMode(4, INPUT); //GREEN
  pinMode(5, INPUT); //BLUE
  
  
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
  
  Serial.begin(9600);

  lcd.init();
  lcd.backlight(); 
}

void loop() {

if(pointsPlayer1 == 0 && pointsPlayer2 == 0 && newGame == 0){
  startGame();
  newGame = 1;
  }
}

void startGame(){
  tone(11, 250, 150);
  delay(100);
  tone(11, 350, 150);
  delay(100);
  tone(11, 450, 150);
  delay(100);
  tone(11, 550, 150);

  lcd.clear();
  lcd.setCursor(1,1);
  lcd.print("Welcome to Veo Veo");
  delay(2500);
  player1Chooses();
  }

void player1Chooses(){ 
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Player 1");
  lcd.setCursor(3,2);
  lcd.print("Choose a color");
  while(keyRead == 0){ 
    readKey();
    }
  }

void player2Chooses(){
  lcd.clear();
  lcd.setCursor(6,0);
  lcd.print("Player 2");
  lcd.setCursor(3,2);
  lcd.print("Choose a color");
  while(keyRead == 0){
    readKey();
    }
  }  

void showPoints(){
  lcd.clear();
  lcd.setCursor(7,0);
  lcd.print("Score:");
  lcd.setCursor(4,2);
  lcd.print("Player 1: ");
  lcd.print(pointsPlayer1);
  lcd.setCursor(4,3);
  lcd.print("Player 2: ");
  lcd.print(pointsPlayer2);
  delay(5000);
  }  

void newRound(){
  color = 0;
  keyRead = 0;
  if(playerOnTurn == 2){
    playerOnTurn = 1;
    pointsPlayer2++;
    rightColorFound = 0;
    showPoints();
    player2Chooses();
    }else{
      playerOnTurn = 2;
      pointsPlayer1++;
      rightColorFound = 0;
      showPoints();
      player1Chooses();
      }
  }

void readKey(){

  if(digitalRead(2) == HIGH){
    color = 1;
    keyRead= 1;

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 150);
    delay(100);
    tone(11, 750, 150);
    
    lcd.clear();
    lcd.setCursor(6,0);
    lcd.print("Player " + String(playerOnTurn));
    lcd.setCursor(3,2);
    lcd.print("Find a RED thing");
    
    startTime = millis();
    while(rightColorFound == 0 && currentTime - startTime <= roundTime){
      checkRed();
      currentTime = millis();
      }

    lcd.clear();
  
    tone(11, 150, 150);
    delay(300);
    tone(11, 50, 150);

    lcd.setCursor(4,2);
    lcd.print("Time is up!");
    delay(1500);
    proofBluff();
 
    }else if(digitalRead(3) == HIGH){
       color = 4;
       keyRead= 1;

       tone(11, 450, 150);
       delay(100);
       tone(11, 650, 150);
       delay(100);
       tone(11, 750, 150);
       
       lcd.clear();
       lcd.setCursor(6,0);
       lcd.print("Player " + String(playerOnTurn));
       lcd.setCursor(0,2);
     lcd.print("YELLOW! Find YELLOW!");
    
       startTime = millis();
       while(rightColorFound == 0 && currentTime - startTime <= roundTime){
         checkYellow();
         currentTime = millis();
         }
      
       lcd.clear();
      
       tone(11, 150, 150);
       delay(300);
       tone(11, 50, 150);

       lcd.setCursor(4,2);
       lcd.print("Time is up!");
       delay(1500);
       proofBluff();

      }else if(digitalRead(4) == HIGH){
       color = 2;
       keyRead= 1;

       tone(11, 450, 150);
       delay(100);
       tone(11, 650, 150);
       delay(100);
       tone(11, 750, 150);
       
       lcd.clear();
       lcd.setCursor(6,0);
       lcd.print("Player " + String(playerOnTurn));
       lcd.setCursor(2,2);
       lcd.print("Something Green!");
    
       startTime = millis();
       while(rightColorFound == 0 && currentTime - startTime <= roundTime){
         checkGreen();
         currentTime = millis();
         }
      
       lcd.clear(); 
       
       tone(11, 150, 150);
       delay(300);
       tone(11, 50, 150);

       lcd.setCursor(4,2);
       lcd.print("Time is up!");
       delay(1500);
       proofBluff();

      }else if(digitalRead(5) == HIGH){
         color = 3;
         keyRead= 1;

         tone(11, 450, 150);
         delay(100);
         tone(11, 650, 150);
         delay(100);
         tone(11, 750, 150);
         
         lcd.clear();
         lcd.setCursor(6,0);
         lcd.print("Player " + String(playerOnTurn));
         lcd.setCursor(4,2);
         lcd.print("Gimme BLUE!");
    
         startTime = millis(); //Startzeit des Suchvorgangs
         while(rightColorFound == 0 && currentTime - startTime <= roundTime){
           checkBlue();
           currentTime = millis();
         }
      
         lcd.clear(); 
         
         tone(11, 150, 150);
         delay(300);
         tone(11, 50, 150);

         lcd.setCursor(4,2);
         lcd.print("Time is up!");
         delay(1500);
         proofBluff();
        }
  }

void colorPicker(){
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  frequencyR = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequencyR = map(frequencyR, 25,72,255,0);

    if(frequencyR < 0){
    frequencyR = 0;
    }else if(frequencyR > 255){
      frequencyR = 255;
      }
  
  // Printing the value on the serial monitor
  Serial.print("R= ");//printing name
  Serial.print(frequencyR);//printing RED color frequency
  Serial.print("  ");

  // Setting Green filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequencyG = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequencyG = map(frequencyG, 30,90,255,0);

  if(frequencyG < 0){
    frequencyG = 0;
    }else if(frequencyG > 255){
      frequencyG = 255;
      }
    
  // Printing the value on the serial monitor
  Serial.print("G= ");//printing name
  Serial.print(frequencyG);//printing RED color frequency
  Serial.print("  ");

  // Setting Blue filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  frequencyB = pulseIn(sensorOut, LOW);
  //Remaping the value of the frequency to the RGB Model of 0 to 255
  frequencyB = map(frequencyB, 25,70,255,0);

    if(frequencyB < 0){
    frequencyB = 0;
    }else if(frequencyB > 255){
      frequencyB = 255;
      }
    
  // Printing the value on the serial monitor
  Serial.print("B= ");//printing name
  Serial.print(frequencyB);//printing RED color frequency
  Serial.println("  ");
  }


void checkRed(){
  colorPicker();
  if(frequencyR > 200 && frequencyG < 115 && frequencyB < 115){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);

    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRound();
    }
  }


void checkYellow(){
  colorPicker();
  if(frequencyR < 200 && frequencyG > 200 && frequencyB < 210){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);
    
    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRound();
    }
  }

void checkGreen(){
  colorPicker();
  if(frequencyR < 200 && frequencyG > 200 && frequencyB < 210){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);
    
    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRound();
    }
  }

void checkBlue(){
  colorPicker();
  if(frequencyR < 120 && frequencyG < 120 && frequencyB > 150){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);
    
    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRound();
    }
  }

void newRoundBluff(){
  color = 0;
  keyRead = 0; //keyRead wieder zurücksetzen
  if(playerOnTurn == 2){ //Spieler switchen, Punkt geben, anderen spieler aufrufen
    playerOnTurn = 1;
    pointsPlayer1++;
    rightColorFound = 0;
    showPoints();
    player2Chooses();
    }else{
      playerOnTurn = 2;
      pointsPlayer2++; // GEHT NICHT
      rightColorFound = 0;
      showPoints();
      player1Chooses();
      }
  }

void proofBluff(){

  if(color == 1){

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 150);
    delay(100);
    tone(11, 750, 150);
    
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("Opponent!");
    lcd.setCursor(0,2);
    lcd.print("Where is that color?");
    startTime = millis(); 
    while(rightColorFound == 0 && currentTime - startTime <= roundTime){
      checkRedBluff();
      currentTime = millis(); 
      }
      
    lcd.clear();
    
    tone(11, 150, 150);
    delay(300);
    tone(11, 50, 150);

    lcd.setCursor(4,2);
    lcd.print("Time is up!");
    delay(1500);
    newRound();
    }else if(color == 2){

      tone(11, 450, 150);
      delay(100);
      tone(11, 650, 150);
      delay(100);
      tone(11, 750, 150);
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Opponent!");
      lcd.setCursor(0,2);
      lcd.print("Where is that color?");
      startTime = millis(); 
      while(rightColorFound == 0 && currentTime - startTime <= roundTime){
      checkGreenBluff();
      currentTime = millis();
      }
      
      lcd.clear();    
      
      tone(11, 150, 150);
      delay(300);
      tone(11, 50, 150);

      lcd.setCursor(4,2);
      lcd.print("Time is up!");
      delay(1500);
      newRound();
      }else if(color == 4){
      tone(11, 450, 150);
      delay(100);
      tone(11, 650, 150);
      delay(100);
      tone(11, 750, 150);
      lcd.clear();
      lcd.setCursor(5,0);
      lcd.print("Opponent!");
      lcd.setCursor(0,2);
      lcd.print("Where is that color?");
      startTime = millis();
      while(rightColorFound == 0 && currentTime - startTime <= roundTime){
      checkYellowBluff();
      currentTime = millis(); 
      }
      
      lcd.clear();        
      
      tone(11, 150, 150);
      delay(300);
      tone(11, 50, 150);

      lcd.setCursor(4,2);
      lcd.print("Time is up!");
      delay(1500);
      newRound();
      }else if(color == 3){
        tone(11, 450, 150);
        delay(100);
        tone(11, 650, 150);
        delay(100);
        tone(11, 750, 150);
        
        lcd.clear();
        lcd.setCursor(5,0);
        lcd.print("Opponent!");
        lcd.setCursor(0,2);
        lcd.print("Where is that color?");
        startTime = millis(); 
        while(rightColorFound == 0 && currentTime - startTime <= roundTime){
        checkBlueBluff();
        currentTime = millis(); 
      }
      
      lcd.clear();        
      
      tone(11, 150, 150);
      delay(300);
      tone(11, 50, 150);

      lcd.setCursor(4,2);
      lcd.print("Time is up!");
      delay(1500);
      newRound();
        }
  }

void checkRedBluff(){
  colorPicker();
  if(frequencyR > 200 && frequencyG < 115 && frequencyB < 115){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);
    
    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRoundBluff();
    }
  }

void checkYellowBluff(){
  colorPicker();
  if(frequencyR < 200 && frequencyG > 200 && frequencyB < 210){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);
    
    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRoundBluff();
    }
  }

void checkGreenBluff(){
  colorPicker();
  if(frequencyR < 200 && frequencyG > 200 && frequencyB < 210){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);
    
    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRoundBluff();
    }
  }

void checkBlueBluff(){
  colorPicker();
  if(frequencyR < 120 && frequencyG < 120 && frequencyB > 150){
    lcd.clear();

    tone(11, 450, 150);
    delay(100);
    tone(11, 650, 350);

    lcd.setCursor(6,2);
    lcd.print("Great!");
    rightColorFound = 1;
    delay(3000);
    newRoundBluff();
    }
  }
