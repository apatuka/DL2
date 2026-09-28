// FUN_00475da4 @ 00475da4 size=156 sig=undefined FUN_00475da4() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_00475040,FUN_004750c4,FUN_0044c9a0

void FUN_00475da4(int param_1)

{
  short sVar1;
  ushort uVar2;
  int iVar3;
  uint uVar4;
  
  iVar3 = 0;
  sVar1 = *(short *)(param_1 + 0x1a);
  if (sVar1 != -1) {
    iVar3 = FUN_004750c4(sVar1);
  }
  if ((iVar3 == 0) && (sVar1 != -1)) {
    FUN_00475040(*(undefined4 *)(param_1 + 4));
  }
  else {
    uVar2 = *(ushort *)(param_1 + 0x1c);
    if ((uVar2 & 0xff) == 0xff) {
      uVar4 = 0xffffffff;
    }
    else {
      uVar4 = uVar2 & 0xff;
    }
    FUN_0044c9a0(&DAT_005a43d0 + (uint)*(ushort *)(param_1 + 0x18) * 0xadc,uVar4,iVar3,
                 (uVar2 & 0x4000) != 0,(uVar2 & 0x8000) != 0);
  }
  return;
}

