/*
 * Author: Brendan Le Foll <brendan.le.foll@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be
 * included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 * LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#pragma once

/** @file
 *
 * @brief Inter-Integrated Circuit
 *
 * This file defines the i2c/Iic interface for libmaa. A context represents a
 * bus and that bus may contain multiple addresses or i2c slaves. It is
 * considered best practice to make sure the address is correct before doing
 * any calls on i2c, in case another application or even thread changed the
 * addres on that bus. Multiple instances of the same bus can exist.
 *
 * @snippet i2c_HMC5883L.c Interesting
 */

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdint.h>

#include "maa.h"
#include "gpio.h"

/**
 * Opaque pointer definition to the internal struct _i2c
 */
typedef struct _i2c* maa_i2c_context;

/** Initialise i2c context, using board defintions
 *
 * @param bus i2c bus to use
 * @return maa_i2c_context i2c context ready for other calls.
 */
maa_i2c_context maa_i2c_init(int bus);

/** Initialise i2c context, passing in spi bus to use.
 *
 * @param bus The i2c bus to use i.e. /dev/i2c-2 would be "2"
 * @return maa_i2c_context i2c context ready for other calls.
 */
maa_i2c_context maa_i2c_init_raw(unsigned int bus);

/** Sets the frequency of the i2c context
 *
 *  @param dev the i2c context
 *  @param hz The bus frequency in hertz
 *
 *  @return maa_result_t the maa result.
 */
maa_result_t maa_i2c_frequency(maa_i2c_context dev, int hz);

/** Read from an i2c context
 *
 *  @param dev the i2c context
 *  @param data pointer to the byte array to read data in to
 *  @param length max number of bytes to read
 *
 *  @return maa_result_t the maa result.
 */
maa_result_t maa_i2c_read(maa_i2c_context dev, uint8_t *data, int length);

/** Read a single byte from the i2c context
 *
 *  @param dev the i2c context
 *
 *  @return byte the result of the read or -1 if failed.
 */
uint8_t maa_i2c_read_byte(maa_i2c_context dev);

/** Write to an i2c context
 *
 *  @param dev the i2c context
 *  @param data pointer to the byte array to be written
 *  @param length the number of bytes to transmit
 *
 *  @return maa_result_t the maa result.
 */
maa_result_t maa_i2c_write(maa_i2c_context dev, const uint8_t *data, int length);

/** Write a single byte to an i2c context
 *
 *  @param dev the i2c context
 *  @data the byte to write
 *
 *  @return maa_result_t the maa result.
 */
maa_result_t maa_i2c_write_byte(maa_i2c_context dev, const uint8_t data);

/** Sets the i2c context address.
 *
 *  @param dev the i2c context
 *  @param address The address to set for the slave (ignoring the least
 *  signifcant bit). If set to 0, the slave will only respond to the
 *  general call address.
 *
 *  @return maa_result_t the maa result.
 */
maa_result_t maa_i2c_address(maa_i2c_context dev, int address);

/** De-inits an maa_i2c_context device
 *
 *  @param dev the i2c context
 *
 *  @return maa_result_t the maa result.
 */
maa_result_t maa_i2c_stop(maa_i2c_context dev);

#ifdef __cplusplus
}
#endif
