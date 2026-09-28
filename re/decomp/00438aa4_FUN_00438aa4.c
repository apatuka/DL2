// FUN_00438aa4 @ 00438aa4 size=110 sig=undefined FUN_00438aa4() cc=unknown
// callers: FUN_00438b14,FUN_00420e34,FUN_0041d414
// callees: CheckUnitList,FUN_00438830,FUN_00438214

undefined4 FUN_00438aa4(undefined4 param_1,undefined1 *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  DAT_00559338 = param_1;
  iVar1 = FUN_00438830();
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    FUN_00438214();
    *param_3 = 0;
    while ((((iVar1 = *param_3, iVar1 != 3 && (iVar1 != 4)) && (iVar1 != 8)) &&
           (((iVar1 != 10 && (iVar1 != 0xb)) && (iVar1 != 9))))) {
      iVar1 = CheckUnitList();
      *param_3 = iVar1;
    }
    *param_2 = DAT_005594a8;
    uVar2 = DAT_004c4738;
    if (*param_3 != 3) {
      uVar2 = 0;
    }
  }
  return uVar2;
}

