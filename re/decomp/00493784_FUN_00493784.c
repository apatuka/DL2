// FUN_00493784 @ 00493784 size=496 sig=undefined FUN_00493784() cc=unknown
// callers: FUN_004644f8,FUN_0046411c,FUN_00464620,FUN_0043acd4,FUN_0046458c,DisableMainInterface,FUN_00468a28,FUN_00415180,FUN_00493de5,DisableMainInterface_c1a4
// callees: FUN_0048e89c,FUN_0048f670,FUN_00499840,FUN_0048f55d,FUN_0048f507,FUN_0048f5b3

void FUN_00493784(int param_1,int param_2,int param_3,int param_4,uint param_5,undefined4 param_6,
                 int param_7)

{
  if (param_1 < DAT_0065e57c) {
    if (param_1 < DAT_0065e574) {
      param_1 = DAT_0065e574;
    }
    if (DAT_0065e574 <= param_3) {
      if (DAT_0065e57c < param_3) {
        param_3 = DAT_0065e57c;
      }
      if ((param_1 < param_3) && (param_2 < DAT_0065e578)) {
        if (param_2 < DAT_0065e570) {
          param_2 = DAT_0065e570;
        }
        if (param_4 != DAT_0065e570) {
          if (DAT_0065e578 < param_4) {
            param_4 = DAT_0065e578;
          }
          if (param_2 < param_4) {
            FUN_00499840(param_1,param_2);
            if (*(int *)(DAT_0051bddc + 0xc) == 8) {
              if (param_7 == 0) {
                param_5 = param_5 & 0xff;
                FUN_0048e89c(param_4 - param_2,param_3 - param_1,
                             param_5 | param_5 << 8 | param_5 << 0x10 | param_5 << 0x18,DAT_0051c3c4
                             ,DAT_0051c3c0);
              }
            }
            else if (*(int *)(DAT_0051bddc + 0xc) == 0x10) {
              if (param_7 == 0) {
                FUN_0048e89c(param_4 - param_2,(param_3 - param_1) * 2,
                             param_5 & 0xffff | (param_5 & 0xffff) << 0x10,DAT_0051c3c4,DAT_0051c3c0
                            );
              }
              else if (param_7 == 1) {
                FUN_0048f507(param_4 - param_2,param_3 - param_1,param_5,DAT_0051c3c4,DAT_0051c3c0);
              }
              else if (param_7 == 2) {
                FUN_0048f55d(param_4 - param_2,param_3 - param_1,param_5,DAT_0051c3c4,DAT_0051c3c0);
              }
              else if (param_7 == 3) {
                DAT_0051d6e0 = param_5 * 0x400 + DAT_0051e218;
                if (*(short *)(DAT_0051bddc + 0x26) == 2) {
                  FUN_0048f5b3(param_4 - param_2,param_3 - param_1,param_6,DAT_0051c3c4,DAT_0051c3c0
                              );
                }
                else {
                  FUN_0048f670(param_4 - param_2,param_3 - param_1,param_6,DAT_0051c3c4,DAT_0051c3c0
                              );
                }
              }
            }
          }
        }
      }
    }
  }
  return;
}

