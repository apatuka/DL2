// FUN_0045ef64 @ 0045ef64 size=107 sig=undefined FUN_0045ef64() cc=unknown
// callers: FUN_0043baf4,FUN_0043be98
// callees: FUN_0041b280,FUN_0045ee88,FUN_0042836c
// strings: \"Sorry, but you may only place buildings in territories you own and have settled.\"|\"Oolan's Advice\"

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_0045ef64(void)

{
  int iVar1;
  
  if (DAT_004d59b4 == 1) {
    if ((DAT_004d5aa0 == '\0') &&
       ((*(char *)(DAT_00657de0 + 0x20) != DAT_0058f1f4 || (*(short *)(DAT_00657de0 + 0x30) == 0))))
    {
      FUN_0042836c(PTR_s_Oolan_s_Advice_00508fa4,PTR_s_Sorry__but_you_may_only_place_bu_00509784,4,0
                   ,9);
    }
    else {
      iVar1 = FUN_0041b280(DAT_00657de0);
      if (iVar1 != 0) {
        FUN_0045ee88(iVar1);
        DAT_004d1c7c = 1;
        _DAT_004c5b6c = 1;
        return;
      }
    }
  }
  return;
}

