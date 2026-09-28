// FUN_0040ee34 @ 0040ee34 size=228 sig=undefined FUN_0040ee34() cc=unknown
// callers: FUN_0040ef18
// callees: FUN_0040fc14,FUN_00401108

undefined4 FUN_0040ee34(int param_1,int param_2)

{
  bool bVar1;
  bool bVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int *piVar6;
  int local_14;
  int local_10;
  
  iVar3 = FUN_0040fc14((int)*(char *)(param_2 + 8),(int)*(char *)(param_2 + 7));
  if (*(char *)(param_2 + 6) < iVar3) {
    bVar2 = false;
    bVar1 = false;
    local_10 = 0;
    do {
      if (*(int *)(&DAT_00522584 + param_1 * 0x2648 + local_10 * 0xc4) != 1) {
        piVar6 = &DAT_005225c8 + local_10 * 0x31 + param_1 * 0x992;
        local_14 = 0;
        do {
          iVar3 = *piVar6;
          if ((iVar3 != 0) && (*(char *)(param_2 + 7) == *(char *)(iVar3 + 7))) {
            iVar5 = FUN_00401108(param_2,0,0,0,0);
            iVar3 = FUN_00401108(iVar3,0,0,0,0);
            if (iVar5 < iVar3) {
              bVar1 = true;
            }
            else {
              bVar2 = true;
            }
          }
          local_14 = local_14 + 1;
          piVar6 = piVar6 + 1;
        } while (local_14 < 0x10);
      }
      local_10 = local_10 + 1;
    } while (local_10 < 0x32);
    if ((!bVar1) || (bVar2)) {
      uVar4 = 0;
    }
    else {
      uVar4 = 1;
    }
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

