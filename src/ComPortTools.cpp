#include <stdexcept>
#include <string>

#include "str_switch.h"
#include "ComPortTools.h"

std::vector<std::u16string> ComPortTools::names = {
	AddComponent(u"ComPortTools", []() { return new ComPortTools; }),
};

ComPortTools::ComPortTools()
{
	AddProperty(
		u"Version", u"Версия",
		[&](VH var) { var = this->version(); });


	AddFunction(u"GetLine", u"ПолучитьСтроку", [&]() { this->result = this->GetLine(); });
	AddProcedure(u"InitPort", u"ИнициализироватьПорт", [&](VH number_com_port,
							       VH baud_rate,
							       VH data_bits,
							       VH parity,
							       VH stop_bit,
							       VH timeout, 
							       VH linux_name_com_port) { this->InitPort(number_com_port,
													baud_rate,
													data_bits,
													parity,
													stop_bit,
													timeout,
													linux_name_com_port); });

}

std::string ComPortTools::GetLine()
{
  if(com_.has_value()) {
    return com_.value().getLine();
  }
  else {
    AddError(u"Порт не настроен, получение строки невозможно", 1009);
    return "Порт не настроен, получение строки невозможно.";
  }
}

void ComPortTools::InitPort(const int &number_com_port,
	      const int &baud_rate,
	      const int &data_bits,
	      const std::string &parity,
       	      const std::string &stop_bit,
	      const int &timeout,
	      const std::string &linux_name_com_port) { 
  try{
   com_.emplace(number_com_port,
                 baud_rate,
		 getParity(parity),
  		 data_bits,
                 getStopBit(stop_bit),
    		 timeout,
		 linux_name_com_port);
  }
  catch(...){
     AddError(u"Ошибка инициализации порта", 1009);
  }
   
}

xserial::ComPort::eParity ComPortTools::getParity(const std::string& parity){
 
  SWITCH(parity){
    CASE ("even"):
	return xserial::ComPort::eParity::COM_PORT_EVENPARITY;
    CASE ("mark"):
	return xserial::ComPort::eParity::COM_PORT_MARKPARITY;
    CASE ("no"):
	return xserial::ComPort::eParity::COM_PORT_NOPARITY;
    CASE ("odd"):
	return xserial::ComPort::eParity::COM_PORT_ODDPARITY;
    CASE ("space"):
	return xserial::ComPort::eParity::COM_PORT_SPACEPARITY;
      DEFAULT:
	 throw std::runtime_error(u8"Не правльно задан контроль четности, параметр не распознан.");
  }
  
}

xserial::ComPort::eStopBit ComPortTools::getStopBit(const std::string& stop_bit){

  using namespace std::literals;

  SWITCH(stop_bit){
    CASE ("one"):
	return xserial::ComPort::eStopBit::COM_PORT_ONESTOPBIT;
    CASE ("two"):
	return xserial::ComPort::eStopBit::COM_PORT_TWOSTOPBITS;
    CASE ("onefive"):
	return xserial::ComPort::eStopBit::COM_PORT_ONE5STOPBITS;
      DEFAULT:
	 throw std::runtime_error(u8"Не правльно задан стоповый бит, параметр не распознан.");
  }
  
}





