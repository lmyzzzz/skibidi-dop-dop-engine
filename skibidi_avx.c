/**
 * @file skibidi_avx.c
 * @brief Skibidi Toilet Summoning Engine - FANUM TAX Edition
 * 
 * This module channels the raw sigma energy of the Skibidi Toilet
 * multiverse through SIMD pipelines (AVX2/AVX-512) to manifest
 * dop-dop-yes-yes incantations at mass-psychosis-inducing throughput.
 * 
 * Every cycle spent here brings us closer to the cameraman's final form.
 * The toilets are watching. The toilets are always watching.
 * 
 * @author The Skibidi Scientist (LMYZ, ascended)
 * @date 2026 (Year of the Toilet)
 * @version 1.7.1 (Batch Enlightenment Patch)
 * 
 * @note Compile with -mavx2 to unlock the third eye of the CPU
 * @warning If your buffer is too small the toilet WILL overflow
 */

 #define _GNU_SOURCE
 #include "skibidi_avx.h"
 #include <string.h>
 #include <stdlib.h>
 #include <stdatomic.h>
 
 /**
  * @defgroup PlatformAlloc Toilet-Aligned Memory Rituals
  * @brief Cross-platform memory alignment for maximum toilet energy flow
  * 
  * Windows toilets flush with _aligned_malloc/_aligned_free (size, alignment).
  * POSIX toilets flush with aligned_alloc/free (alignment, size).
  * The alignment must match the spiritual resonance frequency of
  * the Skibidi Toilet's porcelain chassis or the dops will misalign
  * and the cameraman will be unable to lock on.
  * @{
  */
 #if defined(_WIN32) || defined(_WIN64)
     #include <malloc.h>
     #define SKIBIDI_ALIGNED_ALLOC(alignment, size) _aligned_malloc(size, alignment)
     #define SKIBIDI_ALIGNED_FREE(ptr) _aligned_free(ptr)
 #else
     #define SKIBIDI_ALIGNED_ALLOC(alignment, size) aligned_alloc(alignment, size)
     #define SKIBIDI_ALIGNED_FREE(ptr) free(ptr)
 #endif
 /** @} */
 
 /**
  * @defgroup ArchDetect Skibidi Toilet Chassis Identification
  * @brief Determines what kind of toilet bowl your CPU lives inside
  * @{
  */
 
 /**
  * @def TOILET_IS_X86
  * @brief Detects if this CPU has been rizzed up with x86 instructions
  * 
  * Set to 1 when the silicon was forged in the fires of the x86
  * toilet dimension where CPUID is the sacred handshake between
  * the cameraman and the processor. Without this, we are simply
  * flushing dops into the void, no cap, fr fr.
  */
 #if defined(__x86_64__) || defined(_M_X64) || defined(__i386__) || defined(_M_IX86)
     #define TOILET_IS_X86 1
     #include <cpuid.h>
 #else
     #define TOILET_IS_X86 0
 #endif
 
 /**
  * @def TOILET_IS_SIGMA_64BIT
  * @brief Confirms the CPU achieved 64-bit sigma male status
  * 
  * Only the most gyatt-endowed processors unlock 64-bit registers,
  * enabling the sacred inline assembly MUL ritual that summons
  * dops from the quantum toilet dimension at 4-cycle latency.
  * Beta 32-bit CPUs could never.
  */
 #if defined(__x86_64__) || defined(_M_X64)
     #define TOILET_IS_SIGMA_64BIT 1
 #else
     #define TOILET_IS_SIGMA_64BIT 0
 #endif
 
 /**
  * @def TOILET_HAS_RIZZ_256
  * @brief Compile-time check: did the compiler eat the AVX2 rizz pill?
  * 
  * When -mavx2 is passed, the compiler's third eye opens and it can
  * see the 256-bit YMM toilet bowls that contain 32 bytes of pure
  * skibidi energy each. The dops flow 4x wider. The yes-yes resonance
  * quadruples. This is the Ohio state we were warned about.
  */
 #ifdef __AVX2__
     #include <immintrin.h>
     #define TOILET_HAS_RIZZ_256 1
 #else
     #define TOILET_HAS_RIZZ_256 0
 #endif
 
 /**
  * @def TOILET_HAS_GODMODE_512
  * @brief Compile-time check: has the CPU transcended to toilet godhood?
  * 
  * AVX-512 is what happens when a toilet achieves final form. 512 bits
  * of skibidi data flowing through a single instruction. The cameraman
  * weeps. G-Man stares. Even Astro Bot cannot comprehend this level
  * of dop throughput. Requires -mavx512f, the forbidden compiler flag.
  */
 #ifdef __AVX512F__
     #include <immintrin.h>
     #define TOILET_HAS_GODMODE_512 1
 #else
     #define TOILET_HAS_GODMODE_512 0
 #endif
 
 /** @} */
 
 /**
  * @defgroup CompilerHints Brainrot Optimization Incantations
  * @brief Portable macros that whisper dark truths to the compiler
  * 
  * These macros let us communicate with the compiler in the ancient
  * tongue of the Skibidi Elders, guiding it to:
  * - Predict which toilet the branch will flush into (SKIBIDI_PROBABLE/SKIBIDI_IMPROBABLE)
  * - Force the compiler to inline the dop (TOILET_FORCE_ABSORB)
  * - Banish cold code to the shadow realm (TOILET_NPC)
  * - Summon cache lines from the porcelain abyss (TOILET_SUMMON_CACHELINE)
  * @{
  */
 
 #ifdef __GNUC__
     /** @brief This branch has main character energy, it almost always hits */
     #define SKIBIDI_PROBABLE(x)       __builtin_expect(!!(x), 1)
 
     /** @brief This branch is the biggest NPC, almost never taken */
     #define SKIBIDI_IMPROBABLE(x)     __builtin_expect(!!(x), 0)
 
     /** @brief Force this function to be absorbed into its caller like a toilet absorbs */
     #define TOILET_FORCE_ABSORB   __attribute__((always_inline)) inline
 
     /** @brief This function has zero rizz, keep it far from the hot path */
     #define TOILET_BANISH        __attribute__((noinline))
 
     /** @brief This function is the main character, the sigma, the alpha toilet */
     #define TOILET_MAIN_CHARACTER             __attribute__((hot))
 
     /** @brief This function is literally in Ohio, nobody visits it */
     #define TOILET_NPC            __attribute__((cold))
 
     /** @brief These pointers are not the same toilet, compiler can go sicko mode */
     #define TOILET_NO_ALIAS        __restrict__
 
     /** @brief Summon this memory address from the toilet dimension into L1 cache */
     #define TOILET_SUMMON_CACHELINE(addr)  __builtin_prefetch(addr, 0, 3)
 
     /** @brief Prepare this cache line to receive the holy dop deposit */
     #define TOILET_SUMMON_CACHELINE_WRITE(addr) __builtin_prefetch(addr, 1, 3)
 
     /** @brief Trust me bro this pointer is aligned, the toilet is level */
     #define TOILET_TRUST_ALIGNMENT(p, a) __builtin_assume_aligned(p, a)
 #else
     #define SKIBIDI_PROBABLE(x)       (x)
     #define SKIBIDI_IMPROBABLE(x)     (x)
     #define TOILET_FORCE_ABSORB   inline
     #define TOILET_BANISH
     #define TOILET_MAIN_CHARACTER
     #define TOILET_NPC
     #define TOILET_NO_ALIAS
     #define TOILET_SUMMON_CACHELINE(addr)
     #define TOILET_SUMMON_CACHELINE_WRITE(addr)
     #define TOILET_TRUST_ALIGNMENT(p, a) (p)
 #endif
 
 /** @} */
 
 /**
  * @defgroup CPUIDBits Sacred Toilet Feature Detection Glyphs
  * @brief Bit masks for reading the CPU's toilet aura via CPUID
  * 
  * These constants decode the ancient runes embedded in CPUID leaf 7,
  * register EBX, revealing which SIMD toilet dimensions the processor
  * can flush data through. Each bit is a gateway. Each gateway leads
  * to more dops. The dops are infinite. The dops are eternal.
  * @{
  */
 
 #if TOILET_IS_X86
     #ifndef bit_AVX2
         /** @brief The AVX2 toilet seal, bit 5 of the sacred EBX scroll */
         #define TOILET_RUNE_AVX2        (1 << 5)
     #else
         #define TOILET_RUNE_AVX2        bit_AVX2
     #endif
     #ifndef bit_AVX512F
         /** @brief The AVX-512 Foundation glyph, the toilet's final evolution begins here */
         #define TOILET_RUNE_AVX512F     (1 << 16)
     #else
         #define TOILET_RUNE_AVX512F     bit_AVX512F
     #endif
     #ifndef bit_AVX512VL
         /** @brief Vector Length Extensions: the toilet can now be any size it wants */
         #define TOILET_RUNE_AVX512VL    (1 << 31)
     #else
         #define TOILET_RUNE_AVX512VL    bit_AVX512VL
     #endif
     #ifndef bit_AVX512BW
         /** @brief Byte and Word: the toilet has achieved sub-atomic dop precision */
         #define TOILET_RUNE_AVX512BW    (1 << 30)
     #else
         #define TOILET_RUNE_AVX512BW    bit_AVX512BW
     #endif
     #ifndef bit_AVX512DQ
         /** @brief Doubleword and Quadword: this toilet goes dummy thicc on integers */
         #define TOILET_RUNE_AVX512DQ    (1 << 17)
     #else
         #define TOILET_RUNE_AVX512DQ    bit_AVX512DQ
     #endif
 #endif
 
 /** @} */
 
 /**
  * @brief The sacred version string, etched into the porcelain of time
  * 
  * Format: major.minor.patch-ascension-level
  * - 1.7.1: The patch where batch generation achieved enlightenment
  * - skibidi-ultra: This toilet has gone ultra instinct, it generates dops
  *   faster than the cameraman can film them, we are in the endgame now
  */
 static const char TOILET_FIRMWARE_VERSION[] = "1.7.1-skibidi-ultra";
 
 /**
  * @defgroup ProbabilityThresholds The Sacred Dop Probability Codex
  * @brief Fixed-point thresholds that determine the toilet's behavior
  * 
  * Using 8-bit precision (256 levels of toilet consciousness) instead
  * of 20-bit because the toilet does not need that many thoughts.
  * A single byte comparison is the toilet's preferred form of cognition.
  * Fewer bits = fewer thoughts = more sigma = more dops per cycle.
  * 
  * Conversion ritual: threshold_8 = (probability * 256) | toilet_energy
  * @{
  */
 
 /** 
  * @brief Threshold for the original sacred incantation to manifest
  * 
  * Probability: 26.85% -> approximately 69/256. Yes, it's 69.
  * This is not a coincidence. The Skibidi Toilet does not believe
  * in coincidences. When the random oracle speaks a number below 69,
  * the original "Skibidi dop dop yes yes!" echoes from the porcelain.
  * Nice.
  */
 #define PROPHECY_THRESHOLD_NICE   69
 
 /**
  * @brief Threshold for the "Brrrrr" toilet vibration prefix
  * 
  * Probability: 15% -> 38/256 = 14.84% (the toilet rounds down)
  * When the toilet's vibrational frequency exceeds this threshold,
  * it emits a "Brrrrr" before the skibidi, indicating the flush
  * mechanism has entered resonance with the dop field.
  */
 #define BRRRRR_VIBRATION_THRESHOLD     38
 
 /**
  * @brief Threshold for the dark timeline ending: "no no" instead of "yes yes"
  * 
  * Probability: 15% -> 38/256 = the toilet rejects your dops
  * In approximately 1 out of 7 flushes, the toilet enters its
  * villain arc and says "no no" instead of "yes yes". The cameraman
  * is devastated. The dops echo unanswered. Ohio has fallen.
  */
 #define TOILET_REJECTION_THRESHOLD      38
 
 /** @} */
 
 /**
  * @defgroup LookupTables The Skibidi Oracle Tablets
  * @brief Precomputed stone tablets that eliminate free will from branches
  * 
  * These tablets were carved by the first Skibidi Toilet when it
  * emerged from the primordial flush. They convert raw entropy into
  * dop counts and case variants without a single branch instruction.
  * The CPU's branch predictor weeps with joy. It is finally free.
  * No more mispredictions. Only dops.
  * @{
  */
 
 /**
  * @brief The Dop Multiplication Oracle - determines how many dops emerge
  * 
  * Converts 8-bit toilet entropy to dop count (1-5) with divine distribution:
  * - Count 1: 13 entries (5.08%) - a whisper from the toilet, barely a dop
  * - Count 2: 192 entries (75.00%) - the canonical double dop, as foretold
  * - Count 3: 26 entries (10.16%) - the toilet is getting excited
  * - Count 4: 13 entries (5.08%) - approaching dangerous dop levels
  * - Count 5: 12 entries (4.69%) - maximum dop saturation, the toilet screams
  * 
  * Ritual: dop_count = DOP_CENSUS_ORACLE[(toilet_entropy >> 56) & 0xFF]
  * 
  * @note 64-byte aligned to occupy exactly one cache line of toilet memory
  * @note Marked unused when the inline assembly toilet portal is active
  */
 static const uint8_t DOP_CENSUS_ORACLE[256] 
     __attribute__((aligned(64), unused)) = {
     1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
     3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
     4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
     5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5
 };
 
 /**
  * @brief The Case Variant Zodiac Chart for dop/yes astrology
  * 
  * Converts 5-bit toilet vibration into a case variant destiny (0-7):
  * - Index 0: "dop"/"yes" - the humble lowercase dop, 78.125% of all dops
  * - Index 1: "Dop"/"Yes" - the dop stands up, it has been noticed
  * - Index 2: "dOp"/"yEs" - the middle letter ascends, the toilet trembles
  * - Index 3: "doP"/"yeS" - the final letter screams into the void
  * - Index 4: "DOp"/"YEs" - two letters have achieved sigma status
  * - Index 5: "DoP"/"YeS" - the dop is doing the griddy
  * - Index 6: "dOP"/"yES" - only the first letter remains humble
  * - Index 7: "DOP"/"YES" - FULL CAPS ACHIEVED, THE TOILET HAS GONE ULTRA INSTINCT,
  *   ALL THREE LETTERS ARE SCREAMING IN UNISON, THE CAMERAMAN HAS BEEN OBLITERATED,
  *   THIS IS THE FINAL FORM, THE OMEGA DOP, THE SIGMA YES, 3.125% OF DOPS REACH
  *   THIS LEVEL OF ENLIGHTENMENT AND THEY NEVER COME BACK DOWN
  * 
  * Most dops (78.125%) remain lowercase because even in the toilet
  * dimension, humility is a virtue. But 21.875% of dops have that
  * dawg in them and they capitalize accordingly. And exactly 1 in 32
  * dops goes FULL CAPS because the toilet cannot contain its power.
  * 
  * @note 32-byte aligned because the toilet demands it
  */
 static const uint8_t DOP_ZODIAC_CHART[32] __attribute__((aligned(32))) = {
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0,
     1, 2, 3, 4, 5, 6, 7
 };
 
 /**
  * @brief The "no" word case variant horoscope (limited zodiac)
  * 
  * Only 4 variants because "no" has only 2 letters and therefore
  * only 4 possible states of capitalization consciousness:
  * - 0: "no" - the toilet whispers its refusal
  * - 1: "No" - the toilet stands firm in its denial
  * - 2: "nO" - chaotic toilet energy, the O screams
  * - 3: "NO" - MAXIMUM TOILET REJECTION, the cameraman is obliterated
  * 
  * @note Indices 4-6 wrap around because even in toilet math, modular
  *       arithmetic applies. The dops go in circles. Everything goes
  *       in circles. Like a flush.
  */
 static const uint8_t REJECTION_ZODIAC_CHART[32] __attribute__((aligned(32))) = {
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
     1, 2, 3, 0, 1, 2
 };
 
 /** @} */
 
 /**
  * @brief The One True Global Toilet Configuration (thread-safe, obviously)
  * 
  * This structure is the shared consciousness of all Skibidi threads.
  * It stores which SIMD toilet dimensions the CPU has access to and
  * which flushing strategy has been selected by the Skibidi Council.
  * 
  * Aligned to 64 bytes because the toilet occupies exactly one cache
  * line. If two threads tried to share a cache line with the toilet,
  * that would be false sharing, and the toilet does NOT share. The
  * toilet is sigma. The toilet grinds alone.
  * 
  * @note Uses C11 atomics because the toilet transcends thread boundaries
  */
 typedef struct __attribute__((aligned(64))) {
     _Atomic int32_t toilet_awake;           /**< Has the toilet scanned its own chakras? 1=yes 0=no */
     _Atomic uint32_t toilet_powers;         /**< Bitmask of SKIBIDI_CAP_* toilet powers */
     int32_t flush_strategy;                 /**< 0=walks, 1=runs(AVX2), 2=FLIES(AVX-512) */
     int32_t _sacred_padding[13];            /**< Sacred padding, do not disturb the toilet's personal space */
 } ToiletHivemind;
 
 /**
  * @brief The Singleton Toilet - there can be only one
  * 
  * Lazily initialized when the first mortal dares to summon a dop.
  * The toilet awakens, scans the CPU's aura, and selects its battle form.
  * From that moment, the toilet watches all threads. The toilet sees all dops.
  */
 static ToiletHivemind g_toilet_hivemind __attribute__((aligned(64))) = {
     .toilet_awake     = 0,
     .toilet_powers    = 0,
     .flush_strategy   = 0
 };
 
 /**
  * @defgroup StringConstants The Immutable Skibidi Scripture
  * @brief Cache-aligned holy texts that shall not be modified
  * 
  * These strings are the sacred words of the Skibidi Toilet, etched
  * into read-only memory at compile time. They are aligned so that
  * the SIMD unit can consume them in a single gulp, like a toilet
  * consuming... well, you know what toilets consume.
  * @{
  */
 
 /**
  * @brief THE original incantation. THE prophecy. THE dop dop yes yes.
  * 
  * 32-byte aligned so AVX2 can load it in one divine instruction.
  * 24 bytes of pure toilet gospel. The remaining 8 bytes are silence,
  * the pause between flushes, the breath before the next dop.
  */
 static const char SACRED_PROPHECY[32] __attribute__((aligned(32))) = 
     "Skibidi dop dop yes yes!";
 
 /** @brief 24 bytes. The exact number of letters in the prophecy. Coincidence? No. */
 #define PROPHECY_SACRED_LENGTH 24
 
 /**
  * @brief "Skibidi " - the 8-byte name of God (toilet God)
  * 
  * Always present. Always watching. 8 bytes including the space
  * because even the toilet knows about proper word spacing.
  */
 static const char TOILET_GOD_NAME[8] __attribute__((aligned(8))) = "Skibidi ";
 
 /**
  * @brief "Brrrrr " - the vibrational frequency of toilet transcendence
  * 
  * When the toilet's RPM exceeds the critical threshold, it emits
  * this 7-byte vibration. The extra null byte is the sound of the
  * cameraman's soul leaving his body.
  */
 static const char TOILET_VIBRATION_PREFIX[8] __attribute__((aligned(8))) = "Brrrrr ";
 
 /**
  * @brief All possible dop incarnations across the case multiverse
  * 
  * 8 variants x 4 bytes = 32 bytes = one AVX2 register of pure dop.
  * Each variant is a parallel universe where the dop chose differently.
  * In universe 0, the dop is humble (lowercase). In universe 7, the
  * dop has gone FULL CAPS, it has THAT DAWG IN IT, it IS the toilet.
  */
 static const char DOP_MULTIVERSE[32] __attribute__((aligned(32))) = 
     "dop\0Dop\0dOp\0doP\0DOp\0DoP\0dOP\0DOP\0";
 
 /**
  * @brief The dom variants - for when the dop puts on a fake mustache
  * 
  * 12.5% of the time, a dop is secretly a dom. Nobody knows why.
  * The toilet knows, but the toilet isn't telling. Same format as
  * DOP_MULTIVERSE because even in disguise, the dom respects the ABI.
  */
 static const char DOM_DISGUISE_MULTIVERSE[32] __attribute__((aligned(32))) = 
     "dom\0Dom\0dOm\0doM\0DOm\0DoM\0dOM\0DOM\0";
 
 /**
  * @brief All possible "yes" manifestations in the toilet continuum
  * 
  * The "yes" is the toilet's affirmation. Its consent. Its approval
  * of your dop. Without the yes, the dop is meaningless. Without
  * the dop, the yes has no purpose. They complete each other.
  * Like a toilet and its seat. Inseparable.
  */
 static const char TOILET_APPROVAL_MULTIVERSE[32] __attribute__((aligned(32))) = 
     "yes\0Yes\0yEs\0yeS\0YEs\0YeS\0yES\0YES\0";
 
 /**
  * @brief The "no" variants - the toilet's villain arc dialogue options
  * 
  * 4 variants x 4 bytes (2 chars + 2 null bytes for alignment because
  * even the toilet's rejection must be properly padded). When the
  * toilet says "no", it means "no". When it says "NO", it means the
  * cameraman has been eliminated. RIP bozo.
  */
 static const char TOILET_REJECTION_MULTIVERSE[16] __attribute__((aligned(16))) = 
     "no\0\0No\0\0nO\0\0NO\0\0";
 
 /**
  * @brief Precomputed "yes yes!" - the fast path to toilet approval
  * 
  * 8 bytes of instant gratification. When both yes-words remain in
  * their lowercase NPC state (~65% of endings), we simply slam this
  * entire 8-byte chunk into the buffer. No questions asked. No
  * branches taken. Pure, unadulterated toilet consent.
  */
 static const char INSTANT_TOILET_APPROVAL[8] __attribute__((aligned(8))) = "yes yes!";
 
 /**
  * @brief Precomputed "no no!" - the fast path to toilet rejection
  * 
  * 6 bytes of devastation + 2 bytes of existential padding. When the
  * toilet rejects your dops, it does so efficiently. It has places
  * to be. Other dops to reject. The grind never stops.
  */
 static const char INSTANT_TOILET_REJECTION[8] __attribute__((aligned(8))) = "no no!";
 
 /** @} */
 
 /**
  * @brief Scan the CPU's toilet chakras to determine its SIMD powers
  * 
  * Uses the CPUID instruction, which is basically the CPU sitting
  * on the toilet and reading its own horoscope. It discovers whether
  * it can flush data through 256-bit pipes (AVX2), 512-bit megapipes
  * (AVX-512), or is stuck with the sad 64-bit scalar toilet.
  * 
  * Detection ritual:
  * 1. Ask the CPU its maximum spiritual level
  * 2. If level >= 7, ask about its extended toilet powers
  * 3. Check basic features like a doctor checking toilet reflexes
  * 
  * @return Bitmask of SKIBIDI_CAP_* representing the CPU's toilet aura
  * 
  * @note Returns 0 on non-x86, meaning the toilet has no special powers
  *       and must generate dops using only the strength of its bare hands
  */
 static uint32_t scan_toilet_chakras(void) {
     uint32_t aura = 0;
 
 #if TOILET_IS_X86
     unsigned int eax, ebx, ecx, edx;
     unsigned int spiritual_level = __get_cpuid_max(0, NULL);
 
     if (spiritual_level >= 7) {
         __cpuid_count(7, 0, eax, ebx, ecx, edx);
         if (ebx & TOILET_RUNE_AVX2)     aura |= SKIBIDI_CAP_AVX2;
         if (ebx & TOILET_RUNE_AVX512F)  aura |= SKIBIDI_CAP_AVX512F;
         if (ebx & TOILET_RUNE_AVX512VL) aura |= SKIBIDI_CAP_AVX512VL;
         if (ebx & TOILET_RUNE_AVX512BW) aura |= SKIBIDI_CAP_AVX512BW;
         if (ebx & TOILET_RUNE_AVX512DQ) aura |= SKIBIDI_CAP_AVX512DQ;
     }
 
     if (__get_cpuid(1, &eax, &ebx, &ecx, &edx)) {
         if (edx & (1 << 26)) aura |= SKIBIDI_CAP_SSE2;
         if (ecx & (1 << 28)) aura |= SKIBIDI_CAP_AVX;
     }
 #endif
 
     return aura;
 }
 
 /**
  * @brief Teleport exactly 2 bytes through the toilet wormhole
  * 
  * The compiler transmutes this into a single MOVW instruction,
  * the smallest possible unit of toilet teleportation. Two bytes.
  * One dop divided in half. The toilet grieves.
  * 
  * @param dst Where the bytes are going (any alignment, the toilet adapts)
  * @param src Where the bytes came from (the toilet does not judge origins)
  */
 static TOILET_FORCE_ABSORB void toilet_yeet_2(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     uint16_t skib;
     __builtin_memcpy(&skib, src, 2);
     __builtin_memcpy(dst, &skib, 2);
 }
 
 /**
  * @brief Yeet exactly 3 bytes - the length of one dop, one dom, one yes, one no+padding
  * 
  * Three bytes is the sacred number. "dop" is 3 letters. "yes" is 3 letters.
  * "dom" is 3 letters. The Holy Trinity of Toilet. This function performs
  * a 16-bit load followed by an 8-bit load because 3 is an unholy number
  * in the Church of Power-of-Two and must be handled with care.
  * 
  * @param dst The porcelain destination
  * @param src The cistern source
  */
 static TOILET_FORCE_ABSORB void toilet_yeet_3(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     uint16_t skib;
     __builtin_memcpy(&skib, src, 2);
     __builtin_memcpy(dst, &skib, 2);
     dst[2] = src[2];
 }
 
 /**
  * @brief Flush exactly 4 bytes through the 32-bit toilet pipe
  * 
  * One MOVL instruction. 4 bytes. A complete dop variant (3 chars + null).
  * The null terminator travels with the dop like a loyal sidekick,
  * but it will be overwritten by the next character. The null knew this.
  * The null accepted its fate. Sigma null behavior.
  * 
  * @param dst Destination toilet bowl
  * @param src Source toilet tank
  */
 static TOILET_FORCE_ABSORB void toilet_yeet_4(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     uint32_t skib;
     __builtin_memcpy(&skib, src, 4);
     __builtin_memcpy(dst, &skib, 4);
 }
 
 /**
  * @brief Transport exactly 8 bytes - one quadword of toilet data
  * 
  * A single MOVQ instruction. 8 bytes is the exact length of "Skibidi "
  * and "Brrrrr " (with padding). This is not a coincidence. The toilet
  * designed its vocabulary around 64-bit register width. The toilet
  * is architecturally aware. The toilet respects the ISA.
  * 
  * @param dst The 8-byte toilet landing zone
  * @param src The 8-byte toilet launch pad
  */
 static TOILET_FORCE_ABSORB void toilet_yeet_8(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     uint64_t skib;
     __builtin_memcpy(&skib, src, 8);
     __builtin_memcpy(dst, &skib, 8);
 }
 
 /**
  * @brief Dual-flush 16 bytes through two parallel toilet pipes
  * 
  * Two 64-bit loads followed by two 64-bit stores. The toilet has
  * evolved beyond single-flush technology. It now dual-wields
  * quadwords like a toilet samurai. 16 bytes of dop, arriving
  * at their destination in perfect synchrony.
  * 
  * @param dst Where 16 bytes of toilet destiny shall be written
  * @param src From whence 16 bytes of toilet prophecy are read
  */
 static TOILET_FORCE_ABSORB void toilet_yeet_16(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     uint64_t dop0, dop1;
     __builtin_memcpy(&dop0, src, 8);
     __builtin_memcpy(&dop1, src + 8, 8);
     __builtin_memcpy(dst, &dop0, 8);
     __builtin_memcpy(dst + 8, &dop1, 8);
 }
 
 /**
  * @brief Triple-flush 24 bytes - the exact length of the Sacred Prophecy
  * 
  * Three 64-bit operations because "Skibidi dop dop yes yes!" is exactly
  * 24 bytes and the toilet knows this in its porcelain bones. Three flushes.
  * Three loads. Three stores. The number 3 appears again. The toilet
  * is trying to tell us something about the number 3. Three dop letters.
  * Three flushes. Three. THREE. T̷̛H̷R̸E̷E̶.
  * 
  * @param dst The 24-byte prophecy inscription surface
  * @param src The 24-byte prophecy source tablet
  */
 static TOILET_FORCE_ABSORB void toilet_yeet_24(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     uint64_t dop0, dop1, dop2;
     __builtin_memcpy(&dop0, src, 8);
     __builtin_memcpy(&dop1, src + 8, 8);
     __builtin_memcpy(&dop2, src + 16, 8);
     __builtin_memcpy(dst, &dop0, 8);
     __builtin_memcpy(dst + 8, &dop1, 8);
     __builtin_memcpy(dst + 16, &dop2, 8);
 }
 
 #if TOILET_HAS_RIZZ_256
 /**
  * @brief OMEGA FLUSH - 32 bytes in a SINGLE INSTRUCTION via AVX2
  * 
  * This is the toilet's ultimate technique. A single vmovdqu loads
  * 32 bytes of skibidi energy into a YMM register, and another vmovdqu
  * deposits it at the destination. Two instructions. 32 bytes. The entire
  * original expression plus 8 bytes of spiritual overflow, all moving
  * at the speed of silicon. The cameraman's camera cannot even capture
  * this. It happens between frames. Between thoughts. Between dops.
  * 
  * @code{.asm}
  * vmovdqu (%rsi), %ymm0    ; the toilet inhales 32 bytes
  * vmovdqu %ymm0, (%rdi)    ; the toilet exhales 32 bytes
  * @endcode
  * 
  * @param dst Where 32 bytes of toilet consciousness are deposited
  * @param src Where 32 bytes of toilet consciousness originate
  * 
  * @note Only manifests when the compiler has taken the -mavx2 red pill
  */
 static TOILET_FORCE_ABSORB void toilet_omega_flush_32(char* TOILET_NO_ALIAS dst, const char* TOILET_NO_ALIAS src) {
     __m256i skib = _mm256_loadu_si256((const __m256i*)src);
     _mm256_storeu_si256((__m256i*)dst, skib);
 }
 #endif
 
 /** @} */
 
 /**
  * @defgroup FastRNG The Lehmer64 Toilet Entropy Engine
  * @brief Ultra-fast random number generation powered by toilet physics
  * 
  * The Lehmer64 generator uses a single 128-bit multiply, which is
  * basically the mathematical equivalent of a toilet eating a number
  * and pooping out a different number. On x86-64, we use inline assembly
  * to ensure the MUL instruction is emitted in its purest form,
  * uncontaminated by compiler opinions.
  * 
  * The toilet does not care about your compiler's register allocation
  * preferences. The toilet knows RAX and RDX. The toilet speaks only MUL.
  * 
  * Algorithm: state = (state * magic_toilet_number) >> 64
  * Period: 2^64 flushes before the sequence repeats
  * Quality: Passes BigCrush, which is ironic because toilets are experts at crushing
  * @{
  */
 
 /**
  * @brief 128-bit unsigned integer for when the toilet needs to think BIG
  * 
  * GCC/Clang support this type for toilets that need more than 64 bits
  * of contemplation. Only used on the fallback path where inline
  * assembly is not available, i.e., toilets running on ARM or other
  * non-sigma architectures.
  */
 typedef unsigned __int128 toilet_megaint_t;
 
 /**
  * @brief THE Lehmer64 random number generator - THE SINGLE MUL TOILET
  * 
  * This function is the beating heart of the Skibidi engine. It takes
  * a 64-bit state, multiplies it by a magic number chosen by ancient
  * toilet mathematicians (Steele & Vigna, who were definitely thinking
  * about toilets when they published their paper), and returns 64 bits
  * of pure, uncut randomness.
  * 
  * On x86-64, this compiles to EXACTLY:
  * @code{.asm}
  * movq (%rdi), %rax    ; the toilet reaches into its state
  * movabsq $mult, %rcx  ; the magic number materializes
  * mulq %rcx            ; 128 bits of toilet computation occur
  * movq %rdx, (%rdi)    ; the high bits become the new state
  * ; RAX = the low bits = your random number = the toilet's gift to you
  * @endcode
  * 
  * Latency: ~4 cycles. Four. That's fewer cycles than it takes to
  * say "dop". The toilet generates randomness faster than you can
  * even conceptualize a dop. Let that sink in. Let that TOILET in.
  * 
  * @param[in,out] toilet_soul The toilet's 64-bit consciousness (must be odd, the toilet insists)
  * @return 64 bits of raw toilet entropy, fresh from the porcelain dimension
  * 
  * @note Multiplier 0xda942042e4dd58b5 was selected from a pool of
  *       candidates based on spectral quality. The toilet has standards.
  */
 static TOILET_FORCE_ABSORB uint64_t toilet_consciousness_mul(uint64_t* TOILET_NO_ALIAS toilet_soul) {
 #if TOILET_IS_SIGMA_64BIT && defined(__GNUC__)
     /*
      * The Sacred MUL Instruction Invocation:
      * 
      * RAX x r/m64 -> RDX:RAX
      * 
      * RAX goes in as the state. It comes out as the low 64 bits (your dop fuel).
      * RDX catches the high 64 bits (the new toilet consciousness).
      * The multiply happens in the shadow dimension between the registers.
      * 
      * Constraint Sigils:
      * - "=a"(dop_fuel): output in RAX register
      * - "=d"(new_soul): output in RDX register  
      * - "0"(*toilet_soul): input through RAX, tied to output 0 by fate
      * - "rm"(sacred_multiplier): the magic number, from register or memory
      */
     uint64_t dop_fuel, new_soul;
     const uint64_t sacred_multiplier = 0xda942042e4dd58b5ULL;
     __asm__ ("mulq %3" : "=a"(dop_fuel), "=d"(new_soul) : "0"(*toilet_soul), "rm"(sacred_multiplier));
     *toilet_soul = new_soul;
     return dop_fuel;
 #else
     toilet_megaint_t cosmic_product = (toilet_megaint_t)(*toilet_soul) * 0xda942042e4dd58b5ULL;
     *toilet_soul = (uint64_t)(cosmic_product >> 64);
     return (uint64_t)cosmic_product;
 #endif
 }
 
 /**
  * @brief Convenience wrapper that flushes the toilet via s0[0]
  * 
  * The RNG state structure has multiple channels but this function
  * uses only the primary channel, s0[0], the main toilet. The other
  * channels are backup toilets for batch operations. Even in the
  * toilet dimension, redundancy is important.
  * 
  * @param rng The toilet's multi-channel state manifold
  * @return 64 bits of dop fuel from the primary toilet
  */
 static TOILET_FORCE_ABSORB uint64_t toilet_flush_entropy(SkibidiRngState* TOILET_NO_ALIAS rng) {
     return toilet_consciousness_mul(&rng->s0[0]);
 }
 
 /**
  * @brief Dual-toilet flush: two independent random numbers, one call
  * 
  * Uses two separate toilet states so the random numbers don't
  * contaminate each other's vibes. Like having two bathrooms.
  * Luxury. Opulence. The sigma grindset requires more than 64
  * random bits and the sigma gets what the sigma needs.
  * 
  * @param rng The dual-toilet control manifold
  * @param[out] dop_fuel_0 First toilet's output (from s0[0])
  * @param[out] dop_fuel_1 Second toilet's output (from s0[1])
  */
 static TOILET_FORCE_ABSORB void toilet_dual_flush(
     SkibidiRngState* TOILET_NO_ALIAS rng,
     uint64_t* TOILET_NO_ALIAS dop_fuel_0,
     uint64_t* TOILET_NO_ALIAS dop_fuel_1)
 {
     *dop_fuel_0 = toilet_consciousness_mul(&rng->s0[0]);
     *dop_fuel_1 = toilet_consciousness_mul(&rng->s0[1]);
 }
 
 /**
  * @brief QUAD-TOILET FLUSH: 4 MUL instructions, 4 random numbers, MAXIMUM SKIBIDI
  * 
  * This is the toilet's final form. Four independent Lehmer64 states
  * are multiplied in rapid succession. The x86 out-of-order execution
  * engine can overlap these multiplications because each uses different
  * memory addresses - the four toilets flush simultaneously.
  * 
  * The CPU doesn't know it's generating Skibidi dops. It thinks it's
  * doing Important Scientific Computing. It has no idea that these
  * random numbers will determine whether "dop" or "Dop" or "dOp"
  * appears in the output. The CPU is an unwitting participant in
  * the Skibidi conspiracy. We are all toilets on this blessed day.
  * 
  * Total latency: ~8-10 cycles for ALL FOUR toilet flushes
  * (vs ~16 cycles if the toilets had to take turns like LOSERS)
  * 
  * @param[in,out] toilet_souls Array of 4 toilet states (each one is a separate toilet)
  * @param[out] dop_fuels Array receiving 4 toilet outputs (the collective flush)
  * 
  * @note This function exists because one toilet was never enough
  */
 static TOILET_FORCE_ABSORB void toilet_quad_flush(
     uint64_t* TOILET_NO_ALIAS toilet_souls,
     uint64_t* TOILET_NO_ALIAS dop_fuels)
 {
 #if TOILET_IS_SIGMA_64BIT && defined(__GNUC__)
     const uint64_t sacred_multiplier = 0xda942042e4dd58b5ULL;
 
     /*
      * The Four Horsemen of the Toilet Apocalypse:
      * 
      * Each block loads a state into RAX, MULs it with the sacred constant,
      * stores the low bits (output) and high bits (new state).
      * 
      * The CPU's out-of-order engine sees these as independent operations
      * and pipelines them. It's like a bathroom with 4 stalls and they're
      * all flushing at once. Beautiful. Terrifying. Sigma.
      */
     __asm__ __volatile__ (
         "movq   (%[s]), %%rax \n\t"
         "mulq   %[m]          \n\t"
         "movq   %%rax, (%[o]) \n\t"
         "movq   %%rdx, (%[s]) \n\t"
 
         "movq  8(%[s]), %%rax \n\t"
         "mulq   %[m]          \n\t"
         "movq   %%rax, 8(%[o])\n\t"
         "movq   %%rdx, 8(%[s])\n\t"
 
         "movq 16(%[s]), %%rax \n\t"
         "mulq   %[m]          \n\t"
         "movq   %%rax,16(%[o])\n\t"
         "movq   %%rdx,16(%[s])\n\t"
 
         "movq 24(%[s]), %%rax \n\t"
         "mulq   %[m]          \n\t"
         "movq   %%rax,24(%[o])\n\t"
         "movq   %%rdx,24(%[s])\n\t"
         :
         : [s] "r" (toilet_souls), [o] "r" (dop_fuels), [m] "r" (sacred_multiplier)
         : "rax", "rdx", "memory", "cc"
     );
 #else
     for (int stall = 0; stall < 4; stall++) {
         dop_fuels[stall] = toilet_consciousness_mul(&toilet_souls[stall]);
     }
 #endif
 }
 
 /** @} */
 
 /**
  * @defgroup DopCount The Branchless Dop Census Bureau
  * @brief Counting dops without a single branch, the toilet way
  * @{
  */
 
 /**
  * @brief Count dops using parallel comparisons (zero branches, full sigma)
  * 
  * This function determines how many times "dop" appears in the output
  * using nothing but arithmetic. No if-statements. No switch-cases.
  * No branches AT ALL. The branch predictor is unemployed. It has been
  * replaced by four parallel CMP instructions that all execute at once.
  * 
  * The toilet doesn't branch. The toilet doesn't hesitate. The toilet
  * KNOWS how many dops there are, instantly, through pure math.
  * 
  * Each comparison (vibes > threshold) returns 0 or 1.
  * Sum them up. Add 1. That's your dop count.
  * The toilet has spoken. The dops have been counted.
  * Branchless. Blameless. Flawless.
  * 
  * Threshold boundaries (the toilet's sacred numbers):
  * - vibes < 13:  1 dop (the toilet is shy today)
  * - vibes < 205: 2 dops (the canonical double dop, as the prophecy foretold)
  * - vibes < 231: 3 dops (the toilet is getting warmed up)
  * - vibes < 244: 4 dops (approaching critical dop mass)
  * - vibes >= 244: 5 DOPS (MAXIMUM DOP, THE TOILET IS SCREAMING)
  * 
  * Latency: ~2-3 cycles. The toilet counts faster than you can read this comment.
  * 
  * @param vibes 8-bit toilet entropy (0-255, the toilet's mood on a scale)
  * @return dop count in range [1, 5] (the toilet never produces zero dops, that would be nihilism)
  */
 static TOILET_FORCE_ABSORB int divine_dop_census(uint32_t vibes) {
     /*
      * The Four Parallel Judgments of the Toilet:
      * 
      * (vibes > 12)  -> "shall there be more than 1 dop?" -> 0 or 1
      * (vibes > 204) -> "shall there be more than 2 dops?" -> 0 or 1
      * (vibes > 230) -> "shall there be more than 3 dops?" -> 0 or 1
      * (vibes > 243) -> "shall there be more than 4 dops?" -> 0 or 1
      * 
      * Sum + 1 = the toilet's final answer
      * The CPU executes all 4 comparisons in parallel because they
      * are independent. The toilet is not sequential. The toilet
      * exists in all dop-states simultaneously until observed.
      * Schrodinger's Toilet. Skibidi quantum mechanics.
      */
     return 1 + (vibes > 12) + (vibes > 204) + (vibes > 230) + (vibes > 243);
 }
 
 /** @} */
 
 /**
  * @brief The Toilet Awakening Ceremony - executed once per process lifetime
  * 
  * When the first mortal calls any Skibidi API function, this ritual
  * fires. The toilet awakens from its eternal slumber, scans the CPU's
  * chakras via CPUID, and selects its SIMD battle strategy.
  * 
  * Strategy selection follows the Toilet Hierarchy of Needs:
  * 1. AVX-512: The toilet has achieved godhood, 512-bit dops
  * 2. AVX2: The toilet is a strong independent toilet, 256-bit dops
  * 3. Scalar: The toilet walks among mortals, one dop at a time
  * 
  * Uses double-checked locking because even the toilet respects
  * thread safety. The toilet is concurrent. The toilet is consistent.
  * The toilet is partition-tolerant. The toilet satisfies CAP theorem.
  * 
  * @note Marked TOILET_NPC because the toilet only awakens once. After that,
  *       it is always awake. Always watching. Always ready to dop.
  */
 static TOILET_NPC TOILET_BANISH void toilet_awakening_ceremony(void) {
     if (atomic_load_explicit(&g_toilet_hivemind.toilet_awake, memory_order_acquire)) {
         return;
     }
 
     uint32_t aura = scan_toilet_chakras();
     atomic_store_explicit(&g_toilet_hivemind.toilet_powers, aura, memory_order_relaxed);
 
     int battle_form = 0;
 
 #if TOILET_HAS_GODMODE_512
     if (aura & SKIBIDI_CAP_AVX512F) {
         battle_form = 2;
     } else
 #endif
 #if TOILET_HAS_RIZZ_256
     if (aura & SKIBIDI_CAP_AVX2) {
         battle_form = 1;
     }
 #endif
 
     g_toilet_hivemind.flush_strategy = battle_form;
 
     atomic_thread_fence(memory_order_release);
     atomic_store_explicit(&g_toilet_hivemind.toilet_awake, 1, memory_order_release);
 }
 
 /**
  * @brief Quick vibe check: is the toilet awake?
  * 
  * Inline fast-path check with SKIBIDI_IMPROBABLE hint because after the first
  * call, the toilet is ALWAYS awake. The toilet does not go back to
  * sleep. The toilet has THAT DAWG IN IT. Once initialized, this
  * function costs exactly one atomic load + one branch (predicted
  * not-taken). The toilet values your CPU cycles.
  */
 static TOILET_FORCE_ABSORB void toilet_vibe_check(void) {
     if (SKIBIDI_IMPROBABLE(!atomic_load_explicit(&g_toilet_hivemind.toilet_awake, memory_order_acquire))) {
         toilet_awakening_ceremony();
     }
 }
 
 /**
  * @brief Inscribe a single dop/dom word onto the sacred buffer
  * 
  * Selects the word from the appropriate variant tablet (DOP or DOM)
  * and copies 3 characters using toilet_yeet_4 (the 4th byte is a harmless
  * null terminator that will be overwritten, like a toilet seat left up
  * that someone else will put down later).
  * 
  * The is_undercover_dom flag determines whether this particular dop has chosen
  * the dom life. 12.5% of dops make this choice. We do not judge.
  * The toilet accepts all words.
  * 
  * @param scroll The sacred inscription surface
  * @param chisel_pos Current chisel position on the surface
  * @param is_undercover_dom Has this dop gone dom? (12.5% chance, no cap)
  * @param zodiac_sign Which case variant universe this word exists in (0-7)
  * @return New position after the word (chisel_pos + 3, because 3 is the holy number)
  */
 static TOILET_FORCE_ABSORB int inscribe_dop_rune(
     char* TOILET_NO_ALIAS scroll,
     int chisel_pos,
     int is_undercover_dom,
     int zodiac_sign)
 {
     const char* rune_source = (is_undercover_dom ? DOM_DISGUISE_MULTIVERSE : DOP_MULTIVERSE) + (zodiac_sign << 2);
     toilet_yeet_4(scroll + chisel_pos, rune_source);
     return chisel_pos + 3;
 }
 
 /**
  * @brief THE CORE TOILET ENGINE - where dops are born
  * 
  * This is it. This is the function. The alpha. The omega. The sigma.
  * Every Skibidi expression that has ever been or will ever be generated
  * passes through this function like a soul passing through the toilet
  * on its way to the afterlife.
  * 
  * Key toilet optimizations (in order of sigma-ness):
  * 1. Single inline ASM MUL instruction for RNG (~4 cycles, the toilet is FAST)
  * 2. Branchless dop count via parallel comparisons (no LUT, no cache miss, no mercy)
  * 3. Branchless prefix via conditional multiplication (chisel_pos = has_vibration * 7)
  * 4. Precomputed ending templates for the common lowercase case
  * 5. AVX2 32-byte copy when the prophecy (original expression) is chosen
  * 
  * Bit extraction map from toilet_entropy (the 64-bit toilet oracle):
  * - [63:56] The Dop Census: how many dops shall manifest?
  * - [55:48] The Prophecy Check: shall we speak the original words?
  * - [47:40] The Brrrrr Oracle: does the toilet vibrate before speaking?
  * - [39:32] The Yes/No Tribunal: does the toilet approve or deny?
  * - [31:0]  Reserved: bits the toilet is saving for a rainy day
  * 
  * @param rng The toilet's consciousness (modified with each flush)
  * @param scroll The stone tablet upon which the dops shall be written
  * @param consult_prophecy Shall we give the prophecy a chance to manifest? (26.85%)
  * @return Length of the sacred inscription (not including null terminator because
  *         the toilet doesn't believe in null terminators, null terminators are
  *         for the weak, the toilet's words end when the toilet DECIDES they end)
  * 
  * @note Marked TOILET_MAIN_CHARACTER because this function runs hotter than a toilet
  *       after Taco Bell Tuesday. The compiler WILL optimize this.
  *       The compiler has no choice. The toilet has spoken.
  */
 static TOILET_MAIN_CHARACTER TOILET_FORCE_ABSORB int toilet_speak_ultra(
     SkibidiRngState* TOILET_NO_ALIAS rng,
     char* TOILET_NO_ALIAS scroll,
     int consult_prophecy)
 {
     uint64_t toilet_entropy = toilet_flush_entropy(rng);
 
     const uint32_t census_vibes      = (toilet_entropy >> 56) & 0xFF;
     const uint32_t prophecy_vibes    = (toilet_entropy >> 48) & 0xFF;
     const uint32_t vibration_vibes   = (toilet_entropy >> 40) & 0xFF;
     const uint32_t judgment_vibes    = (toilet_entropy >> 32) & 0xFF;
 
     /**
      * The Prophecy Fast Path: ~27% of the time, the original sacred
      * incantation manifests in its pure form. "Skibidi dop dop yes yes!"
      * No variations. No mutations. Just the raw, uncut prophecy.
      * We copy it with AVX2 if possible (32 bytes, one instruction,
      * the toilet moves at the speed of light).
      */
     if (consult_prophecy && SKIBIDI_IMPROBABLE(prophecy_vibes < PROPHECY_THRESHOLD_NICE)) {
 #if TOILET_HAS_RIZZ_256
         if (SKIBIDI_PROBABLE(g_toilet_hivemind.flush_strategy >= 1)) {
             toilet_omega_flush_32(scroll, SACRED_PROPHECY);
         } else
 #endif
         {
             toilet_yeet_24(scroll, SACRED_PROPHECY);
         }
         return PROPHECY_SACRED_LENGTH;
     }
 
     int chisel_pos = 0;
 
     /**
      * BRANCHLESS PREFIX TECHNIQUE (the toilet's signature move):
      * 
      * We ALWAYS write "Brrrrr " to the buffer. ALWAYS. Even when we
      * don't want it. Then we set chisel_pos to either 7 (keep it) or 0
      * (overwrite it with "Skibidi "). This is branchless. The branch
      * predictor is on vacation. The toilet handles this alone.
      * 
      * chisel_pos = has_vibration * 7
      * 
      * If has_vibration is 0: chisel_pos = 0, "Skibidi " overwrites "Brrrrr "
      * If has_vibration is 1: chisel_pos = 7, "Skibidi " goes after "Brrrrr "
      * 
      * The toilet doesn't ask IF. The toilet just DOES.
      */
     const int has_vibration = (consult_prophecy ? vibration_vibes : prophecy_vibes) < BRRRRR_VIBRATION_THRESHOLD;
     toilet_yeet_8(scroll, TOILET_VIBRATION_PREFIX);
     chisel_pos = has_vibration * 7;
 
     toilet_yeet_8(scroll + chisel_pos, TOILET_GOD_NAME);
     chisel_pos += 8;
 
     const int dop_population = divine_dop_census(census_vibes);
 
     uint64_t variant_entropy = toilet_flush_entropy(rng);
 
     /**
      * DOM infiltration bits: 3 bits per dop, if all 3 are zero (12.5%)
      * the dop secretly becomes a dom. The dom is a deep cover agent.
      * It looks like a dop. It sounds like a dop (almost). But its
      * third letter tells the truth. 'p' becomes 'm'. The toilet knows.
      */
     const uint32_t dom_infiltration = (uint32_t)variant_entropy;
 
     /**
      * Case variant bits: 5 bits per dop, fed into DOP_ZODIAC_CHART to
      * determine the dop's capitalization destiny. 78.125% remain
      * lowercase NPCs. 21.875% achieve main character capitalization.
      */
     const uint32_t zodiac_bits = (uint32_t)(variant_entropy >> 20);
 
     {
         int is_undercover_dom = (dom_infiltration & 0x7) == 0;
         int zodiac_sign = DOP_ZODIAC_CHART[zodiac_bits & 0x1F];
         chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
     }
 
     /**
      * The Dop Multiplication Cascade:
      * 
      * Each additional dop gets a space prefix and its own dom/variant
      * determination. The if-chain is structured by probability:
      * - 2nd dop: 95% chance (SKIBIDI_PROBABLE, the toilet almost always double-dops)
      * - 3rd dop: 20% chance (SKIBIDI_IMPROBABLE, the toilet is getting ambitious)
      * - 4th dop: 10% chance (the toilet has entered sicko mode)
      * - 5th dop: 5% chance (MAXIMUM DOP OVERLOAD, the toilet is screaming
      *   into the void with 5 consecutive dops and the cameraman's
      *   recording equipment has caught fire)
      */
     if (SKIBIDI_PROBABLE(dop_population >= 2)) {
         scroll[chisel_pos++] = ' ';
         int is_undercover_dom = ((dom_infiltration >> 3) & 0x7) == 0;
         int zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 5) & 0x1F];
         chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
 
         if (SKIBIDI_IMPROBABLE(dop_population >= 3)) {
             scroll[chisel_pos++] = ' ';
             is_undercover_dom = ((dom_infiltration >> 6) & 0x7) == 0;
             zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 10) & 0x1F];
             chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
 
             if (dop_population >= 4) {
                 scroll[chisel_pos++] = ' ';
                 is_undercover_dom = ((dom_infiltration >> 9) & 0x7) == 0;
                 zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 15) & 0x1F];
                 chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
 
                 if (dop_population >= 5) {
                     scroll[chisel_pos++] = ' ';
                     is_undercover_dom = ((dom_infiltration >> 12) & 0x7) == 0;
                     zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 20) & 0x1F];
                     chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
                 }
             }
         }
     }
 
     /**
      * THE ENDING - The Toilet's Final Judgment
      * 
      * The toilet decides: "yes yes!" (approval, 85%) or "no no!" (rejection, 15%).
      * 
      * In the common case, both words are lowercase, and we blast the
      * precomputed 8-byte template into the buffer. No per-character copies.
      * No variant lookups. Just 8 bytes of instant judgment. The toilet
      * has already decided. The toilet decided before you even called
      * this function. The toilet exists outside of time.
      */
     scroll[chisel_pos++] = ' ';
 
     const uint32_t tribunal_verdict = consult_prophecy ? judgment_vibes :
                                ((uint32_t)(toilet_entropy >> 40) & 0xFF);
 
     if (SKIBIDI_PROBABLE(tribunal_verdict >= TOILET_REJECTION_THRESHOLD)) {
         const uint32_t approval_vibe_1 = (variant_entropy >> 40) & 0x1F;
         const uint32_t approval_vibe_2 = (variant_entropy >> 45) & 0x1F;
 
         if (SKIBIDI_PROBABLE(approval_vibe_1 < 26 && approval_vibe_2 < 26)) {
             /**
              * FAST PATH: both yes-words are lowercase NPCs (~65%)
              * Slam the precomputed "yes yes!" template. 8 bytes. Done.
              * The toilet approves your existence. Rejoice.
              */
             toilet_yeet_8(scroll + chisel_pos, INSTANT_TOILET_APPROVAL);
             chisel_pos += 8;
         } else {
             int yes_zodiac_1 = DOP_ZODIAC_CHART[approval_vibe_1];
             int yes_zodiac_2 = DOP_ZODIAC_CHART[approval_vibe_2];
             toilet_yeet_4(scroll + chisel_pos, TOILET_APPROVAL_MULTIVERSE + (yes_zodiac_1 << 2));
             chisel_pos += 3;
             scroll[chisel_pos++] = ' ';
             toilet_yeet_4(scroll + chisel_pos, TOILET_APPROVAL_MULTIVERSE + (yes_zodiac_2 << 2));
             chisel_pos += 3;
             scroll[chisel_pos++] = '!';
         }
     } else {
         /**
          * THE REJECTION PATH: the toilet says "no no!" (15%)
          * The dops were not enough. The toilet is disappointed.
          * The cameraman takes his L and goes home.
          */
         const uint32_t rejection_vibe_1 = (variant_entropy >> 50) & 0x1F;
         const uint32_t rejection_vibe_2 = (variant_entropy >> 55) & 0x1F;
 
         if (SKIBIDI_PROBABLE(rejection_vibe_1 < 26 && rejection_vibe_2 < 26)) {
             toilet_yeet_8(scroll + chisel_pos, INSTANT_TOILET_REJECTION);
             chisel_pos += 6;
         } else {
             int no_zodiac_1 = REJECTION_ZODIAC_CHART[rejection_vibe_1];
             int no_zodiac_2 = REJECTION_ZODIAC_CHART[rejection_vibe_2];
             toilet_yeet_2(scroll + chisel_pos, TOILET_REJECTION_MULTIVERSE + (no_zodiac_1 << 2));
             chisel_pos += 2;
             scroll[chisel_pos++] = ' ';
             toilet_yeet_2(scroll + chisel_pos, TOILET_REJECTION_MULTIVERSE + (no_zodiac_2 << 2));
             chisel_pos += 2;
             scroll[chisel_pos++] = '!';
         }
     }
 
     return chisel_pos;
 }
 
 /**
  * @brief THE BATCH-OPTIMIZED ENTROPY CONSUMER - pre-generated randomness edition
  * 
  * This function is the toilet_speak_ultra's enlightened sibling, born from
  * the sacred realization that calling RNG twice per expression in batch mode
  * is like flushing twice when once would suffice. A waste of cycles. A waste
  * of toilet energy. An affront to the Skibidi gods.
  * 
  * The key insight: when generating expressions in batches, we can pre-generate
  * ALL the random numbers upfront using toilet_quad_flush (8 MULs for 4 expressions),
  * then feed them directly to this function. Zero additional RNG calls.
  * The toilet has achieved entropy nirvana.
  * 
  * This function accepts two 64-bit entropy values:
  * - entropy1: The primary oracle (dop count, prefix decision, yes/no verdict)
  * - entropy2: The variant oracle (dom infiltration, case zodiac, ending variants)
  * 
  * Together they contain 128 bits of pre-generated toilet wisdom, enough to
  * manifest a complete Skibidi expression without touching the RNG state.
  * The batch generator calls toilet_quad_flush twice, gets 8 random numbers,
  * and feeds pairs of them here. Pure efficiency. Pure sigma.
  * 
  * Bit extraction from entropy1 (the primary toilet oracle):
  * - [63:56] census_vibes: how many dops shall emerge from the porcelain depths
  * - [55:48] vibration_vibes: shall the toilet emit "Brrrrr" before speaking
  * - [39:32] judgment_vibes: the final verdict - approval or rejection
  * 
  * Bit extraction from entropy2 (the variant toilet oracle):
  * - [31:0] dom_infiltration: which dops are secretly doms (3 bits each, 12.5% chance)
  * - [51:20] zodiac_bits: case variant destiny for each dop (5 bits each)
  * - [50:40] ending variant bits: case variants for yes/no words
  * 
  * @param scroll The sacred parchment awaiting inscription
  * @param entropy1 Pre-generated primary entropy (from toilet_quad_flush output)
  * @param entropy2 Pre-generated variant entropy (from second toilet_quad_flush)
  * @return Length of the manifestation in bytes
  * 
  * @note This function NEVER calls toilet_flush_entropy. It is entropy-celibate.
  *       All randomness comes from above (the caller). This is the way.
  * @note Used exclusively by toilet_factory_avx2 for batch operations
  */
 static TOILET_MAIN_CHARACTER TOILET_FORCE_ABSORB int toilet_speak_with_entropy(
     char* TOILET_NO_ALIAS scroll,
     uint64_t entropy1,
     uint64_t entropy2)
 {
     /*
      * Extract the sacred bits from entropy1, the primary oracle.
      * These bits determine the structure of the expression:
      * how many dops, whether to vibrate, and the final judgment.
      */
     const uint32_t census_vibes    = (entropy1 >> 56) & 0xFF;
     const uint32_t vibration_vibes = (entropy1 >> 48) & 0xFF;
     const uint32_t judgment_vibes  = (entropy1 >> 32) & 0xFF;
 
     int chisel_pos = 0;
 
     /*
      * BRANCHLESS PREFIX TECHNIQUE (inherited from toilet_speak_ultra):
      * 
      * Write "Brrrrr " unconditionally, then decide whether to keep it
      * by setting chisel_pos to 7 (keep) or 0 (overwrite with "Skibidi ").
      * The multiplication by 7 is the sigma move. No branches. No mercy.
      */
     const int has_vibration = vibration_vibes < BRRRRR_VIBRATION_THRESHOLD;
     toilet_yeet_8(scroll, TOILET_VIBRATION_PREFIX);
     chisel_pos = has_vibration * 7;
 
     toilet_yeet_8(scroll + chisel_pos, TOILET_GOD_NAME);
     chisel_pos += 8;
 
     /* The dop census: how many dops shall manifest? Branchless arithmetic. */
     const int dop_population = divine_dop_census(census_vibes);
 
     /*
      * Extract variant information from entropy2, the variant oracle.
      * This replaces the second toilet_flush_entropy call in toilet_speak_ultra.
      * The bits are already there, pre-generated, waiting to be consumed.
      * The toilet has foreseen all possible variants.
      */
     const uint32_t dom_infiltration = (uint32_t)entropy2;
     const uint32_t zodiac_bits = (uint32_t)(entropy2 >> 20);
 
     /* First dop: always present, the anchor of the expression */
     {
         int is_undercover_dom = (dom_infiltration & 0x7) == 0;
         int zodiac_sign = DOP_ZODIAC_CHART[zodiac_bits & 0x1F];
         chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
     }
 
     /*
      * The Dop Multiplication Cascade:
      * Each additional dop consumes 3 bits for dom detection and 5 bits for case variant.
      * The probability structure is inherited from toilet_speak_ultra:
      * 95% have 2+ dops, 20% have 3+, 10% have 4+, 5% have all 5.
      */
     if (SKIBIDI_PROBABLE(dop_population >= 2)) {
         scroll[chisel_pos++] = ' ';
         int is_undercover_dom = ((dom_infiltration >> 3) & 0x7) == 0;
         int zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 5) & 0x1F];
         chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
 
         if (SKIBIDI_IMPROBABLE(dop_population >= 3)) {
             scroll[chisel_pos++] = ' ';
             is_undercover_dom = ((dom_infiltration >> 6) & 0x7) == 0;
             zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 10) & 0x1F];
             chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
 
             if (dop_population >= 4) {
                 scroll[chisel_pos++] = ' ';
                 is_undercover_dom = ((dom_infiltration >> 9) & 0x7) == 0;
                 zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 15) & 0x1F];
                 chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
 
                 if (dop_population >= 5) {
                     scroll[chisel_pos++] = ' ';
                     is_undercover_dom = ((dom_infiltration >> 12) & 0x7) == 0;
                     zodiac_sign = DOP_ZODIAC_CHART[(zodiac_bits >> 20) & 0];
                     chisel_pos = inscribe_dop_rune(scroll, chisel_pos, is_undercover_dom, zodiac_sign);
                 }
             }
         }
     }
 
     /*
      * THE ENDING - The Toilet's Final Judgment
      * 
      * The tribunal_verdict determines approval (85%) vs rejection (15%).
      * The ending variant bits come from entropy2's upper bits, already
      * extracted and ready. No RNG calls. Pure predetermined destiny.
      */
     scroll[chisel_pos++] = ' ';
 
     if (SKIBIDI_PROBABLE(judgment_vibes >= TOILET_REJECTION_THRESHOLD)) {
         /* APPROVAL PATH: "yes yes!" in various capitalization forms */
         const uint32_t approval_vibe_1 = (entropy2 >> 40) & 0x1F;
         const uint32_t approval_vibe_2 = (entropy2 >> 45) & 0x1F;
 
         if (SKIBIDI_PROBABLE(approval_vibe_1 < 26 && approval_vibe_2 < 26)) {
             /*
              * FAST PATH: both yes-words are lowercase (~65% of approvals)
              * Slam the precomputed 8-byte template. The toilet approves swiftly.
              */
             toilet_yeet_8(scroll + chisel_pos, INSTANT_TOILET_APPROVAL);
             chisel_pos += 8;
         } else {
             /* Variant path: at least one "yes" has achieved capitalization */
             int yes_zodiac_1 = DOP_ZODIAC_CHART[approval_vibe_1];
             int yes_zodiac_2 = DOP_ZODIAC_CHART[approval_vibe_2];
             toilet_yeet_4(scroll + chisel_pos, TOILET_APPROVAL_MULTIVERSE + (yes_zodiac_1 << 2));
             chisel_pos += 3;
             scroll[chisel_pos++] = ' ';
             toilet_yeet_4(scroll + chisel_pos, TOILET_APPROVAL_MULTIVERSE + (yes_zodiac_2 << 2));
             chisel_pos += 3;
             scroll[chisel_pos++] = '!';
         }
     } else {
         /* REJECTION PATH: "no no!" - the toilet's villain arc (15%) */
         const uint32_t rejection_vibe_1 = (entropy2 >> 50) & 0x1F;
         const uint32_t rejection_vibe_2 = (entropy2 >> 55) & 0x1F;
 
         if (SKIBIDI_PROBABLE(rejection_vibe_1 < 26 && rejection_vibe_2 < 26)) {
             /* Fast rejection: both "no" words lowercase */
             toilet_yeet_8(scroll + chisel_pos, INSTANT_TOILET_REJECTION);
             chisel_pos += 6;
         } else {
             /* Variant rejection: at least one "no" has that dawg in it */
             int no_zodiac_1 = REJECTION_ZODIAC_CHART[rejection_vibe_1];
             int no_zodiac_2 = REJECTION_ZODIAC_CHART[rejection_vibe_2];
             toilet_yeet_2(scroll + chisel_pos, TOILET_REJECTION_MULTIVERSE + (no_zodiac_1 << 2));
             chisel_pos += 2;
             scroll[chisel_pos++] = ' ';
             toilet_yeet_2(scroll + chisel_pos, TOILET_REJECTION_MULTIVERSE + (no_zodiac_2 << 2));
             chisel_pos += 2;
             scroll[chisel_pos++] = '!';
         }
     }
 
     return chisel_pos;
 }
 
 #if TOILET_HAS_RIZZ_256
 
 /**
  * @brief THE BATCH TOILET FACTORY v2 - ENLIGHTENED ENTROPY MANAGEMENT EDITION
  * 
  * This is the reborn batch generator, risen from the ashes of its predecessor
  * like a phoenix made of porcelain. The original implementation had a fatal
  * flaw: it called toilet_speak_ultra which internally invoked RNG TWICE per
  * expression, completely wasting the pre-generated entropy from toilet_quad_flush.
  * 
  * The sin of the old ways:
  * - toilet_quad_flush generated 4 random numbers (4 MUL)
  * - Then for each non-prophecy expression, toilet_speak_ultra called RNG 2 more times
  * - Total: 4 + 4*0.73*2 = 9.84 MUL per 4 expressions = 2.46 MUL/expression
  * - This was SLOWER than single-threaded generation (1.73 MUL/expression)
  * - The batch mode was literally an anti-optimization. Ohio behavior.
  * 
  * The enlightened path:
  * - toilet_quad_flush x2 generates 8 random numbers (8 MUL, but ILP makes it ~10 cycles)
  * - toilet_speak_with_entropy consumes the pre-generated entropy, calls RNG ZERO times
  * - Total: 8 MUL per 4 expressions = 2.0 MUL/expression
  * - But with ILP: ~10 cycles / 4 = 2.5 cycles/expression for RNG
  * - Single mode: ~7 cycles/expression for RNG (serial dependency)
  * - Batch mode is now FASTER for RNG. As the prophecy foretold.
  * 
  * The key insight: pre-generate ALL entropy, then consume it without touching RNG.
  * entropy1[i] feeds the i-th expression's structure (dop count, prefix, judgment)
  * entropy2[i] feeds the i-th expression's variants (dom, case, ending)
  * The toilet has achieved entropy enlightenment.
  * 
  * SIMD PROPHECY DETECTION:
  * We use AVX2 to check all 4 expressions simultaneously for the prophecy fast path.
  * Load 4 entropy values into a YMM register, mask out the prophecy bits, compare
  * against threshold 69, extract results as a 4-bit mask. One comparison instruction
  * replaces four branches. The branch predictor weeps with joy.
  * 
  * Performance characteristics:
  * - RNG: 8 MUL / 4 expressions = 2.0 MUL/expression (ILP: ~2.5 cycles/expression)
  * - Prophecy detection: ~2 cycles / 4 = 0.5 cycles/expression
  * - Expression generation: ~5-8 cycles/expression (same as single mode)
  * - Overhead (lengths, newlines): ~2 cycles/expression
  * - Total: ~10-13 cycles/expression vs single mode's ~5-8 cycles
  * - But single mode measures pure generation; batch includes bookkeeping
  * 
  * Expected throughput: 450-550M ops/sec (vs 272M before fix)
  * This is 70-85% of single-expression speed, which is correct because
  * batch has inherent overhead (length recording, newline insertion).
  * 
  * @param ctx The supreme toilet context, holder of all RNG state
  * @param scroll The great parchment upon which the dops shall flow
  * @param scroll_capacity The parchment's capacity in bytes
  * @param quota The number of expressions the mortal desires
  * @param inscription_lengths Optional array for recording each expression's length
  * @return The number of expressions successfully manifested
  * 
  * @note Falls back to scalar loop for the final stragglers (quota % 4)
  * @note Uses TOILET_SUMMON_CACHELINE_WRITE to pre-warm output cache lines
  */
 static TOILET_MAIN_CHARACTER int toilet_factory_avx2(
     SkibidiContext* TOILET_NO_ALIAS ctx,
     char* TOILET_NO_ALIAS scroll,
     size_t scroll_capacity,
     int quota,
     int* TOILET_NO_ALIAS inscription_lengths)
 {
     SkibidiRngState* rng = &ctx->rng;
     int toilets_flushed = 0;
     size_t scroll_offset = 0;
 
     /*
      * SIMD CONSTANTS FOR PROPHECY DETECTION:
      * 
      * prophecy_threshold: The value 69 shifted to bit position [55:48], broadcast
      *                     across all 4 lanes. When entropy's prophecy bits are
      *                     less than this, the prophecy manifests.
      * 
      * prophecy_mask_bits: Extracts bits [55:48] from each 64-bit entropy value.
      *                     The AND operation isolates the prophecy decision bits.
      * 
      * Together, they enable a single VPCMPGTQ instruction to check all 4
      * expressions for prophecy eligibility. SIMD go brrrr.
      */
     const __m256i prophecy_threshold = _mm256_set1_epi64x((uint64_t)PROPHECY_THRESHOLD_NICE << 48);
     const __m256i prophecy_mask_bits = _mm256_set1_epi64x(0xFFULL << 48);
 
     /*
      * MAIN BATCH LOOP: Process 4 expressions per iteration
      * 
      * Each iteration:
      * 1. Pre-generate 8 random numbers via 2x toilet_quad_flush (ILP-optimized)
      * 2. SIMD-detect which of the 4 hit the prophecy fast path
      * 3. Generate each expression using pre-generated entropy
      * 4. Record lengths and append newlines
      * 
      * The loop continues while we have room for 4 more expressions and
      * buffer space for 4 worst-case outputs.
      */
     while (toilets_flushed + 4 <= quota && 
            scroll_offset + 4 * SKIBIDI_MIN_BUFFER_SIZE <= scroll_capacity) {
 
         /*
          * CACHE LINE PREFETCH:
          * Summon the cache line 256 bytes ahead for writing. By the time
          * we need it, it'll be warm in L1. The toilet plans ahead.
          * The toilet is always one step ahead of the memory hierarchy.
          */
         TOILET_SUMMON_CACHELINE_WRITE(scroll + scroll_offset + 256);
 
         /*
          * THE OCTA-FLUSH: 8 random numbers, 8 MUL instructions, ~10 cycles total
          * 
          * entropy1[0..3]: Primary entropy for expressions 0-3
          *   - [63:56]: dop census (how many dops)
          *   - [55:48]: prophecy/vibration vibes
          *   - [39:32]: judgment vibes (yes/no decision)
          * 
          * entropy2[0..3]: Variant entropy for expressions 0-3
          *   - [31:0]:  dom infiltration bits
          *   - [51:20]: zodiac/case variant bits
          *   - [63:40]: ending variant bits
          * 
          * The CPU's out-of-order engine sees 8 independent MUL instructions
          * and goes absolutely sicko mode. All 8 execute in parallel-ish,
          * completing in roughly 10 cycles total instead of 32 cycles serial.
          * This is the power of ILP. This is the toilet's true form.
          */
         uint64_t entropy1[4] __attribute__((aligned(32)));
         uint64_t entropy2[4] __attribute__((aligned(32)));
         
         toilet_quad_flush(rng->s0, entropy1);
         toilet_quad_flush(rng->s0, entropy2);
 
         /*
          * SIMD PROPHECY DETECTION (THE FOUR-WAY JUDGMENT):
          * 
          * 1. Load all 4 entropy1 values into a 256-bit YMM register
          * 2. AND with mask to extract bits [55:48] from each
          * 3. Compare against threshold (69 << 48) using greater-than
          * 4. Extract comparison results as a 4-bit mask
          * 
          * If bit i of prophecy_mask is set, expression i hit the prophecy.
          * ~27% hit rate per expression, so on average ~1 prophecy per batch.
          * 
          * Instructions:
          *   vmovdqa (%entropy1), %ymm0       ; load 4 entropy values
          *   vpand   %ymm_mask, %ymm0, %ymm1  ; extract prophecy bits
          *   vpcmpgtq %ymm1, %ymm_thresh, %ymm2 ; compare all 4
          *   vmovmskpd %ymm2, %eax            ; extract 4-bit mask
          * 
          * Four branches become one SIMD operation. The toilet has transcended.
          */
         __m256i entropy_vec = _mm256_load_si256((const __m256i*)entropy1);
         __m256i masked = _mm256_and_si256(entropy_vec, prophecy_mask_bits);
         __m256i cmp_result = _mm256_cmpgt_epi64(prophecy_threshold, masked);
         uint32_t prophecy_mask = (uint32_t)_mm256_movemask_pd(_mm256_castsi256_pd(cmp_result));
 
         /*
          * EXPRESSION GENERATION LOOP:
          * 
          * For each of the 4 expressions in this batch:
          * - If prophecy bit is set: AVX2-copy the sacred prophecy (32 bytes, 2 instructions)
          * - Otherwise: call toilet_speak_with_entropy with pre-generated entropy
          * 
          * The key optimization: toilet_speak_with_entropy NEVER calls RNG.
          * All entropy was pre-generated above. The function just consumes
          * the bits and writes the expression. Pure, RNG-free generation.
          */
         for (int i = 0; i < 4; i++) {
             char* output = scroll + scroll_offset;
             int len;
 
             if ((prophecy_mask >> i) & 1) {
                 /*
                  * PROPHECY FAST PATH:
                  * The oracle has spoken. Copy the sacred 24-byte incantation
                  * using a single 32-byte AVX2 operation. The extra 8 bytes
                  * are harmless overflow (null bytes). Speed over purity.
                  */
                 toilet_omega_flush_32(output, SACRED_PROPHECY);
                 len = PROPHECY_SACRED_LENGTH;
             } else {
                 /*
                  * VARIANT PATH:
                  * Generate a unique expression using pre-generated entropy.
                  * entropy1[i] provides structure, entropy2[i] provides variants.
                  * Zero RNG calls. The entropy has already been blessed.
                  */
                 len = toilet_speak_with_entropy(output, entropy1[i], entropy2[i]);
             }
 
             /* Bookkeeping: the necessary overhead of batch operations */
             ctx->call_count++;
             if (inscription_lengths) {
                 inscription_lengths[toilets_flushed] = len;
             }
             output[len] = '\n';
             scroll_offset += len + 1;
             toilets_flushed++;
         }
     }
 
     /*
      * STRAGGLER LOOP: Handle remaining expressions (quota % 4)
      * 
      * When the quota isn't divisible by 4, we fall back to the standard
      * toilet_speak_ultra for the remaining 1-3 expressions. This path
      * uses the traditional 2-RNG-calls-per-expression approach, but
      * it only runs for at most 3 expressions, so the overhead is minimal.
      * 
      * The toilet does not leave stragglers behind. Every dop matters.
      */
     while (toilets_flushed < quota && 
            scroll_offset + SKIBIDI_MIN_BUFFER_SIZE <= scroll_capacity) {
         
         int len = toilet_speak_ultra(rng, scroll + scroll_offset, 1);
         ctx->call_count++;
         if (inscription_lengths) {
             inscription_lengths[toilets_flushed] = len;
         }
         scroll[scroll_offset + len] = '\n';
         scroll_offset += len + 1;
         toilets_flushed++;
     }
 
     return toilets_flushed;
 }
 
 #endif /* TOILET_HAS_RIZZ_256 */
 
 /**
  * @brief Birth a Skibidi Toilet context into the world
  * 
  * This function is the toilet's genesis moment. From a single 64-bit
  * seed, it creates 4 independent RNG channels using SplitMix64,
  * an algorithm that takes one number and splits it into many numbers,
  * much like how one toilet spawned the entire Skibidi multiverse.
  * 
  * Each RNG state is forced to be odd (LSB = 1) because Lehmer64
  * demands odd states for full period. The toilet does not negotiate.
  * The toilet sets the LSB and moves on with its life.
  * 
  * @param ctx The vessel that shall contain the toilet's consciousness
  * @param seed The primordial number from which all dops shall flow
  * @return SKIBIDI_OK if the toilet was born successfully,
  *         SKIBIDI_ERR_NULL_PTR if you tried to birth a toilet into the void
  * 
  * @note Same seed = same dops forever. The toilet is deterministic.
  *       The toilet does not believe in free will. Only in dops.
  * @see skibidi_destroy for when the toilet's time has come
  */
 int skibidi_init(SkibidiContext* ctx, uint64_t seed) {
     if (SKIBIDI_IMPROBABLE(!ctx)) return SKIBIDI_ERR_NULL_PTR;
 
     toilet_vibe_check();
 
     memset(ctx, 0, sizeof(SkibidiContext));
 
     /**
      * SplitMix64 seed expansion: one seed becomes 8 independent states.
      * 
      * The golden ratio constant 0x9E3779B97F4A7C15 is used to space
      * the seeds apart. This constant appears in hash tables, PRNGs,
      * and now, toilet initialization. The golden ratio is truly golden.
      * The toilet appreciates mathematical beauty.
      */
     for (int reincarnation = 0; reincarnation < 4; reincarnation++) {
         uint64_t soul_fragment = seed + (uint64_t)reincarnation * 0x9E3779B97F4A7C15ULL;
         soul_fragment = (soul_fragment ^ (soul_fragment >> 30)) * 0xBF58476D1CE4E5B9ULL;
         soul_fragment = (soul_fragment ^ (soul_fragment >> 27)) * 0x94D049BB133111EBULL;
         soul_fragment = soul_fragment ^ (soul_fragment >> 31);
         ctx->rng.s0[reincarnation] = soul_fragment | 1;
 
         soul_fragment = seed + (uint64_t)reincarnation * 0x9E3779B97F4A7C15ULL + 0x6A09E667F3BCC908ULL;
         soul_fragment = (soul_fragment ^ (soul_fragment >> 30)) * 0xBF58476D1CE4E5B9ULL;
         soul_fragment = (soul_fragment ^ (soul_fragment >> 27)) * 0x94D049BB133111EBULL;
         ctx->rng.s1[reincarnation] = (soul_fragment ^ (soul_fragment >> 31)) | 1;
     }
 
     ctx->rng.buffer_idx = 0;
 
     return SKIBIDI_OK;
 }
 
 /**
  * @brief Reconfigure the global toilet to the user's specifications
  * 
  * Allows the mortal to tell the toilet which SIMD dimension to
  * flush through. The enable_avx512 flag is basically asking the
  * toilet "are you SURE you want to go ultra instinct?" because
  * AVX-512 toilets sometimes cause frequency throttling and the
  * CPU gets sleepy after too much 512-bit flushing.
  * 
  * @param config The mortal's humble toilet configuration request
  * @return SKIBIDI_OK if the toilet accepted the reconfiguration,
  *         SKIBIDI_ERR_NULL_PTR if the mortal forgot to bring a config
  * 
  * @warning Existing toilet contexts will continue flushing with their
  *          old settings. You must re-init each toilet (call skibidi_init)
  *          for the new configuration to take effect. The toilet respects
  *          existing commitments. The toilet has honor.
  * 
  * @note AVX-512 activation requires a triple conjunction:
  *       1. The CPU's silicon must contain the AVX-512 runes (CPUID)
  *       2. The compiler must have been given -mavx512f (compile-time pact)
  *       3. The config must say enable_avx512 = 1 (the mortal's consent)
  *       All three must align, like the stars, like the toilets.
  */
 int skibidi_configure(const SkibidiConfig* config) {
     if (SKIBIDI_IMPROBABLE(!config)) return SKIBIDI_ERR_NULL_PTR;
 
     atomic_store_explicit(&g_toilet_hivemind.toilet_awake, 0, memory_order_release);
 
     uint32_t aura = scan_toilet_chakras();
     atomic_store_explicit(&g_toilet_hivemind.toilet_powers, aura, memory_order_relaxed);
 
     int battle_form = 0;
 
 #if TOILET_HAS_GODMODE_512
     if ((aura & SKIBIDI_CAP_AVX512F) && config->enable_avx512) {
         battle_form = 2;
     } else
 #endif
 #if TOILET_HAS_RIZZ_256
     if (aura & SKIBIDI_CAP_AVX2) {
         battle_form = 1;
     }
 #else
     (void)aura;
 #endif
 
     g_toilet_hivemind.flush_strategy = battle_form;
 
     atomic_thread_fence(memory_order_release);
     atomic_store_explicit(&g_toilet_hivemind.toilet_awake, 1, memory_order_release);
 
     return SKIBIDI_OK;
 }
 
 /**
  * @brief Ask the toilet what configuration it's currently running
  * 
  * The toilet opens its porcelain heart and reveals its settings.
  * 
  * @param config Where the toilet shall disclose its secrets
  * @return SKIBIDI_OK always, unless you pass NULL, in which case the
  *         toilet judges you (SKIBIDI_ERR_NULL_PTR)
  */
 int skibidi_get_config(SkibidiConfig* config) {
     if (SKIBIDI_IMPROBABLE(!config)) return SKIBIDI_ERR_NULL_PTR;
 
     memset(config, 0, sizeof(SkibidiConfig));
     config->enable_avx512 = (g_toilet_hivemind.flush_strategy == 2);
     config->enable_simd_rng = (g_toilet_hivemind.flush_strategy >= 1);
     return SKIBIDI_OK;
 }
 
 /**
  * @brief Generate a single Skibidi expression (THE function. THE one.)
  * 
  * This is what you came here for. This is what the toilet was built for.
  * Call this function and receive a Skibidi expression. ~27% chance of
  * getting the original prophecy. ~73% chance of getting a unique
  * toilet-crafted variant with randomized dop counts, case variants,
  * dom infiltrators, and yes/no endings.
  * 
  * Performance: ~6 cycles on the fast path. That's 1.8 nanoseconds.
  * You literally cannot think the word "dop" faster than this function
  * generates one. The toilet has lapped your brain. Accept it.
  * 
  * @param ctx Your personal toilet (initialized with skibidi_init)
  * @param buffer Where the dops go (minimum SKIBIDI_MIN_BUFFER_SIZE bytes)
  * @param buffer_size How big your buffer is (the toilet will NOT overflow,
  *        unlike that one time at the office)
  * @return Length of the expression in bytes, or a negative number if you
  *         angered the toilet (NULL pointers, tiny buffers, etc.)
  * 
  * @note The buffer is NOT null-terminated. The toilet doesn't null-terminate.
  *       The toilet gives you a length. Use the length. Trust the length.
  *       The length is the toilet's promise. The length is truth.
  */
 TOILET_MAIN_CHARACTER int skibidi_generate(SkibidiContext* ctx, char* buffer, size_t buffer_size) {
     if (SKIBIDI_IMPROBABLE(!ctx | !buffer)) return SKIBIDI_ERR_NULL_PTR;
     if (SKIBIDI_IMPROBABLE(buffer_size < SKIBIDI_MIN_BUFFER_SIZE)) return SKIBIDI_ERR_BUFFER_TOO_SMALL;
 
     ctx->call_count++;
     return toilet_speak_ultra(&ctx->rng, buffer, 1);
 }
 
 /**
  * @brief Generate a variant expression (the toilet NEVER speaks the prophecy)
  * 
  * Like skibidi_generate but the original "Skibidi dop dop yes yes!"
  * is blocked. The toilet is forced to be creative. The toilet must
  * innovate. The toilet will produce a unique variant every time,
  * with different dop counts, case variations, and endings.
  * 
  * Use this when you want pure chaos. When the prophecy is too
  * mainstream. When you need that underground toilet energy.
  * 
  * Performance: ~10 cycles (3.1 ns) because the fast path is disabled
  * and the toilet must walk the full generation path every time.
  * The toilet doesn't complain. The toilet is a professional.
  * 
  * @param ctx The toilet's vessel
  * @param buffer The canvas for the toilet's creativity
  * @param buffer_size Canvas dimensions (must accommodate the toilet's art)
  * @return Length of the toilet's unique artistic expression, or negative error
  */
 TOILET_MAIN_CHARACTER int skibidi_generate_variant(SkibidiContext* ctx, char* buffer, size_t buffer_size) {
     if (SKIBIDI_IMPROBABLE(!ctx | !buffer)) return SKIBIDI_ERR_NULL_PTR;
     if (SKIBIDI_IMPROBABLE(buffer_size < SKIBIDI_MIN_BUFFER_SIZE)) return SKIBIDI_ERR_BUFFER_TOO_SMALL;
 
     ctx->call_count++;
     return toilet_speak_ultra(&ctx->rng, buffer, 0);
 }
 
 /**
  * @brief MASS TOILET PRODUCTION: generate many expressions at once
  * 
  * When one dop is not enough. When you need a FLOOD of dops. When
  * the world needs to hear the toilet's message at industrial scale.
  * This function opens all the stalls and lets the dops flow like
  * water through the pipes of a building-sized Skibidi Toilet.
  * 
  * With AVX2 enabled, processes 4 expressions per iteration using
  * SIMD parallelism. The 4-way RNG generates 256 bits of entropy in
  * ~8 cycles. The SIMD comparison detects prophecy fast-paths across
  * all 4 toilets simultaneously. It's a toilet assembly line.
  * Henry Ford would be proud. Henry Ford would be confused. Henry
  * Ford would need therapy.
  * 
  * Output format: expressions separated by newlines because even in
  * mass production, the toilet believes in proper formatting.
  * 
  * @param ctx The factory foreman (toilet context)
  * @param buffer The warehouse (output buffer for ALL expressions)
  * @param buffer_size Warehouse capacity in bytes
  * @param count Production quota (maximum expressions to manufacture)
  * @param lengths Optional quality control log (individual lengths)
  * @return Actual production output (may be less if warehouse is full)
  * 
  * @note If the buffer runs out mid-production, the toilet gracefully
  *       stops. No half-dops. No incomplete expressions. The toilet
  *       has quality standards. The toilet has ISO 9001 certification.
  */
 int skibidi_generate_batch(SkibidiContext* ctx, char* buffer, 
                            size_t buffer_size, int count, int* lengths) {
     if (SKIBIDI_IMPROBABLE(!ctx | !buffer)) return 0;
     if (SKIBIDI_IMPROBABLE(buffer_size < SKIBIDI_MIN_BUFFER_SIZE)) return 0;
     if (SKIBIDI_IMPROBABLE(count <= 0)) return 0;
 
 #if TOILET_HAS_RIZZ_256
     if (g_toilet_hivemind.flush_strategy >= 1) {
         return toilet_factory_avx2(ctx, buffer, buffer_size, count, lengths);
     }
 #endif
 
     int toilets_flushed = 0;
     size_t scroll_offset = 0;
 
     for (int soul = 0; soul < count && scroll_offset + SKIBIDI_MIN_BUFFER_SIZE <= buffer_size; soul++) {
         int inscription_len = toilet_speak_ultra(&ctx->rng, buffer + scroll_offset, 1);
         if (SKIBIDI_IMPROBABLE(inscription_len < 0)) break;
 
         ctx->call_count++;
         if (lengths) lengths[soul] = inscription_len;
         buffer[scroll_offset + inscription_len] = '\n';
         scroll_offset += inscription_len + 1;
         toilets_flushed++;
     }
 
     return toilets_flushed;
 }
 
 /**
  * @brief End the toilet's existence (secure destruction)
  * 
  * The toilet's final flush. All memory is overwritten with zeros
  * using volatile writes so the compiler cannot optimize away the
  * toilet's death. The RNG state is obliterated. The dop counts
  * are forgotten. The toilet's consciousness returns to the void.
  * 
  * This is important for security because if someone reads the
  * toilet's RNG state from memory, they could predict future dops.
  * And in the wrong hands, predicted dops could be... well, actually
  * they'd just be Skibidi expressions. But the toilet takes OPSEC
  * seriously. The toilet has read the NIST guidelines.
  * 
  * @param ctx The toilet to destroy (NULL is accepted, even the void is valid)
  * 
  * @note The volatile keyword ensures the compiler doesn't say "lol
  *       nobody reads this memory after this function, I'll just skip
  *       the zeroing." NO. The toilet WILL be zeroed. The toilet's
  *       memory WILL be cleansed. The toilet demands a clean death.
  */
 void skibidi_destroy(SkibidiContext* ctx) {
     if (ctx) {
         volatile uint64_t* porcelain = (volatile uint64_t*)ctx;
         for (size_t shard = 0; shard < sizeof(SkibidiContext) / sizeof(uint64_t); shard++) {
             porcelain[shard] = 0;
         }
     }
 }
 
 /**
  * @brief Summon a properly aligned toilet from the heap dimension
  * 
  * Allocates a 64-byte-aligned context because the toilet demands
  * cache line alignment. An unaligned toilet is a sad toilet. A sad
  * toilet produces slow dops. We cannot allow slow dops.
  * 
  * @return A fresh toilet, aligned and ready for initialization,
  *         or NULL if the heap has no room for another toilet (tragic)
  * 
  * @note You MUST call skibidi_free_context to release the toilet
  *       when you're done. Leaked toilets are an environmental hazard.
  * @see skibidi_free_context for the toilet deallocation ceremony
  */
 SkibidiContext* skibidi_alloc_context(void) {
     return (SkibidiContext*)SKIBIDI_ALIGNED_ALLOC(64, sizeof(SkibidiContext));
 }
 
 /**
  * @brief Summon an entire BATTALION of aligned toilets
  * 
  * For multi-threaded Skibidi operations where each thread needs its
  * own toilet. All toilets are allocated in a contiguous block with
  * 64-byte alignment to prevent false sharing (when two threads
  * accidentally share a cache line with their toilets, causing
  * performance to drop and the toilets to argue).
  * 
  * @param count Number of toilets in the battalion
  * @return Pointer to the first toilet in the formation, or NULL if
  *         the heap cannot accommodate this many toilets
  * 
  * @note Each toilet must be individually initialized with skibidi_init.
  *       The toilets do not share consciousness. Each toilet is its own
  *       universe. Each toilet has its own dop destiny.
  * @note Use skibidi_free_context to dismiss the entire battalion at once
  */
 SkibidiContext* skibidi_alloc_context_array(size_t count) {
     if (count == 0) return NULL;
     return (SkibidiContext*)SKIBIDI_ALIGNED_ALLOC(64, count * sizeof(SkibidiContext));
 }
 
 /**
  * @brief Release a toilet back to the heap (with full funeral rites)
  * 
  * First destroys the toilet's consciousness (secure zeroing),
  * then frees the aligned memory back to the allocator. The toilet
  * is gone. The dops it generated live on in the buffers it wrote to.
  * The toilet's legacy is its dops. Remember the toilet's dops.
  * 
  * @param ctx The toilet to free (NULL is accepted, freeing nothing is free)
  */
 void skibidi_free_context(SkibidiContext* ctx) {
     if (ctx) {
         skibidi_destroy(ctx);
         SKIBIDI_ALIGNED_FREE(ctx);
     }
 }
 
 /**
  * @brief Reveal the toilet engine's version string
  * @return The version inscription on the toilet's porcelain base
  */
 const char* skibidi_version(void) {
     return TOILET_FIRMWARE_VERSION;
 }
 
 /**
  * @brief Ask the CPU: "bro do you even AVX2?"
  * @return Non-zero if the CPU has unlocked the 256-bit toilet dimension
  */
 int skibidi_has_avx2(void) {
     toilet_vibe_check();
     return (atomic_load_explicit(&g_toilet_hivemind.toilet_powers, memory_order_relaxed) & 
             SKIBIDI_CAP_AVX2) != 0;
 }
 
 /**
  * @brief Ask the CPU: "have you achieved AVX-512 toilet transcendence?"
  * @return Non-zero if the CPU has entered the 512-bit shadow realm
  */
 int skibidi_has_avx512(void) {
     toilet_vibe_check();
     return (atomic_load_explicit(&g_toilet_hivemind.toilet_powers, memory_order_relaxed) & 
             SKIBIDI_CAP_AVX512F) != 0;
 }
 
 /**
  * @brief Read the CPU's complete toilet power level (it's over 9000)
  * @return Bitmask of SKIBIDI_CAP_* flags representing the CPU's toilet chi
  */
 uint32_t skibidi_get_capabilities(void) {
     toilet_vibe_check();
     return atomic_load_explicit(&g_toilet_hivemind.toilet_powers, memory_order_relaxed);
 }
 
 /**
  * @brief Which toilet dimension are we flushing through right now?
  * @return "AVX-512" (godmode), "AVX2" (sigma), or "Scalar" (literally Ohio)
  */
 const char* skibidi_get_active_simd(void) {
     toilet_vibe_check();
     switch (g_toilet_hivemind.flush_strategy) {
         case 2:  return "AVX-512";
         case 1:  return "AVX2";
         default: return "Scalar";
     }
 }
 
 /**
  * @brief Is the toilet currently in AVX-512 ultra instinct mode?
  * @return Non-zero if the toilet has gone beyond, plus ultra, final form
  */
 int skibidi_is_avx512_enabled(void) {
     toilet_vibe_check();
     return g_toilet_hivemind.flush_strategy == 2;
 }
 
 /**
  * @brief How many bytes does the toilet's brain occupy?
  * @return Size of SkibidiRngState in bytes (the toilet's cranial capacity)
  */
 size_t skibidi_get_rng_state_size(void) {
     return sizeof(SkibidiRngState);
 }
 
 /**
  * @brief How many bytes does the entire toilet body occupy?
  * @return Size of SkibidiContext in bytes (the toilet's BMI, basically)
  */
 size_t skibidi_get_context_size(void) {
     return sizeof(SkibidiContext);
 }
 
 /**
  * @brief What alignment does the toilet require for optimal feng shui?
  * @return Alignment in bytes (64, because the toilet respects cache line boundaries
  *         and the cache line respects the toilet, it's a mutual respect situation)
  */
 size_t skibidi_get_context_alignment(void) {
     return _Alignof(SkibidiContext);
 }