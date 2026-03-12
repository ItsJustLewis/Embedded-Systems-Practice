int xPin = A1;   // joystick horizontal
int yPin = A0;   // joystick vertical

int ledUp = 8;
int ledRight = 9;
int ledDown = 10;
int ledLeft = 11;

int xValue = 0;
int yValue = 0;

void setup() {
  pinMode(ledUp, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledDown, OUTPUT);
  pinMode(ledLeft, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  Serial.print("X: ");
  Serial.print(xValue);
  Serial.print(" | Y: ");
  Serial.println(yValue);

  // Turn all LEDs off first
  digitalWrite(ledUp, LOW);
  digitalWrite(ledRight, LOW);
  digitalWrite(ledDown, LOW);
  digitalWrite(ledLeft, LOW);

  // Up
  if (yValue < 300) {
    digitalWrite(ledUp, HIGH);
  }

  // Down
  if (yValue > 700) {
    digitalWrite(ledDown, HIGH);
  }

  // Right
  if (xValue > 700) {
    digitalWrite(ledRight, HIGH);
  }

  // Left
  if (xValue < 300) {
    digitalWrite(ledLeft, HIGH);
  }

  delay(50);
}
