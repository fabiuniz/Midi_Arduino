//http://arduino.esp8266.com/stable/package_esp8266com_index.json
//Instalar CH341SER.EXE
//apertar 4 vezes reset+gnd apos messagem do arduino "carregando" para fazer o upload do steck
//resistor leader in parallelo pulling up pins that aren't connected to anything
//**********************************************************
// Sketch:'''''''''''''''''' Teclado matricial 7x8 Arduino Leonardo Atmega32u4 16 mhz 5v
// Autor : Fabiano
//**********************************************************
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(ARDUINO_AVR_LEONARDO)
//int pinosLinhas[]={};
//int pinosColunas[]={};
#include <MIDIUSB.h>
int pinosLinhas[]  = {A3, A2, A1, A0, 15, 14, 16}; //7 notas
int pinosColunas[] = {2, 3, 4, 5, 6, 7, 9,8 }; //8 conjuntos das 7 notas de cada pinosLinhas
#endif
#if defined(__AVR_ATmega328P__)
int pinosLinhas[]  = {A3, A2, A1, A0, A5, A4, 13};
int pinosColunas[] = {2, 3, 4, 5, 6, 7, 8, 9};
#endif
#if  defined(__AVR_ATmega168__)
int pinosLinhas[]  = {A1, A2, A3, A4, A5, A6, A7};
int pinosColunas[] = {4, 5, 6, 7, 9, 10, 11, 12};
#endif
#define d_lines 7//8
#define d_cols 8
//Classe para pegar push de gpios
//cls_chkbutton *clschkbutton;
//void setup(){clschkbutton = new cls_chkbutton();clschkbutton->callrunfc = xxx; clschkbutton->inicialize()};
//void loop(){ clschkbutton->checkinButtonPower();}
class cls_chkbutton {
  public:
    typedef void (*TFuncPress)(int qtdpres );
    int inButtonPower = 2;
    int outGpio0 = A3;
    int qtdpress = 0;
    int flagpress = 1;
    unsigned long lastTime = 0;
    unsigned long timeDelay = 3000;
    unsigned long timeHolding = 0;
    void runcmd(int qtdpress);
    void checkinButtonPower();
    void inicialize();
    TFuncPress callrunfc;
};

void cls_chkbutton::inicialize() {
  Serial.begin(9600);
  Serial.println("Start");
  pinMode(inButtonPower, INPUT);
  pinMode(outGpio0, OUTPUT);
  digitalWrite(outGpio0, LOW);
}

void  cls_chkbutton::runcmd(int qtdpress) {
  if (callrunfc != NULL)
    callrunfc(qtdpress);
  Serial.println("Pressed");
  Serial.println(String(qtdpress));
  delay(2000);
}

void cls_chkbutton::checkinButtonPower() {
  int val = digitalRead(inButtonPower);   // read the input pin
  digitalWrite(outGpio0, val);  // sets the LED to the button's value
  if (digitalRead(outGpio0) == LOW) {
    if (flagpress == 1) {
      qtdpress = qtdpress + 1;
    }
    flagpress = 0;
    timeHolding = millis() - lastTime;
    Serial.print(String(timeHolding));
    Serial.print("->");
    Serial.println(String(timeDelay));
    if (timeHolding > (timeDelay) ) {
      flagpress = 0;
      lastTime = millis();
      runcmd(qtdpress);
      qtdpress = 0;
    }
  } else {
    flagpress = 1;
    lastTime = millis();
  }
}
cls_chkbutton *clschkbutton;
void rungpioscmds (int numcmd) {
  switch (numcmd) {
    case 2:
      Serial.print("Reiniciando...");      
      break;
     default:
      Serial.print("Comando desconhecido");
      break;
  }
  Serial.print(String(numcmd));
  Serial.println(":Comando executado!");
  delay(500);
}

/*----------------------------------*/
//Classe itens
class cls_itens {
  public:
    String strnote = "";
    int intnote = 0;
    bool bolpress = false;
    unsigned long milesecs = millis();
    int freq = 0;
};
/*----------------------------------*/
//Classe notas correntes
class cls_notas {
    bool nomsg = false;
    int portpotenciometer = 10;
    int NumAcumnotes = 0;
    int oldvalue=0;
    int NumAcumpress = 0;
    int startnote = 35; //posição inicial da nota 54 keys
    int delai = 127;
    byte velocity = 127;
    byte channel = 1;
    int NumLines = sizeof(pinosLinhas) / sizeof(pinosLinhas[0]);
    int NumCols = sizeof(pinosColunas) / sizeof(pinosColunas[0]);
    int qtdteclas = NumLines * NumCols;
    cls_itens *tcls[d_lines * d_cols];
    cls_itens *itnotes;
    void printmsg(String msg) ;
    void noteOff( byte pitch, String deb);
    void noteOn( byte pitch, String deb);
    void sustainOn( byte pitch, String deb) ;
    void getkeyport(int port) ;
    void popula();
    String hello();
    void runsetup();
    String strdebug(int l, int c, String note, int numnote, String desc);
  public:
    cls_notas(bool noms);//construtor
    void sweeping_key();
};
//Construtor /*-  ---------------------------------------------*/
cls_notas::cls_notas(bool noms) {
  nomsg = noms;
  printmsg(hello());
  clschkbutton = new cls_chkbutton();
  clschkbutton->callrunfc = rungpioscmds;
  clschkbutton->inicialize();
  runsetup();
}
/*--------------------------------------------------------------*/
void cls_notas::runsetup() {
  popula();
  pinMode(portpotenciometer, INPUT);
  for (int nL = 0; nL <= d_lines - 1; nL++) {
    pinMode(pinosLinhas[nL], OUTPUT);
    digitalWrite(pinosLinhas[nL], HIGH);
  }
  for (int nC = 0; nC <= d_cols - 1; nC++) {
    pinMode(pinosColunas[nC], INPUT_PULLUP);//para não precisar de resistor
  }  
}
String cls_notas::strdebug(int l, int c, String note, int numnote, String desc) {
  String strret = "";
  if (nomsg == false) {
    strret += "Tecla: ";
    strret += String(numnote);
    strret += " " ;
    strret += String(note) ;
    strret += " " ;
    strret += String(c + 1) ;
    strret += " x " ;
    strret += String(l + 1) ;
    strret += " " ;    
    strret += desc ;
  }
  return strret;
}
/*--------------------------------------------------------------*/
String cls_notas::hello() {
  String strret = "";
  if (nomsg == false) {
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(ARDUINO_AVR_LEONARDO)
    strret += "ARDUINO LEONARDO";
#endif
#if defined(__AVR_ATmega328P__) || defined(__AVR_ATmega168__)
    //strret += "ARDUINO UNO R3 SMD";
#endif
    strret += "\n";
    strret += "Teclado ";
    strret += NumLines;
    strret += "x";
    strret += NumCols;
    strret += "\n";
    strret += String(digitalRead(portpotenciometer));
    strret += "\n";
    strret += "Aguardando ACIONAMENTO das teclas...";
  }
  return strret;
}
/*--------------------------------------------------------------*/
void cls_notas::printmsg(String msg) {
  if (nomsg == false) {
    Serial.begin(9600);
    while (!Serial) ;
    Serial.print(msg);
    Serial.println("\n");
  }
}
/*--------------------------------------------------------------*/
void cls_notas::popula() {
  NumAcumpress = 0;
  String strnotas[12] = {"B", "C", "C#", "D", "D#", "E", "F", "F#", "G", "G#", "A", "A#"};
  for (int nL = 0; nL <= NumLines - 1; nL++) {//percorre notas
    for (int nC = 0; nC <= NumCols - 1; nC++) {//percorre conjuntos de 7 notas
      int numTecla = ((nL + 1  + NumAcumpress + nC) );
      itnotes = new cls_itens;
      itnotes->strnote = strnotas[numTecla % 12];
      itnotes->intnote = numTecla;
      itnotes->milesecs = delai + 1;
      itnotes->bolpress = false;
      itnotes->freq = 0;
      tcls[numTecla] = itnotes;
    }
    NumAcumpress = NumAcumpress + NumCols - 1;
  }
}
/*--------------------------------------------------------------*/
void cls_notas::sweeping_key() {
  //faz varredura em todas as linhas, desligando uma de cada vez
  NumAcumnotes = 0;
  for (int nL = 0; nL <= NumLines - 1; nL++) {//percorre notas
    digitalWrite(pinosLinhas[nL], LOW);
    //faz varredura em todas as colunas verificando se tem algum botao apertado
    for (int nC = 0; nC <= NumCols - 1; nC++) {//percorre conjuntos de 7 notas
      int numTecla = ((nL + 1  + NumAcumnotes + nC) );
      String nota = tcls[numTecla]->strnote;
      String dbg = strdebug(nL, nC, nota, numTecla, "");
      if (digitalRead(pinosColunas[nC]) == LOW) {//teclas precionadas
        tcls[numTecla]->freq = analogRead(pinosColunas[nC]);
        //noteOff(numTecla, dbg);
        if ((millis() - tcls[numTecla]->milesecs) >= delai) {
          noteOn(numTecla, dbg );
        } else {
          sustainOn(numTecla, dbg );
        }
        //noteOff(numTecla, dbg);
        //if ((millis() - tcls[numTecla]->milesecs) > delai) {
        //if (tcls[numTecla]->bolpress == true) {
      } else {
        if (tcls[numTecla]->bolpress == true) {
          if ((millis() - tcls[numTecla]->milesecs) >= delai) {
            noteOff(numTecla, dbg );
          }
        }
      }
    }
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(ARDUINO_AVR_LEONARDO)
    MidiUSB.flush();
#endif
    digitalWrite(pinosLinhas[nL], HIGH);
    NumAcumnotes = NumAcumnotes + NumCols - 1;
  }
  getkeyport(10);
}
/*--------------------------------------------------------------*/
void cls_notas::noteOn( byte pitch, String deb) {
  //printmsg(deb +  " " + millis() + " " + tcls[pitch]->milesecs + " On");
  printmsg(deb +   " On");
  tcls[pitch]->bolpress = true;
  tcls[pitch]->milesecs = millis();
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(ARDUINO_AVR_LEONARDO)
  midiEventPacket_t noteOn = {0x09, 0x90 | channel, startnote + pitch, velocity};
  MidiUSB.sendMIDI(noteOn);
  //MidiUSB.flush();
#endif
}
/*--------------------------------------------------------------*/
void cls_notas::sustainOn( byte pitch, String deb) {
  printmsg(deb + " Mid seq:" + (startnote + pitch)  +  " SecA" + millis() + " SecB:" + tcls[pitch]->milesecs + " Fre:" + tcls[pitch]->freq + " Sus" );
  //tcls[pitch]->bolpress = true;
  tcls[pitch]->milesecs = millis();
  //midiEventPacket_t noteSus = {0xB0, 0xB0 | channel, startnote + pitch, velocity + 200};//0x40
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(ARDUINO_AVR_LEONARDO)
  midiEventPacket_t noteSus = {0xB0, 0xB0 | 0x00, 0x40, 0x7F};//0x40
  MidiUSB.sendMIDI(noteSus);
  //MidiUSB.flush();
  // Sustain value (≤63 off, ≥64 on)
#endif
}
/*--------------------------------------------------------------*/
void cls_notas::noteOff( byte pitch, String deb) {
  printmsg(deb + " Off");
  tcls[pitch]->bolpress = false;
  tcls[pitch]->milesecs = millis() - delai;
#if defined(__AVR_ATmega32U4__) || defined(__AVR_ATmega16U4__) || defined(ARDUINO_AVR_LEONARDO)
  midiEventPacket_t noteOff = {0x08, 0x80 | channel, startnote + pitch, velocity};
  MidiUSB.sendMIDI(noteOff);
  //MidiUSB.flush();
#endif
}
/*--------------------------------------------------------------*/
void cls_notas::getkeyport(int port) {
  int  valport = analogRead(port);
  int key = map(valport, 0, 995, 0, 10);
  if (oldvalue != key) {
    oldvalue = key;
    double volts =  (5 / 995.0) * valport;
   // noteOn(startnote + key, "" );
   // noteOff(startnote + key, "" );
    Serial.println( String(volts, 2) + " volts" + " " + String(key) + " " +  String(valport));
  }
  //return  key;
}
