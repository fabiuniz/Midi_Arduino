//**********************************************************
// Sketch:'''''''''''''''''' Library
// Autor : Fabiano
//**********************************************************
/*
  Escopo para a criação de uma classe
   class nome_da_classe{
     private:
       membros privados (funções e atributos)
     public:
       membros públicos (funções e atributos)
   };
   //Declara as funções membros
   [Tipo_retorno] nome_classe :: nome_método([parametros]){
    Código do método
   }
*/
class cls_lib {
  public:
    cls_lib();
    void runsetup() ;
    void listencmds() ;
};

cls_lib::cls_lib() {
  runsetup();
}
void cls_lib::runsetup() {
  Serial.begin(9600);
  while (!Serial) ;
}
void cls_lib::sweepingldr() {
  int ldr = analogRead(A0);
  Serial.println(ldr);
  delay(2000);
}

void cls_lib::listencmds() {
  if (Serial.available()) {
    while (Serial.available()) { // While there is more to be read, keep reading.
      command += (char)Serial.read();
      delay (10);
    }
    Serial.println(command);
    if (getValue(command, ':', 0) == "h")
      shor.write(fixh + getValue(command, ':', 1).toInt()); // Inicia motor posição zero
    if (getValue(command, ':', 0) == "v")
      sver.write(fixv + getValue(command, ':', 1).toInt()); // Inicia motor posição zero
    delay(15);
    command = "";
  }
}
//-----------------------------------------------------------------------------------
//Classe itens
class cls_itens {
  public:
    char* nnprm = "";
    String value = "";
};

//-------------------------
cls_itens *tcls[20];
int find(char* s) {
  for (int i = 0; tcls[i]; i++) {
    if (!strcmp(s, tcls[i]->nnprm)) return i;
  }
  return -1; // -1 means "not found"
}
//--------------------------
cls_itens *itnotes;
void apeendgent(char* nm, String vl) {
  int id = find(nm);
  if (id == -1) {
    itnotes = new cls_itens;
    itnotes->nnprm = nm;
    itnotes->value = vl;
    tcls[sizeof(tcls)] = itnotes;
  } else {
    tcls[id]->value = vl;
  }
}
