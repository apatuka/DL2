// FUN_00459948 @ 00459948 size=242 sig=undefined FUN_00459948() cc=unknown
// callers: FUN_00459bdc
// callees: sprintf,FUN_00459ee0,FUN_0043ee40,FUN_00459864,FUN_00484818

void FUN_00459948(undefined4 param_1,int param_2,int *param_3)

{
  char *pcVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  uint uVar5;
  undefined1 local_1c [12];
  int local_10;
  int local_c;
  int local_8;
  
  uVar5 = 0;
  local_8 = 0;
  do {
    if (*param_3 != 0) {
      pcVar1 = *(char **)(param_2 + 0x84 + *(char *)(param_2 + 0x75) * 4);
      iVar3 = (int)uVar5 >> 1;
      iVar4 = (int)pcVar1[1];
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar5 & 1) != 0);
      }
      iVar3 = *pcVar1 + iVar3;
      if (DAT_004d5ad0 == 0) {
        FUN_00459ee0(iVar3,iVar4,&local_c,&local_10);
      }
      else {
        FUN_0043ee40(iVar3,iVar4,&local_c,&local_10);
        local_c = local_c + -0x10;
        local_10 = local_10 + -0x20;
      }
      uVar2 = uVar5 & 0x80000001;
      if ((int)uVar2 < 0) {
        uVar2 = (uVar2 - 1 | 0xfffffffe) + 1;
      }
      if (uVar2 != 0) {
        local_c = local_c + 0x10;
      }
      FUN_00459864(param_1,0x3ef,local_8,local_c,local_10 + 0x10);
      sprintf(local_1c,&DAT_004d1b84,*param_3);
      FUN_00484818(local_c,local_10 + 0xb,0x10,0xb,local_1c,0xd);
      uVar5 = uVar5 + 1;
    }
    local_8 = local_8 + 1;
    param_3 = param_3 + 1;
  } while (local_8 < 7);
  return;
}

