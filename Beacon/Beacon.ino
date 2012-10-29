const int gerkonPin = 10;
int pins[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
int length = 9;
int defaultCurrentPos = 6;
int currentPos = 5;
int defaultDelayTime = 1000;
int delayTime = defaultDelayTime;
int gerkonState = 0; 
int prevGerkonState = 0;
int minDelayTime = 10;
int maxDelayTime = 10000;
int sectorRate = 8;
unsigned long lastStartTime = 0;
unsigned long prevMillis = 0;

void setup() {
  for (int i = 0; i < length; i = i + 1)
    pinMode(pins[i], OUTPUT);
  pinMode(gerkonPin, INPUT);
}

void loop() {
  unsigned long currentMillis = millis();
  gerkonState = digitalRead(gerkonPin);
  
  if(gerkonState == HIGH && prevGerkonState == LOW)
  {
    currentPos = defaultCurrentPos;
    if(lastStartTime != 0)
    {
      long dTime = (currentMillis - lastStartTime) / sectorRate;
      if(dTime < minDelayTime)
        goto out;
      delayTime = dTime;
    }
    lastStartTime = currentMillis;
  }
  prevGerkonState = gerkonState;
  if((currentMillis - lastStartTime) > maxDelayTime)
  {
    clearAll();
    delayTime = defaultDelayTime;
    return;
  }
  out:
  goWave(delayTime, currentMillis);
}

void goWave(long delayTime, long currentMillis)
{
  if(currentMillis - prevMillis > delayTime) {
    prevMillis = currentMillis;
    clearAll();
    digitalWrite(pins[currentPos], HIGH);
    currentPos = getPos(currentPos + 1);
    digitalWrite(pins[currentPos], HIGH);    
  }
}

void clearAll()
{
  for (int i = 0; i < length; i = i + 1)
    digitalWrite(pins[i], LOW);
}

int getPos(int pos)
{
  if(pos > length - 1)
    pos =  pos - length;
  return pos;
}
