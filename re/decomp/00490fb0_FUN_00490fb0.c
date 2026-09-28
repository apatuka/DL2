// FUN_00490fb0 @ 00490fb0 size=337 sig=undefined FUN_00490fb0() cc=unknown
// callers: FUN_00491101
// callees: FUN_0048f7f1,FUN_00498b98,FUN_0048f774,FUN_004989de

int * FUN_00490fb0(int *param_1)

{
  int *piVar1;
  int *piVar2;
  int iVar3;
  int *piVar4;
  int local_1c;
  int local_14;
  int local_10;
  int local_8;
  
  local_10 = *(int *)(*param_1 + 0xc) * 8 + 0x14;
  for (iVar3 = 0; iVar3 < *(int *)(*param_1 + 0xc); iVar3 = iVar3 + 1) {
    local_10 = *(int *)(*param_1 + *(int *)(*param_1 + 0x18 + iVar3 * 8)) * 0x28 + local_10;
  }
  piVar1 = (int *)FUN_00498b98(*(int *)(*param_1 + 0xc) * 8 + 0x14 + local_10);
  if (piVar1 != (int *)0x0) {
    FUN_0048f7f1(*param_1,*piVar1,0x14);
    *(int *)(*piVar1 + 0x10) = local_10;
    local_14 = *(int *)(*param_1 + 0xc) * 8 + 0x14;
    for (iVar3 = 0; iVar3 < *(int *)(*param_1 + 0xc); iVar3 = iVar3 + 1) {
      local_1c = *param_1 + *(int *)(*param_1 + 0x18 + iVar3 * 8);
      FUN_0048f7f1(*param_1 + iVar3 * 8 + 0x14,*piVar1 + iVar3 * 8 + 0x14,8);
      *(int *)(*piVar1 + 0x18 + iVar3 * 8) = local_14;
      piVar2 = (int *)(*piVar1 + *(int *)(*piVar1 + 0x18 + iVar3 * 8));
      FUN_0048f7f1(local_1c,piVar2,8);
      local_14 = local_14 + 8;
      local_1c = local_1c + 8;
      piVar4 = piVar2 + 2;
      for (local_8 = 0; local_8 < *piVar2; local_8 = local_8 + 1) {
        FUN_0048f774(piVar4,0x28,0);
        FUN_0048f7f1(local_1c,piVar4,0x1c);
        local_14 = local_14 + 0x28;
        local_1c = local_1c + 0x1c;
        piVar4 = piVar4 + 10;
      }
    }
    FUN_004989de(param_1);
  }
  return piVar1;
}

