// FUN_004aa5ac @ 004aa5ac size=108 sig=undefined FUN_004aa5ac() cc=unknown
// callers: FUN_004aa630
// callees: FUN_004aa578,FUN_004ac2cc

undefined4 FUN_004aa5ac(undefined4 *param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((*(byte *)((int)param_1 + 0x13) & 2) != 0) {
    FUN_004aa578();
  }
  *param_1 = param_1[1];
  iVar1 = FUN_004ac2cc((int)*(char *)((int)param_1 + 0x16),param_1[1],param_1[3]);
  param_1[2] = iVar1;
  param_1[2] = iVar1;
  if (iVar1 < 1) {
    if (param_1[2] == 0) {
      *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) & 0xfe7f | 0x20;
    }
    else {
      param_1[2] = 0;
      *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) | 0x10;
    }
    uVar2 = 0xffffffff;
  }
  else {
    *(ushort *)((int)param_1 + 0x12) = *(ushort *)((int)param_1 + 0x12) & 0xffdf;
    uVar2 = 0;
  }
  return uVar2;
}

