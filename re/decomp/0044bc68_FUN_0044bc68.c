// FUN_0044bc68 @ 0044bc68 size=162 sig=undefined FUN_0044bc68() cc=unknown
// callers: FUN_0044bddc
// callees: FUN_0044b620,FUN_00484e88

int FUN_0044bc68(int param_1)

{
  char cVar1;
  undefined4 uVar2;
  int iVar3;
  char *pcVar4;
  int iVar5;
  int *local_18;
  int local_14;
  int local_c;
  int local_8;
  
  local_8 = 1000;
  local_c = -1;
  uVar2 = FUN_0044b620(param_1);
  local_18 = (int *)(param_1 + 0x18);
  iVar5 = 0;
  pcVar4 = (char *)(param_1 + 0x2c);
  do {
    cVar1 = *pcVar4;
    if ((cVar1 != '\0') && ((0x100 << ((byte)iVar5 & 0x1f) & (int)*(short *)(param_1 + 2)) == 0)) {
      local_14 = 999;
      if ((cVar1 != '\x15') && ((cVar1 != '\x02' && (cVar1 != '\x14')))) {
        if (cVar1 == '\v') {
          iVar3 = FUN_00484e88(uVar2);
          if (iVar3 < 1) goto LAB_0044bce0;
        }
        local_14 = *local_18;
      }
LAB_0044bce0:
      if (local_14 < local_8) {
        local_8 = local_14;
        local_c = iVar5;
      }
    }
    local_18 = local_18 + 1;
    iVar5 = iVar5 + 1;
    pcVar4 = pcVar4 + 1;
    if (4 < iVar5) {
      return local_c;
    }
  } while( true );
}

