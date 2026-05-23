#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10  
#define RST_PIN 9  

#define LED_AMARELO 5     // Pino do Arduino para o LED de acesso
#define LED_VERDE 6  // Pino do Arduino para o LED de acesso autorizado
#define LED_VERMELHO 7 // Pino do Arduino para o LED de acesso negado

#define RELE_PIN 4

MFRC522 mfrc522(SS_PIN, RST_PIN); 

// Números de série dos cartões autorizados
String cartaoAutorizado1 = "90cb9512";
String cartaoAutorizado2 = "7e443143";

void setup() {
  Serial.begin(9600);  // Inicializa a comunicação serial
  SPI.begin();         // Inicializa a comunicação SPI
  mfrc522.PCD_Init();  // Inicializa o leitor RFID

  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(RELE_PIN, OUTPUT);

  digitalWrite(RELE_PIN, HIGH);

  digitalWrite(LED_AMARELO, HIGH);

  Serial.println("Aproxime o seu cartão RFID para autenticação...");
  Serial.println();
}

void loop() {
  // Verifica se um novo cartão RFID está presente
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Lê o número de série do cartão RFID
    String cardSerial = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      cardSerial.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : ""));
      cardSerial.concat(String(mfrc522.uid.uidByte[i], HEX));
    }
    Serial.print("Número de série do cartão: ");
    Serial.println(cardSerial);

    // Verifica se o cartão é válido
    if (cardSerial == cartaoAutorizado1 || cardSerial == cartaoAutorizado2) {
      Serial.println("Acesso permitido!");
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERDE, HIGH);
      digitalWrite(LED_VERMELHO, LOW);
      digitalWrite(RELE_PIN, LOW);
      delay(1000);
      // Realiza as ações necessárias para o acesso permitido

    } else {
      Serial.println("Acesso negado!");
      digitalWrite(LED_AMARELO, LOW);
      digitalWrite(LED_VERDE, LOW);
      digitalWrite(LED_VERMELHO, HIGH);
      delay(4000);
      // Realiza as ações necessárias para o acesso negado
    }

    // Aguarda um breve período antes de desligar os LEDs
    digitalWrite(RELE_PIN, HIGH);
    digitalWrite(LED_AMARELO, HIGH);
    digitalWrite(LED_VERDE, LOW);
    digitalWrite(LED_VERMELHO, LOW);

    // Finaliza a leitura do cartão atual
    mfrc522.PICC_HaltA();
  }
}
