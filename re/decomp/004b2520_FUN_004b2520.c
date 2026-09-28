// FUN_004b2520 @ 004b2520 size=391 sig=undefined FUN_004b2520() cc=unknown
// callers: 
// callees: FUN_004b366c,FUN_004adff4,FUN_004adfe0

undefined4 FUN_004b2520(int *param_1,undefined4 param_2,int param_3)

{
  code *pcVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  uint uVar5;
  undefined4 local_8;
  
  iVar2 = FUN_004b366c();
  if ((iVar2 != 0) && (iVar2 = *(int *)(iVar2 + 0x28), iVar2 != 0)) {
    uVar5 = 0;
    iVar4 = *param_1;
    if (iVar4 < -0x3fffff6e) {
      if (iVar4 == -0x3fffff6f) {
        iVar4 = 2;
        local_8 = 0x84;
        uVar5 = 8;
      }
      else if (iVar4 == -0x3ffffffb) {
        local_8 = 0xc;
        iVar4 = 3;
      }
      else if (iVar4 == -0x3fffffe3) {
        local_8 = 0x14;
        iVar4 = 1;
      }
      else if (iVar4 == -0x3fffff72) {
        iVar4 = 2;
        local_8 = 0x83;
        uVar5 = 4;
      }
      else {
        if (iVar4 != -0x3fffff70) {
          return 1;
        }
        iVar4 = 2;
        local_8 = 0x81;
        uVar5 = 1;
      }
    }
    else if (iVar4 == -0x3fffff6e) {
      iVar4 = 2;
      local_8 = 0x87;
      uVar5 = 0x49;
    }
    else if (iVar4 == -0x3fffff6d) {
      iVar4 = 2;
      local_8 = 0x85;
      uVar5 = 0x10;
    }
    else if (iVar4 == -0x3fffff6c) {
      local_8 = 0x7f;
      iVar4 = 2;
    }
    else {
      if (iVar4 != -0x3fffff6a) {
        return 1;
      }
      local_8 = 0x16;
      iVar4 = 1;
    }
    pcVar1 = *(code **)(iVar2 + iVar4 * 4);
    if (pcVar1 == (code *)0x1) {
      uVar3 = 0;
    }
    else if (pcVar1 == (code *)0x0) {
      uVar3 = 1;
    }
    else {
      *(undefined4 *)(iVar2 + iVar4 * 4) = 0;
      if (((iVar4 == 1) || (iVar4 == 3)) || (iVar4 == 2)) {
        FUN_004adfe0();
        FUN_004adff4(DAT_00520f14,7999);
        (*pcVar1)((&DAT_00521460)[iVar4],local_8);
        *(uint *)(param_3 + 0x20) = *(uint *)(param_3 + 0x20) & ~uVar5;
      }
      else {
        (*pcVar1)((&DAT_00521460)[iVar4]);
      }
      uVar3 = 0;
    }
    return uVar3;
  }
  return 1;
}

