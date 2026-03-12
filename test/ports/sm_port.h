//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef SM_PORT_H_
#define SM_PORT_H_

// SM_Hsm port. ==============================================================
// #define SM_HSM_ROM const
// #define SM_HSM_RETT
#include <stdbool.h>

//............................................................................
#include <stddef.h> // offsetof
#ifndef container_of
    #define container_of(ptr_, type_, member_) \
                        ((type_ *)((char *)(ptr_) - offsetof(type_, member_)))
#endif // container_of

// SM_Tracer port. ===========================================================

//============================================================================
#include "sm_hsm.h"

#endif // SM_PORT_H_
