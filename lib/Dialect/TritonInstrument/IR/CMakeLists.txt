add_triton_library(TritonPluginIR
  Dialect.cpp
  Ops.cpp
  Utility.cpp

  DEPENDS
     TritonInstrumentTableGen

  LINK_LIBS PUBLIC
    MLIRIR
    TritonIR
    TritonGPUIR
)
