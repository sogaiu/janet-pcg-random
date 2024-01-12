(import pcgrand)

(comment

  (def rng
    (pcgrand/make (int/u64 "1") (int/u64 "1")))

  (pcgrand/random rng)
  # =>
  -914190447

  (:random rng)
  # =>
  361947764

  )

(comment

  (def rng
    (pcgrand/make (int/u64 "1") (int/u64 "1")))

  (pcgrand/boundedrand rng 28)
  # =>
  9

  (:boundedrand rng 9)
  # =>
  2

  )

(comment

  (def rng
    (pcgrand/make (int/u64 "1") (int/u64 "1")))

  (pcgrand/random rng)
  # =>
  -914190447

  (:random rng)
  # =>
  361947764

  (pcgrand/srandom rng (int/u64 "1") (int/u64 "1"))
  # =>
  nil

  (:random rng)
  # =>
  -914190447

  )

