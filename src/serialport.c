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


static mrb_sym sym_baud;
static mrb_sym sym_data_bits;
static mrb_sym sym_stop_bits;
static mrb_sym sym_parity;

static mrb_sym sym_rts;
static mrb_sym sym_dtr;
static mrb_sym sym_cts;
static mrb_sym sym_dsr;
static mrb_sym sym_dcd;
static mrb_sym sym_ri;

static mrb_value
mrb_serial_create_port(mrb_state *mrb, mrb_value self)
{
  mrb_int fd;

  fd = mrb_serial_create_port_impl(mrb, self);

  return mrb_fixnum_value(fd);
}

static mrb_value
mrb_serial_break(mrb_state *mrb, mrb_value self)
{
  mrb_int time;

  mrb_get_args(mrb, "i", &time);

  mrb_serial_break_impl(mrb, self, time);

  return mrb_nil_value();
}

static mrb_value
mrb_serial_set_dtr(mrb_state *mrb, mrb_value self)
{
  struct line_signals_t signals = { 0 };
  mrb_int dtr;

  mrb_get_args(mrb, "i", &dtr);

  switch (dtr) {
  case 0:
    signals.dtr = -1;
    break;
  case 1:
    signals.dtr = 1;
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Must be 0 or 1.");
    break;
  }

  mrb_serial_set_signals_impl(mrb, self, &signals);

  return mrb_fixnum_value(dtr);
}

static mrb_value
mrb_serial_flow_control(mrb_state *mrb, mrb_value self)
{
  mrb_int flow_control;

  flow_control = mrb_serial_flow_control_impl(mrb, self);

  return mrb_fixnum_value(flow_control);
}

static mrb_value
mrb_serial_set_flow_control(mrb_state *mrb, mrb_value self)
{
  mrb_int flow_control;

  mrb_get_args(mrb, "i", &flow_control);

  mrb_serial_set_flow_control_impl(mrb, self, flow_control);

  return mrb_fixnum_value(flow_control);
}

static mrb_value
mrb_serial_get_modem_params(mrb_state *mrb, mrb_value self)
{
  struct modem_params_t modem_params;
  mrb_value hash;

  mrb_serial_get_modem_params_impl(mrb, self, &modem_params);

  hash = mrb_hash_new(mrb);

  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_baud),      mrb_fixnum_value(modem_params.baud_rate));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_data_bits), mrb_fixnum_value(modem_params.data_bits));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_stop_bits), mrb_fixnum_value(modem_params.stop_bits));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_parity),    mrb_fixnum_value(modem_params.parity));

  return hash;
}

static mrb_value
mrb_serial_get_signals(mrb_state *mrb, mrb_value self)
{
  struct line_signals_t signals;
  mrb_value hash;

  mrb_serial_get_signals_impl(mrb, self, &signals);

  hash = mrb_hash_new(mrb);

#if 1 /* not windows */
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_rts), mrb_fixnum_value(signals.rts));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_dtr), mrb_fixnum_value(signals.dtr));
#endif
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_cts), mrb_fixnum_value(signals.cts));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_dsr), mrb_fixnum_value(signals.dsr));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_dcd), mrb_fixnum_value(signals.dcd));
  mrb_hash_set(mrb, hash, mrb_symbol_value(sym_ri),  mrb_fixnum_value(signals.ri));

  return hash;
}

static mrb_value
mrb_serial_read_timeout(mrb_state *mrb, mrb_value self)
{
  return mrb_read_timeout_impl(mrb, self);
}

static mrb_value
mrb_serial_set_read_timeout(mrb_state *mrb, mrb_value self)
{
  mrb_int time;

  mrb_get_args(mrb, "i", &time);

  mrb_set_read_timeout_impl(mrb, self, time);

  return mrb_fixnum_value(time);
}

static mrb_value
mrb_serial_set_rts(mrb_state *mrb, mrb_value self)
{
  struct line_signals_t signals = { 0 };
  mrb_int rts;

  mrb_get_args(mrb, "i", &rts);

  switch (rts) {
  case 0:
    signals.rts = -1;
    break;
  case 1:
    signals.rts = 1;
    break;
  default:
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Must be 0 or 1.");
    break;
  }

  mrb_serial_set_signals_impl(mrb, self, &signals);

  return mrb_fixnum_value(rts);
}


static inline void
mrb_serial_set_modem_params_hash(mrb_state *mrb, mrb_value hash, struct modem_params_t *modem_params)
{
  mrb_value keys;
  mrb_int keys_len;
  mrb_int i;
  mrb_value key;
  mrb_value value;
  mrb_int int_value;

  keys = mrb_hash_keys(mrb, hash);
  keys_len = RARRAY_LEN(keys);

  for (i = 0; i < keys_len; i++) {
    mrb_value cmp;
    key = mrb_ary_entry(keys, i);

    switch (mrb_type(key)) {
    case MRB_TT_STRING:
      cmp = mrb_str_intern(mrb, key);
      break;
    case MRB_TT_SYMBOL:
      cmp = key;
      break;
    default:
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid key `%S'.", key);
    }

    value = mrb_hash_get(mrb, hash, key);
    if (mrb_type(value) != MRB_TT_FIXNUM) {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid value `%S'.", value);
    }
    int_value = mrb_fixnum(value);

    if (mrb_symbol(cmp) == sym_baud) {
      modem_params->baud_rate = int_value;
    }
    else if (mrb_symbol(cmp) == sym_data_bits) {
      modem_params->data_bits = int_value;
    }
    else if (mrb_symbol(cmp) == sym_stop_bits) {
      modem_params->stop_bits = int_value;
    }
    else if (mrb_symbol(cmp) == sym_parity) {
      modem_params->parity = int_value;
    }
    else {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid key `%S'.", key);
    }
  }
}

static inline void
mrb_serial_set_modem_params_args(mrb_state *mrb, int argc, mrb_value *argv, struct modem_params_t *modem_params)
{
  mrb_int previous_data_bits;

  previous_data_bits = modem_params->data_bits;

  /* It's guaranteed argc is more than 1 by mrb_serial_set_modem_params(). */

  if (mrb_nil_p(argv[0])) {
    /* Do nothing. Keep previous baud_rate parameter. */
  } else {
    if (mrb_type(argv[0]) == MRB_TT_FIXNUM) {
      modem_params->baud_rate = mrb_fixnum(argv[0]);
    }
    else {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid value `%S' for baud_rate.", argv[0]);
    }
  }

  if (argc > 1) {
    if (mrb_type(argv[1]) == MRB_TT_FIXNUM) {
      modem_params->data_bits = mrb_fixnum(argv[1]);
    }
    else {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid value `%S' for data_bits.", argv[1]);
    }
  }
  else {
    modem_params->data_bits = 8;
  }

  if (argc > 2) {
    if (mrb_type(argv[2]) == MRB_TT_FIXNUM) {
      modem_params->stop_bits = mrb_fixnum(argv[2]);
    }
    else {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid value `%S' for stop_bits.", argv[2]);
    }
  }
  else {
    modem_params->stop_bits = 1;
  }
    
  if (argc > 3) {
    if (mrb_type(argv[3]) == MRB_TT_FIXNUM) {
      modem_params->parity = mrb_fixnum(argv[3]);
    }
    else {
      mrb_raisef(mrb, E_ARGUMENT_ERROR, "Invalid value `%S' for parity.", argv[3]);
    }
  }
  else {
    modem_params->parity = (previous_data_bits == 8) ? MRBGEM_SERIALPORT_NONE : MRBGEM_SERIALPORT_EVEN;
  }

  if (argc > 4) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "Too many arguments.");
  }
}

static mrb_value
mrb_serial_set_modem_params(mrb_state *mrb, mrb_value self)
{
  mrb_value *argv;
  int argc;
  struct modem_params_t modem_params;
  mrb_value result;

  mrb_get_args(mrb, "*", &argv, &argc);

  if (argc == 0) {
    result = self;
  }
  else {
      mrb_serial_get_modem_params_impl(mrb, self, &modem_params);

      if (argc == 1 && mrb_type(argv[0]) == MRB_TT_HASH) {
	mrb_serial_set_modem_params_hash(mrb, argv[0], &modem_params);
      }
      else {
	mrb_serial_set_modem_params_args(mrb, argc, argv, &modem_params);
      }

      if (modem_params.baud_rate < 50 ||
	  modem_params.baud_rate > 256000) {
	mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid value for baud_rate.");
      }

      if (modem_params.data_bits < 4 ||
	  modem_params.data_bits > 8) {
	mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid value for data_bits.");
      }
      if (modem_params.stop_bits != 1 &&
	  modem_params.stop_bits != 2) {
	mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid value for stop_bits.");
      }

      if (modem_params.parity != MRBGEM_SERIALPORT_NONE &&
	  modem_params.parity != MRBGEM_SERIALPORT_EVEN &&
	  modem_params.parity != MRBGEM_SERIALPORT_ODD  &&
	  modem_params.parity != MRBGEM_SERIALPORT_MARK &&
	  modem_params.parity != MRBGEM_SERIALPORT_SPACE) {
	mrb_raise(mrb, E_ARGUMENT_ERROR, "Invalid value for parity.");
      }

      mrb_serial_set_modem_params_impl(mrb, self, & modem_params);

      result = argv[0];
  }

  return result;
}

static mrb_value
mrb_serial_write_timeout(mrb_state *mrb, mrb_value self)
{
  mrb_int time;

  time = mrb_write_timeout_impl(mrb, self);

  return mrb_fixnum_value(time);
}

static mrb_value
mrb_serial_set_write_timeout(mrb_state *mrb, mrb_value self)
{
  mrb_int time;

  mrb_get_args(mrb, "i", &time);

  mrb_set_write_timeout_impl(mrb, self, time);

  return mrb_fixnum_value(time);
}

void
mrb_mruby_serialport_gem_init(mrb_state *mrb)
{
  struct RClass *io_class = mrb_class_get(mrb, "IO");
  struct RClass *serialport_class;

  mrb_assert(io_class != NULL);

  serialport_class = mrb_define_class(mrb, "SerialPort", io_class);

  sym_baud      = mrb_intern_lit(mrb, "baud");
  sym_data_bits = mrb_intern_lit(mrb, "data_bits");
  sym_stop_bits = mrb_intern_lit(mrb, "stop_bits");
  sym_parity    = mrb_intern_lit(mrb, "parity");

  sym_rts = mrb_intern_lit(mrb, "rts");
  sym_dtr = mrb_intern_lit(mrb, "dtr");
  sym_cts = mrb_intern_lit(mrb, "cts");
  sym_dsr = mrb_intern_lit(mrb, "dsr");
  sym_dcd = mrb_intern_lit(mrb, "dcd");
  sym_ri  = mrb_intern_lit(mrb, "ri");

  mrb_define_method(mrb, serialport_class, "create_port", mrb_serial_create_port, MRB_ARGS_REQ(1));

  mrb_define_method(mrb, serialport_class, "break",            mrb_serial_break,             MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "dtr=",             mrb_serial_set_dtr,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "flow_control",     mrb_serial_flow_control,      MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "flow_control=",    mrb_serial_set_flow_control,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "get_modem_params", mrb_serial_get_modem_params,  MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "get_signals",      mrb_serial_get_signals,       MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "read_timeout",     mrb_serial_read_timeout,      MRB_ARGS_NONE());
  mrb_define_method(mrb, serialport_class, "read_timeout=",    mrb_serial_set_read_timeout,  MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "rts=",             mrb_serial_set_rts,           MRB_ARGS_REQ(1));
  mrb_define_method(mrb, serialport_class, "set_modem_params", mrb_serial_set_modem_params,  MRB_ARGS_ANY());
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

}

void
mrb_mruby_serialport_gem_final(mrb_state *mrb)
{
}
