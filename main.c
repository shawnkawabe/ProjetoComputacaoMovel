/*output uno ->
[13~8]->roxo(LCD)
[7]->preto(Botão)
[6~]->azul(Servo)
[5~]->verde(Sensor)
[4~2]->cinza(LED)
*/
// --------- # -------------
//Importando libs
#include <LiquidCrystal.h>
#include <Servo.h>
#include <math.h>
// --------- # -------------
//Definindo entradas
#define R 2
#define G 4
#define B 3

Servo servoMovimento;

LiquidCrystal lcd(13, 11, 10, 8, 9, 12);
int botao = 7;
bool condicaoMovimento = false;
// --------- # -------------
void setup(){
    //Entrada do servo    
    int sensorMovimento = digitalRead(5);
    servoMovimento.attach(6);
    //Startando Sensor de Movimento
    pinMode(botao, INPUT);
    pinMode(5, INPUT);
    // Entradas do LED RGB
    pinMode(R, OUTPUT);
    pinMode(G, OUTPUT);
    pinMode(B, OUTPUT);
    //Startando o LCD
    lcd.begin(16,2);
    //Setando o servo para a posição inicial
    servoMovimento.write(90);
}
// --------- # -------------
void loop(){
  	int varbutton =  digitalRead(botao);
    int sensorMovimento = digitalRead(5);
  
    // Condição que define se o botão irá funcionar ou não.
    bool condicaoMovimento = false;
    //Setando a (coluna,linha) de inicio 
    lcd.setCursor(0,0);
    lcd.print("Fechada");
    //Troca de cores pra mostrar o estado do sensor
    //Cor: Branco
    analogWrite(R, 255);
    analogWrite(G, 255);
    analogWrite(B, 255);

    delay(1000);
    //Cor: Laranja
    analogWrite(R, 255);
    analogWrite(G, 130);
    analogWrite(B, 0);

    delay(1000);
    int auxsensor = digitalRead(5);
    sensorMovimento = auxsensor;
    // --------- # -------------
    if(sensorMovimento) {
        condicaoMovimento = !condicaoMovimento;
        //Cor: Amarelo
        analogWrite(R, 255);
        analogWrite(G, 200);
        analogWrite(B, 0);
      	int varauxbutton =  digitalRead(botao);
      	varbutton = varauxbutton;
      	lcd.setCursor(0,1); 
        lcd.print("com movimento");
      	while(sensorMovimento){
          	int varauxbutton =  digitalRead(botao);
      		varbutton = varauxbutton;
			if(varbutton==0 && condicaoMovimento){
                //Printa no LCD
                lcd.setCursor(0,0); 
                lcd.print("Liberada"); 
              	delay(100);
              	lcd.setCursor(0,1); 
        		lcd.print("com movimento");
                //Movimento do servo simulando a abertura de alguma entrada
                servoMovimento.write(180);
                //Muda a cor do rgb pra verde
                //Cor: Verde
                analogWrite(R, 0);
                analogWrite(G, 255);
                analogWrite(B, 0);
              	delay(1000);
              	int auxsensor = digitalRead(5);
    			sensorMovimento = auxsensor;
    		}
        }   
         
    }
  	if(sensorMovimento){
  		condicaoMovimento = true;
    }
  	else{
  		condicaoMovimento = false;
      	lcd.setCursor(0,1); 
        lcd.print("Sem movimento");
    }
    if(!condicaoMovimento && varbutton==0){
        lcd.setCursor(0,1); 
        lcd.print("Sem movimento");
        //Muda a cor do rgb pra vermelho
        //Cor: Vermelho
        analogWrite(R, 255);
        analogWrite(G, 0);
        analogWrite(B, 0);
    }
    delay(1000);
    //Volta o servo para o estado inicial
    servoMovimento.write(90);
    lcd.setCursor(0,0);
    lcd.print("Fechada ");
    //RGB Retorna para estado inativo
    //Cor: Branco
    analogWrite(R, 255);
    analogWrite(G, 255);
    analogWrite(B, 255);
    delay(1000);
}

/*
#Estados do sensor->
Laranja / Branco : Inativo(Sem detectar nada) 
Verde : Liberado(todas condições passando)
Vermelho : Negado(Nenhuma detecção de movimento)
Amarelo : Parcial(Primeira condição, detectado movimento)
*/
