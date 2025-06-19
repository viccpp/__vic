// Config library macros, mainly for using with C++ modules
//
// Platform: ISO C++ 98
// $Id$
//
// (c) __vic 2025

#ifndef __VIC_CONFIG_PARSER_MACROS_H
#define __VIC_CONFIG_PARSER_MACROS_H

#define __VIC_REGISTER_CONFIG_PARAM(c,p) this->register_param((c).p, #p)
#define __VIC_REGISTER_CONFIG_PARAM_VP(c,p,vp) this->register_param<vp>((c).p, #p)
#define __VIC_REGISTER_COMPLEX_CONFIG_PARAM(c,p,cp) this->register_complex_param<cp>((c).p, #p)

#endif // header guard
