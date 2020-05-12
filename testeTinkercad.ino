#define pfme 2    // PINO DE MOVIMENTAÇÃO FRENTE MOTOR ESQUERDO
#define ptme 4    // PINO DE MOVIMENTAÇÃO TRAS MOTOR ESQUERDO
#define pvelme 3  // PINO DE VELOCIDADE MOTOR ESQUERDO

#define pfmd 6		// PINO DE MOVIMENTAÇÃO FRENTE MOTOR DIREITO
#define ptmd 7		// PINO DE MOVIMENTAÇÃO TRAS MOTOR DIREITO
#define pvelmd 5	// PINO DE VELOCIDADE MOTOR DIREITO

// FUNÇÃO PARA IMPRIMIR A INSTRUÇÃO RECEBIDA E A MOVIMENTAÇÃO EXECUTADA 
void imprimir(char letra, String movimento) {
  
  Serial.print("Instrucao Recebida: ");
  Serial.println(letra);
  Serial.print("Movimento realizado: ");
  Serial.println(movimento);
  Serial.println("----------------------");
}

int time; 
int vel;  
String msgRec; // VARIÁVEL QUE ARMAZENA A MENSAGEM DOS MOVIMENTOS
String mov; // VARIÁVEL QUE ARMAZENA O MOVIMENTO EXECUTADO

class Motor{
public:
  
  int pf, pt, pv; // PINOS - FRENTE, TRÁS E VELOCIDADE
  
  Motor(int pf, int pt, int pv){
    this->pf=pf;
    this->pt=pt;
    this->pv=pv;
    
    pinMode(pf, OUTPUT);
    pinMode(pt, OUTPUT);
    pinMode(pv, OUTPUT);
    
    // MOTOR INICIAR PARADO
    digitalWrite(pf, LOW); 
    digitalWrite(pt, LOW);
  }
  
  // MÉTODOS DAS MOVIMENTAÇÕES DOS MOTORES
  
  void frente(int v){
    digitalWrite(pf, HIGH);
    digitalWrite(pt, LOW);
    analogWrite(pv, v);
  }
  
  void tras(int v){
    digitalWrite(pf, LOW);
    digitalWrite(pt, HIGH);
    analogWrite(pv, v);
  }
  
  void freia(){
    digitalWrite(pf, HIGH);
    digitalWrite(pt, HIGH);
  }
  
  void para(){
    digitalWrite(pf, LOW);
    digitalWrite(pt, LOW);
  }
};

Motor me(pfme, ptme, pvelme); // INSTANCIAMENTO DO OBJETO MOTOR ESQUERDO
Motor md(pfmd, ptmd, pvelmd); // INSTANCIAMENTO DO OBJETO MOTOR DIREITO



void setup() {
  vel = 32;
  time = 3000;
  Serial.begin(9600);
}

void loop() {
  
  if (Serial.available() > 0) {
    
    msgRec=Serial.readString();
    
    for (char i = 0; i < msgRec.length(); i++) {
      
      char instrucao = msgRec.charAt(i); // VARIÁVEL QUE ARMAZENA CADA CARACTERE DA MENSAGEM
    
      if(instrucao == 'f') {

        mov = "frente";
        me.frente(vel);
        md.frente(vel);
        delay(time);
        me.freia();
        md.freia();
        me.para();
        md.para();
        imprimir(instrucao, mov);
        delay(time);

      } else if(instrucao == 't') {

        mov = "tras";
        me.tras(vel);
        md.tras(vel);
        delay(time);
        me.freia();
        md.freia();
        me.para();
        md.para();
        imprimir(instrucao, mov);
        delay(time);

      } else if(instrucao == 'd') {

        mov = "direita";
        me.frente(vel);
        md.tras(vel);
        delay(time);
        me.freia();
        md.freia();
        me.para();
        md.para();
        imprimir(instrucao, mov);
        delay(time);

      } else if(instrucao == 'e') {

        mov = "esquerda";
        me.tras(vel);
        md.frente(vel);
        delay(time);
        me.freia();
        md.freia();
        me.para();
        md.para();
        imprimir(instrucao, mov);
        delay(time);

      }
    } 
  }
}