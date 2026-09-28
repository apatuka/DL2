// FUN_0044bd0c @ 0044bd0c size=205 sig=undefined FUN_0044bd0c() cc=unknown
// callers: FUN_0044bddc
// callees: FUN_0044b620,FUN_00484e88,IsBuildTaskDifferent

int FUN_0044bd0c(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  char *local_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_8 = -1000;
  local_c = -1;
  uVar2 = FUN_0044b620(param_1);
  iVar5 = 0;
  piVar4 = (int *)(param_1 + 0x18);
  local_18 = (char *)(param_1 + 0x2c);
  do {
    cVar1 = *local_18;
    if ((cVar1 != '\0') && ((0x100 << ((byte)iVar5 & 0x1f) & (int)*(short *)(param_1 + 2)) == 0)) {
      local_14 = 0;
      if (((cVar1 == '\x14') || ((cVar1 == '\v' && (iVar3 = FUN_00484e88(uVar2), 0 < iVar3)))) ||
         (((cVar1 == '\x15' || (cVar1 == '\x02')) &&
          (iVar3 = IsBuildTaskDifferent(param_1,iVar5,*piVar4,*piVar4 + -1), iVar3 == 0)))) {
        if (*piVar4 != 0) {
          return iVar5;
        }
      }
      else {
        local_14 = *piVar4;
      }
      if (local_8 < local_14) {
        local_8 = local_14;
        local_c = iVar5;
      }
    }
    iVar5 = iVar5 + 1;
    piVar4 = piVar4 + 1;
    local_18 = local_18 + 1;
  } while (iVar5 < 5);
  return local_c;
}

