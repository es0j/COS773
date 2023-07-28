#include "config.h"

#define REG_SIZE 20

char *helloStr="#Hello world from C!";

int getnumber(){
  char *line=getLine();
  return atoi(line);
}

int regfile[REG_SIZE];

int doOperation(int n1,int n2,char op){
  switch (op)
  {
  case '+':
    return n1+n2;
    break;
  case '-':
    return n1-n2;
    break;
  case '*':
    return n1*n2;
    break;
  case 's':
    regfile[n1]+=n2;
    return regfile[n1];
    break;
  
  default:
    earlyPrintf("Operation not implemented");
    break;
  }
}

int main(){

    init_idt();
    picRemap();
    
    earlyPrintf(CLEAR_SCREEN);
    earlyPrintf(helloStr);

    char *line;
    int n1;
    int n2;
    char operation;

    for(int i=0;i<100000;i++){
      
    }
    for(int i=0;i<REG_SIZE;i++){
      regfile[i]=0;
    }

    earlyPrintf("#### super safe kernel calculator #######");
    do
    {
      earlyPrintf("Insert number 1: ");
      n1=getnumber();
      earlyPrintf("Insert operation: ");
      operation=*getLine();
      earlyPrintf("Insert number 2: ");
      n2=getnumber();
      earlyPrintf("Result: ");
      printNum(doOperation(n1,n2,operation));
      
      
    }while(1); // 1= ESCAPE
    
   
}




















