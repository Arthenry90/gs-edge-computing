#define PIN_TRIG 7
#define PIN_ECHO 6
#define PIN_BUZZER 1

void setup() {
  Serial.begin(115200);
  pinMode(PIN_TRIG, OUTPUT);
  pinMode(PIN_ECHO, INPUT);
  pinMode(PIN_BUZZER, OUTPUT);
}

void loop() {

  // Envia pulso para iniciar leitura do sensor ultrassônico
  digitalWrite(PIN_TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(PIN_TRIG, HIGH);
  delayMicroseconds(15);
  digitalWrite(PIN_TRIG, LOW);

  // Mede o tempo de resposta do eco
  long duration = pulseIn(PIN_ECHO, HIGH);

  // Converte o tempo em distância
  int distance = duration / 58;

  // Mostra no monitor serial
  Serial.print("Distância: ");
  Serial.print(distance);
  Serial.println(" cm");



  // Se a distância for menor que 10 cm, simula envio de POST
  if (distance < 10) {

    Serial.println("\n----- SIMULAÇÃO HTTP POST -----");
    delay(300);

    Serial.println("POST /api/acidente HTTP/1.1");
    delay(200);

    Serial.println("Host: servidor.com");
    delay(200);

    Serial.println("Content-Type: application/json");
    delay(200);

    Serial.println("Content-Length: 52");
    delay(300);

    Serial.println();
    Serial.println("{");
    delay(200);

    Serial.println("  \"alerta\": \"Possivel acidente detectado\",");
    delay(300);

    Serial.println("  \"sensor\": \"ultrassom\"");
    delay(200);

    Serial.println("}");
    delay(300);

    Serial.println("ERRO: Sem conexão – requisição não enviada");
    Serial.println("--------------------------------\n");

    // Delay maior entre alertas simulados
    delay(2500);
  }

  //----------------------------------------------------
  // LÓGICA DO BUZZER
  //----------------------------------------------------

  // Caso esteja MUITO perto (menos de 15 cm e maior que 0)
  if(distance < 15 && distance > 0) {
    tone(PIN_BUZZER, 1000); 
    delay(150);
    noTone(PIN_BUZZER);
    delay(120);

    Serial.println("Buzzer vibrando rápido (ALERTA URGENTE)");
    delay(300);
  }
  
  // Caso esteja perto, porém mais seguro (15–40 cm)
  else if(distance < 40 && distance > 0) {
    tone(PIN_BUZZER, 800); 
    delay(300);
    noTone(PIN_BUZZER);  
    delay(500);

    Serial.println("Buzzer vibrando moderado (ALERTA LEVE)");
    delay(400);
  } 
  
  // Caso esteja longe e seguro (+40 cm)
  else {
    noTone(PIN_BUZZER);
    Serial.println("Sem alerta – ambiente seguro");
    delay(400);
  }

}
