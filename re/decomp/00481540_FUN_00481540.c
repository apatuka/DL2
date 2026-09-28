// FUN_00481540 @ 00481540 size=713 sig=undefined FUN_00481540() cc=unknown
// callers: FUN_00481da0
// callees: FUN_00481c80,FUN_0046458c,FUN_004644f8

void FUN_00481540(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6)

{
  int iVar1;
  char *pcVar2;
  uint uVar3;
  int iVar4;
  undefined4 *local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  local_8 = (int)*(char *)(param_1 + 0x21);
  local_c = param_4;
  local_10 = param_4;
  if ((DAT_004d5ad4 != 0) || (param_5 != -1)) {
    iVar1 = local_8 * 4;
    local_20 = (undefined4 *)(param_1 + 0x80);
    for (local_14 = 0; local_14 < *(char *)(param_1 + 0x7e); local_14 = local_14 + 1) {
      pcVar2 = (char *)*local_20;
      iVar4 = param_5;
      if (param_5 == -1) {
        if (DAT_004d5ad4 == 2) {
          iVar4 = 0;
        }
        else if (local_8 == 0) {
          iVar4 = 0x40;
        }
        else {
          iVar4 = *(int *)(&DAT_004dce08 + iVar1);
        }
      }
      uVar3 = (uint)pcVar2[4];
      if (uVar3 != 0) {
        if (param_6 == 0) {
          local_18 = *pcVar2 * param_4 + param_2;
          local_1c = pcVar2[1] * param_4 + param_3;
        }
        else {
          FUN_00481c80((int)*pcVar2,(int)pcVar2[1],&local_18,&local_1c,&local_c,&local_10,param_4,
                       param_6);
        }
        if ((uVar3 & 2) != 0) {
          FUN_0046458c(local_18,local_1c,local_10,iVar4);
        }
        if ((uVar3 & 8) != 0) {
          FUN_0046458c(local_18 + local_c + -1,local_1c,local_10,iVar4);
        }
        if ((uVar3 & 1) != 0) {
          FUN_004644f8(local_18,local_1c,local_c,iVar4);
        }
        if ((uVar3 & 4) != 0) {
          FUN_004644f8(local_18,local_1c + local_10 + -1,local_c,iVar4);
        }
        if ((uVar3 & 0x10) != 0) {
          FUN_004644f8(local_18,local_1c,1,iVar4);
        }
        if ((uVar3 & 0x20) != 0) {
          FUN_004644f8(local_18 + local_c + -1,local_1c,1,iVar4);
        }
        if ((uVar3 & 0x40) != 0) {
          FUN_004644f8(local_18,local_1c + local_10 + -1,1,iVar4);
        }
        if ((uVar3 & 0x80) != 0) {
          FUN_004644f8(local_18 + local_c + -1,local_1c + local_10 + -1,1,iVar4);
        }
        if ((uVar3 & 2) != 0) {
          FUN_0046458c(local_18,local_1c,param_4,iVar4);
        }
        if ((uVar3 & 8) != 0) {
          FUN_0046458c(local_18 + param_4 + -1,local_1c,param_4,iVar4);
        }
        if ((uVar3 & 1) != 0) {
          FUN_004644f8(local_18,local_1c,param_4,iVar4);
        }
        if ((uVar3 & 4) != 0) {
          FUN_004644f8(local_18,local_1c + param_4 + -1,param_4,iVar4);
        }
        if ((uVar3 & 0x10) != 0) {
          FUN_004644f8(local_18,local_1c,1,iVar4);
        }
        if ((uVar3 & 0x20) != 0) {
          FUN_004644f8(local_18 + param_4 + -1,local_1c,1,iVar4);
        }
        if ((uVar3 & 0x40) != 0) {
          FUN_004644f8(local_18,local_1c + param_4 + -1,1,iVar4);
        }
        if ((uVar3 & 0x80) != 0) {
          FUN_004644f8(local_18 + param_4 + -1,local_1c + param_4 + -1,1,iVar4);
        }
      }
      local_20 = local_20 + 1;
    }
  }
  return;
}

