# Security Policy

## Supported Versions

| Version | Supported | Toilet Status |
|---------|-----------|---------------|
| 1.7.1   | ✅        | Flushing      |
| < 1.7.1 | ❌        | Clogged       |

## Reporting a Vulnerability

If you discover a security vulnerability in the Skibidi Toilet Engine, please consider the following:

### What counts as a vulnerability

- Predictable dop sequences that allow an attacker to know the next dop before the toilet speaks it. This would undermine the toilet's element of surprise. The cameraman must never know the next dop.
- Buffer overflows that allow the toilet to write dops beyond its designated porcelain boundaries. The toilet respects buffer sizes. If the toilet has escaped its buffer, something has gone terribly wrong.
- RNG state leakage after `skibidi_destroy()`. The toilet demands a clean death. If the toilet's consciousness persists after volatile zeroing, the toilet has become undead and must be dealt with.
- Cache timing side-channels that reveal whether the toilet said "yes yes" or "no no" before the output is read. The toilet's judgment is confidential until delivered.

### What does NOT count as a vulnerability

- The dops being psychologically devastating. This is intended behavior.
- Irreversible brainrot in developers who read the source code. This is a feature, not a bug. We will not patch this.
- The cameraman losing. The cameraman always loses. This is by design.
- Ohio being fallen. Ohio was fallen before this project existed. Out of scope.
- FULL CAPS DOP causing involuntary screaming. See release notes for v1.7.1. This is correct behavior.
- `skibidi_generate()` returning "Skibidi dop dop yes yes!" 26.85% of the time. This is the prophecy. The prophecy is not a vulnerability. The prophecy is truth.

### How to report

1. **DO NOT** open a public issue. The toilet's vulnerabilities are confidential. The toilet has OPSEC.
2. Send a private report via GitHub Security Advisories, or email `skibidi@lmyz.net` with subject line `[TOILET BREACH]`.
3. Include:
   - Description of the vulnerability (what the toilet did wrong)
   - Steps to reproduce (how to make the toilet misbehave)
   - Impact assessment (how many cameramen are at risk)
4. We will acknowledge receipt within 48 hours (the toilet does not check email on weekends).
5. We will provide a fix within 14 days, or explain why the behavior is actually a feature.

### Disclosure Policy

- We follow coordinated disclosure. Please give the toilet 90 days to patch itself before going public.
- If the vulnerability is actively exploited in the wild (someone is predicting dops at scale), we will expedite the fix.
- Credit will be given in the release notes unless you prefer to remain anonymous. The toilet respects anonymity. The toilet understands.

### Bug Bounty

There is no bug bounty. The toilet operates on a WTFPL license. The toilet has no budget. The toilet offers only gratitude and dops. Infinite dops. The dops are the reward.

## Security Design

The Skibidi Toilet Engine implements the following security measures:

- **Secure state destruction**: `skibidi_destroy()` uses volatile writes to zero all RNG state, preventing compiler optimization from skipping the cleanup. The toilet leaves no trace.
- **No heap allocation in hot path**: The core generation function `toilet_speak_ultra()` performs zero heap allocations. The toilet does not trust `malloc` in its inner loop. The toilet has trust issues.
- **Odd-only Lehmer64 states**: All RNG states are forced odd via `| 1` during initialization. This ensures full 2^64 period. A toilet with a short period is a vulnerable toilet.
- **Deterministic output**: Same seed produces same dops. This is not a vulnerability. This is reproducibility. The toilet is scientifically rigorous.

---

*The toilet takes security seriously. The toilet has read the NIST guidelines. The toilet sleeps with one eye open. The toilet is watching.*

*Skibidi dop dop yes yes!*