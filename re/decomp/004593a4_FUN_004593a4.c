// FUN_004593a4 @ 004593a4 size=104 sig=undefined FUN_004593a4() cc=unknown
// callers: FUN_0041e494,FUN_0041a14c,FUN_0045940c
// callees: 

undefined * FUN_004593a4(int param_1,int param_2)

{
  int iVar1;
  
  if (((&DAT_004faf87)[param_2 * 0x24] == '\t') || ((&DAT_004faf87)[param_2 * 0x24] == '\x14')) {
    iVar1 = 0;
  }
  else {
    iVar1 = (int)(char)(&DAT_0059f162)[param_1 * 0x2d8];
  }
  return (&PTR_DAT_004d02f4)[(iVar1 + *(short *)(&DAT_004faf84 + param_2 * 0x24)) * 3] +
         (char)(&DAT_004faf86)[param_2 * 0x24] * 0x10;
}

