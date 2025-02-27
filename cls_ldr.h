//**********************************************************
// Sketch:'''''''''''''''''' LDR foto resistor 5516
// Autor : Fabiano
//**********************************************************
class cls_ldr {
  public:
    cls_ldr();
    void runsetup() ;
    void sweepingldr() ;
};

cls_ldr::cls_ldr() {
  runsetup();
}
void cls_ldr::runsetup() {
  Serial.begin(9600);
  while (!Serial) ;
}
void cls_ldr::sweepingldr() {
  int ldr = analogRead(A0);
  Serial.println(ldr);
  delay(2000);
}
