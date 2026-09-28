// FUN_0047f5cc @ 0047f5cc size=161 sig=undefined FUN_0047f5cc() cc=unknown
// callers: FUN_00480150
// callees: BlitSprite8

void FUN_0047f5cc(int param_1,int param_2,int param_3)

{
  int iVar1;
  
  if ((((param_3 != 0) && ((*(byte *)(param_3 + 2) & 4) != 0)) &&
      ((char)(&DAT_005a4405)[*(short *)(param_3 + 8) * 0xadc] < 'd')) &&
     ((DAT_004d5aa0 == '\0' && ((&DAT_004f9dc8)[*(char *)(param_3 + 4) * 0x32] != '\0')))) {
    iVar1 = param_1 + 0x2d;
    if ((&DAT_004f9dc5)[*(char *)(param_3 + 4) * 0x32] == '\x02') {
      iVar1 = param_1;
    }
    BlitSprite8(DAT_004e3074,iVar1,param_2 + 0x14,(int)DAT_004e3070,(int)DAT_004e3072,
                (int)DAT_004e3070,0);
  }
  return;
}

