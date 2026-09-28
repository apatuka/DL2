// FUN_004481a4 @ 004481a4 size=105 sig=undefined FUN_004481a4() cc=unknown
// callers: FUN_004480a8,FUN_00455c88,FUN_00448008,FUN_00455a04
// callees: 

int FUN_004481a4(int param_1)

{
  int iVar1;
  
  if ((((*(int *)(param_1 + 4) == 0xf) && (*(int *)(param_1 + 0x3c) != 0)) &&
      ((&DAT_004faf87)[*(int *)(*(int *)(param_1 + 0x3c) + 4) * 0x24] != '\t')) &&
     ((&DAT_004faf87)[*(int *)(*(int *)(param_1 + 0x3c) + 4) * 0x24] != '\n')) {
    iVar1 = (int)*(short *)(&DAT_00559fb2 +
                           (char)(&DAT_0059f162)[(uint)*(byte *)(param_1 + 0x1e) * 0x2d8] * 2);
  }
  else {
    iVar1 = 0;
  }
  return iVar1;
}

