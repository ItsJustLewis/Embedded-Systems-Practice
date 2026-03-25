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
const int yellowLed = 11;

// PIN system
String correctPin = "";
String enteredPin = "";
bool passwordSet = false;
bool setMode = false;

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
  pinMode(yellowLed, OUTPUT);

  digitalWrite(greenLed, LOW);
  digitalWrite(redLed, LOW);
  digitalWrite(yellowLed, LOW);

  Serial.println("Keypad PIN System Ready");
  Serial.println("Press A to set a new 4-digit password");
}

void loop() {
  char key = getKey();

  if (key != '\0') {
    Serial.print("Key: ");
    Serial.println(key);

    // Enter password set mode
    if (key == 'A') {
      enteredPin = "";
      setMode = true;
      Serial.println("SET MODE: Enter new 4-digit password, then press #");
      return;
    }

    // Clear current input
    if (key == '*') {
      enteredPin = "";
      Serial.println("Cleared");
      return;
    }

    // Submit
    if (key == '#') {
      if (setMode) {
        saveNewPassword();
      } else {
        checkPin();
      }
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
      } else {
        Serial.println("Maximum 4 digits only");
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

  // Only register once per press-release cycle
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

// Save new password
void saveNewPassword() {
  if (enteredPin.length() == 4) {
    correctPin = enteredPin;
    passwordSet = true;
    setMode = false;

    digitalWrite(yellowLed, HIGH);

    Serial.print("New password set: ");
    Serial.println(correctPin);
    Serial.println("Yellow LED ON - password stored");
  } else {
    Serial.println("Password must be exactly 4 digits");
    flashRed(2, 150);
  }

  enteredPin = "";
}

// Check entered PIN
void checkPin() {
  if (!passwordSet) {
    Serial.println("No password set yet. Press A to create one.");
    flashRed(2, 150);
    enteredPin = "";
    return;
  }

  if (enteredPin == correctPin) {
    Serial.println("Access Granted");
    digitalWrite(greenLed, HIGH);
    delay(1000);
    digitalWrite(greenLed, LOW);
  } else {
    Serial.println("Access Denied");
    flashRed(3, 200);
  }

  enteredPin = "";
}

// Flash red LED
void flashRed(int times, int delayTime) {
  for (int i = 0; i < times; i++) {
    digitalWrite(redLed, HIGH);
    delay(delayTime);
    digitalWrite(redLed, LOW);
    delay(delayTime);
  }
}