#define TRIG_PIN 9
#define ECHO_PIN 10
#define GREEN_LED 4
#define YELLOW_LED 5
#define RED_LED 6
#define BUZZER_PIN 3

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  long duration;
  float distance;

  // שליחת פולס לחיישן
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // קריאת זמן החזרת האות
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.034) / 2; // חישוב המרחק בס"מ

  // הדפסת המרחק לסיריאל
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // איפוס לדים
  digitalWrite(GREEN_LED, LOW);
  digitalWrite(YELLOW_LED, LOW);
  digitalWrite(RED_LED, LOW);
  digitalWrite(BUZZER_PIN, LOW); // אפס את הבזזר

  // אם המרחק יותר מ-50 ס"מ, זה סימן למרחק בטוח אז נדלק נורה ירוקה
  if (distance > 50) {
    digitalWrite(GREEN_LED, HIGH);  // מרחק בטוח -> ירוק
  } 
  // אם המרחק בין 20 ל-50 ס"מ, נדלק נורה צהובה
  else if (distance > 20 && distance <= 50) {
    digitalWrite(YELLOW_LED, HIGH); // מרחק ביניים -> צהוב
  } 
  // אם המרחק פחות מ-20 ס"מ, זה סימן למרחק מסוכן אז נדלק נורה אדומה והבזזר יצפצף
  else if (distance <= 20) {
    digitalWrite(RED_LED, HIGH);  // מרחק מסוכן -> אדום
    tone(BUZZER_PIN, 500,500);  // צליל התראה
  }


  delay(200);
}
