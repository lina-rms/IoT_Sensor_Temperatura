//constantes da equação de Steinhart-Hart (valores típicos para um NTC 10K MF58)
const float A = 0.001129148;
const float B = 0.000234125;
const float C = 0.0000000876741;

int pinNTC = A2; //pino analógico onde o NTC está conectado
int seriesResistor = 10000; //resistor de 10K em série com o NTC

void setup() {
  Serial.begin(9600);
}

void loop() {
  int adcValue = analogRead(pinNTC); //ler o valor do ADC
  float voltage = adcValue * (5.0 / 1023.0); //converter para tensão
  float ntcResistance = (5.0 - voltage) / voltage * seriesResistor; //calcular a resistência do NTC
  
  //equação de Steinhart-Hart
  float logR = log(ntcResistance);
  float tempKelvin = 1.0 / (A + B * logR + C * logR * logR * logR); //temperatura em Kelvin
  float tempCelsius = tempKelvin - 273.15; //converter para Celsius
  
  Serial.print(tempCelsius);
  Serial.println(" °C");
  
  delay(1000); //1 segundo antes da próxima leitura
}