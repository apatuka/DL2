// FUN_004935fc @ 004935fc size=303 sig=undefined FUN_004935fc() cc=unknown
// callers: FUN_004a0ff9,FUN_004a08c5,FUN_0049c710,FUN_004a5a0b,FUN_0049e47a,FUN_0041e4d0,FUN_004a060f,FUN_00493b24,FUN_0049da81,FUN_00463e20,FUN_0047eed8,FUN_004877c8,FUN_0049d7f4,FUN_004a016e,FUN_0049c54a,FUN_00464620,FUN_00492d67,FUN_0049c5e7,FUN_0043c78c,FUN_00463e88,FUN_00463ee0,FUN_004897ea,FUN_00414bd8,FUN_004a03cf,FUN_0049372b
// callees: FUN_00499b9f,FUN_0048e89c,FUN_00499840

void FUN_004935fc(int param_1,int param_2,int param_3,int param_4,uint param_5)

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
            if ((param_5 & 0x80000000) != 0) {
              param_5 = FUN_00499b9f(DAT_0051bddc,param_5);
            }
            if (*(int *)(DAT_0051bddc + 0xc) == 8) {
              param_5 = param_5 & 0xff;
              param_5 = param_5 | param_5 << 8 | param_5 << 0x10 | param_5 << 0x18;
            }
            else if (*(int *)(DAT_0051bddc + 0xc) == 0x10) {
              param_5 = param_5 & 0xffff | (param_5 & 0xffff) << 0x10;
            }
            FUN_00499840(param_1,param_2);
            FUN_0048e89c(param_4 - param_2,
                         (param_3 - param_1) * (*(int *)(DAT_0051bddc + 0xc) + 7 >> 3),param_5,
                         DAT_0051c3c4,DAT_0051c3c0);
          }
        }
      }
    }
  }
  return;
}

