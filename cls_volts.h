//**********************************************************
// Sketch:'''''''''''''''''' Potenciometro
// Autor : Fabiano
//**********************************************************
class cls_vlts {
  public:
    cls_vlts();
    int old = 0;
    int port = 10;
    void runsetup() ;
    void portidrun() ;
};
cls_vlts::cls_vlts() {
  runsetup();
}
void cls_vlts::runsetup() {
  pinMode(port, INPUT);
  Serial.begin(9600);
  while (!Serial) ;
  port = 10;
  Serial.println(analogRead(port));
}
void cls_vlts::portidrun() {
  int  valport = analogRead(port);
  int key = map(valport, 0, 995, 0, 10);
  if (old != key) {
    old = key;
    double volts =  (5 / 995.0) * valport;
    Serial.println( String(volts, 2) + " volts" + " " + String(key) + " " +  String(valport));
  }
  //return  key;
}
