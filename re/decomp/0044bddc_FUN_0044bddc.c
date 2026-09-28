// FUN_0044bddc @ 0044bddc size=170 sig=undefined FUN_0044bddc() cc=unknown
// callers: FUN_0044c2c0,_MovePopulation
// callees: FUN_0044bc68,FUN_0044ba18,FUN_0044bd0c

undefined4 FUN_0044bddc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int local_c;
  int local_8;
  
  local_8 = FUN_0044ba18(param_1);
  uVar4 = 0;
  if (param_2 < 1) {
    if (param_2 < 0) {
      for (local_c = -param_2; local_c != 0; local_c = local_c - iVar1) {
        iVar2 = FUN_0044bd0c(param_1);
        if (iVar2 < 0) {
          return 0;
        }
        piVar3 = (int *)(param_1 + 0x18 + iVar2 * 4);
        if (local_c <= *piVar3) {
          piVar3 = &local_c;
        }
        iVar1 = *piVar3;
        piVar3 = (int *)(param_1 + 0x18 + iVar2 * 4);
        *piVar3 = *piVar3 - iVar1;
      }
      uVar4 = 1;
    }
  }
  else {
    iVar2 = FUN_0044bc68(param_1);
    if (-1 < iVar2) {
      piVar3 = (int *)(param_1 + 0x18 + iVar2 * 4);
      *piVar3 = *piVar3 + param_2;
      uVar4 = 1;
    }
  }
  if (((0 < param_2) && (local_8 == 0)) && ((&DAT_004f9dc8)[*(char *)(param_1 + 4) * 0x32] != '\0'))
  {
    *(ushort *)(param_1 + 2) = *(ushort *)(param_1 + 2) | 4;
  }
  return uVar4;
}

