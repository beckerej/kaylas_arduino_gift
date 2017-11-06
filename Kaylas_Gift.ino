#define aref_voltage 5.0

int pinA = 2; // Connected to the 7 segments of the display.
int pinB = 3; // Connected to the 7 segments of the display.
int pinC = 4; // Connected to the 7 segments of the display.
int pinD = 5; // Connected to the 7 segments of the display.
int pinE = 6; // Connected to the 7 segments of the display.
int pinF = 7; // Connected to the 7 segments of the display.
int pinG = 8; // Connected to the 7 segments of the display.

int D1 = 9; // Digit Control - Connected to the 7 segments of the display.
int D2 = 10; // Digit Control - Connected to the 7 segments of the display.
int D3 = 11; // Digit Control - Connected to the 7 segments of the display.
int D4 = 12; // Digit Control - Connected to the 7 segments of the display.
int tempPin = 3;

const int _DELAY = 5;
const int _DELAYWORD = 5;
const int _WORDTIME = 60;
const int _SCROLLTIME = 20;
const int _SWIRLDELAY = 50;



// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pins as outputs.
  pinMode(pinA, OUTPUT);     
  pinMode(pinB, OUTPUT);     
  pinMode(pinC, OUTPUT);     
  pinMode(pinD, OUTPUT);     
  pinMode(pinE, OUTPUT);     
  pinMode(pinF, OUTPUT);     
  pinMode(pinG, OUTPUT);   
  pinMode(D1, OUTPUT);  
  pinMode(D2, OUTPUT);  
  pinMode(D3, OUTPUT);  
  pinMode(D4, OUTPUT);
  // Serial.begin(9600); // TODO - Must be uncommented for temperature testing
  animation(); // debug animation (:
  greetings();
}

// the loop routine runs over and over again forever:
void loop() {
  animation(); // debug animation (:
  clearDisplay(); // Initialize Display

// It is
  drawString("It  ",_WORDTIME);
  drawString(" is ",_WORDTIME);

// x
  int reading = analogRead(tempPin); // Get initial voltage from temperature sensor
  float voltage = reading * 5.0; // We are using 5.0 v from the Arduino
  voltage /= 1024.0; // Scale down for sensor
  float temperatureC = (voltage - 0.5) * 100 ; // Celsius Formula
  // Fahrenheit Formula, with 60 being added as a constant because the sensor was off.
  int temperatureF = ((temperatureC * 9.0 / 5.0) + 32.0) + 60; // TODO: Change 60 accordingly
  // Serial.print(temperatureF); // <- Was used for testing to make sure the temperature was correct. 
  drawInt(temperatureF, _WORDTIME*2); // Draw the temperature for a while

// degrees
  drawString("degr",_WORDTIME);
  drawString("ees ",_WORDTIME);
  
  clearDisplay(); // Clear Display

// My Jingle
  
  int totalJingles = 12; // Set bank size of Jingles to be printed
  int jingle = random(totalJingles); // randomly choose jingle id


// jingle = 9;  // TESTING ONLY: Uncomment - for testing

// Begin Jingle
  if(jingle == 0){
    drawString("    ",_WORDTIME);
    drawString("   t",_WORDTIME);
    drawString("  te",_WORDTIME);
    drawString(" tes",_WORDTIME);
    drawString("test",_WORDTIME);
    drawString("est0",_WORDTIME);
    drawString("st0 ",_WORDTIME);
    drawString("t0  ",_WORDTIME);
    drawString("0   ",_WORDTIME);
    drawString("    ",_WORDTIME);
  }
  else if(jingle == 1){
    drawString("    ",_WORDTIME);
    drawString("   j",_WORDTIME);
    drawString("  ji",_WORDTIME);
    drawString(" jin",_WORDTIME);
    drawString("jing",_WORDTIME);
    drawString("ingl",_WORDTIME);
    drawString("ngle",_WORDTIME);
    drawString("gle ",_WORDTIME);
    drawString("le  ",_WORDTIME);
    drawString("e   ",_WORDTIME);
    drawString("    ",_WORDTIME);
  }
  else{
    delay(15*100); // sleep for 15 seconds
  }
}

void clearDisplay(){
  drawString("    ",_WORDTIME);
}

bool drawString(const char word[], int frames){
  if(frames == 0){
    //word[0] = ' ';
    //word[1] = ' ';
    //word[2] = ' ';
    //word[3] = ' ';
    return true;
  }

  if(word[0] != 0){
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH); // PRINT TO THIS DIGIT
    if(!writeChar(word[0]))
      return false;
    delay(_DELAYWORD);
  }

  if(word[1] != 0){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH); // PRINT TO THIS DIGIT
    if(!writeChar(word[1]))
      return false;
    delay(_DELAYWORD);
  }

  if(word[2] != 0){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH); // PRINT TO THIS DIGIT
    if(!writeChar(word[2]))
      return false;
    delay(_DELAYWORD);
  }

  if(word[3] != 0){
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW); // PRINT TO THIS DIGIT
    if(!writeChar(word[3]))
      return false;
    delay(_DELAYWORD);
  }
  drawString(word, frames-1);
  return true;
}

// Number must be from 0-9999
bool drawInt(int number, int frames){
  if(number < 0 || number > 9999){
    return false;
  }

  if(frames == 0){
    return true;
  }
  
  int dig = 0;
  
  if(number >= 0){
    dig = number % 10;
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, LOW); // PRINT TO THIS DIGIT
    if(!writeDig(dig))
      return false;
    delay(_DELAY);
  }
  
  if(number > 10){
    dig = (number/10) % 10;
    digitalWrite(D1, HIGH);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, LOW);
    digitalWrite(D4, HIGH); // PRINT TO THIS DIGIT
    //0
    if(!writeDig(dig))
      return false;
    delay(_DELAY);
  }
  
  if(number > 100){
    dig = (number/100) % 10;
    digitalWrite(D1, HIGH);
    digitalWrite(D2, LOW);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH); // PRINT TO THIS DIGIT
    //0
    if(!writeDig(dig))
      return false;
    delay(_DELAY);
  }
  
  if(number > 1000){
    dig = (number/1000) % 10;
    digitalWrite(D1, LOW);
    digitalWrite(D2, HIGH);
    digitalWrite(D3, HIGH);
    digitalWrite(D4, HIGH); // PRINT TO THIS DIGIT
    //0
    if(!writeDig(dig))
      return false;
    delay(_DELAY);
  }
  drawInt(number, frames-1);
  return true;
}

/*
 * Integer will be written on the 4-digit LED screen
 * returns true if successfully drawn
 * precondition: int x is bounded by 0-9999 inclusively
 * postcondition: an integer will be displayed on the 4-digit LED screen
 */
bool writeDig(int x){
  // Prints 0
  if(x == 0){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW);
  }
  // Prints 1
  else if(x == 1){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }
  // Prints 2
  else if(x == 2){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH);
  }
  // Prints 3
  else if(x == 3){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH);
  }
  // Prints 4
  else if(x == 4){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  // Prints 5
  else if(x == 5){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  // Prints 6
  else if(x == 6){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  // Prints 7
  else if(x == 7){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
  }
  // Prints 8
  else if(x == 8){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  // Prints 9
  else if(x == 9){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  // Prints a blank space on error and returns false
  else{
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
    return false;
  }
  return true;
}

/*
 * Character will be written on the 4-digit LED screen
 * returns true if successfully drawn
 * precondition: char x is 'A'-'Z' and '-'
 * postcondition: a character will be displayed on the 4-digit LED screen
 */
bool writeChar(char x){
  if(x == 'a' || x == 'A'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  else if(x == 'b' || x == 'B'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  else if(x == 'c' || x == 'C'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH);
  }
  else if(x == 'd' || x == 'D'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH);
  }
  else if(x == 'e' || x == 'E'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH);
  }
  else if(x == 'f' || x == 'F'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'g' || x == 'G'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'h' || x == 'H' || x == 'x' || x == 'X'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'i' || x == 'I'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'j' || x == 'J'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'l' || x == 'L'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'n' || x == 'N'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'o' || x == 'O'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'p' || x == 'P'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'q' || x == 'Q'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'r' || x == 'R'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 's' || x == 'S'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 't' || x == 'T'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'u' || x == 'U' || x == 'v' || x == 'V'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'y' || x == 'Y'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'z' || x == 'Z'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH); 
  }
  // Others
  else if(x == '-'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == '?'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == ' ' || x == 0){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'm' || x == 'M'){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW); 
  }
  else if(x == 'k' || x == 'K'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else if(x == 'w' || x == 'W'){
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, HIGH);   
    digitalWrite(pinG, HIGH); 
  }
  else{
    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);   
    digitalWrite(pinG, LOW);
    return false;
  }
  return true;
}

void animation(){
// Digit 1 - swirl
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW); // PRINT TO THIS DIGIT
  swirl();

// Digit 2 - swirl
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW); // PRINT TO THIS DIGIT
  digitalWrite(D4, HIGH); 
  swirl();

// Digit 3 - swirl
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW); // PRINT TO THIS DIGIT
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
  swirl();

// Digit 4 - swirl
  digitalWrite(D1, LOW); // PRINT TO THIS DIGIT
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
  swirl();

// Digit 1 - =
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, LOW); // PRINT TO THIS DIGIT
  equal();

// Digit 2 - =
  digitalWrite(D1, HIGH);
  digitalWrite(D2, HIGH);
  digitalWrite(D3, LOW); // PRINT TO THIS DIGIT
  digitalWrite(D4, HIGH); 
  equal();

// Digit 3 - =
  digitalWrite(D1, HIGH);
  digitalWrite(D2, LOW); // PRINT TO THIS DIGIT
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
  equal();

// Digit 4 - =
  digitalWrite(D1, LOW); // PRINT TO THIS DIGIT
  digitalWrite(D2, HIGH);
  digitalWrite(D3, HIGH);
  digitalWrite(D4, HIGH); 
  equal();
}

void swirl(){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);
    delay(_SWIRLDELAY);

    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, HIGH);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);
    delay(_SWIRLDELAY);

    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, HIGH);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);
    delay(_SWIRLDELAY);

    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);
    delay(_SWIRLDELAY);

    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, HIGH);   
    digitalWrite(pinF, LOW);
    delay(_SWIRLDELAY);

    digitalWrite(pinA, LOW);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, LOW);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, HIGH);
    delay(_SWIRLDELAY);
}

void greetings()
{
  drawString("Gree",_WORDTIME);
  drawString("reet",_SCROLLTIME);
  drawString("eeti",_SCROLLTIME);
  drawString("etin",_SCROLLTIME);
  drawString("ting",_SCROLLTIME);
  drawString("ings",_SCROLLTIME);
  drawString("ngs ",_SCROLLTIME);
  drawString("gs k",_SCROLLTIME);
  drawString("s ka",_SCROLLTIME);
  drawString(" kay",_SCROLLTIME);
  drawString("kayl",_SCROLLTIME);
  drawString("ayla",_SCROLLTIME);
  drawString("yla ",_SCROLLTIME);
}

void equal(){
    digitalWrite(pinA, HIGH);   
    digitalWrite(pinB, LOW);   
    digitalWrite(pinC, LOW);   
    digitalWrite(pinD, HIGH);   
    digitalWrite(pinE, LOW);   
    digitalWrite(pinF, LOW);
    delay(_SWIRLDELAY);
}
