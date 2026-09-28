// FUN_004aa418 @ 004aa418 size=115 sig=undefined FUN_004aa418() cc=unknown
// callers: FUN_00479700,FUN_00479b6c,FUN_004ab3c8,FUN_004aa994,FUN_0041244c
// callees: FUN_004aa3bc,FUN_004ab648,FUN_004a9c80,FUN_004ab710,FUN_004acf20

undefined4 FUN_004aa418(undefined4 *param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  FUN_004ab648(param_1);
  iVar1 = FUN_004a9c80(param_1);
  if (iVar1 == 0) {
    if ((param_3 == 1) && (0 < (int)param_1[2])) {
      iVar1 = FUN_004aa3bc(param_1);
      param_2 = param_2 - iVar1;
    }
    *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) & 0xfe5f;
    param_1[2] = 0;
    *param_1 = param_1[1];
    iVar1 = FUN_004acf20((int)*(char *)((int)param_1 + 0x16),param_2,param_3);
    if (iVar1 == -1) {
      uVar2 = 0xffffffff;
    }
    else {
      uVar2 = 0;
    }
  }
  else {
    uVar2 = 0xffffffff;
  }
  FUN_004ab710(param_1);
  return uVar2;
}

