#include "ComPortTools.h"
#include <iostream>
#include <chrono>

const uint16_t* GetUI(const char *c)
{
    const size_t cSize = strlen(c)+1;
    uint16_t* uint = new uint16_t[cSize];
    for(size_t i = 0; i < cSize; ++i){
      uint[i] = (uint16_t)c[i];
    }
    return uint;
}

int main(){
    
  ComPortTools com = ComPortTools();
  // com.InitPort(0,9600,8,"no","one",5);
  //auto tmp = com.GetLine();

  //  if (std::holds_alternative<std::string>(tmp)) {
  //   std::cout << std::get<std::string>(tmp) << std::endl;
  // }
  //tmp = com.GetLine();

  //  if (std::holds_alternative<std::string>(tmp)) {
  //  std::cout << std::get<std::string>(tmp) << std::endl;
  //}

  std::cout << com.FindMethod(GetUI("InitPort")) << std::endl;
    
  return 0;
}
