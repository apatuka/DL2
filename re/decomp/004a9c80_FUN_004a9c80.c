// FUN_004a9c80 @ 004a9c80 size=143 sig=undefined FUN_004a9c80() cc=unknown
// callers: FUN_004aa418,FUN_004aa0dc,fclose,FUN_004aa578,FUN_004aa718,FUN_004ac5d8
// callees: FUN_004ab648,FUN_004a9e50,FUN_004ac4cc,FUN_004ab710

undefined4 FUN_004a9c80(int *param_1)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  if (param_1 == (int *)0x0) {
    FUN_004a9e50();
    uVar1 = 0;
  }
  else if ((char)param_1 == *(char *)((int)param_1 + 0x17)) {
    FUN_004ab648(param_1);
    if (param_1[2] < 0) {
      iVar3 = param_1[3] + param_1[2] + 1;
      param_1[2] = param_1[2] - iVar3;
      *param_1 = param_1[1];
      iVar2 = FUN_004ac4cc((int)*(char *)((int)param_1 + 0x16),param_1[1],iVar3);
      if ((iVar3 == iVar2) || ((*(byte *)((int)param_1 + 0x13) & 2) != 0)) {
        uVar1 = 0;
      }
      else {
        *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) | 0x10;
        uVar1 = 0xffffffff;
      }
    }
    else {
      if ((((*(byte *)((int)param_1 + 0x12) & 8) != 0) || (param_1 + 5 == (int *)*param_1)) &&
         (param_1[2] = 0, param_1 + 5 == (int *)*param_1)) {
        *param_1 = param_1[1];
      }
      uVar1 = 0;
    }
    FUN_004ab710(param_1);
  }
  else {
    uVar1 = 0xffffffff;
  }
  return uVar1;
}

