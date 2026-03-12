//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#include "smhsmtst.h"

//============================================================================
// Signal
enum SmHsmTstSig {
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
    uint8_t sig;
} SmHsmTstEvt;
#define SMHSMTST_SIG(evt_) ((evt_)->sig)

// SmHsmTst ==================================================================
typedef struct {
    SM_Hsm sm_hsm_;

    VC_Handler init;
    VC_Handler dispatch;

    uint8_t foo;
} SmHsmTst;

//============================================================================
// UML-Top-Initial
static SM_StatePtr SmHsmTst_TOP_initial_(SM_Hsm * const me) SM_HSM_RETT;
// State-SmHsmTst_s
static SM_StatePtr SmHsmTst_s_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s = {
    (SM_StatePtr)NULL,                    // super
    (SM_InitHandler)&SmHsmTst_s_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s_         // handler
};
// State-SmHsmTst_s1
static SM_StatePtr SmHsmTst_s1_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s1_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s1_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s1_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s1 = {
    (SM_StatePtr)&SmHsmTst_s,              // super
    (SM_InitHandler)&SmHsmTst_s1_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s1_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s1_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s1_         // handler
};
// State-SmHsmTst_s11
static void SmHsmTst_s11_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s11_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s11_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s11 = {
    (SM_StatePtr)&SmHsmTst_s1,              // super
    (SM_InitHandler)NULL,                   // init_
    (SM_ActionHandler)&SmHsmTst_s11_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s11_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s11_         // handler
};
// State-SmHsmTst_s2
static SM_StatePtr SmHsmTst_s2_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s2_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s2_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s2_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s2 = {
    (SM_StatePtr)&SmHsmTst_s,              // super
    (SM_InitHandler)&SmHsmTst_s2_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s2_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s2_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s2_         // handler
};
// State-SmHsmTst_s21
static SM_StatePtr SmHsmTst_s21_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s21_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s21_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s21_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s21 = {
    (SM_StatePtr)&SmHsmTst_s2,              // super
    (SM_InitHandler)&SmHsmTst_s21_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s21_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s21_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s21_         // handler
};
// State-SmHsmTst_s211
static void SmHsmTst_s211_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s211_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s211_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT;
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
SM_Hsm * AO_SmHsmTst = &SmHsmTst_inst.sm_hsm_;
// functions
static void SmHsmTst_init(SmHsmTst * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    (void)e;
    SM_Hsm_init_(&me->sm_hsm_, (SM_InitHandler)SmHsmTst_TOP_initial_);
}
static void SmHsmTst_dispatch(SmHsmTst * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    // Translate *me and *e.
    SM_Hsm_dispatch_(&me->sm_hsm_, e);
}
static void SmHsmTst_ctor(void) {
    SmHsmTst *me = &SmHsmTst_inst;

    me->init     = (VC_Handler)SmHsmTst_init;
    me->dispatch = (VC_Handler)SmHsmTst_dispatch;

    me->foo = 0;
}

// HSM implementations .....................................................
// UML-Top-Initial
static SM_StatePtr SmHsmTst_TOP_initial_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("top-INIT.");
    return _SM_INIT(&SmHsmTst_s2);
}
// State-SmHsmTst_s
static SM_StatePtr SmHsmTst_s_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s-INIT.");
    return _SM_INIT(&SmHsmTst_s11);
}
static void SmHsmTst_s_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s-ENTRY.");
}
static void SmHsmTst_s_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s-EXIT.");
}
static SM_RetState SmHsmTst_s_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case I_SIG: {
            if (container_of(me, SmHsmTst, sm_hsm_)->foo) {
                container_of(me, SmHsmTst, sm_hsm_)->foo = 0U;
                BSP_print("s-I.");
                return _SM_HANDLED();
            } else {
                return _SM_SUPER();
            }
        }
        case E_SIG: {
            BSP_print("s-E.");
            return _SM_TRAN(&SmHsmTst_s11);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s1
static SM_StatePtr SmHsmTst_s1_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s1-INIT.");
    return _SM_INIT(&SmHsmTst_s11);
}
static void SmHsmTst_s1_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s1-ENTRY.");
}
static void SmHsmTst_s1_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s1-EXIT.");
}
static SM_RetState SmHsmTst_s1_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case I_SIG: {
            BSP_print("s1-I.");
            return _SM_HANDLED();
        }
        case B_SIG: {
            BSP_print("s1-B.");
            return _SM_TRAN(&SmHsmTst_s11);
        }
        case A_SIG: {
            BSP_print("s1-A.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case F_SIG: {
            BSP_print("s1-F.");
            return _SM_TRAN(&SmHsmTst_s211);
        }
        case C_SIG: {
            BSP_print("s1-C.");
            return _SM_TRAN(&SmHsmTst_s2);
        }
        case D_SIG: {
            if (!container_of(me, SmHsmTst, sm_hsm_)->foo) {
                container_of(me, SmHsmTst, sm_hsm_)->foo = 1U;
                BSP_print("s1-D.");
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
static void SmHsmTst_s11_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s11-ENTRY.");
}
static void SmHsmTst_s11_exit_(SM_Hsm * const me) SM_HSM_RETT{
    (void)me;
    BSP_print("s11-EXIT.");
}
static SM_RetState SmHsmTst_s11_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case H_SIG: {
            BSP_print("s11-H.");
            return _SM_TRAN(&SmHsmTst_s);
        }
        case D_SIG: {
            if (container_of(me, SmHsmTst, sm_hsm_)->foo) {
                container_of(me, SmHsmTst, sm_hsm_)->foo = 0U;
                BSP_print("s11-D.");
                return _SM_TRAN(&SmHsmTst_s1);
            } else {
                return _SM_SUPER();
            }
        }
        case G_SIG: {
            BSP_print("s11-G.");
            return _SM_TRAN(&SmHsmTst_s211);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s2
static SM_StatePtr SmHsmTst_s2_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s2-INIT.");
    return _SM_INIT(&SmHsmTst_s211);
}
static void SmHsmTst_s2_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s2-ENTRY.");
}
static void SmHsmTst_s2_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s2-EXIT.");
}
static SM_RetState SmHsmTst_s2_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case I_SIG: {
            if (!container_of(me, SmHsmTst, sm_hsm_)->foo) {
                container_of(me, SmHsmTst, sm_hsm_)->foo = 1U;
                BSP_print("s2-I.");
                return _SM_HANDLED();
            } else {
                return _SM_SUPER();
            }
        }
        case C_SIG: {
            BSP_print("s2-C.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case F_SIG: {
            BSP_print("s2-F.");
            return _SM_TRAN(&SmHsmTst_s11);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s21
static SM_StatePtr SmHsmTst_s21_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s21-INIT.");
    return _SM_INIT(&SmHsmTst_s211);
}
static void SmHsmTst_s21_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s21-ENTRY.");
}
static void SmHsmTst_s21_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s21-EXIT.");
}
static SM_RetState SmHsmTst_s21_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case G_SIG: {
            BSP_print("s21-G.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case A_SIG: {
            BSP_print("s21-A.");
            return _SM_TRAN(&SmHsmTst_s21);
        }
        case B_SIG: {
            BSP_print("s21-B.");
            return _SM_TRAN(&SmHsmTst_s211);
        }
        default: {
            return _SM_SUPER();
        }
    }
}
// State-SmHsmTst_s211
static void SmHsmTst_s211_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s211-ENTRY.");
}
static void SmHsmTst_s211_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s211-EXIT.");
}
static SM_RetState SmHsmTst_s211_(SM_Hsm * const me, SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case H_SIG: {
            BSP_print("s211-H.");
            return _SM_TRAN(&SmHsmTst_s);
        }
        case D_SIG: {
            BSP_print("s211-D.");
            return _SM_TRAN(&SmHsmTst_s21);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

//..........................................................................
static void SM_Hsm_test_dispatch(enum SmHsmTstSig sig) {
    SmHsmTstEvt e;
    e.sig = sig;
    (*SmHsmTst_inst.dispatch)(&SmHsmTst_inst, &e);
}
void SmHsmTst_test(void) {
    // Constructor
    SmHsmTst_ctor();

    // Top initial tran
    (*SmHsmTst_inst.init)(&SmHsmTst_inst, (SmHsmTstEvt *)0);

    // // Event Dipatch - A
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(A_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(B_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(D_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(E_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(I_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(F_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(I_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(I_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(F_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(A_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(B_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(D_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(D_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(E_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(G_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(H_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(H_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(C_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(G_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(C_SIG);
    // BSP_print("\n");
    // SM_Hsm_test_dispatch(C_SIG);
    // BSP_print("\n");

    // Event Dipatch - B
    BSP_print("\n");
    SM_Hsm_test_dispatch(G_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(I_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(A_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(D_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(D_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(C_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(E_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(E_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(G_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(I_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(I_SIG);
    BSP_print("\n");
}
