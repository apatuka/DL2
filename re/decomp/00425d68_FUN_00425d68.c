// FUN_00425d68 @ 00425d68 size=399 sig=undefined FUN_00425d68() cc=unknown
// callers: 
// callees: FUN_00412d38,FUN_0049ea99,FUN_0049a93f,FUN_004a1150,FUN_004a43da,FUN_0049f22b,FUN_0049fd2e,FUN_0049a8ed,FUN_0049aa64,FUN_0049fca2

undefined4 FUN_00425d68(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  int iVar4;
  int *piVar5;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    piVar5 = &local_1c;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049f22b(uVar1,piVar5);
    FUN_0049aa64(&local_1c);
    FUN_004a43da(param_1,3,param_3,param_4);
    if (((DAT_004b7d00 == 0) && (DAT_004b7cf8 != 0)) && (*(char *)(DAT_004b7cf8 + 0x3c) == '\0')) {
      FUN_00412d38(DAT_004b7cf8,*(undefined4 *)(DAT_004b7ce4 + 0x3c));
    }
    local_1c = 0x42;
    local_18 = 0x24;
    local_14 = 0xd6;
    local_10 = 0xb8;
    if (DAT_00557558 != -1) {
      uVar1 = FUN_004a1150(DAT_004b7ce4,10,1);
      FUN_0049fca2(uVar1,DAT_00557558,0,0,&local_8,&local_c);
      uVar2 = (local_14 - local_1c) - local_8;
      iVar3 = (int)uVar2 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
      }
      uVar2 = (local_10 - local_18) - local_c;
      iVar4 = (int)uVar2 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar2 & 1) != 0);
      }
      FUN_0049fd2e(uVar1,&local_1c,iVar3,iVar4,DAT_00557558,0,0);
    }
    if (DAT_0055755c != -1) {
      uVar1 = FUN_004a1150(DAT_004b7ce4,0xb,1);
      FUN_0049fca2(uVar1,DAT_0055755c,0,0,&local_8,&local_c);
      uVar2 = (local_14 - local_1c) - local_8;
      iVar3 = (int)uVar2 >> 1;
      if (iVar3 < 0) {
        iVar3 = iVar3 + (uint)((uVar2 & 1) != 0);
      }
      uVar2 = (local_10 - local_18) - local_c;
      iVar4 = (int)uVar2 >> 1;
      if (iVar4 < 0) {
        iVar4 = iVar4 + (uint)((uVar2 & 1) != 0);
      }
      FUN_0049fd2e(uVar1,&local_1c,iVar3,iVar4,DAT_0055755c,0,0);
    }
    FUN_0049a93f();
    uVar1 = 1;
  }
  else {
    uVar1 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar1;
}

