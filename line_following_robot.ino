// ============================
// TB6612 Pins
// ============================

#define PWMA 25
#define AIN1 26
#define AIN2 27

#define PWMB 14
#define BIN1 12
#define BIN2 13

#define STBY 33

// ============================
// Sensor Pins
// ============================

int sensorPins[8] = {4, 5, 18, 19, 21, 22, 23, 32};

int weights[8] = {-7, -5, -3, -1, 1, 3, 5, 7};

// ============================
// PD Variables
// ============================

float Kp = 20;
float Kd = 30;

int baseSpeed = 150;

int error = 0;
int previousError = 0;

// ============================
// Setup
// ============================

void setup()
{
  Serial.begin(115200);

  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);

  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);

  pinMode(STBY, OUTPUT);

  digitalWrite(STBY, HIGH);

  ledcAttach(PWMA, 1000, 8);
  ledcAttach(PWMB, 1000, 8);

  for (int i = 0; i < 8; i++)
  {
    pinMode(sensorPins[i], INPUT);
  }
}

// ============================
// Error Calculation
// ============================

int calculateError()
{
  int sum = 0;
  int activeSensors = 0;

  for (int i = 0; i < 8; i++)
  {
    if (digitalRead(sensorPins[i]) == 1)   // BLACK = 1
    {
      sum += weights[i];
      activeSensors++;
    }
  }

  if (activeSensors == 0)
  {
    return previousError;
  }

  return sum / activeSensors;
}

// ============================
// Motor Function
// ============================

void drive(int leftSpeed, int rightSpeed)
{
  digitalWrite(AIN1, HIGH);
  digitalWrite(AIN2, LOW);

  digitalWrite(BIN1, HIGH);
  digitalWrite(BIN2, LOW);

  leftSpeed = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  ledcWrite(PWMA, leftSpeed);
  ledcWrite(PWMB, rightSpeed);
}

// ============================
// Main Loop
// ============================

void loop()
{
  error = calculateError();

  float P = Kp * error;

  float D = Kd * (error - previousError);

  float correction = P + D;

  previousError = error;

  int leftSpeed  = baseSpeed - correction;
  int rightSpeed = baseSpeed + correction;

  leftSpeed  = constrain(leftSpeed, 0, 255);
  rightSpeed = constrain(rightSpeed, 0, 255);

  drive(rightSpeed, leftSpeed);

  Serial.print("Error: ");
  Serial.print(error);

  Serial.print("  Left: ");
  Serial.print(leftSpeed);

  Serial.print("  Right: ");
  Serial.println(rightSpeed);

  delay(5);
}