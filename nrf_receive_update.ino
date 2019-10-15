#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(9, 10); // CE, CSN
const byte address[6] = "00001";
int LEDPin = A4;
boolean switch1 = 0;

void setup() {
  Serial.begin(9600);
  pinMode(LEDPin, OUTPUT);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if (radio.available()) {
    char text[32] = "";
    radio.read(&text, sizeof(text));
    radio.read(&switch1, sizeof(switch1));

    if (switch1 == 1) {
      digitalWrite(LEDPin, HIGH);
      Serial.println(text);

    }

    else {
      digitalWrite(LEDPin, LOW);
    }
  }
  else {
    Serial.println("no");
  }
  delay(5);
}
