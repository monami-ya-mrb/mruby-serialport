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

#include "serialport-impl.h"

static int
get_fd_helper(mrb_state *mrb)
{
  /* TODO: implement */
  return -1;
}

void
mrb_serial_break_impl(mrb_state *mrb, mrb_int time)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

mrb_int
mrb_serial_flow_control_impl(mrb_state *mrb)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

void
mrb_serial_set_flow_control_impl(mrb_state *mrb, mrb_int flow_control)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

mrb_int
mrb_read_timeout_impl(mrb_state *mrb)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

void
mrb_set_read_timeout_impl(mrb_state *mrb, mrb_int time)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

mrb_int
mrb_write_timeout_impl(mrb_state *mrb)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

void
mrb_set_write_timeout_impl(mrb_state *mrb, mrb_int time)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

void
mrb_serial_get_modem_params_impl(mrb_state *mrb, struct modem_params_t *modem_params)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

void
mrb_serial_get_signals_impl(mrb_state *mrb, struct line_signals_t *signals)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

mrb_value
mrb_serial_set_modem_params_impl(mrb_state *mrb, struct modem_params_t *modem_params)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

void
mrb_serial_set_signals_impl(mrb_state *mrb, struct line_signals_t *signals)
{
  int fd;
  fd = get_fd_helper(mrb);

  /* TODO: implement */
}

