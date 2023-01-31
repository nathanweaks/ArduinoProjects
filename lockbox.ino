#include <Keypad.h>
#include <Servo.h>
#include <IRremote.h>
#include <IRremoteInt.h>
Servo lock;
int pos=180;
const int button1 = 2; //first button is on pin 8
const int button2 = 3; //second is on pin 9
const int button3 = 4; //third is pin 10
const int button4 = 5; //fourth is pin 11


void checkEntered1(int button);

int code[] = {4,2,3,1}; //the desired code is entered in this array,
                        //separated by commas

int entered[5]; //create a new empty array for the code entered by
                //the user (has 4 elements)

const byte ROWS = 4; //four rows
const byte COLS = 4; //three columns
char keys[ROWS][COLS] = {
{'1','2','3','A'},

{'4','5','6','B'},

{'7','8','9','C'},

{'*','0','#','D'}
};
byte rowPins[ROWS] = {22, 23, 24, 25}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {26, 27, 28, 29}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );

void checkPasskey1(int numberpad);
int putin[] = {1, 2, 3, 4};
int passkey[5];

int receiver = 6; // Signal Pin of IR receiver to Arduino Digital Pin 11

/*-----( Declare objects )-----*/
IRrecv irrecv(receiver);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'

void checkPassed1(int remote);
int password[] = {1, 2, 3, 4};

int passed[5];

void setup(){ //run once at sketch startup
  Serial.begin(9600); //begin Serial

  pinMode(button1, INPUT_PULLUP); //button 1 is an input
  pinMode(button2, INPUT_PULLUP); //button 2 is an input
  pinMode(button3, INPUT_PULLUP); //button 3 is an input
  pinMode(button4, INPUT_PULLUP); //button 4 is an input

  lock.attach(9);

  irrecv.enableIRIn(); // Start the receiver
    
  }


void loop(){ //run repeatedly
  if (digitalRead(button1) == LOW){ //if button1 is pressed
    checkEntered1(1); //call checkEntered and pass it a 1
    
    delay(250);//wait, needed for correct functioning, otherwise
               //buttons are deemed to be pressed more than once
    
  }
  else if (digitalRead(button2) == LOW){ //if button2 is pressed
    checkEntered1(2); //call checkEntered1 and pass it a 2
    
    delay(250); //wait
    
  }
  else if (digitalRead(button3) == LOW){ //if button3 is pressed
    checkEntered1(3); //call checkEntered1 and pass it a 3
    
    delay(250); //wait
    
  }
  else if (digitalRead(button4) == LOW){ //if button4 is pressed
    checkEntered1(4); //call checkEntered1 and pass it a 4
    
    delay(250); //wait
    
  }
   char key = keypad.getKey();
  
  if (key=='1'){
    Serial.println(key);
    checkPasskey1(1);
    delay(250);
  }
  else if (key == '2'){
    Serial.println(key);
    checkPasskey1(2);
  }
  else if (key == '3'){
    Serial.println(key);
    checkPasskey1(3);
  }
  else if (key == '4'){
    Serial.println(key);
    checkPasskey1(4);
  }
  if (key == '*'){
    lock.write(90);
  }
    if (irrecv.decode(&results)) // have we received an IR signal?

  {
    translateIR(); 
    irrecv.resume(); // receive the next value
  }  
}/* --(end main loop )-- */

/*-----( Function )-----*/
void translateIR() // takes action based on IR code received

// describing Remote IR codes 

{

  switch(results.value)
    
  {
  case 0xFFA25D: Serial.println("POWER"); lock.attach(9); break;
  case 0xFFE21D: Serial.println("FUNC/STOP"); lock.detach(); break;
  case 0xFF629D: Serial.println("VOL+"); break;
  case 0xFF22DD: Serial.println("FAST BACK");    break;
  case 0xFF02FD: Serial.println("PAUSE");    break;
  case 0xFFC23D: Serial.println("FAST FORWARD");   break;
  case 0xFFE01F: Serial.println("DOWN");    break;
  case 0xFFA857: Serial.println("VOL-");    break;
  case 0xFF906F: Serial.println("UP");    break;
  case 0xFF9867: Serial.println("EQ");    break;
  case 0xFFB04F: Serial.println("ST/REPT");    break;
  case 0xFF6897: Serial.println("0");    break;
  case 0xFF30CF: Serial.println("1"); checkPassed1(1);   break;
  case 0xFF18E7: Serial.println("2"); checkPassed1(2);   break;
  case 0xFF7A85: Serial.println("3"); checkPassed1(3);   break;
  case 0xFF10EF: Serial.println("4"); checkPassed1(4);   break;
  case 0xFF38C7: Serial.println("5");    break;
  case 0xFF5AA5: Serial.println("6");    break;
  case 0xFF42BD: Serial.println("7");    break;
  case 0xFF4AB5: Serial.println("8");    break;
  case 0xFF52AD: Serial.println("9");    break;
  case 0xFFFFFFFF: Serial.println(" REPEAT");break;  

  default: 
    Serial.println(" other button   ");

  }// End Case

  delay(500); // Do not get immediate repeat 
}

void checkEntered1(int button){ //check the first element of the entered[] array
  
  if (entered[0] != 0){ //if it is not a zero, i.e. it has already been inputted
    checkEntered2(button); //move on to checkEntered2, passing it "button"
  }
  
  else if(entered[0] == 0){ //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[0] = button; //set the first element as the button that has been pressed
    Serial.print("1: ");Serial.println(entered[0]); //for debugging
  }
  
}

void checkEntered2(int button){ //check the second element of the entered[] array
  
  if (entered[1] != 0){ //if it is not a zero, i.e. it has already been inputted
    checkEntered3(button); //move on to checkEntered3, passing it "button"
  }
  
  else if(entered[1] == 0){ //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[1] = button; //set the second element as the button that has been pressed
    Serial.print("2: ");Serial.println(entered[1]); //for debugging
  }
  
}

void checkEntered3(int button){  //check the third element of the entered[] array
 
  if (entered[2] != 0){ //if it is not a zero, i.e. it has already been inputted
    checkEntered4(button); //move on to checkEntered4, passing it "button"
  }
  
  else if (entered[2] == 0){ //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[2] = button; //set the third element as the button that has been pressed
    Serial.print("3: ");Serial.println(entered[2]); //for debugging
  }
  
}

void checkEntered4(int button){  //check the third element of the entered[] array
   if (entered[3] == 0){ //if it is zero, i.e. if it hasn't been defined with a button yet
    entered[3] = button; //set the third element as the button that has been pressed
    Serial.print("4: ");Serial.println(entered[3]); //for debugging
    delay(100); //allow time for processing
    compareCode(); //call the compareCode function
  }
}

void compareCode(){ //checks if the code entered is correct by comparing the code[] array with the entered[] array
  for (int i = 0; i<4;i++){ //these three lines are for debugging
    Serial.println(entered[i]);
  }
  if ((entered[0]==code[0]) && (entered[1]==code[1]) && (entered[2]==code[2]) && (entered[3]==code[3])){ //if all the elements of each array are equal
    Serial.println("unlocked");
    lock.write(180);

    
    for (int i = 0; i < 5; i++){ //this next loop is for debugging
      entered[i] = 0;
      
    }
   
    loop(); //return to loop() (not really necessary)
  }
  
  else { //if you (or the intruder) get the code wrong
    
    Serial.println("locked");
    for (int i = 0; i < 5; i++){ //this next loop is for debugging
      entered[i] = 0;
     
    }
    
  }
}
void checkPasskey1(int numberpad){
  if (passkey[0] != 0){
    checkPasskey2(numberpad);
  }
  else if(passkey[0] == 0){
  passkey[0] = numberpad;
  Serial.print("1: "); Serial.println(passkey[0]);
}
}
void checkPasskey2(int numberpad){
  if (passkey[1] != 0){
    checkPasskey3(numberpad);
  }
  else if(passkey[1] == 0){
    passkey[1] = numberpad;
    Serial.print("2: "); Serial.println(passkey[1]);
  }
}
void checkPasskey3(int numberpad){
  if (passkey[2] != 0){
    checkPasskey4(numberpad);
  }
  else if (passkey[2] == 0){
    passkey[2] = numberpad;
    Serial.print("3: "); Serial.println(passkey[2]);
  }
}
void checkPasskey4(int numberpad){
  if (passkey[3] == 0){
    passkey[3] = numberpad;
    Serial.print("4: "); Serial.println(passkey[3]);
    delay(100);
    comparePutin();
  }
}
void comparePutin(){
  for (int i = 0; i<4;i++){ //these three lines are for debugging
    Serial.println(passkey[i]);
}
if ((passkey[0] == putin[0]) && (passkey[1] == putin[1]) && (passkey[2] == putin[2]) && (passkey[3] == putin[3])){
  Serial.println("unlocked");
  lock.write(180);

  for (int i = 0; i < 5; i++){ //this next loop is for debugging
      passkey[i] = 0;
      
    }
   
    loop();
}
 else { //if you (or the intruder) get the code wrong
    
    Serial.println("locked");
    for (int i = 0; i < 5; i++){ //this next loop is for debugging
      passkey[i] = 0;
}
 }
}
void checkPassed1(int remote){
  if (passed[0] != 0){
    checkPassed2(remote);
  }
  else if(passed[0] == 0){
    passed[0] = remote;
    Serial.print("1: "); Serial.println(passed[0]);
  }
}
void checkPassed2(int remote){
  if (passed[1] != 0){
    checkPassed3(remote);
  }
  else if (passed[1] == 0){
    passed[1] = remote;
    Serial.print("2: "); Serial.println(passed[1]);
  }
}
void checkPassed3(int remote){
  if (passed[2] != 0){
    checkPassed4(remote);
  }
  else if (passed[2] == 0){
    passed[2] = remote;
    Serial.print("3: "); Serial.println(passed[2]);
  }
}
void checkPassed4(int remote){
  if (passed[3] == 0){
    passed[3] = remote;
    Serial.print("4: "); Serial.println(passed[3]);
    delay(100);
    comparePassword();
  }
}
void comparePassword(){
  for (int i = 0; i<4;i++){ //these three lines are for debugging
    Serial.println(passed[i]);
}
if ((passed[0] == password[0]) && (passed[1] == password[1]) && (passed[2] == password[2]) && (passed[3] == password[3])){
  Serial.println("unlocked");
    lock.write(180);

    
    for (int i = 0; i < 5; i++){ //this next loop is for debugging
      passed[i] = 0;
      
    }
   
    loop(); //return to loop() (not really necessary)
  }
  
  else { //if you (or the intruder) get the code wrong
    
    Serial.println("locked");
    for (int i = 0; i < 5; i++){ //this next loop is for debugging
      passed[i] = 0;
     
    }
}
}
