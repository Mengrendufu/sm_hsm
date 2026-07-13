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
#include "sm_assert.h"
#include "sm_hsm.h"

//============================================================================
SM_DEFINE_MODULE("sm_hsm")

//............................................................................
// SM_StatePtr carries SM_HSM_ROM (const on host, const code on C51).
// The explicit cast pins the pointer's storage space so C51 uses
// memory-specific addressing (code *) instead of a generic 3-byte pointer.
#define SM_STATE_CAST_(pstate_) ((SM_StatePtr)(pstate_))

static void SM_Hsm_transition_(SM_Hsm * const me,
                               SM_StatePtr source,
                               SM_StatePtr target) SM_HSM_RETT;

//============================================================================
//! @private @memberof SM_Hsm
void SM_Hsm_init_(SM_Hsm * const me, SM_InitHandler initial_) SM_HSM_RETT {
    SM_StatePtr path[SM_MAX_NEST_DEPTH_];
    SM_StatePtr s;
    SM_StatePtr target;
    signed char ip;
    signed char i;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(initial_ != (SM_InitHandler)0);

    target = (*((SM_InitHandler)(initial_)))(me);
    SM_ENSURE(target != (SM_StatePtr)0);

    ip = -1;
    s = target;
    while (s != (SM_StatePtr)0) {
        SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
        path[++ip] = s;
        s = SM_STATE_CAST_(s)->super;
    }

    while (ip >= 0) {
        s = SM_STATE_CAST_(path[ip]);
        if (s->entry_) {
            (*s->entry_)(me);
        }
        --ip;
    }

    me->curr = target;
    me->next = (SM_StatePtr)0;

    while (SM_STATE_CAST_(me->curr)->init_ != (SM_InitHandler)0) {
        target = (*(SM_STATE_CAST_(me->curr)->init_))(me);
        SM_ENSURE(target != (SM_StatePtr)0);
        ip = -1;
        s = target;
        while (s != (SM_StatePtr)0 && s != me->curr) {
            SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
            path[++ip] = s;
            s = SM_STATE_CAST_(s)->super;
        }
        SM_ENSURE(s == me->curr);
        for (i = ip; i >= 0; --i) {
            s = SM_STATE_CAST_(path[i]);
            me->curr = s;
            if (s->entry_) {
                (*s->entry_)(me);
            }
        }
    }
}

//............................................................................
//! @private @memberof SM_Hsm
void SM_Hsm_dispatch_(SM_Hsm * const me,
                      void const * const e) SM_HSM_RETT
{
    SM_StatePtr s;
    SM_RetState ret;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(e != (void *)0);

    s = me->curr;

    SM_REQUIRE(s != (SM_StatePtr)0);
    while (s != (SM_StatePtr)0) {
        ret = (*(SM_STATE_CAST_(s)->handler_))(me, e);
        switch (ret) {
            case SM_RET_HANDLED: {
                return;
            }
            case SM_RET_SUPER: {
                s = SM_STATE_CAST_(s)->super;
                break;
            }
            case SM_RET_TRAN:
            case SM_RET_HIST: {
                SM_Hsm_transition_(me,
                                   s, me->next);
                return;
            }

            default: {
                // Illegal return code from state handler.
                SM_ERROR("Whip.");
                break;
            }
        }
    }
}

//............................................................................
//! @private @memberof SM_Hsm
static void SM_Hsm_transition_(SM_Hsm * const me,
                               SM_StatePtr source,
                               SM_StatePtr target) SM_HSM_RETT
{
    SM_StatePtr path[SM_MAX_NEST_DEPTH_];
    SM_StatePtr s;
    signed char ip;
    signed char i;
    bool bLCAFound;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(SM_STATE_CAST_(source) != (SM_StatePtr)0);
    SM_REQUIRE(SM_STATE_CAST_(target) != (SM_StatePtr)0);

    // Build entry path: target -> root.
    ip = -1;
    s = target;
    while (s != (SM_StatePtr)0) {
        SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
        path[++ip] = s;
        s = SM_STATE_CAST_(s)->super;
    }

    // Exit curr -> source (exclusive).  Shared by all transition types.
    s = me->curr;
    while (s != source) {
        SM_REQUIRE(s != (SM_StatePtr)0);
        if (SM_STATE_CAST_(s)->exit_) {
            (*(SM_STATE_CAST_(s)->exit_))(me);
        }
        s = SM_STATE_CAST_(s)->super;
    }
    // s == source

    // --- Simple transitions ---
    if (source == target) {
        // (a) Self-transition: exit source, enter from target->super down.
        if (SM_STATE_CAST_(source)->exit_) {
            (*(SM_STATE_CAST_(source)->exit_))(me);
        }
        i = 1; // LCA is target->super.
    } else if (source == SM_STATE_CAST_(target)->super) {
        // (b) source is target's parent: no exit source, enter target.
        i = 1;
    } else if (
        SM_STATE_CAST_(source)->super == SM_STATE_CAST_(target)->super
    ) {
        // (c) Same parent: exit source, enter target.
        if (SM_STATE_CAST_(source)->exit_) {
            (*(SM_STATE_CAST_(source)->exit_))(me);
        }
        i = 1;
    } else if (SM_STATE_CAST_(source)->super == target) {
        // (d) target is source's parent: exit source, no entry.
        if (SM_STATE_CAST_(source)->exit_) {
            (*(SM_STATE_CAST_(source)->exit_))(me);
        }
        i = 0;
    } else {
        // --- Complex transition ---
        bLCAFound = false;

        // Search LCA upwards from source.
        while (s != (SM_StatePtr)0) {
            for (i = 0; i <= ip; ++i) {
                if (s == path[i]) {
                    bLCAFound = true;
                    break;
                }
            }
            if (bLCAFound) {
                break;
            }
            if (SM_STATE_CAST_(s)->exit_) {
                (*(SM_STATE_CAST_(s)->exit_))(me);
            }
            s = SM_STATE_CAST_(s)->super;
        }

        // No runtime LCA check here. State-tree consistency is validated
        // by the static checker (tools/check_hsm_tree.py or similar).
        // Without that check, a transition between unrelated trees exits
        // the entire source tree and entries the entire target tree,
        // which is the intended behavior for top-level sibling states.
    }

    while (--i >= 0) {
        s = SM_STATE_CAST_(path[i]);
        if (s->entry_) {
            (*s->entry_)(me);
        }
    }

    me->curr = target;
    while (SM_STATE_CAST_(me->curr)->init_ != (SM_InitHandler)0) {
        target = (*(SM_STATE_CAST_(me->curr)->init_))(me);
        SM_ENSURE(target != (SM_StatePtr)0);
        ip = -1;
        s = target;
        while (s != (SM_StatePtr)0 && s != me->curr) {
            SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
            path[++ip] = s;
            s = SM_STATE_CAST_(s)->super;
        }
        SM_ENSURE(s == me->curr);
        for (i = ip; i >= 0; --i) {
            s = SM_STATE_CAST_(path[i]);
            me->curr = s;
            if (s->entry_) {
                (*s->entry_)(me);
            }
        }
    }
}

//............................................................................
//! @static @public @memberof SM_Hsm
SM_StatePtr SM_Hsm_childState_(SM_Hsm * const me,
                               SM_StatePtr parent) SM_HSM_RETT
{
    SM_StatePtr s;
    SM_StatePtr child;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(parent != (SM_StatePtr)0);

    s = me->curr;
    child = (SM_StatePtr)0;
    while (s != (SM_StatePtr)0) {
        if (SM_STATE_CAST_(s)->super == parent) {
            child = s;
            break;
        }
        s = SM_STATE_CAST_(s)->super;
    }
    SM_ENSURE(child != (SM_StatePtr)0);

    return child;
}
