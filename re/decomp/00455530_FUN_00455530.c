// FUN_00455530 @ 00455530 size=381 sig=undefined FUN_00455530() cc=unknown
// callers: FUN_004556b0
// callees: FUN_00450e04,FUN_004511a4

undefined4 FUN_00455530(int param_1,int *param_2,int *param_3)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00450e04(param_1);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x10) < 0x13) {
      if (*(int *)(param_1 + 0x10) < 0) {
        *param_2 = *(int *)(param_1 + 0x20);
        *param_3 = -9;
        while( true ) {
          iVar1 = FUN_004511a4(*param_2,*param_3);
          if ((iVar1 != 0) || (*param_3 < 0x12)) break;
          *param_3 = *param_3 + 1;
        }
        uVar2 = 1;
      }
      else if (*(int *)(param_1 + 0xc) < 0) {
        *param_3 = *(int *)(param_1 + 0x24);
        *param_2 = -9;
        while( true ) {
          iVar1 = FUN_004511a4(*param_2,*param_3);
          if ((iVar1 != 0) || (*param_2 < 0x12)) break;
          *param_2 = *param_2 + 1;
        }
        uVar2 = 1;
      }
      else {
        *param_3 = *(int *)(param_1 + 0x24);
        *param_2 = 0x1a;
        while( true ) {
          iVar1 = FUN_004511a4(*param_2,*param_3);
          if ((iVar1 != 0) || (*param_2 < 0x12)) break;
          *param_2 = *param_2 + -1;
        }
        uVar2 = 1;
      }
    }
    else {
      *param_2 = *(int *)(param_1 + 0x20);
      *param_3 = 0x1a;
      while( true ) {
        iVar1 = FUN_004511a4(*param_2,*param_3);
        if ((iVar1 != 0) || (*param_3 < 0x12)) break;
        *param_3 = *param_3 + -1;
      }
      uVar2 = 1;
    }
  }
  else if ((*(byte *)(DAT_0057cdf8 + 0x84) & 8) == 0) {
    *param_3 = *(int *)(param_1 + 0x24);
    *param_2 = 0;
    uVar2 = 1;
  }
  else if ((*(byte *)(DAT_0057cdf8 + 0x84) & 2) == 0) {
    *param_3 = *(int *)(param_1 + 0x24);
    *param_2 = 0x12;
    uVar2 = 1;
  }
  else if ((*(byte *)(DAT_0057cdf8 + 0x84) & 4) == 0) {
    *param_2 = *(int *)(param_1 + 0x20);
    *param_3 = 0x12;
    uVar2 = 1;
  }
  else if ((*(byte *)(DAT_0057cdf8 + 0x84) & 1) == 0) {
    *param_2 = *(int *)(param_1 + 0x20);
    *param_3 = 0;
    uVar2 = 1;
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

