//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "sm_hsm.h"
#include "smhsmtst.h"

//============================================================================
// Signal
enum SmHsmTst {
    SmHsmTst_dummy = 0,

    A_SIG,
    B_SIG,
    C_SIG,
    D_SIG,
    E_SIG,
    F_SIG,
    G_SIG,
    H_SIG,
    I_SIG,

    SmHsmTst_max
};

// Event
typedef struct {
    SM_HSM_EVT_TYPE super;  // Can be other type here
} SmHsmTstEvt;

// SmHsmTst ==================================================================
typedef struct {
    SM_Hsm super;

    VC_Handler init;
    VC_Handler dispatch;

    uint8_t foo;
} SmHsmTst;

//============================================================================
// UML-Top-Initial
static SM_StatePtr SmHsmTst_TOP_initial_(SmHsmTst * const me) SM_HSM_RETT;
// State-SmHsmTst_s
static SM_StatePtr SmHsmTst_s_init_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s_entry_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s_exit_(SmHsmTst * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s = {
    (SM_StatePtr)NULL,                    // super
    (SM_InitHandler)&SmHsmTst_s_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s_         // handler
};
// State-SmHsmTst_s1
static SM_StatePtr SmHsmTst_s1_init_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s1_entry_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s1_exit_(SmHsmTst * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s1_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s1 = {
    (SM_StatePtr)&SmHsmTst_s,              // super
    (SM_InitHandler)&SmHsmTst_s1_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s1_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s1_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s1_         // handler
};
// State-SmHsmTst_s11
static void SmHsmTst_s11_entry_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s11_exit_(SmHsmTst * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s11_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s11 = {
    (SM_StatePtr)&SmHsmTst_s1,              // super
    (SM_InitHandler)NULL,                   // init_
    (SM_ActionHandler)&SmHsmTst_s11_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s11_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s11_         // handler
};
// State-SmHsmTst_s2
static SM_StatePtr SmHsmTst_s2_init_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s2_entry_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s2_exit_(SmHsmTst * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s2_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s2 = {
    (SM_StatePtr)&SmHsmTst_s,              // super
    (SM_InitHandler)&SmHsmTst_s2_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s2_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s2_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s2_         // handler
};
// State-SmHsmTst_s21
static SM_StatePtr SmHsmTst_s21_init_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s21_entry_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s21_exit_(SmHsmTst * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s21_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s21 = {
    (SM_StatePtr)&SmHsmTst_s2,              // super
    (SM_InitHandler)&SmHsmTst_s21_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s21_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s21_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s21_         // handler
};
// State-SmHsmTst_s211
static void SmHsmTst_s211_entry_(SmHsmTst * const me) SM_HSM_RETT;
static void SmHsmTst_s211_exit_(SmHsmTst * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s211_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s211 = {
    (SM_StatePtr)&SmHsmTst_s21,              // super
    (SM_InitHandler)NULL,                    // init_
    (SM_ActionHandler)&SmHsmTst_s211_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s211_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s211_         // handler
};

//..........................................................................
// Instance
SmHsmTst SmHsmTst_inst;
SM_Hsm * AO_SmHsmTst = &SmHsmTst_inst.super;
// functions
static void SmHsmTst_init(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    (void)e;
    SM_Hsm_init_(SM_HSM_CAST(me), (SM_InitHandler)SmHsmTst_TOP_initial_);
}
static void SmHsmTst_dispatch(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    // Translate *me and *e.
    SM_Hsm_dispatch_(SM_HSM_CAST(me), e);
}
static void SmHsmTst_ctor(void) {
    SmHsmTst *me = &SmHsmTst_inst;

    me->init     = (VC_Handler)SmHsmTst_init;
    me->dispatch = (VC_Handler)SmHsmTst_dispatch;

    me->foo = 0;
}

// HSM implementations .....................................................
// UML-Top-Initial
static SM_StatePtr SmHsmTst_TOP_initial_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("top-INIT.");
    return _SM_INIT(&SmHsmTst_s2);
}
// State-SmHsmTst_s
static SM_StatePtr SmHsmTst_s_init_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s-INIT.");
    return _SM_INIT(&SmHsmTst_s11);
}
static void SmHsmTst_s_entry_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s-ENTRY.");
}
static void SmHsmTst_s_exit_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s-EXIT.");
}
static SM_RetState SmHsmTst_s_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    switch (SM_HSM_EVT_SIG(e)) {
        case I_SIG: {
            if (me->foo) {
                me->foo = 0U;
                printf("s-I.");
                return _SM_HANDLED();
            } else {
                return _SM_SUPER();
            }
        }
        case E_SIG: {
            printf("s-E.");
            return _SM_TRAN(&SmHsmTst_s11);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s1
static SM_StatePtr SmHsmTst_s1_init_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s1-INIT.");
    return _SM_INIT(&SmHsmTst_s11);
}
static void SmHsmTst_s1_entry_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s1-ENTRY.");
}
static void SmHsmTst_s1_exit_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s1-EXIT.");
}
static SM_RetState SmHsmTst_s1_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    switch (SM_HSM_EVT_SIG(e)) {
        case I_SIG: {
            printf("s1-I.");
            return _SM_HANDLED();
        }
        case B_SIG: {
            printf("s1-B.");
            return _SM_TRAN(&SmHsmTst_s11);
        }
        case A_SIG: {
            printf("s1-A.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case F_SIG: {
            printf("s1-F.");
            return _SM_TRAN(&SmHsmTst_s211);
        }
        case C_SIG: {
            printf("s1-C.");
            return _SM_TRAN(&SmHsmTst_s2);
        }
        case D_SIG: {
            if (!me->foo) {
                me->foo = 1U;
                printf("s1-D.");
                return _SM_TRAN(&SmHsmTst_s);
            } else {
                return _SM_SUPER();
            }
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s11
static void SmHsmTst_s11_entry_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s11-ENTRY.");
}
static void SmHsmTst_s11_exit_(SmHsmTst * const me) SM_HSM_RETT{
    (void)me;
    printf("s11-EXIT.");
}
static SM_RetState SmHsmTst_s11_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    switch (SM_HSM_EVT_SIG(e)) {
        case H_SIG: {
            printf("s11-H.");
            return _SM_TRAN(&SmHsmTst_s);
        }
        case D_SIG: {
            if (me->foo) {
                me->foo = 0U;
                printf("s11-D.");
                return _SM_TRAN(&SmHsmTst_s1);
            } else {
                return _SM_SUPER();
            }
        }
        case G_SIG: {
            printf("s11-G.");
            return _SM_TRAN(&SmHsmTst_s211);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s2
static SM_StatePtr SmHsmTst_s2_init_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s2-INIT.");
    return _SM_INIT(&SmHsmTst_s211);
}
static void SmHsmTst_s2_entry_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s2-ENTRY.");
}
static void SmHsmTst_s2_exit_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s2-EXIT.");
}
static SM_RetState SmHsmTst_s2_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    switch (SM_HSM_EVT_SIG(e)) {
        case I_SIG: {
            if (!me->foo) {
                me->foo = 1U;
                printf("s2-I.");
                return _SM_HANDLED();
            } else {
                return _SM_SUPER();
            }
        }
        case C_SIG: {
            printf("s2-C.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case F_SIG: {
            printf("s2-F.");
            return _SM_TRAN(&SmHsmTst_s11);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s21
static SM_StatePtr SmHsmTst_s21_init_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s21-INIT.");
    return _SM_INIT(&SmHsmTst_s211);
}
static void SmHsmTst_s21_entry_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s21-ENTRY.");
}
static void SmHsmTst_s21_exit_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s21-EXIT.");
}
static SM_RetState SmHsmTst_s21_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    switch (SM_HSM_EVT_SIG(e)) {
        case G_SIG: {
            printf("s21-G.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case A_SIG: {
            printf("s21-A.");
            return _SM_TRAN(&SmHsmTst_s21);
        }
        case B_SIG: {
            printf("s21-B.");
            return _SM_TRAN(&SmHsmTst_s211);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s211
static void SmHsmTst_s211_entry_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s211-ENTRY.");
}
static void SmHsmTst_s211_exit_(SmHsmTst * const me) SM_HSM_RETT {
    (void)me;
    printf("s211-EXIT.");
}
static SM_RetState SmHsmTst_s211_(SmHsmTst * const me, SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT {
    switch (SM_HSM_EVT_SIG(e)) {
        case H_SIG: {
            printf("s211-H.");
            return _SM_TRAN(&SmHsmTst_s);
        }
        case D_SIG: {
            printf("s211-D.");
            return _SM_TRAN(&SmHsmTst_s21);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

//..........................................................................
static void SM_Hsm_test_dispatch(SM_HSM_SIGNAL sig) {
    SM_HSM_EVT_TYPE e;
    e.sig = sig;
    (*SmHsmTst_inst.dispatch)(&SmHsmTst_inst, &e);
}
void SmHsmTst_test(void) {
    // Constructor
    SmHsmTst_ctor();

    // Top initial tran
    (*SmHsmTst_inst.init)(&SmHsmTst_inst, (SM_HSM_EVT_TYPE *)0);

    // // Event Dipatch - A
    // printf("\n");
    // SM_Hsm_test_dispatch(A_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(B_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(D_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(E_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(I_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(F_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(I_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(I_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(F_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(A_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(B_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(D_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(D_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(E_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(G_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(H_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(H_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(C_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(G_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(C_SIG);
    // printf("\n");
    // SM_Hsm_test_dispatch(C_SIG);
    // printf("\n");

    // Event Dipatch - B
    printf("\n");
    SM_Hsm_test_dispatch(G_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(I_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(A_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(D_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(D_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(C_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(E_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(E_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(G_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(I_SIG);
    printf("\n");
    SM_Hsm_test_dispatch(I_SIG);
    printf("\n");
}
