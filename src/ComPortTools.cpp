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
    AddMethod(L"Init", L"ИнициализироватьПорт", this, &ComPortTools::Init);

}

variant_t ComPortTools::GetLine() {

  if(com_ != nullptr) {
    return com_->getLine();
  }
  else {
    throw std::runtime_error(u8"Порт не настроен, получение строки невозможно.");
  }
  
}

void ComPortTools::Init(const variant_t &number_com_port,
	      const variant_t &baud_rate,
	      const variant_t &data_bits,
	      const variant_t &parity,
       	      const variant_t &stop_bit,
	      const variant_t &timeout) {
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
        throw std::runtime_error(u8"Не правльно задан, параметр не является числом.");
    }
    
    com_ = std::make_unique<xserial::ComPort>(xserial::ComPort(
                       number_com_port_param,
                       baud_rate_param,
		       data_bits_param,
                       getParty(party),
                       getStopBit(stop_bit),
		       timeout_param));
}

