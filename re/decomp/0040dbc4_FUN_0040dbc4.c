// FUN_0040dbc4 @ 0040dbc4 size=420 sig=undefined FUN_0040dbc4() cc=unknown
// callers: FUN_0040e6e4
// callees: FUN_0040da78,FUN_0040d9d4,FUN_0040c4d4,FUN_0040bbf4,FUN_0040d920,FUN_0040beb4,FUN_00401a18,FUN_0040da38,FUN_0040ab80,FUN_0040d808,FUN_0040db30,FUN_0040daf4,FUN_0040bfb4,FUN_0040d64c,FUN_0040db74

void FUN_0040dbc4(int param_1)

{
  short sVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  undefined4 uVar8;
  
  sVar1 = *(short *)(param_1 + 10);
  iVar4 = *(int *)(param_1 + 0x84);
  if ((1 << ((byte)sVar1 & 0x1f) & (int)DAT_004fc412) != 0) {
    FUN_0040bfb4(param_1,1);
  }
  if (((*(int *)(&DAT_005224c0 + sVar1 * 0x2648 + iVar4 * 0xc4) == 1) ||
      (iVar2 = FUN_0040db74(param_1), iVar2 != 0)) && (iVar2 = FUN_0040db30(param_1), iVar2 == 0)) {
    FUN_0040beb4(param_1);
  }
  iVar2 = FUN_0040daf4(param_1);
  if (iVar2 == 0) {
    FUN_0040beb4(param_1);
  }
  iVar2 = FUN_0040ab80(param_1,0xc);
  if (iVar2 != 0) {
    uVar8 = *(undefined4 *)(iVar2 + 0x38);
    if (*(int *)(&DAT_005224c0 + sVar1 * 0x2648 + iVar4 * 0xc4) == 1) {
      uVar3 = FUN_0040da78((int)*(short *)(param_1 + 10),uVar8);
      *(undefined4 *)(param_1 + 0x10) = uVar3;
    }
    uVar3 = *(undefined4 *)(param_1 + 0x10);
    iVar4 = FUN_0040da38(param_1);
    if (iVar4 != 0) {
      iVar4 = FUN_0040d64c(param_1,uVar8,iVar4);
      if (iVar4 == 0) {
        FUN_0040beb4(param_1);
        return;
      }
      uVar5 = FUN_00401a18(iVar2,iVar4);
      uVar6 = FUN_0040c4d4(uVar5);
      *(undefined4 *)(param_1 + 0x14) = uVar6;
      *(undefined4 *)(param_1 + 0x10) = uVar5;
      FUN_0040bbf4(param_1,0,0);
      *(undefined4 *)(param_1 + 0x10) = uVar3;
    }
    iVar4 = FUN_0040da38(param_1);
    if (iVar4 == 0) {
      iVar4 = FUN_0040d808(param_1,uVar8,uVar3);
      if (iVar4 == 0) {
        uVar8 = FUN_0040da78((int)*(short *)(param_1 + 10),uVar8);
        *(undefined4 *)(param_1 + 0x10) = uVar8;
      }
      else {
        iVar7 = FUN_0040d920(uVar8,iVar4);
        if (iVar7 == 0) {
          uVar8 = FUN_00401a18(iVar2,iVar4);
          uVar5 = FUN_0040c4d4(uVar8);
          *(undefined4 *)(param_1 + 0x14) = uVar5;
          *(undefined4 *)(param_1 + 0x10) = uVar8;
          FUN_0040bbf4(param_1,0,1);
          *(undefined4 *)(param_1 + 0x10) = uVar3;
        }
        else {
          *(int *)(param_1 + 0x10) = iVar4;
          FUN_0040bbf4(param_1,0,2);
          *(undefined4 *)(param_1 + 0x10) = uVar3;
        }
      }
    }
    iVar4 = FUN_0040d9d4(param_1);
    if (iVar4 != 0) {
      FUN_0040beb4(param_1);
    }
  }
  return;
}

