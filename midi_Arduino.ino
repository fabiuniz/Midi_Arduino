//**********************************************************
// Rotinas Arduino:''''''''''''''''''
// Autor : Fabiano
// Data: 05/10/2021
//**********************************************************
//#include "cls_ldr.h"
#include "cls_volts.h"
#include "cls_notes.h"
/*--------------------------------------------------------------*/
cls_notas *clsnotas;
cls_ldr *clsldr;
cls_vlts *clsvlts;
/*--------------------------------------------------------------*/
void setup() {
  clsnotas = new cls_notas(true);
}
void loop() {
  clsnotas->sweeping_key();
}
