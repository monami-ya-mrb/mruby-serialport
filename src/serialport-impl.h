/*
 * SerialPort class for mruby
 *
 * Copyright (c) 2014 Monami-ya LLC, Japan. and others
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#ifndef MRBGEM_MRBGEM_SERIALPORT_IMPL_H__
#define MRBGEM_MRBGEM_SERIALPORT_IMPL_H__

#include "mruby.h"
#include "mruby/ext/io.h"
#include "serialport.h"

struct modem_params_t {
  mrb_int baud_rate;
  mrb_int data_bits;
  mrb_int stop_bits;
  mrb_int parity;
};

struct line_signals_t {
  /* get: 1 = on,  0 = off
   * set: 1 = on, -1 = off, 0 = keep previous
   */
  mrb_int rts;
  mrb_int dtr;
  mrb_int cts;
  mrb_int dsr;
  mrb_int dcd;
  mrb_int ri;
};

void mrb_serial_break_impl(mrb_state *mrb, mrb_value self, mrb_int time);
mrb_int mrb_serial_flow_control_impl(mrb_state *mrb, mrb_value self);
void  mrb_serial_set_flow_control_impl(mrb_state *mrb, mrb_value self, mrb_int flow_control);
mrb_value mrb_read_timeout_impl(mrb_state *mrb, mrb_value self);
void mrb_set_read_timeout_impl(mrb_state *mrb, mrb_value self, mrb_int time);
mrb_int mrb_write_timeout_impl(mrb_state *mrb, mrb_value self);
void mrb_set_write_timeout_impl(mrb_state *mrb, mrb_value self, mrb_int time);
void mrb_serial_get_modem_params_impl(mrb_state *mrb, mrb_value self, struct modem_params_t *modem_params);
void mrb_serial_get_signals_impl(mrb_state *mrb, mrb_value self, struct line_signals_t *signals);
void mrb_serial_set_modem_params_impl(mrb_state *mrb, mrb_value self, struct modem_params_t *modem_params);
void mrb_serial_set_signals_impl(mrb_state *mrb, mrb_value self, struct line_signals_t *signals);

#endif /* MRBGEM_MRBGEM_SERIALPORT_IMPL_H__ */
