// FUN_0047f728 @ 0047f728 size=121 sig=undefined FUN_0047f728() cc=unknown
// callers: FUN_00480150
// callees: FUN_0047e074,FUN_00459864

void FUN_0047f728(int param_1,int param_2,int param_3,int param_4)

{
  int iVar1;
  int iVar2;
  
  if (((param_3 != 0) && ((*(byte *)(param_3 + 2) & 4) == 0)) &&
     ((*(char *)(param_4 + 0x66 + DAT_0058f1f4) == '\x04' || (DAT_00583c20 != 0)))) {
    iVar2 = param_1 + 0x2d;
    if ((&DAT_004f9dc5)[*(char *)(param_3 + 4) * 0x32] == '\x02') {
      iVar2 = param_1 + -6;
    }
    iVar1 = FUN_0047e074();
    if (iVar1 != 0) {
      FUN_00459864(iVar1,0x3f6,0,iVar2,param_2 + 0x14);
    }
  }
  return;
}

