/*
 *  Modern Native AddIn
 *  Copyright (C) 2018  Infactum
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Affero General Public License as
 *  published by the Free Software Foundation, either version 3 of the
 *  License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Affero General Public License for more details.
 *
 *  You should have received a copy of the GNU Affero General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <chrono>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <string>
#include <thread>

#include "ComPortTools.h"

std::string ComPortTools::extensionName() {
    return "ComPortTools";
}

ComPortTools::ComPortTools() {

    // Full featured property registration example
    AddProperty(L"Version", L"ВерсияКомпоненты", [&]() {
        auto s = std::string(Version);
        return std::make_shared<variant_t>(std::move(s));
    });

    // Method registration.
    // Lambdas as method handlers are not supported.
    AddMethod(L"GetLine", L"ПолучитьСтроку", this, &ComPortTools::GetLine);
    AddMethod(L"InitPort", L"ИнициализироватьПорт", this, &ComPortTools::InitPort);
 
}

variant_t ComPortTools::GetLine() {

  if(com_.has_value()) {
    return com_.value().getLine();
  }
  else {
    throw std::runtime_error(u8"Порт не настроен, получение строки невозможно.");
  }
  
}

void ComPortTools::InitPort(const variant_t &number_com_port,
	      const variant_t &baud_rate,
	      const variant_t &data_bits,
	      const variant_t &parity,
       	      const variant_t &stop_bit,
	      const variant_t &timeout,
	      const variant_t &linux_name_com_port) {
   long baud_rate_param = 0;
    if (std::holds_alternative<int32_t>(baud_rate)) {
      baud_rate_param = static_cast<long>(std::get<int32_t>(baud_rate));
    } else {
        throw std::runtime_error(u8"Не правльно задана скорость порта, параметр не является числом.");
    }

    long number_com_port_param = 0;
    if (std::holds_alternative<int32_t>(number_com_port)) {
      number_com_port_param = static_cast<long>(std::get<int32_t>(number_com_port));
    } else {
        throw std::runtime_error(u8"Не правльно задан номер порта, параметр не является числом.");
    }
   
    long data_bits_param = 0;
    if (std::holds_alternative<int32_t>(data_bits)) {
      data_bits_param = static_cast<long>(std::get<int32_t>(data_bits));
    } else {
        throw std::runtime_error(u8"Не правльно задано передаваемое по порту количество бит, параметр не является числом.");
    }

    long timeout_param = 0;
    if (std::holds_alternative<int32_t>(timeout)) {
      timeout_param = static_cast<long>(std::get<int32_t>(timeout));
    } else {
        throw std::runtime_error(u8"Не правльно задана задержка считывания с порта, параметр не является числом.");
    }

    std::string linux_name_com_port_param;
    if (std::holds_alternative<std::string>(linux_name_com_port)) {
      linux_name_com_port_param = std::get<std::string>(linux_name_com_port);
    } else {
        throw std::runtime_error(u8"Не правльно задано название com-порта для linux, параметр не является строкой.");
    }
    
    com_.emplace(number_com_port_param,
                 baud_rate_param,
                 getParity(parity),
    		 data_bits_param,
                 getStopBit(stop_bit),
    		 timeout_param,
    		 linux_name_com_port_param);
}

xserial::ComPort::eParity ComPortTools::getParity(const variant_t& parity){
  
  std::string parity_param;
  if (std::holds_alternative<std::string>(parity)) {
    parity_param = std::get<std::string>(parity);
    } else {
        throw std::runtime_error(u8"Не правльно задан контроль четности, параметр не является строкой.");
    }

  SWITCH(parity_param){
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

xserial::ComPort::eStopBit ComPortTools::getStopBit(const variant_t& stop_bit){

  using namespace std::literals;
  
  std::string stop_bit_param;
  if (std::holds_alternative<std::string>(stop_bit)) {
    stop_bit_param = std::get<std::string>(stop_bit);
    } else {
        throw std::runtime_error(u8"Не правльно задан стоповый бит, параметр не является строкой.");
    }

  SWITCH(stop_bit_param){
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



