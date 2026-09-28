// FUN_0044bacc @ 0044bacc size=147 sig=undefined FUN_0044bacc() cc=unknown
// callers: FUN_00475d40,FUN_00475d60
// callees: FUN_0044bea8,FUN_004023dc,FUN_0044ba40,FUN_0046c3fc

void FUN_0044bacc(int param_1)

{
  int iVar1;
  undefined4 *puVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int local_14;
  undefined1 local_10 [4];
  int local_c;
  int local_8;
  
  FUN_0046c3fc(param_1,&local_c,local_10);
  local_8 = 0;
  piVar5 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar5;
    if (iVar1 != 0) {
      iVar4 = 0;
      puVar2 = (undefined4 *)(iVar1 + 0x18);
      do {
        iVar4 = iVar4 + 1;
        *puVar2 = 0;
        puVar2 = puVar2 + 1;
      } while (iVar4 < 5);
      iVar4 = FUN_004023dc(iVar1,0x14);
      if (iVar4 != -1) {
        local_14 = FUN_0044ba40(iVar1);
        if (local_c < local_14) {
          piVar3 = &local_c;
        }
        else {
          piVar3 = &local_14;
        }
        local_c = local_c - *piVar3;
        *(int *)(iVar1 + 0x18 + iVar4 * 4) = *piVar3;
      }
    }
    local_8 = local_8 + 1;
    piVar5 = piVar5 + 0xd;
  } while (local_8 < 0x24);
  FUN_0044bea8(param_1);
  return;
}

