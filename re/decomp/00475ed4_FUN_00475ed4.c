// FUN_00475ed4 @ 00475ed4 size=169 sig=undefined FUN_00475ed4() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0044df94,BroadcastDirect

undefined4 FUN_00475ed4(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar1 = FUN_0044df94(&DAT_005a43d0 + (uint)*(ushort *)(param_1 + 0x1a) * 0xadc,
                       &DAT_0059f160 + *(short *)(param_1 + 0x16) * 0x2d8,
                       *(undefined2 *)(param_1 + 0x18));
  if ((uVar1 & 0xf001) == 0) {
    if (DAT_0058f1f4 == DAT_004d5a58) {
      BroadcastDirect(*(undefined4 *)(param_1 + 4),DAT_0058f1f4,0x42,0x17,uVar1,0,0,0);
    }
    uVar2 = 1;
  }
  else {
    if (DAT_0058f1f4 == DAT_004d5a58) {
      BroadcastDirect(*(undefined4 *)(param_1 + 4),DAT_0058f1f4,0x43,0x17,uVar1,0,0,0);
    }
    uVar2 = 0;
  }
  return uVar2;
}

