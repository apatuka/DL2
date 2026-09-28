// FUN_0044c754 @ 0044c754 size=69 sig=undefined FUN_0044c754() cc=unknown
// callers: FUN_0041e0a8,FUN_0041daa4,FUN_0041c258,FUN_0041bd60,FUN_00406424,FUN_0041c418,FUN_0041db10,FUN_0041b71c,FUN_0044c9a0,FUN_004063c0
// callees: FUN_004023dc

int FUN_0044c754(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int local_8;
  
  local_8 = 0;
  iVar4 = 0;
  piVar3 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar3;
    if (iVar1 != 0) {
      iVar2 = FUN_004023dc(iVar1,0x14);
      if (iVar2 != -1) {
        local_8 = local_8 + *(int *)(iVar1 + 0x18 + iVar2 * 4);
      }
    }
    iVar4 = iVar4 + 1;
    piVar3 = piVar3 + 0xd;
  } while (iVar4 < 0x24);
  return local_8;
}

