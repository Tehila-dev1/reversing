#include <SevSeg.h>

// יצירת אובייקט לתצוגת 7-סגמנטים
SevSeg sevseg;

// הגדרות פינים
const int buzzerPin = A2;
const int potXPin = A0;
const int potYPin = A1;

// משתנים
int x = 40; // קצב נקישות בדקה (BPM), יתחיל ב-40
int y = 0;  // אורך הרצף, יתחיל ב-0
unsigned long lastUpdateTime = 0;
unsigned long lastBeatTime = 0;
const unsigned long updateInterval = 200; // מרענן תצוגה כל 200ms כדי לא לשדר יותר מדי מהר

void setup() {
  // הגדרת תצוגת 7-סגמנטים
  byte numDigits = 4;
  byte digitPins[] = {13, 12, 11, 10};
  byte segmentPins[] = {2, 3, 4, 5, 6, 7, 8, 9};
  bool resistorsOnSegments = true; // נגדים מחוברים לסגמנטים
  byte hardwareConfig = COMMON_CATHODE;
  bool updateWithDelays = false;
  bool leadingZeros = false;

  sevseg.begin(hardwareConfig, numDigits, digitPins, segmentPins, resistorsOnSegments, updateWithDelays, leadingZeros);
  sevseg.setBrightness(90);

  // הגדרות פינים
  pinMode(buzzerPin, OUTPUT);

  // הגדרת תקשורת סדרתית לבדיקה
  Serial.begin(9600);
}

void loop() {
  unsigned long currentTime = millis();

  // קריאה מהפוטנציומטרים
  x = map(analogRead(potXPin), 0, 1023, 40, 240); // ממפה ערכי פוטנציומטר ל-X
  y = map(analogRead(potYPin), 0, 1023, 0, 9);    // ממפה ערכי פוטנציומטר ל-Y

  // הצגת הערכים בתצוגת 7-סגמנטים
  sevseg.refreshDisplay(); // רענון תצוגה

  if (currentTime - lastUpdateTime >= updateInterval) {
    lastUpdateTime = currentTime;

    // יצירת מחרוזת עבור התצוגה - ערך X (שלוש ספרות) ואז נקודה ו-Y
    char displayValue[5];
    sprintf(displayValue, "%3d.%1d", x, y); // מייצר מחרוזת "X.Y"
    sevseg.setChars(displayValue);

    // הדפסה לבדיקה ב-Serial Monitor
    Serial.print("X (BPM): ");
    Serial.print(x);
    Serial.print(" | Y (Sequence Length): ");
    Serial.println(y);
  }

  // ניהול הבאזר לפי הקצב והרצף
  int beatInterval = 60000 / x; // חישוב משך הזמן בין נקישות (ms)
  static int beatIndex = 0;

  if (currentTime - lastBeatTime >= beatInterval) {
    lastBeatTime = currentTime;

    // השמעת צליל
    if (beatIndex == 0) {
      tone(buzzerPin, 1000, 100); // נקישה ראשונה בתדר גבוה יותר
    } else {
      tone(buzzerPin, 800, 100);  // נקישות אחרות בתדר נמוך יותר
    }

    // עדכון אינדקס הנקישות ברצף
    beatIndex = (beatIndex + 1) % (y + 1);
  }
}
