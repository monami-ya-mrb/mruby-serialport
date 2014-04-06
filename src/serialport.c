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

#include "mruby.h"
#include "mruby/hash.h"
#include "mruby/khash.h"
#include "mruby/class.h"
#include "mruby/array.h"
#include "mruby/string.h"
#include "mruby/variable.h"

#include "serialport.h"
#include "serialport-impl.h"

static mrb_sym sym_rts;
static mrb_sym sym_dtr;
static mrb_sym sym_cts;
static mrb_sym sym_dsr;
static mrb_sym sym_dcd;
static mrb_sym sym_ri;

mrb_value
mrb_serial_baud(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_baud(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_break(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_create(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_cts(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_data_bits(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_data_bits(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_dcd(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_dsr(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_dtr(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_dtr(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_flow_control(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_flow_control(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_get_modem_params(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_get_signals(mrb_state *mrb, mrb_value val)
{
  struct line_signals_t signals;
  mrb_value hash;

  mrb_serial_get_signals_impl(mrb, &signals);

  hash = mrb_hash_new(mrb);

#if 0 /* windows */
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_rts), mrb_fixnum_value(signals.rts));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_dtr), mrb_fixnum_value(signals.dtr));
#endif
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_cts), mrb_fixnum_value(signals.cts));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_dsr), mrb_fixnum_value(signals.dsr));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_dcd), mrb_fixnum_value(signals.dcd));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_ri),  mrb_fixnum_value(signals.ri));

  return hash;
}

mrb_value
mrb_serial_modem_params(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_new(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_parity(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_parity(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_read_timeout(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_read_timeout(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_ri(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_rts(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_rts(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_modem_params(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_signals(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_stop_bits(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_stop_bits(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_write_timeout(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

mrb_value
mrb_serial_set_write_timeout(mrb_state *mrb, mrb_value val)
{
  mrb_raise(mrb, E_NOTIMP_ERROR, "Not implemented yet");
  return mrb_nil_value();
}

void
mrb_mruby_serialport_gem_init(mrb_state *mrb)
{
  struct RClass *io_class = mrb_class_get(mrb, "IO");
  struct RClass *serialport_class;

  mrb_assert(io != NULL);

  serialport_class = mrb_define_class(mrb, "SerialPort", io_class);

  mrb_define_method(mrb, serialport_class, "baud",             mrb_serial_baud,              MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "baud=",            mrb_serial_set_baud,          MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "break",            mrb_serial_break,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "create",           mrb_serial_create,             MRB_ARGS_ANY()); /* private mehtod */
  mrb_define_method(mrb, serialport_class, "cts",              mrb_serial_cts,               MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "data_bits",        mrb_serial_data_bits,         MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "data_bits=",       mrb_serial_set_data_bits,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "dcd",              mrb_serial_dcd,               MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "dsr",              mrb_serial_dsr,               MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "dtr",              mrb_serial_dtr,               MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "dtr=",             mrb_serial_set_dtr,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "flow_control",     mrb_serial_flow_control,      MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "flow_control=",    mrb_serial_set_flow_control,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "get_modem_params", mrb_serial_get_modem_params,  MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "get_signals",      mrb_serial_get_signals,       MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "modem_params",     mrb_serial_modem_params,      MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "modem_params=",    mrb_serial_set_modem_params,  MRB_ARGS_ANY());
  mrb_define_method(mrb, serialport_class, "new",              mrb_serial_new,               MRB_ARGS_ANY());
  mrb_define_method(mrb, serialport_class, "parity",           mrb_serial_parity,            MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "parity=",          mrb_serial_set_parity,        MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "read_timeout",     mrb_serial_read_timeout,      MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "read_timeout=",    mrb_serial_set_read_timeout,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "ri",               mrb_serial_ri,                MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "rts",              mrb_serial_rts,               MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "rts=",             mrb_serial_set_rts,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "set_modem_params", mrb_serial_set_modem_params,  MRB_ARGS_ANY());
  mrb_define_method(mrb, serialport_class, "signals",          mrb_serial_signals,           MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "stop_bits",        mrb_serial_stop_bits,         MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "stop_bits=",       mrb_serial_set_stop_bits,     MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "write_timeout",    mrb_serial_write_timeout,     MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "write_timeout=",   mrb_serial_set_write_timeout, MRB_ARGS_REQ(1));

  mrb_define_const(mrb, serialport_class, "NONE",    mrb_fixnum_value(MRBGEM_SERIALPORT_NONE));
  mrb_define_const(mrb, serialport_class, "HARD",    mrb_fixnum_value(MRBGEM_SERIALPORT_HARD));
  mrb_define_const(mrb, serialport_class, "SOFT",    mrb_fixnum_value(MRBGEM_SERIALPORT_SOFT));
  mrb_define_const(mrb, serialport_class, "SPACE",   mrb_fixnum_value(MRBGEM_SERIALPORT_SPACE));
  mrb_define_const(mrb, serialport_class, "MARK",    mrb_fixnum_value(MRBGEM_SERIALPORT_MARK));
  mrb_define_const(mrb, serialport_class, "EVEN",    mrb_fixnum_value(MRBGEM_SERIALPORT_EVEN));
  mrb_define_const(mrb, serialport_class, "ODD",     mrb_fixnum_value(MRBGEM_SERIALPORT_ODD));
#define TO_STRING(s) #s
  mrb_define_const(mrb, serialport_class, "VERSION", mrb_str_new_cstr(mrb, TO_STRING(MRBGEM_MRUBY_SERIALPORT_VERSION)));

  sym_rts = mrb_intern_lit(mrb, "rts");
  sym_dtr = mrb_intern_lit(mrb, "dtr");
  sym_cts = mrb_intern_lit(mrb, "cts");
  sym_dsr = mrb_intern_lit(mrb, "dsr");
  sym_dcd = mrb_intern_lit(mrb, "dcd");
  sym_ri  = mrb_intern_lit(mrb, "ri");
}

void
mrb_mruby_serialport_gem_final(mrb_state *mrb)
{
}
