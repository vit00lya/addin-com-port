#include "ComPortTools.h"
#include <iostream>

int main(){
    std::cout << "ОК0" << std::endl;  
  ComPortTools com = ComPortTools();
  std::cout << "ОК1" << std::endl;
  com.InitPort(0,9600,8,"no","one",1,"ttyS");
 std::cout << "ОК2" << std::endl;
 //std::cout << com.GetLine() << std::endl;
 //com.SendLine("OK");
  return 0;
  
}
