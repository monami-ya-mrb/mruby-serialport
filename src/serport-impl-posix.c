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

#include <fcntl.h>
#include <termios.h>
#include <sys/ioctl.h>
#include "serialport-impl.h"

static int
get_fd_helper(mrb_state *mrb, mrb_value self)
{
  return mrb_fixnum(mrb_funcall(mrb, self, "fileno", 0));
}

static inline void
serial_tcgetattr(mrb_state *mrb, mrb_value self, struct termios *params)
{
  int fd;

  fd = get_fd_helper(mrb, self);
  if (tcgetattr(fd, params) == -1) {
    mrb_raise(mrb, E_IO_ERROR, "tcgetattr");
  }
}

static inline void
serial_tcsetattr(mrb_state *mrb, mrb_value self, struct termios *params)
{
  int fd;

  fd = get_fd_helper(mrb, self);
  if (tcsetattr(fd, TCSANOW, params) == -1) {
    mrb_raise(mrb, E_IO_ERROR, "tcsetattr");
  }
}

static inline int
serial_convert_baud_rate(mrb_state *mrb, struct modem_params_t *modem_params)
{
  int baud_rate;

  switch(modem_params->baud_rate) {
  case     50: baud_rate =     B50; break;
  case     75: baud_rate =     B75; break;
  case    110: baud_rate =    B110; break;
  case    134: baud_rate =    B134; break;
  case    150: baud_rate =    B150; break;
  case    200: baud_rate =    B200; break;
  case    300: baud_rate =    B300; break;
  case    600: baud_rate =    B600; break;
  case   1200: baud_rate =   B1200; break;
  case   1800: baud_rate =   B1800; break;
  case   2400: baud_rate =   B2400; break;
  case   4800: baud_rate =   B4800; break;
  case   9600: baud_rate =   B9600; break;
  case  19200: baud_rate =  B19200; break;
  case  38400: baud_rate =  B38400; break;
#ifdef B57600
  case  57600: baud_rate =  B57600; break;
#endif
#ifdef B76800
  case  76800: baud_rate =  B76800; break;
#endif
#ifdef B115200
  case 115200: baud_rate = B115200; break;
#endif
#ifdef B230400
  case 230400: baud_rate = B230400; break;
#endif
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "unknown baud rate");
    baud_rate = 0; /* to supress a warning. */
    break;
  }

  return baud_rate;
}

void
mrb_serial_break_impl(mrb_state *mrb, mrb_value self, mrb_int time)
{
  int fd;
  fd = get_fd_helper(mrb, self);

  if (tcsendbreak(fd, time * 4 / 10) == -1) {   /* 0.4sec * time */
    mrb_raise(mrb, E_IO_ERROR, "tcsendbreak");
  }
}

mrb_int
mrb_serial_flow_control_impl(mrb_state *mrb, mrb_value self)
{
  struct termios params;
  mrb_int result = 0;

  serial_tcgetattr(mrb, self, &params);

  if (params.c_cflag & CRTSCTS) {
    result += MRBGEM_SERIALPORT_HARD;
  }

  if (params.c_iflag & (IXON | IXOFF | IXANY)) {
    result += MRBGEM_SERIALPORT_SOFT;
  }

  return result;
}

void
mrb_serial_set_flow_control_impl(mrb_state *mrb, mrb_value self, mrb_int flow_control)
{
  struct termios params;

  serial_tcgetattr(mrb, self, &params);

  if (flow_control & MRBGEM_SERIALPORT_HARD) {
    params.c_cflag |= CRTSCTS;
  }
  else {
    params.c_cflag &= ~CRTSCTS;
  }

  if (flow_control & MRBGEM_SERIALPORT_SOFT) {
    params.c_iflag |= (IXON | IXOFF | IXANY);
  }
  else {
    params.c_iflag &= ~(IXON | IXOFF | IXANY);
  }

  serial_tcsetattr(mrb, self, &params);
}

mrb_value
mrb_read_timeout_impl(mrb_state *mrb, mrb_value self)
{
  mrb_value result;
  struct termios params;

  serial_tcgetattr(mrb, self, &params);

  if (params.c_cc[VTIME] == 0 && params.c_cc[VMIN] == 0) {
    result = mrb_fixnum_value(-1);
  }

  if (MRB_INT_MAX / params.c_cc[VTIME] <= 100) {
    /* convert to float beacuse there is no Bignum on mruby */
    result = mrb_float_value(mrb, params.c_cc[VTIME] * 100.0);
  }
  else {
    result = mrb_fixnum_value(params.c_cc[VTIME] * 100);
  }

  return result;
}

void
mrb_set_read_timeout_impl(mrb_state *mrb, mrb_value self, mrb_int timeout)
{
  struct termios params;

  serial_tcgetattr(mrb, self, &params);

  if (timeout < 0) {
    params.c_cc[VTIME] = 0;
    params.c_cc[VMIN] = 0;
  }
  else if (timeout == 0) {
    params.c_cc[VTIME] = 0;
    params.c_cc[VMIN] = 1;
  }
  else {
    params.c_cc[VTIME] = (timeout + 50) / 100;
    params.c_cc[VMIN] = 0;
  }

  serial_tcgetattr(mrb, self, &params);
}

mrb_int
mrb_write_timeout_impl(mrb_state *mrb, mrb_value self)
{
  int fd;
  fd = get_fd_helper(mrb, self);

  mrb_raise(mrb, E_NOTIMP_ERROR, "not implemented");

  return 0; /* NOT REACHED */
}

void
mrb_set_write_timeout_impl(mrb_state *mrb, mrb_value self, mrb_int time)
{
  int fd;
  fd = get_fd_helper(mrb, self);

  mrb_raise(mrb, E_NOTIMP_ERROR, "not implemented");
}

void
mrb_serial_get_modem_params_impl(mrb_state *mrb, mrb_value self, struct modem_params_t *modem_params)
{
  struct termios params;

  serial_tcgetattr(mrb, self, &params);

  switch (cfgetospeed(&params)) {
  case B50:     modem_params->baud_rate = 50;    break;
  case B75:     modem_params->baud_rate = 75;    break;
  case B110:    modem_params->baud_rate = 110;   break;
  case B134:    modem_params->baud_rate = 134;   break;
  case B150:    modem_params->baud_rate = 150;   break;
  case B200:    modem_params->baud_rate = 200;   break;
  case B300:    modem_params->baud_rate = 300;   break;
  case B600:    modem_params->baud_rate = 600;   break;
  case B1200:   modem_params->baud_rate = 1200;  break;
  case B1800:   modem_params->baud_rate = 1800;  break;
  case B2400:   modem_params->baud_rate = 2400;  break;
  case B4800:   modem_params->baud_rate = 4800;  break;
  case B9600:   modem_params->baud_rate = 9600;  break;
  case B19200:  modem_params->baud_rate = 19200; break;
  case B38400:  modem_params->baud_rate = 38400; break;
#ifdef B57600
  case B57600:  modem_params->baud_rate = 57600; break;
#endif
#ifdef B76800
  case B76800:  modem_params->baud_rate = 76800; break;
#endif
#ifdef B115200
  case B115200: modem_params->baud_rate = 115200; break;
#endif
#ifdef B230400
  case B230400: modem_params->baud_rate = 230400; break;
#endif
  }

  switch(params.c_cflag & CSIZE) {
  case CS5:
    modem_params->data_bits = 5;
    break;
  case CS6:
    modem_params->data_bits = 6;
    break;
  case CS7:
    modem_params->data_bits = 7;
    break;
  case CS8:
    modem_params->data_bits = 8;
    break;
  default:
    modem_params->data_bits = 0;
    break;
  }

  modem_params->stop_bits = (params.c_cflag & CSTOPB ? 2 : 1);

  if (!(params.c_cflag & PARENB)) {
    modem_params->parity = MRBGEM_SERIALPORT_NONE;
  }
  else if (params.c_cflag & PARODD) {
    modem_params->parity = MRBGEM_SERIALPORT_ODD;
  }
  else {
    modem_params->parity = MRBGEM_SERIALPORT_EVEN;
  }
}

void
mrb_serial_get_signals_impl(mrb_state *mrb, mrb_value self, struct line_signals_t *signals)
{
  int fd;
  int line_status;

  fd = get_fd_helper(mrb, self);

  if (ioctl(fd, TIOCMGET, &line_status) == -1) {
    mrb_raise(mrb, E_IO_ERROR, "TIOCMGET");
  }

  signals->rts = (line_status & TIOCM_RTS ? 1 : 0);
  signals->dtr = (line_status & TIOCM_DTR ? 1 : 0);
  signals->cts = (line_status & TIOCM_CTS ? 1 : 0);
  signals->dsr = (line_status & TIOCM_DSR ? 1 : 0);
  signals->dcd = (line_status & TIOCM_CD  ? 1 : 0);
  signals->ri  = (line_status & TIOCM_RI  ? 1 : 0);
}

void
mrb_serial_set_modem_params_impl(mrb_state *mrb, mrb_value self, struct modem_params_t *modem_params)
{
  struct termios params;
  int baud_rate;
  int data_bits[] = { CS5, CS6, CS7, CS8 };

  serial_tcgetattr(mrb, self, &params);

  baud_rate = serial_convert_baud_rate(mrb, modem_params);
  cfsetispeed(&params, baud_rate);
  cfsetospeed(&params, baud_rate);

  if (modem_params->data_bits < 5 ||
      modem_params->data_bits > 8) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "unknown character size");
  }

  params.c_cflag &= ~CSIZE;
  params.c_cflag |= data_bits[modem_params->data_bits - 5];

  switch(modem_params->stop_bits) {
  case 1:
    params.c_cflag &= ~CSTOPB;
    break;
  case 2:
    params.c_cflag |= CSTOPB;
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "unknown number of stop bits");
    break;
  }

  switch(modem_params->parity) {
  case MRBGEM_SERIALPORT_EVEN:
    params.c_cflag |= PARENB;
    params.c_cflag &= ~PARODD;
    break;
  case MRBGEM_SERIALPORT_ODD:
    params.c_cflag |= PARENB;
    params.c_cflag |= PARODD;
    break;
  case MRBGEM_SERIALPORT_NONE:
    params.c_cflag &= ~PARENB;
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "unknown parity");
    break;
  }

  serial_tcsetattr(mrb, self, &params);
}


void
mrb_serial_set_signals_impl(mrb_state *mrb, mrb_value self, struct line_signals_t *signals)
{
  int fd, line_status;

  fd = get_fd_helper(mrb, self);

  if (ioctl(fd, TIOCMGET, &line_status) == -1) {
    mrb_raise(mrb, E_IO_ERROR, "TIOCMGET");
  }

  /* set: 1 = on, -1 = off, 0 = keep previous */
  if (signals->rts) {
    line_status &= (signals->rts == 1) ? TIOCM_RTS : ~TIOCM_RTS;
  }
  if (signals->dtr) {
    line_status &= (signals->dtr == 1) ? TIOCM_DTR : ~TIOCM_DTR;
  }
  if (signals->cts) {
    line_status &= (signals->cts == 1) ? TIOCM_CTS : ~TIOCM_CTS;
  }
  if (signals->dsr) {
    line_status &= (signals->dsr == 1) ? TIOCM_DSR : ~TIOCM_DSR;
  }
  if (signals->dcd) {
    line_status &= (signals->dcd == 1) ? TIOCM_CD  : ~TIOCM_CD;
  }
  if (signals->ri) {
    line_status &= (signals->ri  == 1) ? TIOCM_RI  : ~TIOCM_RI;
  }

 if (ioctl(fd, TIOCMSET, &line_status) == -1) {
   mrb_raise(mrb, E_IO_ERROR, "TIOCMSET");
 }
}

