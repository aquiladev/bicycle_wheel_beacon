const int gerkonPin = 10;

int length = 9;
int pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int currentPos = 5;
int delayTime = 1000;
int gerkonState = 0; 
int prevGerkonState = 0;
unsigned long lastStartTime = 0;
unsigned long prevMillis = 0;

void setup() {
  for (int i = 0; i < length; i = i + 1) {
    pinMode(pins[i], OUTPUT);
  }  
  pinMode(gerkonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  gerkonState = digitalRead(gerkonPin);
  
  if(gerkonState == HIGH && prevGerkonState == LOW)
  {
    reset();
    if(lastStartTime != 0)
    {
      long dTime = (currentMillis - lastStartTime) / 8;
      if(dTime < 10)
        goto out;
      delayTime = dTime;
    }
    lastStartTime = currentMillis;
  }
  prevGerkonState = gerkonState;
  out:
  goWave(delayTime, currentMillis);
}

void reset()
{
  currentPos = 6;
}

void goWave(long delayTime, long currentMillis)
{
  if(currentMillis - prevMillis > delayTime) {
  
    prevMillis = currentMillis;
    if(currentPos > length - 1)
    {
      currentPos = 0;
    }
    
    clearAll();
    digitalWrite(pins[currentPos], HIGH);
    digitalWrite(pins[getPos(currentPos + 1) ], HIGH);
    
    currentPos = currentPos + 1;
  }
}

void clearAll()
{
  for (int i = 0; i < length; i = i + 1) {
    digitalWrite(pins[i], LOW);
  } 
}

int getPos(int pos)
{
  if(pos > length - 1)
  {
    return pos - length;
  }
  
  return pos;
}
