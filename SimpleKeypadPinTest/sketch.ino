// Keypad size
const int ROWS = 4;
const int COLS = 4;

// Key layout
char keys[ROWS][COLS] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};

// Pin connections
int rowPins[ROWS] = {9, 8, 7, 6};
int colPins[COLS] = {5, 4, 3, 2};

// LEDs
const int greenLed = 13;
const int redLed = 12;

// PIN system
String correctPin = "4343";
String enteredPin = "";

// Key press tracking
bool keyReleased = true;

void setup() {
  Serial.begin(9600);

  // Setup rows as OUTPUT
  for (int i = 0; i < ROWS; i++) {
    pinMode(rowPins[i], OUTPUT);
    digitalWrite(rowPins[i], HIGH);
  }

  // Setup columns as INPUT_PULLUP
  for (int i = 0; i < COLS; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }

  pinMode(greenLed, OUTPUT);
  pinMode(redLed, OUTPUT);

  Serial.println("Manual Keypad PIN System Ready");
}

void loop() {
  char key = getKey();

  if (key != '\0') {
    Serial.print("Key: ");
    Serial.println(key);

    // Clear
    if (key == '*') {
      enteredPin = "";
      Serial.println("Cleared");
      return;
    }

    // Submit
    if (key == '#') {
      checkPin();
      return;
    }

    // Numbers only
    if (key >= '0' && key <= '9') {
      if (enteredPin.length() < 4) {
        enteredPin += key;

        Serial.print("Entered: ");
        for (int i = 0; i < enteredPin.length(); i++) {
          Serial.print("*");
        }
        Serial.println();
      }

      if (enteredPin.length() == 4) {
        checkPin();
      }
    }
  }
}

// Scan keypad manually
char getKey() {
  char detectedKey = '\0';

  for (int row = 0; row < ROWS; row++) {
    digitalWrite(rowPins[row], LOW);

    for (int col = 0; col < COLS; col++) {
      if (digitalRead(colPins[col]) == LOW) {
        detectedKey = keys[row][col];
      }
    }

    digitalWrite(rowPins[row], HIGH);
  }

  // Only register once per full press-release cycle
  if (detectedKey != '\0' && keyReleased) {
    keyReleased = false;
    return detectedKey;
  }

  // Reset when no key is pressed
  if (detectedKey == '\0') {
    keyReleased = true;
  }

  return '\0';
}

// Check PIN
void checkPin() {
  if (enteredPin == correctPin) {
    Serial.println("Access Granted");
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(greenLed, LOW);
  } else {
    Serial.println("Access Denied");
    for (int i = 0; i < 3; i++) {
      digitalWrite(redLed, HIGH);
      delay(200);
      digitalWrite(redLed, LOW);
      delay(200);
    }
  }

  enteredPin = "";
}
