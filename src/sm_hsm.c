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
#include "sm_assert.h"
#include "sm_hsm.h"

//============================================================================
SM_DEFINE_MODULE("sm_hsm")

//============================================================================
//! @private @memberof SM_Hsm
void SM_Hsm_init_(SM_Hsm * const me, SM_InitHandler initial_) SM_HSM_RETT {
    SM_StatePtr path[SM_MAX_NEST_DEPTH_];
    SM_StatePtr s;
    SM_StatePtr target;
    signed char ip;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(initial_ != (SM_InitHandler)0);

    target = (*initial_)(me);
    SM_ENSURE(target != (SM_StatePtr)0);

    ip = -1;
    s = target;
    while (s != (SM_StatePtr)0) {
        SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
        path[++ip] = s;
        s = s->super;
    }

    while (ip >= 0) {
        if (path[ip]->entry_) path[ip]->entry_(me);
        --ip;
    }

    me->curr = target;
    me->next = (SM_StatePtr)0;

    SM_Hsm_initDrill_(me, path);
}

//............................................................................
//! @private @memberof SM_Hsm
void SM_Hsm_dispatch_(SM_Hsm * const me,
                      SM_HSM_EVT_TYPE const * const e) SM_HSM_RETT
{
    SM_StatePtr s;
    SM_RetState ret;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(e != (SM_HSM_EVT_TYPE *)0);

    s = me->curr;

    SM_REQUIRE(s != (SM_StatePtr)0);
    while (s != (SM_StatePtr)0) {
        ret = s->handler_(me, e);
        switch (ret) {
            case SM_RET_TRAN: {
                return SM_Hsm_transition_(me, s, me->next);
            }
            case SM_RET_HANDLED: {
                return;
            }
            case SM_RET_SUPER: {
                s = s->super;
                break;
            }
            default: {
                SM_ERROR("Whip.");
            }
        }
    }
}

//..........................................................................
//! @private @memberof SM_Hsm
void SM_Hsm_transition_(SM_Hsm * const me,
                        SM_StatePtr source,
                        SM_StatePtr target) SM_HSM_RETT
{
    SM_StatePtr path[SM_MAX_NEST_DEPTH_];
    SM_StatePtr s;
    signed char ip;
    signed char i;
    bool bReachedSource;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(source != (SM_StatePtr)0);
    SM_REQUIRE(target != (SM_StatePtr)0);

    // ENTRY path.
    ip = -1;
    s = target;
    while (s != (SM_StatePtr)0) {
        SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
        path[++ip] = s;
        s = s->super;
    }

    i = 0;
    bReachedSource = false;
    s = me->curr;
    while (s != (SM_StatePtr)0) {
        if (s == source) bReachedSource = true;
        if (bReachedSource) {
            if (!((s == source) && (target == source))) { // Not self-tran.
                for (i = 0; i <= ip; ++i) {
                    if (s == path[i]) goto G_TAG_LCA_HIT;
                }
            }
        }
        if (s->exit_) s->exit_(me); // EXIT until source.
        s = s->super;
    }
    if (bReachedSource) { // source->super == NULL && target->super == NULL
        i = ++ip;
        goto G_TAG_LCA_HIT;
    }

    // Should never arrive.
    SM_ERROR("Punishment.");

G_TAG_LCA_HIT:
    while (--i >= 0) { // ENTRY except LCA.
        if (path[i]->entry_) path[i]->entry_(me);
    }

    me->curr = target;
    SM_Hsm_initDrill_(me, path);
}

//............................................................................
//! @private @memberof SM_Hsm
void SM_Hsm_initDrill_(
    SM_Hsm * const me,
    SM_StatePtr * const path) SM_HSM_RETT
{
    SM_REQUIRE(me != (SM_Hsm *)0);
    while (me->curr->init_ != (SM_InitHandler)0) {
        SM_StatePtr s;
        SM_StatePtr target;
        signed char i;
        signed char ip;

        target = me->curr->init_(me);
        SM_ENSURE(target != (SM_StatePtr)0);

        ip = -1;
        s = target;
        while (s != (SM_StatePtr)0 && s != me->curr) {
            SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH_ - 1));
            path[++ip] = s;
            s = s->super;
        }

        for (i = ip; i >= 0; i--) {
            me->curr = path[i];
            if (path[i]->entry_) path[i]->entry_(me);
        }
    }
}
