// הגדרת פינים של תצוגת שבעה מקטעים
int segA = 2;
int segB = 3;
int segC = 4;
int segD = 5;
int segE = 6;
int segF = 7;
int segG = 8;
int segP = 9; // נקודה עשרונית

// הגדרת פינים עבור ספרות התצוגה
int digit1 = 10;
int digit2 = 11;
int digit3 = 12;
int digit4 = 13;

// הגדרת פינים לפוטנציומטרים
int pot1Pin = A0; // פוטנציומטר לשליטה ב-x
int pot2Pin = A1; // פוטנציומטר לשליטה ב-y

// הגדרת פין הזמזם
int buzzerPin = A2; // זמזם מחובר ל-A2

void setup() {
  // הגדרת פינים של תצוגת שבעה מקטעים כמוצאים
  pinMode(segA, OUTPUT);
  pinMode(segB, OUTPUT);
  pinMode(segC, OUTPUT);
  pinMode(segD, OUTPUT);
  pinMode(segE, OUTPUT);
  pinMode(segF, OUTPUT);
  pinMode(segG, OUTPUT);
  pinMode(segP, OUTPUT);

  // הגדרת פינים של הספרות כמוצאים
  pinMode(digit1, OUTPUT);
  pinMode(digit2, OUTPUT);
  pinMode(digit3, OUTPUT);
  pinMode(digit4, OUTPUT);

  // הגדרת פין הזמזם כמוצא
  pinMode(buzzerPin, OUTPUT);

  // פתיחת Serial Monitor
  Serial.begin(9600);
}

// פונקציה לכיבוי כל המקטעים
void clearSegments() {
  digitalWrite(segA, LOW);
  digitalWrite(segB, LOW);
  digitalWrite(segC, LOW);
  digitalWrite(segD, LOW);
  digitalWrite(segE, LOW);
  digitalWrite(segF, LOW);
  digitalWrite(segG, LOW);
  digitalWrite(segP, LOW);
}

// פונקציה להצגת מספר על ספרה בתצוגת שבעה מקטעים
void displayNumber(int digit, int number, bool showDot = false) {
  clearSegments();

  // כיבוי כל הספרות
  digitalWrite(digit1, LOW);
  digitalWrite(digit2, LOW);
  digitalWrite(digit3, LOW);
  digitalWrite(digit4, LOW);

  // הדלקת המקטעים עבור המספר הנדרש
  switch (number) {
    case 0: digitalWrite(segA, HIGH); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, HIGH); digitalWrite(segE, HIGH); digitalWrite(segF, HIGH); digitalWrite(segG, LOW); break;
    case 1: digitalWrite(segA, LOW); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, LOW); digitalWrite(segE, LOW); digitalWrite(segF, LOW); digitalWrite(segG, LOW); break;
    case 2: digitalWrite(segA, HIGH); digitalWrite(segB, HIGH); digitalWrite(segC, LOW); digitalWrite(segD, HIGH); digitalWrite(segE, HIGH); digitalWrite(segF, LOW); digitalWrite(segG, HIGH); break;
    case 3: digitalWrite(segA, HIGH); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, HIGH); digitalWrite(segE, LOW); digitalWrite(segF, LOW); digitalWrite(segG, HIGH); break;
    case 4: digitalWrite(segA, LOW); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, LOW); digitalWrite(segE, LOW); digitalWrite(segF, HIGH); digitalWrite(segG, HIGH); break;
    case 5: digitalWrite(segA, HIGH); digitalWrite(segB, LOW); digitalWrite(segC, HIGH); digitalWrite(segD, HIGH); digitalWrite(segE, LOW); digitalWrite(segF, HIGH); digitalWrite(segG, HIGH); break;
    case 6: digitalWrite(segA, HIGH); digitalWrite(segB, LOW); digitalWrite(segC, HIGH); digitalWrite(segD, HIGH); digitalWrite(segE, HIGH); digitalWrite(segF, HIGH); digitalWrite(segG, HIGH); break;
    case 7: digitalWrite(segA, HIGH); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, LOW); digitalWrite(segE, LOW); digitalWrite(segF, LOW); digitalWrite(segG, LOW); break;
    case 8: digitalWrite(segA, HIGH); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, HIGH); digitalWrite(segE, HIGH); digitalWrite(segF, HIGH); digitalWrite(segG, HIGH); break;
    case 9: digitalWrite(segA, HIGH); digitalWrite(segB, HIGH); digitalWrite(segC, HIGH); digitalWrite(segD, HIGH); digitalWrite(segE, LOW); digitalWrite(segF, HIGH); digitalWrite(segG, HIGH); break;
  }

  // הפעלת הספרה הנכונה
  //if (digit == 1) digitalWrite(digit1, HIGH);
  //if (digit == 2) digitalWrite(digit2, HIGH);
  //if (digit == 3) digitalWrite(digit3, HIGH);
  //if (digit == 4) digitalWrite(digit4, HIGH);

  // הצגת נקודה עשרונית אם נדרש
  if (showDot) {
    digitalWrite(segP, HIGH);
  }
}

// פונקציה להשמעת צליל בזמזם לפי ערך
void playBuzzer(int y) {
  if (y % 2 == 0) {
    tone(buzzerPin, 1000, 200); // תדר 1000Hz למשך 200ms
  } else {
    tone(buzzerPin, 500, 200); // תדר 500Hz למשך 200ms
  }
  delay(250);
}

void loop() {
  // קריאה מהפוטנציומטרים
  int x = map(analogRead(pot1Pin), 0, 1023, 40, 240); // ממפה ערך הפוטנציומטר ל-x
  int y = map(analogRead(pot2Pin), 0, 1023, 0, 9);    // ממפה ערך הפוטנציומטר ל-y

  // הדפסה ל-Serial Monitor
  Serial.print("X: ");
  Serial.print(x);
  Serial.print(" | Y: ");
  Serial.println(y);

  // הצגת ערכי X ו-Y בצורה X.Y
 // displayNumber(1, x / 100);         // מאות של X
  //delay(5);
  //displayNumber(2, (x / 10) % 10, true);  // עשרות של X עם נקודה עשרונית
  //delay(5);
  //displayNumber(3, x % 10);         // אחדות של X
  //delay(5);
  displayNumber(4, y);              // הצגת Y
  delay(5);

  // השמעת צליל בזמזם לפי ערך y
  playBuzzer(y);
}