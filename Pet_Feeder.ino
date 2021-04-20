#include <LiquidCrystal.h>   
#include <Keypad.h>
#include <Servo.h>

unsigned long timer, start, inicial;
						//inicial = tempo ao ligar o arduino
						//Start = tempo ao iniciar o programa
unsigned long time; //Inserida pelo usuário

int pos = 0;
Servo servo_A2;
int a=0, b=0, c=0, d=0;
int var=0;
int C1=1,C2=2,C3=4,C4=5;
char f='*';
int tries=0,wrong=0;
int warning=3;
bool locked = true;


const byte rows = 4;
const byte columns = 4;
char tecla[rows][columns] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte pinRows[rows] = {7, 6, 5, 4};
byte pinColumn[columns] = {3, 2, 1, 0}; 

Keypad keypad = Keypad( makeKeymap(tecla), pinRows, pinColumn, rows, columns);
LiquidCrystal lcd(13,12,11,10, 9, 8); 

void setup(){
  servo_A2.attach(A2, 500, 2500);
  lcd.begin(16,2); 
  pinMode(A5,OUTPUT);//Piezo for future integration
  pinMode(A0,OUTPUT); 
  pinMode(A1,OUTPUT);
  servo_A2.write(0);
  inicial = millis();
}
void setTimer(){
  start = millis();
}
void open(){
  lcd.clear();
  lcd.setCursor(2,0);
    lcd.print("Feeding...");
  
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
    for (pos = 0; pos <= 90; pos += 1) {
        servo_A2.write(pos);//Open
        delay(15);
          }
  	locked = false;
 lcd.clear();
}
void close(){
  lcd.clear();
    lcd.setCursor(4,0);
    lcd.print("Complete...");
  
  digitalWrite(A0,LOW);
	for (pos = 90; pos >= 0; pos -= 1) {
    servo_A2.write(pos);//Close
    delay(15);
  }
     	locked = true;
lcd.clear();
}

int horas, minutos, segundos, milissegundos;

String milisParaHora(){
  segundos = timer / 1000;
  minutos = segundos / 60;
  horas = minutos / 60;
  
  String milisHora = String(horas);
  milisHora.concat(":");
  milisHora.concat(String(minutos));
  milisHora.concat(":");
  milisHora.concat(String(segundos));
  return milisHora;
}

String horaParaMilis(){
  minutos = horas * 60;
  segundos = minutos * 60;
  milissegundos = segundos * 1000;
  
  String horaMilis = String(horas);
  horaMilis.concat(":");
  horaMilis.concat(String(minutos));
  horaMilis.concat(":");
  horaMilis.concat(String(segundos));
  return horaMilis;
}

void concat(int y){
  time = 10*time + y;
}

//LOOP
void loop(){
  timer = millis();
  long t = start + time*1000;
  char key = keypad.getKey();
  if(key){
  switch (key){
   	case '*':
    	setTimer();
    	lcd.clear();
    	break;
    case '1':
    	concat(1);
    lcd.clear();
    	break;
    case '2':
    		concat(2);
    lcd.clear();
    	break;
    case '3':
    		concat(3);
    lcd.clear();
    	break;
    case '4':
    		concat(4);
    lcd.clear();
    	break;
    case '5':
    		concat(5);
    lcd.clear();
    	break;
    case '6':
    		concat(6);
    lcd.clear();
    	break;
    case '7':
    		concat(7);
    lcd.clear();
    	break;
    case '8':
    		concat(8);
    lcd.clear();
    	break;
    case '9':
    		concat(9);
    lcd.clear();
    	break;
    case '0':
    		concat(0);
    lcd.clear();
    	break;
  }
  }
  
  if(timer > t && t > 0){
  	lcd.setCursor(14,1),lcd.print("!");
    open();
    delay(1000);
    close();
    setTimer();
  }
 
 if(locked == false){
   lcd.clear();
     lcd.setCursor(4,0),lcd.print("Feeding...");
   
 } else {
 	 lcd.setCursor(0,0),lcd.print("Feed each");
     lcd.setCursor(13,0),lcd.print(time);
     lcd.setCursor(15,0),lcd.print("s");
   	 lcd.setCursor(1,1),lcd.print(milisParaHora());
 }
}
