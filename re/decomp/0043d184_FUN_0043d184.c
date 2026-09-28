// FUN_0043d184 @ 0043d184 size=283 sig=undefined FUN_0043d184() cc=unknown
// callers: FUN_004556b0,BirthCombatSprites
// callees: FUN_00445074,FUN_00445040,FUN_004864c4,FUN_00486564,FUN_0043d034,FUN_00444b74

void FUN_0043d184(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar1 = *(int *)(param_1 + 0x38);
  if (iVar1 != 0) {
    FUN_00445074((int)*(short *)(iVar1 + 0xe),(int)*(short *)(iVar1 + 0x10),
                 (int)*(short *)(iVar1 + 0x12),(int)*(short *)(iVar1 + 0x14));
    iVar3 = FUN_00486564(*(undefined1 *)(param_1 + 0x30));
    if (iVar3 == -1) {
      iVar3 = 0;
      param_2 = 0;
    }
    if ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] != '\t') {
      *(short *)(iVar1 + 0x30) = (short)iVar3;
      FUN_00445040(iVar1,0,1);
      if ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\n') {
        *(undefined **)(iVar1 + 0x34) = &DAT_00519cce;
      }
    }
    if ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\n') {
      FUN_004864c4(iVar1,*(int *)(param_1 + 0x20) + 1,*(int *)(param_1 + 0x24) + 1);
    }
    else {
      FUN_004864c4(iVar1,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24));
    }
    if (param_2 == 0) {
      *(undefined2 *)(iVar1 + 0x22) = 0;
      *(undefined2 *)(iVar1 + 0x24) = 0;
      iVar3 = FUN_0043d034(param_1);
      FUN_00444b74(iVar1,iVar3 + -1);
    }
    else {
      iVar2 = (&DAT_00512688)[iVar3];
      param_2 = param_2 * DAT_004c4954;
      *(short *)(iVar1 + 0x22) = (short)((int)(&DAT_00512668)[iVar3] / param_2);
      *(short *)(iVar1 + 0x24) = (short)(iVar2 / param_2);
      uVar4 = FUN_0043d034(param_1);
      FUN_00444b74(iVar1,uVar4);
    }
  }
  return;
}

