//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef SM_HSM_H_
#define SM_HSM_H_

//============================================================================
//! @brief Typically, if you use 8051, you might do this:
//                        #define SM_HSM_ROM const code
//                        #define SM_HSM_RETT reentrant
//                    if you use Cortex-M3, you might do this:
//                        #define SM_HSM_ROM const
//                        #define SM_HSM_RETT
//! @cond INTERNAL

#ifndef SM_HSM_ROM
    #define SM_HSM_ROM const
#endif // SM_HSM_ROM

#ifndef SM_HSM_RETT
    #define SM_HSM_RETT
#endif // SM_HSM_RETT

//! @endcond

//============================================================================
//! @brief Event processing return.
//! @cond INTERNAL

typedef unsigned char SM_RetState;
#define SM_RET_HANDLED 0
#define SM_RET_TRAN    1
#define SM_RET_SUPER   2
#define SM_RET_TRAN_HIST 3

//! @endcond

//============================================================================
//! @brief UML Top-Initial handler, Entry/Exit handler, nomal state handler.
//! @cond INTERNAL

typedef void        (*SM_ActionHandler)(void * const me) SM_HSM_RETT;
typedef SM_RetState (*SM_StateHandler) (void * const me,
                                        void const * const e) SM_HSM_RETT;

//! @endcond

//............................................................................
//! @class SM_HsmState
struct SM_HsmState {
    struct SM_HsmState SM_HSM_ROM * super;
    struct SM_HsmState SM_HSM_ROM * (*init_)(void * const me) SM_HSM_RETT;
    SM_ActionHandler entry_;
    SM_ActionHandler exit_;
    SM_StateHandler handler_;
};

//............................................................................
//! @brief Struct type package.
//! @cond INTERNAL

typedef struct SM_HsmState SM_HSM_ROM SM_HsmState;
typedef struct SM_HsmState SM_HSM_ROM * SM_StatePtr;
typedef SM_StatePtr (*SM_InitHandler)(void * const me) SM_HSM_RETT;

//! @endcond

//============================================================================
//! @class SM_Hsm
//! @extends SM_HsmState
typedef struct SM_Hsm {
    SM_StatePtr curr; //!< @private @memberof SM_Hsm
    SM_StatePtr next; //!< @private @memberof SM_Hsm
} SM_Hsm;

//............................................................................
#define _SM_HANDLED()     (SM_RET_HANDLED)
#define _SM_SUPER()       (SM_RET_SUPER)
#define _SM_TRAN(target_) ((((SM_Hsm *)(me))->next) = (target_), SM_RET_TRAN)
#define _SM_TRAN_HIST(hist_) ((((SM_Hsm *)(me))->next) = (hist_), SM_RET_TRAN_HIST)
#define _SM_INIT(target_) (target_) // TOP-INIT && STATE-INIT

//============================================================================
// Deepest nest level for HSM, TOP state exclude
#ifndef SM_MAX_NEST_DEPTH_
    #define SM_MAX_NEST_DEPTH_ 5
#endif // SM_MAX_NEST_DEPTH_

//............................................................................
//! @brief Virtual pointer of SM_Hsm_init_ and SM_Hsm_dispatch_.
//! @cond INTERNAL

typedef void (*VC_Handler)(void * const me, void const * const e) SM_HSM_RETT;

//! @endcond

//============================================================================
//! @static @public @memberof SM_Hsm
void SM_Hsm_init_(SM_Hsm * const me, SM_InitHandler initial_) SM_HSM_RETT;

//! @static @public @memberof SM_Hsm
void SM_Hsm_dispatch_(SM_Hsm * const me,
                      void const * const e) SM_HSM_RETT;

//! @static @public @memberof SM_Hsm
SM_StatePtr SM_Hsm_childState_(SM_Hsm * const me,
                               SM_StatePtr parent) SM_HSM_RETT;

//============================================================================
// NOTE: History Transition (hist_tran)
//
// Consider test/smhsmtst.c, where s2 is a composite with init_→s211
// and s21 (child of s2) has init_→s211, forming s2→s21→s211.
//
// Suppose current state is s211.  The user wants to leave s2 and
// later come back to "where we were."
//
// The history variable lives inside the AO, just like QM-generated code:
//
//   typedef struct {
//       SM_Hsm sm_hsm_;
//       uint8_t foo;
//       SM_StatePtr hist_s2;   // history of s2
//       SM_StatePtr shist_s2;  // shallow history of s2
//   } SmHsmTst;
//
// --- Deep history: restore the innermost active sub-state ------------
//
//   void SmHsmTst_s2_exit_(SM_Hsm * const me) SM_HSM_RETT {
//       SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
//       ao->hist_s2 = me->curr;  // curr == s211, deepest active state
//   }
//
//   case H_SIG: {
//       SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
//       return _SM_TRAN_HIST(ao->hist_s2);
//   }
//
// --- Shallow history: restore only the direct child of s2 ------------
//
//   void SmHsmTst_s2_exit_(SM_Hsm * const me) SM_HSM_RETT {
//       SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
//       ao->shist_s2 = SM_Hsm_childState_(me, &SmHsmTst_s2);
//   }
//
//   case H_SIG: {
//       SmHsmTst *ao = container_of(me, SmHsmTst, sm_hsm_);
//       return _SM_TRAN_HIST(ao->shist_s2);
//   }

#endif // SM_HSM_H_
