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

/**
 * @defgroup Event types that the event dispatcher needs.
 *           You might define it when porting or use the default.
 *
 *           Need micros: SM_HSM_EVT_TYPE
 *                        SM_HSM_SIGNAL
 *                        SM_HSM_EVT_SIG(evt_)
 *
 * @{
 */

//............................................................................
//! @brief Event types that the event dispatcher needs.
//         You might define it when porting or use the default.
//         Need micros: SM_HSM_EVT_TYPE
//             SM_HSM_SIGNAL
//             SM_HSM_EVT_SIG(evt_)
//! @cond INTERNAL

#ifndef SM_HSM_SIGNAL
    typedef unsigned char SM_Hsm_Signal;
    #define SM_HSM_SIGNAL SM_Hsm_Signal
#endif // SM_HSM_SIGNAL

#ifndef SM_HSM_EVT_TYPE
//! @class SM_HsmEvt
typedef struct {
    SM_HSM_SIGNAL sig; //!< @private @memberof SM_HsmEvt
} SM_HsmEvt;
#define SM_HSM_EVT_TYPE SM_HsmEvt
#define SM_HSM_EVT_SIG(evt_)  ((evt_)->sig)
#endif // SM_HSM_EVT_TYPE

//! @endcond

//............................................................................
//! @brief Event processing return.
//! @cond INTERNAL

typedef unsigned char SM_RetState;
#define SM_RET_HANDLED 0
#define SM_RET_TRAN    1
#define SM_RET_SUPER   2

#define _SM_HANDLED()      (SM_RET_HANDLED)
#define _SM_SUPER()        (SM_RET_SUPER)
#define _SM_TRAN(target_) (SM_HSM_CAST(me)->next = (target_), SM_RET_TRAN)
#define _SM_INIT(target_)  (target_) // TOP-INIT && STATE-INIT

//! @endcond

//............................................................................
//! @brief Hsm State pointer.
//! @note Expand to struct SM_HsmState SM_HSM_ROM * in application.
//! @cond INTERNAL

struct SM_HsmState;
typedef struct SM_HsmState SM_HSM_ROM * SM_StatePtr;

//! @endcond

//............................................................................
//! @brief UML Top-Initial handler, Entry/Exit handler, nomal state handler.
//! @cond INTERNAL

typedef SM_StatePtr (*SM_InitHandler)(void * const me) SM_HSM_RETT;
typedef void (*SM_ActionHandler)(void * const me) SM_HSM_RETT;
typedef
SM_RetState
(*SM_StateHandler)(void * const me, void const * const e) SM_HSM_RETT;

//! @endcond

//............................................................................
//! @class SM_HsmState
//! @extends struct SM_StatePtr
typedef struct SM_HsmState {
    SM_StatePtr super;         //!< @private @memberof SM_HsmState
    SM_InitHandler init_;      //!< @private @memberof SM_HsmState
    SM_ActionHandler entry_;   //!< @private @memberof SM_HsmState
    SM_ActionHandler exit_;    //!< @private @memberof SM_HsmState
    SM_StateHandler handler_;  //!< @private @memberof SM_HsmState
} SM_HsmState;

//............................................................................
//! @class SM_Hsm
//! @extends SM_HsmState
typedef struct SM_Hsm {
    SM_StatePtr curr; //!< @private @memberof SM_Hsm
    SM_StatePtr next; //!< @private @memberof SM_Hsm
} SM_Hsm;

#ifndef SM_HSM_CAST
    #define SM_HSM_CAST(me_)  ((SM_Hsm *)(me_))
#endif // SM_HSM_CAST

//............................................................................
// Deepest nest level for HSM, TOP state exclude
#ifndef SM_MAX_NEST_DEPTH_
    #define SM_MAX_NEST_DEPTH_ 5
#endif // SM_MAX_NEST_DEPTH_

//! @brief Virtual pointer of SM_Hsm_init_ and SM_Hsm_dispatch_.
//! @cond INTERNAL
typedef void (*VC_Handler)(void * const me, void const * const e) SM_HSM_RETT;
//! @endcond

//============================================================================
//! @static @public @memberof SM_Hsm
void SM_Hsm_init_(SM_Hsm * const me, SM_InitHandler initial_) SM_HSM_RETT;

//! @static @public @memberof SM_Hsm
void SM_Hsm_dispatch_(SM_Hsm * const me,
                      SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;

//! @static @public @memberof SM_Hsm
void SM_Hsm_transition_(SM_Hsm * const me,
                        SM_StatePtr source,
                        SM_StatePtr target) SM_HSM_RETT;

//! @static @public @memberof SM_Hsm
void SM_Hsm_initDrill_(SM_Hsm * const me,
                       SM_StatePtr * const path) SM_HSM_RETT;

#endif // SM_HSM_H_
