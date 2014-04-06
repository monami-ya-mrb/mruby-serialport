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

#ifndef MRBGEM_MRBGEM_SERIALPORT_H__
#define MRBGEM_MRBGEM_SERIALPORT_H__

#define MRBGEM_SERIALPORT_NONE   0
#define MRBGEM_SERIALPORT_HARD   1
#define MRBGEM_SERIALPORT_SOFT   2

#if 0 /* windows */
   #define MRBGEM_SERIALPORT_SPACE  SPACEPARITY
   #define MRBGEM_SERIALPORT_MARK   MARKPARITY
   #define MRBGEM_SERIALPORT_EVEN   EVENPARITY
   #define MRBGEM_SERIALPORT_ODD    ODDPARITY
#else
   #define MRBGEM_SERIALPORT_SPACE  0
   #define MRBGEM_SERIALPORT_MARK   0
   #define MRBGEM_SERIALPORT_EVEN   1
   #define MRBGEM_SERIALPORT_ODD    2
#endif


#endif /* MRBGEM_MRBGEM_SERIALPORT_H__ */
