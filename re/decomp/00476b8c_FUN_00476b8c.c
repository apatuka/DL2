// FUN_00476b8c @ 00476b8c size=183 sig=undefined FUN_00476b8c() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0042d3dc,FUN_00406c64,FUN_004767f0

void FUN_00476b8c(int param_1)

{
  undefined2 uVar1;
  int iVar2;
  uint uVar3;
  uint uVar4;
  
  uVar1 = *(undefined2 *)(param_1 + 0x18);
  uVar4 = (uint)*(ushort *)(param_1 + 0x1a);
  uVar3 = (uint)*(ushort *)(param_1 + 0x1c);
  if ((uVar3 == DAT_0058f1f4) ||
     (('\x02' < (char)(&DAT_0059f161)[uVar3 * 0x2d8] && (DAT_0058f1f4 == DAT_004d5a58)))) {
    if (*(int *)(&DAT_006534fc + uVar3 * 4) == 0) {
      FUN_004767f0(uVar3,2);
      if (uVar3 == DAT_0058f1f4) {
        iVar2 = FUN_0042d3dc(uVar1,(int)(char)(&DAT_0059f162)[uVar4 * 0x2d8]);
      }
      else {
        iVar2 = FUN_00406c64(uVar4,uVar3,uVar1);
      }
      if (iVar2 == 1) {
        FUN_004767f0(uVar4,3);
      }
      else {
        FUN_004767f0(uVar4,4);
      }
      FUN_004767f0(uVar3,0);
    }
    else {
      FUN_004767f0(uVar4,1);
    }
  }
  return;
}

