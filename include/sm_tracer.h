//============================================================================
// Copyright (C) 2026 Sunny Matato
//
// This program is free software. It comes without any warranty, to
// the extent permitted by applicable law. You can redistribute it
// and/or modify it under the terms of the Do What The Fuck You Want
// To Public License, Version 2, as published by Sam Hocevar.
// See http://www.wtfpl.net/ for more details.
//============================================================================
#ifndef SM_TRACER_H_
#define SM_TRACER_H_

//============================================================================
//! @brief Reentrant keycode;
//         Critical sections.
//! @cond INTERNAL

#ifndef SMT_REET
    #define SMT_REET
#endif // SMT_REET

#ifndef SMT_CRITICAL_SECTION_ENTRY
    #define SMT_CRITICAL_SECTION_ENTRY() ((void)0)
#endif // SMT_CRITICAL_SECTION_ENTRY

#ifndef SMT_CRITICAL_SECTION_EXIT
    #define SMT_CRITICAL_SECTION_EXIT() ((void)0)
#endif // SMT_CRITICAL_SECTION_EXIT

//! @endcond

//============================================================================
//! @class SM_Tracer
typedef struct SM_Tracer {
    void * * volatile freeHead;   //!< @protected @memberof SM_Tracer
    void * * start;               //!< @protected @memberof SM_Tracer
    void * * end;                 //!< @protected @memberof SM_Tracer
    unsigned char blockSize;      //!< @protected @memberof SM_Tracer
    unsigned char nTot;           //!< @protected @memberof SM_Tracer
    unsigned char volatile nFree; //!< @protected @memberof SM_Tracer
    unsigned char nMin;           //!< @protected @memberof SM_Tracer

    void * * ring;                //!< @protected @memberof SM_Tracer
    unsigned char volatile head;  //!< @protected @memberof SM_Tracer
    unsigned char volatile tail;  //!< @protected @memberof SM_Tracer
    unsigned char qLen;           //!< @protected @memberof SM_Tracer
    unsigned char volatile nUsed; //!< @protected @memberof SM_Tracer
    unsigned char qMin;           //!< @protected @memberof SM_Tracer

    unsigned char traceSeq;       //!< @protected @memberof SM_Tracer
    unsigned char isTracing;      //!< @protected @memberof SM_Tracer
    unsigned char *currBuf;       //!< @protected @memberof SM_Tracer
    unsigned char currLen;        //!< @protected @memberof SM_Tracer
    unsigned char currCnt;        //!< @protected @memberof SM_Tracer
    unsigned char chksumIter;     //!< @protected @memberof SM_Tracer
} SM_Tracer;

//............................................................................
extern SM_Tracer SM_Tracer_inst;

//............................................................................
//! @public @memberof SM_Tracer
void SM_Tracer_ctor(SM_Tracer * const me,
                    void * const poolSto, unsigned int poolSize,
                    unsigned char blockSize,
                    void * const qSto,unsigned char qLen);

//! @static @public @memberof SM_Tracer
unsigned char *SM_Trace_getBlock(SM_Tracer * const me) SMT_REET;

//! @static @public @memberof SM_Tracer
void SM_Trace_push(SM_Tracer * const me, unsigned char *pfb) SMT_REET;

//! @public @memberof SM_Tracer
void SM_Tracer_idle(SM_Tracer *me);

//============================================================================
//! @brief Macros in hand.
//! @cond EXTERNAL

#define SM_TRACE_BEGIN(recId_, dateLen_) do {                                \
    unsigned char *fb_;                                                      \
    unsigned char offset_;                                                   \
    offset_ = 0;                                                             \
    fb_ = SM_Trace_getBlock(&SM_Tracer_inst);                                \
    fb_ ? fb_[offset_++] = ((unsigned char)(recId_))   : (void)0;            \
    fb_ ? fb_[offset_++] = ((unsigned char)(dateLen_)) : (void)0;

#define SM_TRACE_PAYLOAD_BE(payload_)                                        \
    fb_ ? fb_[offset_++] = ((unsigned char)(payload_)) : (void)0;

#define SM_TRACE_END(dummy_)                                                 \
    SM_Trace_push(&SM_Tracer_inst, fb_);                                     \
} while (0);

//! @endcond

// BSP =======================================================================
//! @public @memberof SM_Tracer
void SM_Tracer_flush_byte_(unsigned char byte_);

#endif // SM_TRACER_H_
