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
    J_SIG,
    K_SIG,
    L_SIG,
    M_SIG,
    N_SIG,
    O_SIG,
    P_SIG,

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

    bool foo;

    // history variables
    SM_StatePtr hist_s2;   // shallow history of s2
    SM_StatePtr hist_s22;  // deep history of s22
} SmHsmTst;

//============================================================================
// Forward declares — state handlers
static SM_StatePtr SmHsmTst_TOP_initial_(SM_Hsm * const me) SM_HSM_RETT;

// s1
static SM_StatePtr SmHsmTst_s1_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s1_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s1_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s1_(SM_Hsm * const me,
                                SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s1 = {
    (SM_StatePtr)NULL,                     // super
    (SM_InitHandler)&SmHsmTst_s1_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s1_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s1_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s1_         // handler
};
// s11
static void SmHsmTst_s11_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s11_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s11_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s11 = {
    (SM_StatePtr)&SmHsmTst_s1,              // super
    (SM_InitHandler)NULL,                   // init_
    (SM_ActionHandler)&SmHsmTst_s11_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s11_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s11_         // handler
};
// s12
static void SmHsmTst_s12_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s12_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s12_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s12 = {
    (SM_StatePtr)&SmHsmTst_s1,              // super
    (SM_InitHandler)NULL,                   // init_
    (SM_ActionHandler)&SmHsmTst_s12_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s12_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s12_         // handler
};
// s2
static SM_StatePtr SmHsmTst_s2_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s2_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s2_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s2_(SM_Hsm * const me,
                                SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s2 = {
    (SM_StatePtr)NULL,                     // super (= top)
    (SM_InitHandler)&SmHsmTst_s2_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s2_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s2_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s2_         // handler
};
// s21
static void SmHsmTst_s21_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s21_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s21_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s21 = {
    (SM_StatePtr)&SmHsmTst_s2,              // super
    (SM_InitHandler)NULL,                   // init_
    (SM_ActionHandler)&SmHsmTst_s21_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s21_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s21_         // handler
};
// s22
static SM_StatePtr SmHsmTst_s22_init_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s22_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s22_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s22_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s22 = {
    (SM_StatePtr)&SmHsmTst_s2,              // super
    (SM_InitHandler)&SmHsmTst_s22_init_,    // init_
    (SM_ActionHandler)&SmHsmTst_s22_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s22_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s22_         // handler
};
// s221
static void SmHsmTst_s221_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s221_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s221_(SM_Hsm * const me,
                                  SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s221 = {
    (SM_StatePtr)&SmHsmTst_s22,              // super
    (SM_InitHandler)NULL,                    // init_
    (SM_ActionHandler)&SmHsmTst_s221_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s221_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s221_         // handler
};
// s222
static void SmHsmTst_s222_entry_(SM_Hsm * const me) SM_HSM_RETT;
static void SmHsmTst_s222_exit_(SM_Hsm * const me) SM_HSM_RETT;
static SM_RetState SmHsmTst_s222_(SM_Hsm * const me,
                                  SmHsmTstEvt const * const e) SM_HSM_RETT;
SM_HsmState SM_HSM_ROM SmHsmTst_s222 = {
    (SM_StatePtr)&SmHsmTst_s22,              // super
    (SM_InitHandler)NULL,                    // init_
    (SM_ActionHandler)&SmHsmTst_s222_entry_, // entry_
    (SM_ActionHandler)&SmHsmTst_s222_exit_,  // exit_
    (SM_StateHandler)&SmHsmTst_s222_         // handler
};

//..........................................................................
// Instance
static SmHsmTst SmHsmTst_inst;
// functions
static void SmHsmTst_init(SmHsmTst * const me,
                          SmHsmTstEvt const * const e) SM_HSM_RETT {
    (void)e;
    SM_Hsm_init_(&me->sm_hsm_, (SM_InitHandler)SmHsmTst_TOP_initial_);
}
static void SmHsmTst_dispatch(SmHsmTst * const me,
                              SmHsmTstEvt const * const e) SM_HSM_RETT {
    SM_Hsm_dispatch_(&me->sm_hsm_, e);
}
static void SmHsmTst_ctor(void) {
    SmHsmTst *me = &SmHsmTst_inst;

    me->init     = (VC_Handler)SmHsmTst_init;
    me->dispatch = (VC_Handler)SmHsmTst_dispatch;

    me->foo = false;
}

// HSM implementations .......................................................
// UML-Top-Initial
static SM_StatePtr SmHsmTst_TOP_initial_(SM_Hsm * const me) SM_HSM_RETT {
    SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
    ao->foo = false;
    BSP_print("top-INIT.");
    // init history to default children
    ao->hist_s2  = &SmHsmTst_s21;
    ao->hist_s22 = &SmHsmTst_s221;
    return _SM_INIT(&SmHsmTst_s1);
}

// s1 ........................................................................
static SM_StatePtr SmHsmTst_s1_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
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
static SM_RetState SmHsmTst_s1_(SM_Hsm * const me,
                                SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case A_SIG: {
            BSP_print("s1-A.");
            return _SM_TRAN(&SmHsmTst_s2);
        }
        case N_SIG: {
            SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
            BSP_print("s1-N.");
            return _SM_HIST(ao->hist_s22);
        }
        case L_SIG: {
            BSP_print("s1-L.");
            return _SM_TRAN(&SmHsmTst_s12);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s11 .......................................................................
static void SmHsmTst_s11_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s11-ENTRY.");
}
static void SmHsmTst_s11_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s11-EXIT.");
}
static SM_RetState SmHsmTst_s11_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case H_SIG: {
            BSP_print("s11-H.");
            return _SM_TRAN(&SmHsmTst_s12);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s12 .......................................................................
static void SmHsmTst_s12_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s12-ENTRY.");
}
static void SmHsmTst_s12_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s12-EXIT.");
}
static SM_RetState SmHsmTst_s12_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case I_SIG: {
            SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
            BSP_print("s12-I.");
            return _SM_HIST(ao->hist_s2);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s2 ........................................................................
static SM_StatePtr SmHsmTst_s2_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    return _SM_INIT(&SmHsmTst_s221);
}
static void SmHsmTst_s2_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s2-ENTRY.");
}
static void SmHsmTst_s2_exit_(SM_Hsm * const me) SM_HSM_RETT {
    SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
    BSP_print("s2-EXIT.");
    // save shallow history: direct child of s2
    ao->hist_s2 = SM_Hsm_childState_(me, &SmHsmTst_s2);
}
static SM_RetState SmHsmTst_s2_(SM_Hsm * const me,
                                SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case F_SIG: {
            BSP_print("s2-F.");
            return _SM_TRAN(&SmHsmTst_s21);
        }
        case G_SIG: {
            BSP_print("s2-G.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case K_SIG: {
            BSP_print("s2-K.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s21 .......................................................................
static void SmHsmTst_s21_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s21-ENTRY.");
}
static void SmHsmTst_s21_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s21-EXIT.");
}
static SM_RetState SmHsmTst_s21_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case J_SIG: {
            BSP_print("s21-J.");
            return _SM_TRAN(&SmHsmTst_s22);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s22 .......................................................................
static SM_StatePtr SmHsmTst_s22_init_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    return _SM_INIT(&SmHsmTst_s221);
}
static void SmHsmTst_s22_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s22-ENTRY.");
}
static void SmHsmTst_s22_exit_(SM_Hsm * const me) SM_HSM_RETT {
    SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
    BSP_print("s22-EXIT.");
    // save deep history: innermost active state
    ao->hist_s22 = me->curr;
}
static SM_RetState SmHsmTst_s22_(SM_Hsm * const me,
                                 SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case E_SIG: {
            SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
            if (!ao->foo) {
                ao->foo = true;
                BSP_print("s22-E.");
                return _SM_HANDLED();
            }
            return _SM_SUPER();
        }
        case M_SIG: {
            BSP_print("s22-M.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        case O_SIG: {
            BSP_print("s22-O.");
            return _SM_TRAN(&SmHsmTst_s222);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s221 ......................................................................
static void SmHsmTst_s221_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s221-ENTRY.");
}
static void SmHsmTst_s221_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s221-EXIT.");
}
static SM_RetState SmHsmTst_s221_(SM_Hsm * const me,
                                  SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case B_SIG: {
            BSP_print("s221-B.");
            return _SM_TRAN(&SmHsmTst_s221);
        }
        case C_SIG: {
            BSP_print("s221-C.");
            return _SM_TRAN(&SmHsmTst_s22);
        }
        case D_SIG: {
            BSP_print("s221-D.");
            return _SM_TRAN(&SmHsmTst_s2);
        }
        case E_SIG: {
            SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
            if (ao->foo) {
                ao->foo = false;
                BSP_print("s221-E.");
                return _SM_HANDLED();
            }
            return _SM_SUPER();
        }
        case J_SIG: {
            BSP_print("s221-J.");
            return _SM_TRAN(&SmHsmTst_s21);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

// s222 ......................................................................
static void SmHsmTst_s222_entry_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s222-ENTRY.");
}
static void SmHsmTst_s222_exit_(SM_Hsm * const me) SM_HSM_RETT {
    (void)me;
    BSP_print("s222-EXIT.");
}
static SM_RetState SmHsmTst_s222_(SM_Hsm * const me,
                                  SmHsmTstEvt const * const e) SM_HSM_RETT {
    switch (SMHSMTST_SIG(e)) {
        case P_SIG: {
            BSP_print("s222-P.");
            return _SM_TRAN(&SmHsmTst_s1);
        }
        default: {
            return _SM_SUPER();
        }
    }
}

//..........................................................................
// Expected output for sequence  A B C D E E F G H I J K L I M N O P N :
//
//  top-INIT.s1-ENTRY.s11-ENTRY.
//  s1-A.s11-EXIT.s1-EXIT.s2-ENTRY.s22-ENTRY.s221-ENTRY.
//  s221-B.s221-EXIT.s221-ENTRY.
//  s221-C.s221-EXIT.s221-ENTRY.
//  s221-D.s221-EXIT.s22-EXIT.s22-ENTRY.s221-ENTRY.
//  s22-E.
//  s221-E.
//  s2-F.s221-EXIT.s22-EXIT.s21-ENTRY.
//  s2-G.s21-EXIT.s2-EXIT.s1-ENTRY.s11-ENTRY.
//  s11-H.s11-EXIT.s12-ENTRY.
//  s12-I.s12-EXIT.s1-EXIT.s2-ENTRY.s21-ENTRY.
//  s21-J.s21-EXIT.s22-ENTRY.s221-ENTRY.
//  s2-K.s221-EXIT.s22-EXIT.s2-EXIT.s1-ENTRY.s11-ENTRY.
//  s1-L.s11-EXIT.s12-ENTRY.
//  s12-I.s12-EXIT.s1-EXIT.s2-ENTRY.s22-ENTRY.s221-ENTRY.
//  s22-M.s221-EXIT.s22-EXIT.s2-EXIT.s1-ENTRY.s11-ENTRY.
//  s1-N.s11-EXIT.s1-EXIT.s2-ENTRY.s22-ENTRY.s221-ENTRY.
//  s22-O.s221-EXIT.s222-ENTRY.
//  s222-P.s222-EXIT.s22-EXIT.s2-EXIT.s1-ENTRY.s11-ENTRY.
//  s1-N.s11-EXIT.s1-EXIT.s2-ENTRY.s22-ENTRY.s222-ENTRY.
//
static void SM_Hsm_test_dispatch(enum SmHsmTstSig sig) {
    SmHsmTstEvt e;
    e.sig = (uint8_t)sig;
    SmHsmTst_inst.dispatch(&SmHsmTst_inst, &e);
}
void SmHsmTst_test(void) {
    SmHsmTst_ctor();
    SmHsmTst_inst.init(&SmHsmTst_inst, (SmHsmTstEvt *)0);

    // A B C D E E F G H I J K L I M N O P N
    BSP_print("\n");
    SM_Hsm_test_dispatch(A_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(B_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(C_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(D_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(E_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(E_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(F_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(G_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(H_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(I_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(J_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(K_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(L_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(I_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(M_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(N_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(O_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(P_SIG);
    BSP_print("\n");
    SM_Hsm_test_dispatch(N_SIG);
    BSP_print("\n");
}
