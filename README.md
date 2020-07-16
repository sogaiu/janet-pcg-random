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
(pcgrand/make 0 1 0 1)
# => <pcgrand/rng 0x5570B7F0EF80>
```

Please specify 4 32-bit integers [1].  These will represent 2 64-bit
integers, which represent the state initializer and sequence selection
constant (stream id) respectively.

`pcgrand/random` returns a uniformly distributed 32-bit integer.

```
(def rng (pcgrand/make 0 1 0 1))
# => <pcgrand/rng 0x55E021F18930>

(pcgrand/random rng)
# => -914190447
```

`pcgrand/boundedrand` returns a uniformly distributed integer, i,
where 0 <= i < bound.

```
(def rng (pcgrand/make 0 1 0 1))
# => <pcgrand/rng 0x55E021F1A3C0>

(pcgrand/boundedrand rng 28)
# => 9
```

`pcgrand/srandom` seeds a generator using 4 32-bit integers in a
manner similar to `pcgrand/make`:

```
(def rng (pcgrand/make 0 1 0 1))
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

## Footnotes

[1] IIUC, Janet's numbers don't allow specification of all 64-bit
    integers in a straight-forward manner, so 2 32-bit integers are
    used to fake it.  The first is used for the high order 32 bits and the
    second is used for the low order 32 bits.
