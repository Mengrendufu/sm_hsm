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
#include "sm_tracer.h"

//============================================================================
SM_DEFINE_MODULE("sm_tracer")

//============================================================================
SM_Tracer SM_Tracer_inst;

//============================================================================
//! @public @memberof SM_Tracer
void SM_Tracer_ctor(SM_Tracer * const me,
                    void * const poolSto, unsigned int poolSize,
                    unsigned char blockSize,
                    void * const qSto, unsigned char qLen)
{
    void **fb;
    unsigned char nextLink;
    unsigned int poolSize_;

    // memory pool init...
    SM_REQUIRE(poolSto != (void *)0);

    // Pre-loaded...
    poolSize_ = poolSize;
    me->freeHead = (void **)poolSto;
    me->blockSize = (unsigned char)sizeof(void *);

    // link shift round-up...
    nextLink = (unsigned char)1;
    while (me->blockSize < blockSize) {
        me->blockSize += (unsigned char)sizeof(void *);
        ++nextLink;
    }

    // At least one block.
    SM_ENSURE(poolSize_ >= me->blockSize);

    // Link, link, link...
    fb = me->freeHead;
    me->nTot = 1;
    poolSize_ -= (unsigned int)me->blockSize;
    while (poolSize_ >= (unsigned int)blockSize) {
        fb[0] = &fb[nextLink];
        fb = (void **)fb[0];
        ++me->nTot;
        poolSize_ -= (unsigned int)blockSize;
    }
    fb[0] = (void *)0; // Tail of the link.
    me->start = me->freeHead;
    me->end = fb;  // Last block.
    me->nFree = me->nTot;
    me->nMin = me->nTot;

    // Queue init...
    SM_REQUIRE(qSto != (void *)0);
    me->ring  = (void **)qSto;
    me->head  = 0;
    me->tail  = 0;
    me->qLen  = qLen;
    me->nUsed = 0;
    me->qMin  = me->qLen;

    // Idle running control block...
    me->traceSeq = 0;
    me->isTracing = 0;  // False.
}

//............................................................................
//! @static @public @memberof SM_Tracer
static unsigned char SM_Tracer_is_esc(unsigned char byte_) {
    if ((byte_ == 0x7E) || (byte_ == 0x7D)) return 1U;
    else                                    return 0U;
}

//............................................................................
//! @static @public @memberof SM_Tracer
static void SM_Tracer_flush(unsigned char byte_, unsigned char optEsc) {
    if (optEsc) { // Escape needed?
        if (SM_Tracer_is_esc(byte_)) {  // Escape confirm?
            SM_Tracer_flush_byte_(0x7D);
            SM_Tracer_flush_byte_(0x20 ^ byte_);
        } else {
            SM_Tracer_flush_byte_(byte_);
        }
    } else {
        SM_Tracer_flush_byte_(byte_);
    }
}

//..........................................................................
//! @static @public @memberof SM_Tracer
unsigned char *SM_Trace_getBlock(SM_Tracer * const me) SMT_REET {
    unsigned char *fb;

    fb = (unsigned char *)0;  // Default NULL.

    SMT_CRITICAL_SECTION_ENTRY();

    if (me->nFree > 0) {
        fb = (unsigned char *)me->freeHead;
        me->freeHead = (void **)(me->freeHead[0]);
        --me->nFree;
        if (me->nFree < me->nMin) me->nMin = me->nFree;
    }

    SMT_CRITICAL_SECTION_EXIT();

    return fb;
}

//..........................................................................
//! @static @public @memberof SM_Tracer
void SM_Trace_push(SM_Tracer * const me, unsigned char *pfb) SMT_REET {
    if (pfb) {

        SMT_CRITICAL_SECTION_ENTRY();

        if (me->nUsed < me->qLen) {  // Not full.
            me->ring[me->head] = (void *)pfb;
            if (me->head == 0) me->head = me->qLen;
            --me->head;
            ++me->nUsed;
            if (me->qMin > me->qLen - me->nUsed) {
                me->qMin = me->qLen - me->nUsed;
            }
        } else { // Full.
            // GC...
            ((void **)(me->ring[me->tail]))[0] = (void *)me->freeHead;
            me->freeHead = (void **)me->ring[me->tail];
            ++me->nFree;
            if (me->tail == 0) me->tail = me->qLen;
            --me->tail;

            // Newest one...
            me->ring[me->head] = (void *)pfb;
            if (me->head == 0) me->head = me->qLen;
            --me->head;
        }

        SMT_CRITICAL_SECTION_EXIT();
    }
}

//............................................................................
//! @public @memberof SM_Tracer
void SM_Tracer_idle(SM_Tracer * const me) {
    if (!me->isTracing) {

        SMT_CRITICAL_SECTION_ENTRY();

        if (me->nUsed > 0) {
            // SET.
            me->isTracing = 1;

            // Load...
            me->currBuf = (unsigned char *)me->ring[me->tail];
            me->currLen = me->currBuf[1] + 2;
            me->currCnt = me->currLen;
            SM_ENSURE(me->currCnt <= me->blockSize);

            // Refresh...
            if (me->tail == 0) me->tail = me->qLen;
            --me->tail;
            --me->nUsed;

            SMT_CRITICAL_SECTION_EXIT();

            // [0x7E] [seq]...
            SM_Tracer_flush(0x7E, 0);
            me->chksumIter = 0;
            me->chksumIter += me->traceSeq++;
            SM_Tracer_flush(me->chksumIter, 1);

            // RecID...
            me->chksumIter += me->currBuf[me->currLen - me->currCnt--];
            SM_Tracer_flush(me->currBuf[me->currLen - me->currCnt - 1],
                            1);
        } else {
            SMT_CRITICAL_SECTION_EXIT();
        }
    } else {
        if (me->currCnt == 0) {
            // [CHKSUM] [0x7E].
            SM_Tracer_flush(~(me->chksumIter), 1);
            SM_Tracer_flush(0x7E, 0);

            SMT_CRITICAL_SECTION_ENTRY();

            ((void **)(me->currBuf))[0] = (void *)me->freeHead;
            me->freeHead = (void **)me->currBuf;
            ++me->nFree;

            SMT_CRITICAL_SECTION_EXIT();

            me->isTracing = 0;  // Take a breath.
        } else {
            // [pLen] [payload]...
            me->chksumIter += me->currBuf[me->currLen - me->currCnt--];
            SM_Tracer_flush(me->currBuf[me->currLen - me->currCnt - 1],
                            1);
        }
    }
}
