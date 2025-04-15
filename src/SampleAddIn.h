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

#ifndef SAMPLEADDIN_H
#define SAMPLEADDIN_H

#include "Component.h"
#include "xserial.hpp"

class SampleAddIn final : public Component {
public:
    const char *Version = u8"1.0.0";

    SampleAddIn();

private:

    std::string extensionName() override;
    variant_t GetLine();
    unsigned long baud_rate_ = 9600; ///< Скорость UART по умолчанию
    xserial::ComPort::eParity parity_ = xserial::ComPort::COM_PORT_NOPARITY; ///< Настройка проверки четности по умолчанию
    xserial::ComPort::eStopBit stop_bit_ = xserial::ComPort::COM_PORT_ONESTOPBIT; ///< Настройка стопового бита по умолчанию
    const char data_bits_ = 8; ///< Количесвто бит данных по умолчанию
    const xserial::ComPort::eMode mode_ = xserial::ComPort::COM_SYNCHRONOUS; ///< Настройка режима работы с портом по умолчанию

};

#endif //SAMPLEADDIN_H
