const int pinoSensor1 = 2 /* Esquerda */, pinoSensor2 = 3 /* Direita */, led=1;
//MOTOR A
const int MD1 = 5, MD2 = 4;
// MOTOR B
const int ME1 = 7, ME2 = 6;
const int s0 = 11, s1 = 12, s2 = 9, s3 = 10, outRGB = 8;  // RGB
int red = 0, green = 0, blue = 0, lastColor = 1, amarelo = 0; //Variaveis cores

void setup() {
  //DEFINIR PINOS DOS SENSORES COMO ENTRADA
  pinMode(pinoSensor1, INPUT);
  pinMode(pinoSensor2, INPUT);

  //SAIDAS DE CONTROLE DOS MOTORES
  pinMode(ME1, OUTPUT);
  pinMode(ME2, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);

  //DEFINIR PINO DO SENSOR RGB
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(outRGB, INPUT);

  //Os pinos S0 e S1 determinam a frequência de saída (20% neste caso)
  digitalWrite(s0, HIGH);
  digitalWrite(s1, LOW);

  //DEFINIR PINO DO LED
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);
}

void loop() {
  
  detectaCor();

  if(amarelo == 1){
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    delay(200);
    digitalWrite(led, HIGH);
    delay(300);
    digitalWrite(led, LOW);
    amarelo = 0;
  }

  if(lastColor == 1){
    digitalWrite(MD1, 0);
    digitalWrite(ME1, 0);
    digitalWrite(MD2, 0);
    digitalWrite(ME2, 0);

  }else if (lastColor == 2){
    andar();
  }
}

void detectaCor(){
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  red = pulseIn(outRGB, digitalRead(outRGB) == HIGH ? LOW : HIGH);

  digitalWrite(s3, HIGH);
  blue = pulseIn(outRGB, digitalRead(outRGB) == HIGH ? LOW : HIGH);

  digitalWrite(s2, HIGH);
  green = pulseIn(outRGB, digitalRead(outRGB) == HIGH ? LOW : HIGH);

  if(red < 200 && green < 200 && red < blue && green < blue){
    amarelo = 1; //Amarelo
  }else if (red < 200 && red < blue && red < green) {
    lastColor = 1; //vermelho
  }else if(green < 200 && green < blue && green < red){
    lastColor = 2; //verde
  }
}

void andar(){

  //Os dois sensores veem preto, ande
  if (digitalRead(pinoSensor1) == HIGH && digitalRead(pinoSensor2) == HIGH) {
    digitalWrite(MD1, HIGH);
    digitalWrite(ME1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(ME2, LOW);
    delay(80);

  //Sensor esquerdo ve branco, sensor direito ve preto
  } else if (digitalRead(pinoSensor1) == LOW && digitalRead(pinoSensor2) == HIGH) {
    digitalWrite(MD1, HIGH);
    digitalWrite(ME1, LOW);
    digitalWrite(MD2, LOW);
    digitalWrite(ME2, LOW);
    delay(100);
    digitalWrite(MD1, LOW);
    digitalWrite(ME1, LOW);
    digitalWrite(MD2, LOW);
    digitalWrite(ME2, LOW);
    delay(100);

  //Sensor direito ve branco, sensor esquerdo ve preto
  } else if (digitalRead(pinoSensor1) == HIGH && digitalRead(pinoSensor2) == LOW) {
    digitalWrite(MD1, LOW);
    digitalWrite(ME1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(ME2, LOW);
    delay(100);
    digitalWrite(MD1, LOW);
    digitalWrite(ME1, LOW);
    digitalWrite(MD2, LOW);
    digitalWrite(ME2, LOW);
    delay(100);


  //Os dois sensores veem branco, escolher um lado    
  } else {
    digitalWrite(MD1, LOW);
    digitalWrite(ME1, HIGH);
    digitalWrite(MD2, LOW);
    digitalWrite(ME2, LOW);
    delay(80);
  }
}
