// C++ code
//
#include <LiquidCrystal.h>

int buttonPin = 2;      // Pino conectado ao botão
int ledPin = 13;        // Pino conectado ao LED
int buzzerPin = 8;      // Pino conectado ao buzzer
int buttonState = HIGH;       // Estado atual do botão
int lastButtonState = HIGH;   // Estado anterior do botão
unsigned long lastDebounceTime = 0;  // Último tempo de debounce
unsigned long debounceDelay = 10;    // Tempo de debounce em milissegundos
unsigned long tempoluzled = 1000;
unsigned long luzapagaacende = 0;
bool sirenActive = false;     // Sirene ativada ou não
bool displayActive = false;   // Display ativado ou não

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

void setup() {
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buttonPin, HIGH);

  // Desliga o LED e o buzzer no início
  digitalWrite(ledPin, LOW);
  digitalWrite(buzzerPin, LOW);
  lcd.begin(16, 2);
  lcd.clear();
  
}

void loop() {
  int reading = digitalRead(buttonPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonState) {
      buttonState = reading;

      if (buttonState == LOW) {
        // Botão foi pressionado
        sirenActive = !sirenActive;  // Inverte o estado da sirene

        if (sirenActive) {
          // Ativa a sirene
          digitalWrite(ledPin, HIGH);
          tone(buzzerPin, 1000);  // Primeira frequência
           // Ativa o display se a sirene estiver ativada
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Emergencia!!");
          displayActive = true;
        } else {
          // Desativa a sirene
          digitalWrite(ledPin, LOW);
          noTone(buzzerPin);
          lcd.clear();
          displayActive = false;
        }
      }
    }
  }

  lastButtonState = reading;
}