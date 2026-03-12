int xPin = A1;   // joystick horizontal
int yPin = A0;   // joystick vertical

int ledUp = 8;
int ledRight = 9;
int ledDown = 10;
int ledLeft = 11;

int xValue = 0;
int yValue = 0;

// Thresholds based on your current working setup
const int upThreshold = 700;
const int downThreshold = 300;
const int rightThreshold = 300;
const int leftThreshold = 800;

// Centre zone so the joystick must be released before next round
const int centreXLow = 400;
const int centreXHigh = 650;
const int centreYLow = 400;
const int centreYHigh = 650;

enum Direction {
  NONE,
  UP,
  RIGHT,
  DOWN,
  LEFT
};

void setup() {
  pinMode(ledUp, OUTPUT);
  pinMode(ledRight, OUTPUT);
  pinMode(ledDown, OUTPUT);
  pinMode(ledLeft, OUTPUT);

  Serial.begin(9600);
  randomSeed(analogRead(A5)); // randomiser for LED choice

  allLedsOff();

  Serial.println("Reaction Time Game Started!");
  Serial.println("Move the joystick in the SAME direction as the lit LED.");
  Serial.println("Return joystick to centre after each round.");
  Serial.println();
}

void loop() {
  // Wait until joystick is centred before starting a new round
  waitForCentre();

  // Small random delay so the player cannot predict the start
  long waitTime = random(1000, 3001);
  delay(waitTime);

  // Pick a random direction from 1 to 4
  Direction target = (Direction)random(1, 5);

  // Light the correct LED
  lightDirection(target);

  // Start timing
  unsigned long startTime = millis();

  // Wait until the player gives the correct joystick input
  while (true) {
    Direction input = readJoystickDirection();

    if (input == target) {
      unsigned long reactionTime = millis() - startTime;

      allLedsOff();

      Serial.print("LED: ");
      Serial.print(directionToText(target));
      Serial.print(" | Reaction Time: ");
      Serial.print(reactionTime);
      Serial.println(" ms");
      Serial.println();

      break;
    }
  }

  // Wait until joystick returns to centre before next round
  waitForCentre();

  delay(300); // short pause before next round
}

Direction readJoystickDirection() {
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  if (yValue > upThreshold) {
    return UP;
  }
  if (yValue < downThreshold) {
    return DOWN;
  }
  if (xValue < rightThreshold) {
    return RIGHT;
  }
  if (xValue > leftThreshold) {
    return LEFT;
  }

  return NONE;
}

bool isJoystickCentred() {
  xValue = analogRead(xPin);
  yValue = analogRead(yPin);

  return (xValue >= centreXLow && xValue <= centreXHigh &&
          yValue >= centreYLow && yValue <= centreYHigh);
}

void waitForCentre() {
  while (!isJoystickCentred()) {
    allLedsOff();
  }
}

void lightDirection(Direction dir) {
  allLedsOff();

  if (dir == UP) {
    digitalWrite(ledUp, HIGH);
  } else if (dir == RIGHT) {
    digitalWrite(ledRight, HIGH);
  } else if (dir == DOWN) {
    digitalWrite(ledDown, HIGH);
  } else if (dir == LEFT) {
    digitalWrite(ledLeft, HIGH);
  }
}

void allLedsOff() {
  digitalWrite(ledUp, LOW);
  digitalWrite(ledRight, LOW);
  digitalWrite(ledDown, LOW);
  digitalWrite(ledLeft, LOW);
}

const char* directionToText(Direction dir) {
  if (dir == UP) return "UP";
  if (dir == RIGHT) return "RIGHT";
  if (dir == DOWN) return "DOWN";
  if (dir == LEFT) return "LEFT";
  return "NONE";
}