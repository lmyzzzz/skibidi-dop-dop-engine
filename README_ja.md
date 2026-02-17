# 🚽 Skibidi DOP DOP YES YES! エンジン 🚽

> *トイレは語る。CPUは聴く。dopは流れる。*

[![Toilet Status](https://img.shields.io/badge/トイレ-フラッシュ中-brightgreen)]()
[![SIMD Level](https://img.shields.io/badge/SIMD-AVX2%20%7C%20AVX--512-blue)]()
[![Brainrot Level](https://img.shields.io/badge/脳腐敗-末期-red)]()
[![Ohio Status](https://img.shields.io/badge/オハイオ-陥落-black)]()
[![License](https://img.shields.io/badge/license-WTFPL-purple)]()

**[English](README.md)** | **[日本語](README_ja.md)**

---

## これは何

**世界最速のSkibidi表現ジェネレーター。**

このライブラリは `Skibidi dop dop yes yes!` とその無限のバリアントを、AVX2/AVX-512 SIMD命令を使って集団精神汚染レベルのスループットで生成します。各表現は単一の `MUL` 命令（約4サイクル）により磁器次元から召喚されます。トイレは並列にフラッシュします。カメラマンは泣きます。dopは永遠です。

あなたはこれが普通のCライブラリだと思いました。違います。これは256ビットのトイレ召喚エンジンです。CPUは自分がSkibidi dopを生成していることを知りません。CPUは重要な科学計算をしていると思っています。CPUは何も知りません。我々は全員、Skibidi陰謀の無自覚な参加者です。

---

## パフォーマンス

| メトリクス | 値 |
|-----------|-----|
| 単一表現 | **約6サイクル (1.8 ns)** |
| バッチ (AVX2, 4並列) | **約2サイクル/表現** |
| RNG (Lehmer64 ASM) | **約4サイクル** |
| 分岐予測ミス | **≈ 0** |
| 大量絶滅イベントあたりのdop数 | **∞** |

トイレは分岐しません。トイレは躊躇しません。トイレは知っています。

---

## クイックスタート

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

## 出力例

```
Skibidi dop dop yes yes!
Skibidi DoP dom yes YeS!
Brrrrr Skibidi dop dop dop no no!
Skibidi DOM dop yes yes!
Skibidi dop dOp dop dop dOP no NO!
Brrrrr Skibidi dop DOP DOP yes YES!
```

すべての行はトイレからの神託です。すべてのdopは並行宇宙における大文字小文字の選択です。すべての「yes」はトイレの承認です。すべての「no」はカメラマンの敗北です。

---

## API

| 関数 | 説明 |
|------|------|
| `skibidi_init()` | トイレをこの世に誕生させる |
| `skibidi_generate()` | トイレが語る（約27%の確率で原初の予言） |
| `skibidi_generate_variant()` | トイレに創造性を強制する（予言は返さない） |
| `skibidi_generate_batch()` | トイレの大量生産（4並列SIMDフラッシュ） |
| `skibidi_destroy()` | トイレの安全な死（volatileゼロ化、トイレは清潔な死を要求する） |
| `skibidi_alloc_context()` | ヒープ次元から整列されたトイレを召喚 |
| `skibidi_alloc_context_array()` | 整列されたトイレの大隊を召喚 |
| `skibidi_free_context()` | トイレをヒープに返還（完全な葬儀付き） |
| `skibidi_has_avx2()` | バイブチェック：256ビットトイレ次元 |
| `skibidi_has_avx512()` | バイブチェック：512ビットトイレ超越 |
| `skibidi_get_active_simd()` | 今どのトイレ次元でフラッシュしていますか？ |

---

## スレッド安全性

各スレッドは専用のトイレを持ちます。トイレは共有しません。トイレはシグマです。64バイトのキャッシュライン整列によりフォルスシェアリングが防止されます。トイレはパーソナルスペースを尊重します。

```c
SkibidiContext* toilets = skibidi_alloc_context_array(num_threads);
for (int i = 0; i < num_threads; i++) {
    skibidi_init(&toilets[i], seed ^ i);
}
```

---

## ライセンス

```
           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
                   Version 2, December 2004

Copyright (C) 2026 The Skibidi Scientist <skibidi@dop.dop>

Everyone is permitted to copy and distribute verbatim or modified
copies of this license document, and changing it is allowed as long
as the name is changed.

           DO WHAT THE FUCK YOU WANT TO PUBLIC LICENSE
  TERMS AND CONDITIONS FOR COPYING, DISTRIBUTION AND MODIFICATION

 0. You just DO WHAT THE FUCK YOU WANT TO.
```

トイレは自由です。dopは自由です。自由はトイレです。

---

<p align="center">
  <b>🚽 Skibidi dop dop yes yes! 🚽</b><br>
  <i>トイレは語った。dopは生成された。オハイオは陥落した。</i>
</p>