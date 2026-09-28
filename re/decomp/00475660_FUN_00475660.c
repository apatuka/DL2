// FUN_00475660 @ 00475660 size=104 sig=undefined FUN_00475660() cc=unknown
// callers: MasterDispatchNetMessage,FUN_004782ec
// callees: FUN_0045093c

void FUN_00475660(int param_1)

{
  int iVar1;
  
  iVar1 = (int)*(short *)(param_1 + 0x16);
  if ((iVar1 != DAT_0058f1f4) &&
     ((DAT_0058f1f4 != DAT_004d5a58 || ((char)(&DAT_0059f161)[iVar1 * 0x2d8] < '\x03')))) {
    DAT_004d8268 = 1;
    FUN_0045093c(iVar1,*(undefined2 *)(param_1 + 0x18),0xfffffffe,param_1 + 0x1a,0,0,0);
    DAT_004d8268 = 0;
  }
  return;
}

