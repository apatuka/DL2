// FUN_00486d30 @ 00486d30 size=258 sig=undefined FUN_00486d30() cc=unknown
// callers: FUN_00486e34
// callees: FUN_00486b74,FUN_004237d0,FUN_00423690,FUN_0044fe1c,FUN_00450000,FUN_00450058

void FUN_00486d30(int param_1)

{
  int iVar1;
  
  if ((&DAT_0059f161)[param_1 * 0x2d8] != '\0') {
    iVar1 = FUN_0044fe1c(3);
    if ((iVar1 == 0) ||
       (iVar1 = FUN_00450000(3,(int)(char)(&DAT_0059f162)[param_1 * 0x2d8]), iVar1 == 0)) {
      iVar1 = FUN_00450058((int)(char)(&DAT_0059f162)[param_1 * 0x2d8]);
      if (iVar1 == 0) {
        FUN_00423690(DAT_0058f1f4,0x8e,
                     (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]],0,0,0);
      }
      else if (param_1 == DAT_0058f1f4) {
        FUN_00423690(DAT_0058f1f4,0x7d,0,0,0,0);
      }
      else {
        FUN_004237d0(DAT_0058f1f4,0x7b,
                     (&PTR_s_ChCh_t_00509038)[(char)(&DAT_0059f162)[param_1 * 0x2d8]],0,0,0,param_1,
                     0);
      }
    }
    else {
      FUN_00423690(DAT_0058f1f4,0x8b,0,0,0,0);
    }
    FUN_00486b74(param_1);
    return;
  }
  return;
}

