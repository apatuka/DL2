// FUN_00459f18 @ 00459f18 size=287 sig=undefined FUN_00459f18() cc=unknown
// callers: FUN_0045a91c
// callees: FUN_0046458c,FUN_004644f8

void FUN_00459f18(int param_1,int param_2,int param_3,uint param_4)

{
  int iVar1;
  
  if ((*(uint *)(param_3 + 0x1c) & 1) == 0) {
    if ((*(uint *)(param_3 + 0x1c) & 2) == 0) {
      if (*(char *)(param_3 + 0x21) == '\0') {
        iVar1 = 0x40;
      }
      else if (DAT_004d5ad4 == 2) {
        iVar1 = 0;
      }
      else {
        iVar1 = -1;
      }
    }
    else {
      iVar1 = 0xb;
    }
  }
  else {
    iVar1 = 0xff;
  }
  if ((DAT_004d5ad4 != 0) || (iVar1 == 0xff)) {
    if ((param_4 & 2) != 0) {
      FUN_0046458c(param_1,param_2,0x20,iVar1);
    }
    if ((param_4 & 8) != 0) {
      FUN_0046458c(param_1 + 0x1f,param_2,0x20,iVar1);
    }
    if ((param_4 & 1) != 0) {
      FUN_004644f8(param_1,param_2,0x20,iVar1);
    }
    if ((param_4 & 4) != 0) {
      FUN_004644f8(param_1,param_2 + 0x1f,0x20,iVar1);
    }
    if ((param_4 & 0x10) != 0) {
      FUN_004644f8(param_1,param_2,1,iVar1);
    }
    if ((param_4 & 0x20) != 0) {
      FUN_004644f8(param_1 + 0x1f,param_2,1,iVar1);
    }
    if ((param_4 & 0x40) != 0) {
      FUN_004644f8(param_1,param_2 + 0x1f,1,iVar1);
    }
    if ((param_4 & 0x80) != 0) {
      FUN_004644f8(param_1 + 0x1f,param_2 + 0x1f,1,iVar1);
    }
  }
  return;
}

