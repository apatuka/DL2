// DestroyAnim @ 0043db88 size=536 sig=undefined DestroyAnim() cc=unknown
// callers: FUN_00453350
// callees: DebugMessage,FUN_0043d004,FUN_00482ac4,FUN_00445040,FUN_0046ca40,FUN_00444f20,FUN_004482cc,FUN_0043da44,FUN_00444b74
// strings: \"NULL warrior in DestroyAnim\"

/* auto-named from string evidence: DestroyAnim */

void DestroyAnim(int param_1,int param_2)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int local_8;
  
  if (param_1 == 0) {
    DebugMessage(s_NULL_warrior_in_DestroyAnim_004c49f1);
  }
  else {
    switch((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24]) {
    default:
      uVar1 = FUN_0046ca40();
      local_8 = uVar1 % 0xd + 0x47;
      uVar2 = 0xaf;
      iVar4 = 0xb4;
      break;
    case 2:
    case 0xc:
      local_8 = 0x7e;
      uVar2 = 0xb0;
      iVar4 = 0xb4;
      break;
    case 3:
    case 5:
    case 0xd:
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
      local_8 = 0x7e;
      uVar2 = 0xb2;
      iVar4 = -1;
      break;
    case 9:
    case 0x14:
      local_8 = 0x75;
      uVar2 = 0xb3;
      iVar4 = -1;
      break;
    case 10:
      uVar1 = FUN_0046ca40();
      local_8 = uVar1 % 7 + 0x3b;
      uVar2 = 0xb1;
      iVar4 = -1;
    }
    if (((param_2 == 0) &&
        (iVar3 = FUN_00444f20(uVar2,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
                              0), iVar3 != 0)) && (*(int *)(param_1 + 0x38) != 0)) {
      uVar1 = FUN_0046ca40();
      *(short *)(iVar3 + 0x2c) = (short)((ulonglong)uVar1 % 3);
      *(undefined4 *)(iVar3 + 6) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 6);
      *(undefined4 *)(iVar3 + 10) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 10);
      FUN_00444b74(iVar3,*(short *)(*(int *)(param_1 + 0x38) + 4) + 2);
      uVar5 = 0;
      uVar2 = FUN_0043d004((int)*(short *)(*(int *)(param_1 + 0x38) + 0xe));
      FUN_00482ac4(local_8,0,1,0,uVar2,uVar5);
    }
    if (((iVar4 != -1) &&
        (iVar4 = FUN_00444f20(iVar4,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),
                              0), iVar4 != 0)) && (*(int *)(param_1 + 0x38) != 0)) {
      *(undefined2 *)(iVar4 + 0x2e) = 5;
      *(undefined4 *)(iVar4 + 6) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 6);
      *(undefined4 *)(iVar4 + 10) = *(undefined4 *)(*(int *)(param_1 + 0x38) + 10);
      FUN_00444b74(iVar4,*(short *)(*(int *)(param_1 + 0x38) + 4) + 1);
    }
    if (*(int *)(param_1 + 0x38) != 0) {
      if ((*(int *)(param_1 + 4) == 0x1b) && (*(char *)(*(int *)(DAT_00559dbc + 4) + 0x21) == '\0'))
      {
        FUN_00445040(*(undefined4 *)(param_1 + 0x38),3,1);
      }
      else {
        FUN_00445040(*(undefined4 *)(param_1 + 0x38),2,1);
      }
      if ((&DAT_004faf87)[*(int *)(param_1 + 4) * 0x24] == '\n') {
        *(undefined **)(*(int *)(param_1 + 0x38) + 0x34) = &DAT_00519cce;
      }
      else {
        FUN_00444b74(*(int *)(param_1 + 0x38),
                     ((int)*(short *)(*(int *)(param_1 + 0x38) + 4) / 100) * 100 + 0x33);
      }
      iVar4 = *(int *)(param_1 + 0x38);
      *(undefined2 *)(iVar4 + 0x22) = 0;
      *(undefined2 *)(iVar4 + 0x24) = 0;
    }
    iVar4 = FUN_004482cc(param_1);
    if (iVar4 != 0) {
      FUN_0043da44(param_1);
    }
  }
  return;
}

