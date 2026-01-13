/*****************************************************************************
 * Copyright (C) 2026 Sunny Matato
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar.
 * See http://www.wtfpl.net/ for more details.
 ****************************************************************************/
#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include "sm_assert.h"
#include "sm_hsm.h"

/*..........................................................................*/
SM_DEFINE_MODULE("sm_hsm")

/*..........................................................................*/
/* Deepest nest level for HSM, TOP state exclude */
#define SM_MAX_NEST_DEPTH 5

/*..........................................................................*/
void SM_Hsm_init_(SM_Hsm * const me, SM_InitHandler initial_) SM_HSM_RETT {
    SM_StatePtr path[SM_MAX_NEST_DEPTH];
    signed char ip;
    SM_StatePtr s;
    SM_StatePtr target;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(initial_ != (SM_InitHandler)0);

    target = (*initial_)(me);
    SM_ENSURE(target != (SM_StatePtr)0);

    ip = -1;
    s = target;
    while (s != (SM_StatePtr)0) {
        SM_REQUIRE(ip < (SM_MAX_NEST_DEPTH - 1));
        ip++;
        path[ip] = s;
        s = s->super;
    }

    while (ip >= 0) {
        me->curr = path[ip];
        if (path[ip]->entry_) {
            path[ip]->entry_(me);
        }
        ip--;
    }

    me->next = (SM_StatePtr)0;

    SM_Hsm_initDrill_(me);
}
/*..........................................................................*/
void SM_Hsm_dispatch_(
    SM_Hsm * const me,
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
        if (ret == SM_RET_TRAN) {
            SM_Hsm_transition_(me, s, me->next);
            return;
        } else if (ret == SM_RET_HANDLED) {
            return;
        }
        s = s->super;
    }
}
/*..........................................................................*/
void SM_Hsm_transition_(
    SM_Hsm * const me,
    SM_StatePtr source,
    SM_StatePtr target) SM_HSM_RETT
{
    SM_StatePtr path[SM_MAX_NEST_DEPTH];
    signed char ip;
    SM_StatePtr s;
    signed char i;
    bool bReachedSource;

    SM_REQUIRE(me != (SM_Hsm *)0);
    SM_REQUIRE(source != (SM_StatePtr)0);
    SM_REQUIRE(target != (SM_StatePtr)0);

    bReachedSource = (me->curr == source);

    /**
     *   path[SM_MAX_NEST_DEPTH - 1]  target->super.super...
     *   .
     *   .
     *   .
     *   path[1]                      target->super
     *   path[0]                      target
     */
    ip = -1;
    s = target;
    while (s != (SM_StatePtr)0) {
        if (++ip < SM_MAX_NEST_DEPTH) {
            path[ip] = s;
        }
        s = s->super;
    }

    /**
     *   path[SM_MAX_NEST_DEPTH - 1]  target->...super...
     *   .                                                      ^
     *   .                                                      |
     *   .                                                      |
     *   path[1]                      target->super             |
     *   path[0]                      target                    s
     */
    s = me->curr;
    while (s != (SM_StatePtr)0) {
        if (s == source) {
            bReachedSource = 1;
        }
        for (i = 0; i <= ip; i++) {
            if (s == path[i]) {
                if (bReachedSource) {
                    if (s == source && target == source) {
                        break;
                    }
                    goto G_TAG_LCA_HIT; /* LCA found */
                }
            }
        }
        if (s->exit_) {
            s->exit_(me);
        }
        s = s->super;
    }

    SM_ERROR("Punishment");  /* Unreachable, must jump over this point */

    /**
     * Entry link
     */
G_TAG_LCA_HIT:
    while (--i >= 0) {
        if (path[i]->entry_) path[i]->entry_(me);
    }

    /**
     * State initial link
     */
    me->curr = target;
    SM_Hsm_initDrill_(me);
}
/*..........................................................................*/
void SM_Hsm_initDrill_(SM_Hsm * const me) SM_HSM_RETT {
    SM_REQUIRE(me != (SM_Hsm *)0);

    while (me->curr->init_ != (SM_InitHandler)0) {
        SM_StatePtr path[SM_MAX_NEST_DEPTH];
        signed char ip = -1;
        SM_StatePtr s;
        signed char i;
        SM_StatePtr target = me->curr->init_(me);

        SM_ENSURE(target != (SM_StatePtr)0);

        s = target;
        while (s != (SM_StatePtr)0 && s != me->curr) {
            SM_ENSURE(ip < (SM_MAX_NEST_DEPTH - 1));
            ++ip;
            path[ip] = s;
            s = s->super;
        }

        for (i = ip; i >= 0; i--) {
            me->curr = path[i];
            if (path[i]->entry_) {
                path[i]->entry_(me);
            }
        }
    }
}
