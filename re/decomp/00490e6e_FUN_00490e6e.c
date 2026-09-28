// FUN_00490e6e @ 00490e6e size=322 sig=undefined FUN_00490e6e() cc=unknown
// callers: FUN_00491101
// callees: FUN_0048f7f1,FUN_00498b98,FUN_004989de

int * FUN_00490e6e(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  short *local_18;
  int local_10;
  int local_8;
  
  iVar4 = *(int *)(*param_1 + 0xc) * 8 + 0x14;
  for (iVar3 = 0; iVar3 < *(int *)(*param_1 + 0xc); iVar3 = iVar3 + 1) {
    iVar4 = *(short *)(*param_1 + *(int *)(*param_1 + 0x18 + iVar3 * 8)) * 0x28 + iVar4;
  }
  piVar1 = (int *)FUN_00498b98(*(int *)(*param_1 + 0xc) * 8 + 0x14 + iVar4);
  if (piVar1 != (int *)0x0) {
    FUN_0048f7f1(*param_1,*piVar1,0x14);
    *(undefined4 *)(*piVar1 + 8) = 0x10001;
    *(int *)(*piVar1 + 0x10) = iVar4;
    local_10 = *(int *)(*param_1 + 0xc) * 8 + 0x14;
    for (iVar4 = 0; iVar4 < *(int *)(*param_1 + 0xc); iVar4 = iVar4 + 1) {
      local_18 = (short *)(*param_1 + *(int *)(*param_1 + 0x18 + iVar4 * 8));
      *(int *)(*piVar1 + 0x18 + iVar4 * 8) = local_10;
      *(undefined4 *)(*piVar1 + 0x14 + iVar4 * 8) = *(undefined4 *)(*param_1 + 0x14 + iVar4 * 8);
      piVar2 = (int *)(*piVar1 + *(int *)(*piVar1 + 0x18 + iVar4 * 8));
      *piVar2 = (int)*local_18;
      piVar2[1] = (int)local_18[1];
      local_10 = local_10 + 8;
      local_18 = local_18 + 2;
      piVar5 = piVar2 + 2;
      for (local_8 = 0; local_8 < *piVar2; local_8 = local_8 + 1) {
        FUN_0048f7f1(local_18,piVar5,0x20);
        piVar5[8] = 0;
        local_10 = local_10 + 0x28;
        local_18 = local_18 + 0x10;
        piVar5 = piVar5 + 10;
      }
    }
    FUN_004989de(param_1);
  }
  return piVar1;
}

