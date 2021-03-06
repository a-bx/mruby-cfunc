/*
** cfunc-mruby - Interface to C functions on mruby
**
** Copyright (c) MobiRuby developers 2012-
**
** Permission is hereby granted, free of charge, to any person obtaining
** a copy of this software and associated documentation files (the
** "Software"), to deal in the Software without restriction, including
** without limitation the rights to use, copy, modify, merge, publish,
** distribute, sublicense, and/or sell copies of the Software, and to
** permit persons to whom the Software is furnished to do so, subject to
** the following conditions:
**
** The above copyright notice and this permission notice shall be
** included in all copies or substantial portions of the Software.
**
** THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
** EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
** MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
** IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
** CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
** TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
** SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
** [ MIT license: http://www.opensource.org/licenses/mit-license.php ]
*/

#ifndef cfunc_h
#define cfunc_h

#include "mruby.h"

struct cfunc_state {
    struct RClass *namespace;
    
    struct RClass *type_class;
    struct RClass *void_class;
    struct RClass *uint8_class;
    struct RClass *sint8_class;
    struct RClass *uint16_class;
    struct RClass *sint16_class;
    struct RClass *uint32_class;
    struct RClass *sint32_class;
    struct RClass *uint64_class;
    struct RClass *sint64_class;
    struct RClass *float_class;
    struct RClass *double_class;
    struct RClass *pointer_class;
    struct RClass *struct_class;
    struct RClass *closure_class;
    struct RClass *rubyvm_class;
    struct RClass *rubyvm_task_class;

    void (*mrb_state_init)(mrb_state*);
};

void init_cfunc_module(mrb_state *mrb, void (*mrb_state_init)(mrb_state*));

/* offset of cfunc_state in mrb->ud */
extern size_t cfunc_state_offset;

/* service function for setting cfunc_state_offset */
#define cfunc_offsetof(TYPE, MEMBER) ((size_t) &((TYPE *)0)->MEMBER)

/*
example:

struct mrb_state_ud {
    struct cfunc_state cfunc_state;
};

cfunc_state_offset = cfunc_offsetof(struct mrb_state_ud, cfunc_state);

mrb_state *mrb = mrb_open();
mrb->ud = malloc(sizeof(struct mrb_state_ud));

init_cfunc_module(mrb);
*/


static inline struct cfunc_state *
cfunc_state(mrb_state* mrb)
{
  return (struct cfunc_state *)(mrb->ud + cfunc_state_offset);
}

#endif
