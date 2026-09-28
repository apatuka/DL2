// FUN_004770a0 @ 004770a0 size=90 sig=undefined FUN_004770a0() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: 

void FUN_004770a0(int param_1)

{
  int iVar1;
  
  iVar1 = DAT_0058f200;
  if (DAT_0058f200 < DAT_004d5aec) {
    *(ushort *)(&DAT_0059f164 + DAT_0058f200 * 0x2d8) = (ushort)*(byte *)(param_1 + 1);
    (&DAT_0059f161)[iVar1 * 0x2d8] = 2;
    (&DAT_00653518)[DAT_0058f200] = *(undefined4 *)(param_1 + 4);
    DAT_0058f200 = DAT_0058f200 + 1;
  }
  return;
}

