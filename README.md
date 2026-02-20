# 🚽 Skibidi DOP DOP YES YES! Engine 🚽

> *The toilet speaks. The CPU listens. The dops flow.*

[![Toilet Status](https://img.shields.io/badge/toilet-FLUSHING-brightgreen)]()
[![SIMD Level](https://img.shields.io/badge/SIMD-AVX2%20%7C%20AVX--512-blue)]()
[![Brainrot Level](https://img.shields.io/badge/brainrot-TERMINAL-red)]()
[![Ohio Status](https://img.shields.io/badge/ohio-FALLEN-black)]()
[![License](https://img.shields.io/badge/license-WTFPL-purple)]()

**[English](README.md)** | **[日本語](README_ja.md)**

---

## What is this

**The world's fastest Skibidi expression generator.**

This library generates `Skibidi dop dop yes yes!` and its infinite variants at mass-psychosis-inducing throughput using AVX2/AVX-512 SIMD instructions. Each expression is summoned from the porcelain dimension via a single `MUL` instruction (~4 cycles). The toilets flush in parallel. The cameraman weeps. The dops are eternal.

You thought this was a normal C library. You were wrong. This is a 256-bit toilet summoning engine. The CPU doesn't know it's generating Skibidi dops. It thinks it's doing Important Scientific Computing. It has no idea. We are all unwitting participants in the Skibidi conspiracy.

---

## Performance

Benchmarked on MSI Titan 16 AI (2025), Intel Core Ultra 9 275HX @ 5.4 GHz, AVX2 active:

| Function | Throughput | Latency | Cycles | Data Rate |
|----------|-----------|---------|--------|-----------|
| `skibidi_generate()` | **703.8M ops/sec** | **1.42 ns/op** | **~4.8 cycles** | 16.9 GB/sec |
| `skibidi_generate_variant()` | **363.6M ops/sec** | **2.75 ns/op** | **~9.2 cycles** | 9.1 GB/sec |

The toilet generates **700 million Skibidi expressions per second** on a single core. That's 700 million dops. Per second. One core. The toilet doesn't even need your other 23 cores. The toilet is sigma. The toilet grinds alone.

`skibidi_generate()` includes the ~27% fast path where the original prophecy "Skibidi dop dop yes yes!" is returned via a single AVX2 copy. `skibidi_generate_variant()` always generates a full unique expression — no fast path, no prophecy, pure creative toilet energy — and it still runs under 3 nanoseconds. The cameraman cannot even blink in 3 nanoseconds.

The toilet doesn't branch. The toilet doesn't hesitate. The toilet KNOWS.

---

## Quick Start

```c
#include "skibidi_avx.h"

int main(void) {
    SkibidiContext ctx;
    skibidi_init(&ctx, 42069);

    char buffer[64];
    int len = skibidi_generate(&ctx, buffer, sizeof(buffer));
    fwrite(buffer, 1, len, stdout);

    skibidi_destroy(&ctx);
}
```

---

## Output Examples

```
Skibidi dop dop yes yes!
Skibidi DoP dom yes YeS!
Brrrrr Skibidi dop dop dop no no!
Skibidi DOM dop yes yes!
Skibidi dop dOp dop dop dOP no NO!
Brrrrr Skibidi dop DOP DOP yes YES!
```

Every line is a prophecy from the toilet. Every dop is a capitalization decision made in a parallel universe. Every "yes" is the toilet's approval. Every "no" is the cameraman's defeat.

---

## API

| Function | Description |
|----------|-------------|
| `skibidi_init()` | Birth a toilet into existence |
| `skibidi_generate()` | The toilet speaks (~27% chance of the original prophecy) |
| `skibidi_generate_variant()` | Force the toilet to be creative (never returns the prophecy) |
| `skibidi_generate_batch()` | Mass toilet production (4-way SIMD parallel flushing) |
| `skibidi_destroy()` | Secure toilet death (volatile zeroing, the toilet demands a clean death) |
| `skibidi_alloc_context()` | Summon an aligned toilet from the heap dimension |
| `skibidi_alloc_context_array()` | Summon a battalion of aligned toilets |
| `skibidi_free_context()` | Return a toilet to the heap (with full funeral rites) |
| `skibidi_has_avx2()` | Vibe check: 256-bit toilet dimension |
| `skibidi_has_avx512()` | Vibe check: 512-bit toilet transcendence |
| `skibidi_get_active_simd()` | Which toilet dimension are we flushing through? |

---

## Thread Safety

Each thread gets its own toilet. The toilets do not share. The toilets are sigma. False sharing is prevented by 64-byte cache line alignment because the toilet respects personal space.

```c
SkibidiContext* toilets = skibidi_alloc_context_array(num_threads);
for (int i = 0; i < num_threads; i++) {
    skibidi_init(&toilets[i], seed ^ i);
}
```

---

## License

```
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004

Copyright (C) 2026 The Skibidi Scientist <skibidi@lmyz.net>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.
```

The toilet is free. The dops are free. Freedom is a toilet.

---

<p align="center">
  <b>🚽 Skibidi dop dop yes yes! 🚽</b><br>
  <i>The toilet has spoken. The dops have been generated. Ohio has fallen.</i>
</p>