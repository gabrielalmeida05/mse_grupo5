const int LEDPINS[] {2, 3, 4, 5, 6, 7, 8, 9};
#define BUTTONPIN  10
#define POTPIN  A0

bool estadobutao = false;
bool ultimoestado = false;
bool direcaoled = true;
unsigned long previousMillis = 0;
int potValue = 0;
int proxled = 0;
int delayTime = 0;

void setup() {
  pinMode(BUTTONPIN, INPUT_PULLUP);
  for (int i = 0; i < 8; i++) {
    pinMode(LEDPINS[i], OUTPUT);
  }
}

void loop() {
  // lê o estado atual do botão
  estadobutao = digitalRead(BUTTONPIN);

  // verifica se houve mudança no estado do botão
  if (estadobutao != ultimoestado) {
    if (estadobutao == LOW) {
      // inverte o sentido da sequência dos LEDs
      direcaoled = !direcaoled;
    }
    ultimoestado = estadobutao;
  }

  // lê o valor do potenciômetro
  potValue = analogRead(POTPIN);

  // altera o valor do potenciômetro para o intervalo de delay (50ms a 3s)
  delayTime = map(potValue, 0, 1023, 50, 1450);

  // verifica se deve mudar para o próximo LED
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= delayTime) {
    previousMillis = currentMillis;

    // apaga o LED atual
    digitalWrite(LEDPINS[proxled], LOW);

    // vê qual é o próximo LED na sequência
    if (direcaoled) {
      proxled = (proxled + 1) % 8;
    } else {
      proxled = (proxled + 7) % 8;
    }

    // acende o próximo LED
    digitalWrite(LEDPINS[proxled], HIGH);
  }
}
