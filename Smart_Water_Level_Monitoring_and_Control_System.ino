#define RELAY_ACTIVE_HIGH 1 // if active high relay = 1. Otherwise = 0

const float TANK_HEIGHT = 30.0;

const int LED_25 = 2;
const int LED_50 = 3;
const int LED_75 = 4;
const int LED_100 = 5;

const int BUZZER = 6;
const int ALERT_LED = 7;
const int TRIG = 8;
const int ECHO = 9;
const int PUMP = 10;

float duration;
float distance;
float waterLevel;
float percentage;

void pumpON()
{
#if RELAY_ACTIVE_HIGH
  digitalWrite(PUMP, HIGH);
#else
  digitalWrite(PUMP, LOW);
#endif
}

void pumpOFF()
{
#if RELAY_ACTIVE_HIGH
  digitalWrite(PUMP, LOW);
#else
  digitalWrite(PUMP, HIGH);
#endif
}

void setup()
{
  pinMode(LED_25, OUTPUT);
  pinMode(LED_50, OUTPUT);
  pinMode(LED_75, OUTPUT);
  pinMode(LED_100, OUTPUT);

  pinMode(BUZZER, OUTPUT);
  pinMode(ALERT_LED, OUTPUT);

  pinMode(TRIG, OUTPUT);
  pinMode(ECHO, INPUT);

  pinMode(PUMP, OUTPUT);

  Serial.begin(9600);

  digitalWrite(LED_25, LOW);
  digitalWrite(LED_50, LOW);
  digitalWrite(LED_75, LOW);
  digitalWrite(LED_100, LOW);

  digitalWrite(BUZZER, LOW);
  digitalWrite(ALERT_LED, LOW);

  pumpOFF();
}

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(2);

  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);

  digitalWrite(TRIG, LOW);

  duration = pulseIn(ECHO, HIGH, 30000);

  if (duration == 0)
  {
    pumpOFF();
    return;
  }

  distance = duration / 58.82;

  waterLevel = TANK_HEIGHT - distance;

  if (waterLevel < 0)
    waterLevel = 0;

  if (waterLevel > TANK_HEIGHT)
    waterLevel = TANK_HEIGHT;

  percentage = (waterLevel / TANK_HEIGHT) * 100.0;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm | Water Level: ");
  Serial.print(waterLevel);
  Serial.print(" cm | Level: ");
  Serial.print(percentage);
  Serial.println("%");

  digitalWrite(LED_25, LOW);
  digitalWrite(LED_50, LOW);
  digitalWrite(LED_75, LOW);
  digitalWrite(LED_100, LOW);
  digitalWrite(ALERT_LED, LOW);
  digitalWrite(BUZZER, LOW);

  if (percentage > 0 && percentage < 25)
  {
    digitalWrite(LED_25, HIGH);
    pumpON();
  }

  else if (percentage >= 25 && percentage < 50)
  {
    digitalWrite(LED_25, HIGH);
    digitalWrite(LED_50, HIGH);
    pumpON();
  }

  else if (percentage >= 50 && percentage < 75)
  {
    digitalWrite(LED_25, HIGH);
    digitalWrite(LED_50, HIGH);
    digitalWrite(LED_75, HIGH);
    pumpOFF();
  }

  else if (percentage >= 75 && percentage < 100)
  {
    digitalWrite(LED_25, HIGH);
    digitalWrite(LED_50, HIGH);
    digitalWrite(LED_75, HIGH);
    digitalWrite(LED_100, HIGH);
    pumpOFF();
  }

  else if (percentage >= 100)
  {
    digitalWrite(LED_25, HIGH);
    digitalWrite(LED_50, HIGH);
    digitalWrite(LED_75, HIGH);
    digitalWrite(LED_100, HIGH);

    pumpOFF();

    digitalWrite(ALERT_LED, HIGH);
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);
  }

  else
  {
    pumpON();
  }

  delay(500);
}
