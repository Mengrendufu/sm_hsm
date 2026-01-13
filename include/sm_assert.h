/*****************************************************************************
 * Copyright (C) 2026 Sunny Matato
 *
 * This program is free software. It comes without any warranty, to
 * the extent permitted by applicable law. You can redistribute it
 * and/or modify it under the terms of the Do What The Fuck You Want
 * To Public License, Version 2, as published by Sam Hocevar.
 * See http://www.wtfpl.net/ for more details.
 ****************************************************************************/
#ifndef SM_ASSERT_H_
#define SM_ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef SM_DBC_DISABLE  /* DBC enable */

/* ======================================================================== */
/* 0. Module Definition                                                     */
/* ======================================================================== */

    /**
     * @brief Define the current module name to save ROM space.
     * Replaces the standard __FILE__ macro which takes too much space.
     * * Internal Metaphor: The Dungeon Name.
     * Defines the context where the discipline takes place.
     */
    #define SM_DEFINE_MODULE(name_) \
        static char const SM_module_name_[] = name_;

/* =========================================================================*/
/* 1. Assertion Macros                                                      */
/* =========================================================================*/

    /**
     * @brief Unconditional Error
     * Forces a failure immediately. Used in unreachable code paths.
     * * Internal Metaphor: THE_FORBIDDEN_ZONE
     * "You have entered a place explicitly forbidden. Immediate punishment."
     */
    #define SM_ERROR(dummy_) \
        (SM_onAssert(SM_module_name_, __LINE__))

    /**
     * @brief Pre-condition
     * Checks arguments or state before entering the function logic.
     * * Internal Metaphor: KNEEL_BEFORE
     * "Submission to the rules is required before entry."
     */
    #define SM_REQUIRE(cond_) \
        ((cond_) ? (void)0 : SM_onAssert(SM_module_name_, __LINE__))

    /**
     * @brief Post-condition
     * Checks results or state before leaving the function.
     * * Internal Metaphor: AFTERCARE
     * "Ensure the subject is in the expected condition after the session."
     */
    #define SM_ENSURE(cond_) \
        ((cond_) ? (void)0 : SM_onAssert(SM_module_name_, __LINE__))

    /**
     * @brief Invariant / Allege
     * Asserts that a condition is true.
     * The expression IS executed even in Release.
     * Used when the check has side effects (e.g., hardware reads, counters).
     * * Internal Metaphor: HOLD_POSE
     * "Endure the pain.
     *  The action must be performed regardless of observation."
     */
    #define SM_ALLEGE(cond_) \
        ((cond_) ? (void)0 : SM_onAssert(SM_module_name_, __LINE__))

    /**
     * @brief General Assertion
     * Internal logic sanity check.
     * * Internal Metaphor: OBEY
     * "Absolute obedience to logic is mandatory."
     */
    #define SM_ASSERT(cond_) \
        ((cond_) ? (void)0 : SM_onAssert(SM_module_name_, __LINE__))

    /** @{ */

    #ifndef SM_NORETURN
    #define SM_NORETURN void
    #endif  /* SM_NORETURN */

    /**
     * @brief Callback function triggered when assertion fails.
     * * Internal Metaphor: The Safeword.
     * Invoked when limits are breached. Must be implemented by the user.
     */
    SM_NORETURN SM_onAssert(char const *module, int label);

    /** @} */

#else  /* DBC disable */

    #define SM_DEFINE_MODULE(name_)

    #define SM_REQUIRE(cond_) ((void)0)
    #define SM_ENSURE(cond_)  ((void)0)
    #define SM_ASSERT(cond_)  ((void)0)

    /* * In Release mode, ALLEGE must still execute the expression
     * for its side effects, even if we don't check the result.
     * Metaphor: The pose is held, but no one is watching.
     */
    #define SM_ALLEGE(cond_)  ((void)(cond_))

#endif  /* SM_DBC_DISABLE */

#ifdef __cplusplus
}
#endif

#endif /* SM_ASSERT_H_ */
