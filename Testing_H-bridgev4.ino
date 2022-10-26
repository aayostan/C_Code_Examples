const int D1 = 8;
const int D2 = 9;
const int D3 = 10;

String dir    = "No Dir";
bool off      = true;
bool on       = false;

void setup() {
  Serial.begin(9600);
  pinMode(D1, OUTPUT);
  pinMode(D2, OUTPUT);
  pinMode(D3, OUTPUT);
  digitalWrite(D3, LOW);
}

void loop() {
  if (on) {
    digitalWrite(D3, HIGH);
    if (dir == "up") {
      digitalWrite(D1, LOW);
      digitalWrite(D2, HIGH); 
    } else {
      digitalWrite(D2, LOW);
      digitalWrite(D1, HIGH); 
    }
    Serial.println(dir);
    delay(50);
    digitalWrite(D3, LOW);
  }


  if (off) {
    digitalWrite(D3, LOW);
    digitalWrite(D1, LOW);
    digitalWrite(D2, LOW);
    Serial.println("off");
  }
  
  delay(1000);
}


/* 
 * Occurs each time there is some-
 * thing in the serial read buffer 
 */
void serialEvent() 
{
  
  char byteIn = Serial.read();
  
  switch(byteIn) {
    case '0':
      off   = true;
      on    = false;
      break;
    
    case '1':
      off   = false;
      on    = true;
      break;
    
    case 'u':
      dir   = "up";
      off   = true;
      on    = false;
      break;
      
    case 'd':
      dir   = "down";
      off   = true;
      on    = false;
      break;
      
    default:
      break;
  }
  
}
