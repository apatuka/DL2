// FUN_004033d0 @ 004033d0 size=55 sig=undefined FUN_004033d0() cc=unknown
// callers: FUN_00403408
// callees: FUN_00403350

uint FUN_004033d0(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  uVar3 = 0;
  for (iVar2 = 0; (*(int *)(&DAT_0052222c + param_1 * 4) != 0 && (iVar2 < 7)); iVar2 = iVar2 + 1) {
    uVar1 = FUN_00403350(param_1,iVar2);
    uVar3 = uVar3 | uVar1;
  }
  return uVar3;
}

