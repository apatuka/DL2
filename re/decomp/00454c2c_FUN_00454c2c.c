// FUN_00454c2c @ 00454c2c size=216 sig=undefined FUN_00454c2c() cc=unknown
// callers: FUN_00454d94,FUN_00451550
// callees: FUN_00451244,FUN_0045128c,FUN_004511d8,FUN_004511a4,FUN_004511fc,FUN_00451220,FUN_0045126c

int FUN_00454c2c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_004511a4(param_1,param_2);
  if ((iVar1 == 0) || (iVar1 = FUN_00451220(param_1,param_2), iVar1 != 0)) {
    iVar1 = 0x8000;
  }
  else if ((DAT_0057e248 == 3) || (iVar1 = FUN_004511d8(param_1,param_2), iVar1 == 0)) {
    if (DAT_0057e248 != 1) {
      if (DAT_0057e248 == 2) {
        iVar1 = FUN_00451244(param_1,param_2);
        if (iVar1 != 0) {
          return 1;
        }
        return 0x32;
      }
      if (DAT_0057e248 == 3) {
        return 1;
      }
      if (DAT_0057e248 != 6) {
        return 0x32;
      }
      if (*(char *)(DAT_00657de0 + 0x21) == '\0') {
        return 1;
      }
    }
    iVar1 = FUN_004511fc(param_1,param_2);
    if (iVar1 == 0) {
      iVar1 = FUN_0045126c(param_1,param_2);
      iVar1 = *(int *)(&DAT_004cf810 + iVar1 * 4);
    }
    else {
      iVar1 = 1;
    }
    if (DAT_004cf854 != 0) {
      iVar2 = FUN_0045128c(param_1,param_2);
      iVar1 = iVar1 + iVar2;
    }
  }
  else {
    iVar1 = 0x32;
  }
  return iVar1;
}

