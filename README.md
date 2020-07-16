# janet-pcg-random

[Janet](https://janet-lang.org/) bindings for the [PCG
Random](https://www.pcg-random.org/) pseudo random number generator.

## Status

Early stage, expect changes :)

## Installation

```
jpm install https://github.com/sogaiu/janet-pcg-random
```

## Usage

`pcgrand/make` creates a seeded generator instance:

```
(pcgrand/make (int/u64 "1") (int/u64 "1"))
# => <pcgrand/rng 0x5570B7F0EF80>
```

Use two `int/64` values to seed: the state initializer and sequence
selection constant (stream id).

`pcgrand/random` returns a uniformly distributed 32-bit integer.

```
(def rng (pcgrand/make (int/u64 "1") (int/u64 "1")))
# => <pcgrand/rng 0x55E021F18930>

(pcgrand/random rng)
# => -914190447

(:random rng)
# => 361947764
```

`pcgrand/boundedrand` returns a uniformly distributed integer, i,
where 0 <= i < bound.

```
(def rng (pcgrand/make (int/u64 "1") (int/u64 "1")))
# => <pcgrand/rng 0x55E021F1A3C0>

(pcgrand/boundedrand rng 28)
# => 9

(:boundedrand rng 9)
# => 2
```

`pcgrand/srandom` seeds a generator using two `int/u64` values in a
manner similar to `pcgrand/make`:

```
(def rng (pcgrand/make (int/u64 "1") (int/u64 "1")))
# => <pcgrand/rng 0x55E021F1AFB0>

(pcgrand/random rng)
# => -914190447

(:random rng)
# => 361947764

(pcgrand/srandom rng 0 1 0 1)
# => nil

(:random rng)
# => -914190447
```

## Acknowledgments

* andrewchambers - discussion, sample code
* bakpakin - janet, sample code
* cellularmitosis - documented sample code
* pyrmont - documented sample code
