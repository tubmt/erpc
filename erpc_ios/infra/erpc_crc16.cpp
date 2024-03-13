/*
 * Copyright 2021 NXP
 * Copyright 2021 ACRIOS Systems s.r.o.
 * All rights reserved.
 *
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include "erpc_crc16.hpp"
#include <iostream>

using namespace erpc;

////////////////////////////////////////////////////////////////////////////////
// Code
////////////////////////////////////////////////////////////////////////////////

Crc16::Crc16(uint32_t crcStart) : m_crcStart(crcStart) {}

Crc16::Crc16(void) : m_crcStart(0xEF4A) {
    std::cout << "Crc16 - 1" << std::endl;
#if ERPC_THREADS_IS(PTHREADS)
    std::cout << "Crc16 - 2" << std::endl;
#elif ERPC_THREADS_IS(FREERTOS)
    std::cout << "Crc16 - 3" << std::endl;
#elif ERPC_THREADS_IS(ZEPHYR)
    std::cout << "Crc16 - 4" << std::endl;
#elif ERPC_THREADS_IS(MBED)
    std::cout << "Crc16 - 5" << std::endl;
#elif ERPC_THREADS_IS(WIN32)
    std::cout << "Crc16 - 6" << std::endl;
#elif ERPC_THREADS_IS(THREADX)
    std::cout << "Crc16 - 7" << std::endl;
#endif
    std::cout << "Crc16 - 10" << std::endl;
}

Crc16::~Crc16(void) {}

uint16_t Crc16::computeCRC16(const uint8_t *data, uint32_t lengthInBytes)
{
    uint32_t crc = m_crcStart;
    uint32_t j;
    uint32_t i;
    uint32_t byte;
    uint32_t temp;
    const uint32_t andValue = 0x8000U;
    const uint32_t xorValue = 0x1021U;

    for (j = 0; j < lengthInBytes; ++j)
    {
        byte = data[j];
        crc ^= byte << 8;
        for (i = 0; i < 8U; ++i)
        {
            temp = crc << 1;
            if (0UL != (crc & andValue))
            {
                temp ^= xorValue;
            }
            crc = temp;
        }
    }

    return (uint16_t)crc;
}
void Crc16::setCrcStart(uint32_t crcStart)
{
    m_crcStart = crcStart;
}
