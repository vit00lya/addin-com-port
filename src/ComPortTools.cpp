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

	AddProcedure(u"FlushRxAndTx", u"ОчиститьВходИВыходПорта", [&](){this->FlushRxAndTx();});
	AddFunction(u"GetByte", u"ПолучитьБайт", [&](){this->result = this->GetByte();});
	AddFunction(u"GetLine", u"ПолучитьСтроку", [&](VH line_ending_character) { this->result = this->GetLine(line_ending_character);
	},{{0, DefaultHelper(static_cast<int64_t>(10))}}); // По умолчанию ищем символ переноса строки
	AddProcedure(u"SendLine", u"ОтправитьСтроку", [&](VH text){this->SendLine(text);}); 
	AddProcedure(u"InitPort", u"ИнициализироватьПорт", [&](VH number_com_port,
							       VH baud_rate,
							       VH data_bits,
							       VH parity,
							       VH stop_bit,
							       VH timeout, 
							       VH linux_name_com_port)
	                                                      {
			      this->InitPort(number_com_port,baud_rate,data_bits,parity,stop_bit,timeout,linux_name_com_port);},
		     {{0, DefaultHelper(static_cast<int64_t>(0))},
		      {1, DefaultHelper(static_cast<int64_t>(9600))},
		      {2, DefaultHelper(static_cast<int64_t>(8))},
		      {3, u"no"},
		      {4, u"one"},
		      {5, DefaultHelper(static_cast<int64_t>(5))},
		      {6, u"ttyUSB"},
		     });
}

std::string ComPortTools::GetLine(int64_t line_ending_character)
{
  if(com_.has_value()) {
    char separator_char = static_cast<char>(line_ending_character);
    return com_.value().getLine(line_ending_character);
  }
  else {
    AddError(u"Порт не настроен, получение строки невозможно", 1009);
    return "Порт не настроен, получение строки невозможно.";
  }
}

int64_t ComPortTools::GetByte()
{
  if(com_.has_value()) {
    int64_t result;
    result = static_cast<int64_t>(com_.value().readByte());
    if (result == 33){
       AddError(u"Ошибка при чтении байта из порта", 1009);
    }
    return result;
  }
  else {
    AddError(u"Порт не настроен, получение строки невозможно", 1009);
    return 0;
  }
}

void ComPortTools::FlushRxAndTx(){
   if(com_.has_value()) {
     com_.value().flushRxAndTx();
  }
  else {
    AddError(u"Порт не настроен, очистка не возможна", 1009);
  }
}

void ComPortTools::SendLine(std::string text)
{
  if(com_.has_value()) {
      bool result = com_.value().print(text.data());
      if (!result){
          AddError(u"Ошибка при отправке строки", 1009);
      }
  }
  else {
    AddError(u"Порт не настроен, отправка строки невозможна", 1009);
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
	 throw std::runtime_error("Не правльно задан контроль четности, параметр не распознан.");
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
	 throw std::runtime_error("Не правльно задан стоповый бит, параметр не распознан.");
  }
  
}





