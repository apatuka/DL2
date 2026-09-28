// FUN_004031b0 @ 004031b0 size=135 sig=undefined FUN_004031b0() cc=unknown
// callers: 
// callees: FUN_004023dc,FUN_0044c8ac

int FUN_004031b0(undefined4 param_1,int param_2)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int *piVar5;
  int iVar6;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  sVar1 = *(short *)(param_2 + 0x14);
  if (10 < sVar1) {
    iVar2 = FUN_004023dc(param_2,2);
    local_c = (sVar1 + 0x18) / 0x19;
    local_10 = 4;
    if (local_c < 5) {
      piVar5 = &local_c;
    }
    else {
      piVar5 = &local_10;
    }
    iVar6 = *piVar5 - *(int *)(param_2 + 0x18 + iVar2 * 4);
    iVar2 = 0;
    if (0 < iVar6) {
      do {
        uVar3 = FUN_004023dc(param_2,2);
        iVar4 = FUN_0044c8ac(param_1,param_2,uVar3);
        if (iVar4 == 0) {
          return local_8;
        }
        local_8 = local_8 + 1;
        iVar2 = iVar2 + 1;
      } while (iVar2 < iVar6);
    }
  }
  return local_8;
}

