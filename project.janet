(declare-project
  :name "pcgrand"
  :description "Janet bindings for PCG Random"
  :url "https://github.com/sogaiu/janet-pcg-random"
  :repo "git+https://github.com/sogaiu/janet-pcg-random")

(declare-native
  :name "pcgrand"
  :cflags   [;default-cflags
             "-Ipcg-c/include"
             "-std=c99" "-Wall" "-Wextra"]
  :headers ["pcg-c/include/pcg_variants.h"]
  :source ["pcg-c/src/pcg-advance-32.c"
           "pcg_random.c"])
