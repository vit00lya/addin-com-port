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

#ifndef COMPORTTOOLS_H
#define COMPORTTOOLS_H

#include "Component.h"
#include "xserial.hpp"
#include "types.h"
#include "str_switch.h"
#include <optional>

class ComPortTools final : public Component {
public:
    const char *Version = u8"1.0.0";

    ComPortTools();
    // void Init(const variant_t &number_com_port = 0,
    //const variant_t &baud_rate = 9600,
    //	      const variant_t &data_bits = 8,
    //	      const variant_t &parity = "no",
    //   	      const variant_t &stop_bit = "one",
    //	      const variant_t &timeout = 0,
    //	      const variant_t &linux_name_com_port = "ttyUSB");

    ComPortTools(const ComPortTools&) = delete;
    ComPortTools& operator=(const ComPortTools& other) = delete;
    
    //variant_t GetLine();

private:

    void InitPort(const variant_t &number_com_port = 0,
              const variant_t &baud_rate = 9600,
    	      const variant_t &data_bits = 8,
    	      const variant_t &parity = "no",
       	      const variant_t &stop_bit = "one",
    	      const variant_t &timeout = 0,
    	      const variant_t &linux_name_com_port = "ttyUSB");

    variant_t GetLine();

    std::optional<xserial::ComPort> com_;
    xserial::ComPort::eParity getParity(const variant_t&);
    xserial::ComPort::eStopBit getStopBit(const variant_t&);
    std::string extensionName() override;

}; 

#endif //ComPortTools_H
