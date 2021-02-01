#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int  ADD(int  op1,int  op2){return (op1+op2);}
int MULT(int  op1,int  op2){return op1*op2;}
int SLT(int  op1,int  op2){if (op1<op2) return 1;else return 0;}
int BNEZ(int  res, int saut){if (res==0) return 0; else return saut/4; }
int LW_SW(int offset,int  ref ){return offset+ref;}





int calcule_arithmetique_logique (char* opcode ,int  op1,int  op2){
int result;
if ((strcmp(opcode, "ADD") == 0)||(strcmp(opcode, "add") == 0)){result=ADD(op1,op2);}
if ((strcmp(opcode, "MULT") == 0)||(strcmp(opcode, "mult") == 0)){result=MULT(op1,op2);}
if ((strcmp(opcode, "SLT") == 0)||(strcmp(opcode, "slt") == 0)){result=SLT(op1,op2);}
if ((strcmp(opcode, "BNEZ") == 0)||(strcmp(opcode, "bnez") == 0)){result=BNEZ(op1,op2);}
if ((strcmp(opcode, "LW") == 0)||(strcmp(opcode, "lw") == 0)){result=LW_SW(op1,op2);}
if ((strcmp(opcode, "SW") == 0)||(strcmp(opcode, "sw") == 0)){result=LW_SW(op1,op2);}

return result;
}
