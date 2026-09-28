// FUN_0047681c @ 0047681c size=256 sig=undefined FUN_0047681c() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0043793c,FUN_00407c2c,FUN_004767f0

void FUN_0047681c(int param_1)

{
  undefined2 uVar1;
  undefined2 uVar2;
  undefined2 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  uVar1 = *(undefined2 *)(param_1 + 0x18);
  iVar6 = (uint)*(ushort *)(param_1 + 0x1a) * 0xadc;
  iVar7 = (uint)*(ushort *)(param_1 + 0x1c) * 0xadc;
  iVar4 = (int)(char)(&DAT_005a43f0)[iVar6];
  uVar2 = *(undefined2 *)(param_1 + 0x1e);
  iVar5 = (int)(char)(&DAT_005a43f0)[iVar7];
  uVar3 = *(undefined2 *)(param_1 + 0x20);
  if ((iVar5 == DAT_0058f1f4) ||
     (('\x02' < (char)(&DAT_0059f161)[iVar5 * 0x2d8] && (DAT_0058f1f4 == DAT_004d5a58)))) {
    if (*(int *)(&DAT_006534fc + iVar5 * 4) == 0) {
      FUN_004767f0(iVar5,2);
      if (iVar5 == DAT_0058f1f4) {
        iVar6 = FUN_0043793c(&DAT_005a43d0 + iVar6,&DAT_005a43d0 + iVar7,uVar1,uVar2,uVar3);
      }
      else {
        iVar6 = FUN_00407c2c(&DAT_005a43d0 + iVar6,&DAT_005a43d0 + iVar7,uVar1,uVar2,uVar3);
      }
      if (iVar6 == 1) {
        FUN_004767f0(iVar4,3);
      }
      else {
        FUN_004767f0(iVar4,4);
      }
      FUN_004767f0(iVar5,0);
    }
    else {
      FUN_004767f0(iVar4,1);
    }
  }
  return;
}

