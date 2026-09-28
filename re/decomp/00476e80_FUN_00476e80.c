// FUN_00476e80 @ 00476e80 size=100 sig=undefined FUN_00476e80() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0047510c,FUN_00475040,FUN_00475048
// strings: \"Null Army in Net Army Stats.\"

void FUN_00476e80(int param_1)

{
  short sVar1;
  undefined2 uVar2;
  int iVar3;
  undefined1 uVar4;
  
  sVar1 = *(short *)(param_1 + 0x1a);
  uVar2 = *(undefined2 *)(param_1 + 0x1c);
  iVar3 = FUN_0047510c(*(undefined2 *)(param_1 + 0x18));
  if (iVar3 == 0) {
    FUN_00475048(s_Null_Army_in_Net_Army_Stats__004dc1aa,param_1);
    FUN_00475040(*(undefined4 *)(param_1 + 4));
  }
  else {
    uVar4 = (undefined1)uVar2;
    if (sVar1 == 0) {
      *(undefined1 *)(iVar3 + 0x24) = uVar4;
    }
    else if (sVar1 == 1) {
      *(undefined1 *)(iVar3 + 0x25) = uVar4;
    }
    else if (sVar1 == 2) {
      *(undefined1 *)(iVar3 + 0x26) = uVar4;
    }
    else if (sVar1 == 3) {
      *(undefined2 *)(iVar3 + 0x36) = uVar2;
    }
  }
  return;
}

