#include <janet.h>
#include "pcg_variants.h"

static int janet_pcgrng_get(void* p, Janet key, Janet* out);

static void janet_pcgrng_marshal(void* p, JanetMarshalContext* ctx) {
  pcg32_random_t* pcgrng = (pcg32_random_t*) p;
  janet_marshal_abstract(ctx, p);
  janet_marshal_int(ctx, (int64_t) pcgrng->state);
  janet_marshal_int(ctx, (int64_t) pcgrng->inc);
}

static void* janet_pcgrng_unmarshal(JanetMarshalContext* ctx) {
  pcg32_random_t* pcgrng =
    janet_unmarshal_abstract(ctx, sizeof(pcg32_random_t));
  pcgrng->state = (uint64_t) janet_unmarshal_int(ctx);
  pcgrng->inc = (uint64_t) janet_unmarshal_int(ctx);
  return pcgrng;
}

const JanetAbstractType janet_pcgrng_type = {
  "pcgrand/rng",
  NULL,
  NULL,
  janet_pcgrng_get,
  NULL,
  janet_pcgrng_marshal,
  janet_pcgrng_unmarshal,
  JANET_ATEND_UNMARSHAL
};

static Janet cfun_pcgrng_make(int32_t argc, Janet* argv) {
  janet_fixarity(argc, 2);
  pcg32_random_t* pcgrng =
    janet_abstract(&janet_pcgrng_type, sizeof(pcg32_random_t));
  void* abst0 = janet_unwrap_abstract(argv[0]);
  const uint64_t initstate = *(uint64_t*) abst0;
  void* abst1 = janet_unwrap_abstract(argv[1]);
  const uint64_t initseq = *(uint64_t*) abst1;
  pcg32_srandom_r(pcgrng, initstate, initseq);
  return janet_wrap_abstract(pcgrng);
}

static Janet cfun_srandom(int32_t argc, Janet* argv) {
  janet_fixarity(argc, 3);
  pcg32_random_t* pcgrng = janet_getabstract(argv, 0, &janet_pcgrng_type);
  void* abst1 = janet_unwrap_abstract(argv[1]);
  const uint64_t initstate = *(uint64_t*) abst1;
  void* abst2 = janet_unwrap_abstract(argv[2]);
  const uint64_t initseq = *(uint64_t*) abst2;
  pcg32_srandom_r(pcgrng, initstate, initseq);
  return janet_wrap_nil();
}

static Janet cfun_random(int32_t argc, Janet* argv) {
  janet_fixarity(argc, 1);
  pcg32_random_t* pcgrng = janet_getabstract(argv, 0, &janet_pcgrng_type);
  return janet_wrap_integer(pcg32_random_r(pcgrng));
}

static Janet cfun_boundedrand(int32_t argc, Janet* argv) {
  janet_fixarity(argc, 2);
  pcg32_random_t* pcgrng = janet_getabstract(argv, 0, &janet_pcgrng_type);
  const uint32_t bound = janet_getinteger(argv, 1);
  return janet_wrap_integer(pcg32_boundedrand_r(pcgrng, bound));
}

static const JanetMethod pcgrng_methods[] = {
  {"srandom", cfun_srandom},
  {"random", cfun_random},
  {"boundedrand", cfun_boundedrand},
  {NULL, NULL}
};

static int janet_pcgrng_get(void* p, Janet key, Janet* out) {
  (void) p;
  if (!janet_checktype(key, JANET_KEYWORD)) {
    return 0;
  }
  return janet_getmethod(janet_unwrap_keyword(key), pcgrng_methods, out);
}

static const JanetReg cfuns[] = {
  {"make", cfun_pcgrng_make,
   "(pcgrand/make initstate initseq)\n\n"
   "Create a pcg random 32 pseudorandom number generator.\n"
   "Seed using two int/u64 values, state initializer and a "
   "sequence selection constant (a.k.a. stream id).\n"},
  {"srandom", cfun_srandom,
   "(pcgrand/srandom rng initstate initseq)\n\n"
   "Seed the rng.\n"
   "Seed using two int/u64 values, state initializer and a "
   "sequence selection constant (a.k.a. stream id).\n"},
  {"random", cfun_random,
   "(pcgrand/random rng)\n\n"
   "Generate a uniformly distributed 32-bit random number."},
  {"boundedrand", cfun_boundedrand,
   "(pcgrand/boundedrand rng)\n\n"
   "Generate a uniformly distributed integer, i, where 0 <= i < bound."},
  {NULL, NULL, NULL}
};

JANET_MODULE_ENTRY(JanetTable* env) {
  janet_register_abstract_type(&janet_pcgrng_type);
  janet_cfuns(env, "pcgrand", cfuns);
}
