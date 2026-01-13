/*****************************************************************************
 * Copyright (C) 2026 Sunny Matato
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar.
 * See http://www.wtfpl.net/ for more details.
 ****************************************************************************/
#ifndef SM_HSM_H_
#define SM_HSM_H_

/**
 * @defgroup Read-Only key code and function reentrant key code.
 *
 * @brief Typically, if you use 8051, you might do this:
 *                                               #define SM_HSM_ROM const code
 *                                               #define SM_HSM_RETT reentrant
 *
 *                   if you use Cortex-M3, you might do this:
 *                                               #define SM_HSM_ROM const
 *                                               #define SM_HSM_RETT
 * @{
 */

#ifndef SM_HSM_ROM
#define SM_HSM_ROM const
#endif  /* SM_HSM_ROM */

#ifndef SM_HSM_RETT
#define SM_HSM_RETT
#endif  /* SM_HSM_RETT */

/** @} */

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

#ifndef SM_HSM_SIGNAL
typedef unsigned char SM_Hsm_Signal;
#define SM_HSM_SIGNAL SM_Hsm_Signal
#endif  /* SM_HSM_SIGNAL */

#ifndef SM_HSM_EVT_TYPE
typedef struct {
    SM_HSM_SIGNAL sig;
} SM_HsmEvt;
#define SM_HSM_EVT_TYPE SM_HsmEvt
#define SM_HSM_EVT_SIG(evt_)  ((evt_)->sig)
#endif  /* SM_HSM_EVT_TYPE */

/** @} */

/**
 * @defgroup Event processing return.
 *
 * @{
 */

typedef unsigned char SM_RetState;
#define SM_RET_HANDLED 0
#define SM_RET_SUPER   1
#define SM_RET_TRAN    2

#define _SM_HANDLED()      (SM_RET_HANDLED)
#define _SM_SUPER()        (SM_RET_SUPER)
#define _SM_TRAN(target_)                                               \
                                (SM_HSM_CAST(me)->next = (target_),     \
                                    SM_RET_TRAN)  /* return this */
#define _SM_INIT(target_)  (target_)

/** @} */

/**
 * @defgroup Hsm State pointer.
 *
 * @note Expand to struct SM_HsmState SM_HSM_ROM * in application.
 *
 * @{
 */

struct SM_HsmState;
typedef struct SM_HsmState SM_HSM_ROM * SM_StatePtr;

/** @} */

/**
 * @defgroup UML Top-Initial handler, Entry/Exit handler, nomal state handler.
 *
 * @{
 */

typedef SM_StatePtr (*SM_InitHandler)(void * const me) SM_HSM_RETT;
typedef void (*SM_ActionHandler)(void * const me) SM_HSM_RETT;
typedef
SM_RetState
(*SM_StateHandler)(void * const me, void const * const e) SM_HSM_RETT;

/** @} */

/**
 * @defgroup HSM struct.
 *
 * @note SM_StatePtr is always in **ROM**.
 *
 *       When you put HSM into another framework as an normal attr
 *       (not super under single heritance syntax), SM_HSM_CAST will help.
 *       You can define the SM_HSM_CAST somewhere to specify how to get the
 *       SM_Hsm * from me pointer passed to virtual pointer.
 *
 * @{
 */

typedef struct SM_HsmState {
    SM_StatePtr super;
    SM_InitHandler init_;
    SM_ActionHandler entry_;
    SM_ActionHandler exit_;
    SM_StateHandler handler_;
} SM_HsmState;

typedef struct SM_Hsm {
    SM_StatePtr curr;                                     /*! current state */
    SM_StatePtr next;               /*! target state when transition occurs */
} SM_Hsm;

#ifndef SM_HSM_CAST
#define SM_HSM_CAST(me_)  ((SM_Hsm *)(me_))
#endif  /* SM_HSM_CAST */

/** @} */

/**
 * @defgroup Virtual pointer of SM_Hsm_init_ and SM_Hsm_dispatch_
 *
 * @{
 */

typedef void (*VC_Handler)(void * const me, void const * const e) SM_HSM_RETT;

/** @} */

/**
 * @brief Perform the UML TOP-INIT action of Hierarchical State Machine.
 *
 * @param[in] me HSM instance.
 *
 * @param[in] initial_ TOP-INIT transition handler, inside it should plicitly
 *                     execute the initial transition.
 */
void SM_Hsm_init_(SM_Hsm * const me, SM_InitHandler initial_) SM_HSM_RETT;

/**
 * @brief
 *
 * @param[in] me Pointer of a state machine.
 *
 * @param[in] e
 */
void SM_Hsm_dispatch_(
    SM_Hsm * const me,
    SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT;

/**
 * @brief
 *
 * @param[in] me
 *
 * @param[in] source
 *
 * @param[in] target
 */
void SM_Hsm_transition_(
    SM_Hsm * const me,
    SM_StatePtr source,
    SM_StatePtr target) SM_HSM_RETT;

/**
 * @brief
 *
 * @param[in] me
 */
void SM_Hsm_initDrill_(SM_Hsm * const me) SM_HSM_RETT;

/*==========================================================================*/
void SmHsmTst_test(void);

#endif  /* SM_HSM_H_ */
