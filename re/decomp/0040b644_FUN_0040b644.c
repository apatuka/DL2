// FUN_0040b644 @ 0040b644 size=321 sig=undefined FUN_0040b644() cc=unknown
// callers: FUN_0040b87c,FUN_0040b788
// callees: FUN_00401108,FUN_00401440,FUN_0040b2d4,FUN_0040da38,FUN_0040b1b8,FUN_0040b5cc,FUN_0040d64c,FUN_0040b3d0,FUN_0040d808,FUN_0040b4d0

int FUN_0040b644(int *param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = -1;
  if (*param_1 == 9) {
    uVar1 = FUN_0040da38(param_1);
    iVar2 = FUN_0040d64c(param_1,*(undefined4 *)(param_2 + 0x3c),uVar1);
    if ((iVar2 != 0) &&
       (iVar2 = FUN_0040d808(param_1,*(undefined4 *)(param_2 + 0x3c),param_1[4]), iVar2 != 0)) {
      iVar3 = FUN_00401108(param_2,0,0,0,0);
    }
  }
  else if (*param_1 == 0x11) {
    iVar2 = FUN_0040d808(param_1,*(undefined4 *)(param_2 + 0x3c),param_1[4]);
    if (iVar2 != 0) {
      iVar3 = FUN_00401108(param_2,0,0,0,0);
    }
  }
  else {
    iVar2 = FUN_00401440(param_2,param_1[4],1);
    if (iVar2 == 0) {
      if (((&DAT_004faf87)[*(char *)(param_2 + 6) * 0x24] == '\x03') ||
         ((&DAT_004faf87)[*(char *)(param_2 + 6) * 0x24] == '\r')) {
        FUN_0040b5cc(param_1,(int)*(char *)(param_2 + 6));
      }
    }
    else {
      iVar3 = FUN_00401108(param_2,0,0,0,0);
    }
  }
  if (iVar3 < 0) {
    return iVar3;
  }
  iVar2 = FUN_00401440(param_2,param_1[4],0);
  if (iVar2 != 0) {
    iVar3 = iVar3 + 100000;
  }
  if ((((*(char *)(param_2 + 6) != '\x1a') || (iVar2 = FUN_0040b1b8(param_1), iVar2 == 0)) &&
      ((*(char *)(param_2 + 6) != '\x0f' || (iVar2 = FUN_0040b2d4(param_1), iVar2 == 0)))) &&
     ((*(char *)(param_2 + 6) != '\x1c' || (iVar2 = FUN_0040b3d0(param_1), iVar2 == 0)))) {
    if (*(char *)(param_2 + 6) != '!') {
      return iVar3;
    }
    iVar2 = FUN_0040b4d0(param_1);
    if (iVar2 == 0) {
      return iVar3;
    }
  }
  return iVar3 + 10000;
}

