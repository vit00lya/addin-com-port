#ifndef __COMPORTTOOLS_H__
#define __COMPORTTOOLS_H__

#include "AddInNative.h"
#include "ComPortTools.h"
#include "xserial.hpp"
#include <optional>

class ComPortTools: public AddInNative

{
public:
    ComPortTools();
    std::string GetLine();
    void SendLine(std::string);
    void InitPort(const int &number_com_port,
              const int &baud_rate,
    	      const int &data_bits,
    	      const std::string &parity,
       	      const std::string &stop_bit,
    	      const int &timeout,
    	      const std::string &linux_name_com_port);
private:

    static std::vector<std::u16string> names;
    std::optional<xserial::ComPort> com_;
    xserial::ComPort::eParity getParity(const std::string&);
    xserial::ComPort::eStopBit getStopBit(const std::string&);
    

};
#endif 
