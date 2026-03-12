//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "sm_port.h"
#include "bsp.h"

//============================================================================
void BSP_print(char const * const msg) {
    printf(msg);
}

// SM_ASSERT =================================================================
SM_NORETURN SM_onAssert(char const *module, int label) SM_RETT {
    fprintf(stderr, "ASSERT: %s:%d\n", module, label);
    exit(-1);
}
