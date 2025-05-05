#include "ComPortTools.h"
#include <iostream>
#include <chrono>


int main(){
    
    ComPortTools com = ComPortTools();
    auto tmp = com.GetLine();

    if (std::holds_alternative<std::string>(tmp)) {
      std::cout << std::get<std::string>(tmp) << std::endl;
    }
    
    return 0;
}
