/* ________________________________________________________
       yeison mauricio garcia - ian lopez
  ________________________________________________________*/

int salida = 6;                 
const int sensorPin= A0;
int valor_salida_pwm;    //  declaramos  la variable de tipo entero para la ulizacion de la modulacion por ancho de pulso 0-255
int setPoint=30;
long int pru;
long int VsetP; //valor del setpoint de 0-1023
//int Vmin=(15*10*1023)/5000;//valor minimo para que el mapeo sea 255 (de 0-1023) 15 C
float error, pwmAnt, errorAnt, errorAnt2;
int PWM;
void setup() {
pru=setPoint*10230;
  VsetP=((pru)/(5000));
  Serial.begin(9600);
  pinMode (salida, OUTPUT); //definimos pin de salida
}


void loop() {
  int value = analogRead(sensorPin); //0-1023
  float millivolts = (value / 1023.0) * 5000;
  float celsius = millivolts / 10; 
  Serial.print(celsius);
  Serial.print(",");
  //Serial.print(PWM);
  /*Serial.print(",");
//   Serial.print(value);
  Serial.print(",");
  Serial.print(VsetP);*/
  Serial.print(",");
  Serial.println(setPoint);
  delay(1000);     



error=setPoint-celsius;
valor_salida_pwm=(pwmAnt)+(3.27*error)-(3.1091*(errorAnt));//6.3,6.1
pwmAnt=valor_salida_pwm;
//errorAnt2=errorAnt;
errorAnt=error;
//if(valor_salida_pwm>100){valor_salida_pwm=100;}
//if(valor_salida_pwm<0){valor_salida_pwm=0;}
//PWM=map(valor_salida_pwm,-100,100,0,255);
VsetP=map(setPoint,0,100,0,204);//convertir la referencia en un valor 0-100c ---0-205(equivalencia a su entrada analoga 0-1023)
//valor_salida_pwm=map(value,40,VsetP,255,190);// de 19(c)-referencia(c) de - 255 -190pwm //40 equivale a 19c             
//valor_salida_pwm =map(value,0, 1023,0,255); // guardamos el mapeo en la variable (valor salida)
PWM=map(valor_salida_pwm,100,setPoint,255,0); // guardamos el mapeo en la variable (valor salida) 0
  
  
  if(celsius<=setPoint){
    analogWrite(salida, PWM);
  }
  else{
    analogWrite(salida, 0);
  }
}
