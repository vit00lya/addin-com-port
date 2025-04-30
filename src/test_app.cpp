#include "xserial.hpp"

int main(){

    xserial::ComPort com = xserial::ComPort(
                          0,
                          9600,
                          xserial::ComPort::COM_PORT_NOPARITY,
                          8,
                          xserial::ComPort::COM_PORT_ONESTOPBIT);
    std::string tmp = com.getLine();
    std::cout << tmp << std::endl;
    
  return 0;
}
