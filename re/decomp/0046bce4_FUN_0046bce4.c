// FUN_0046bce4 @ 0046bce4 size=87 sig=undefined FUN_0046bce4() cc=unknown
// callers: FUN_0046c49c,FUN_0046bdfc
// callees: FUN_00447b0c,FUN_00416e70

int FUN_0046bce4(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = 0;
  for (iVar1 = *(int *)(param_1 + 0x76); iVar1 != 0; iVar1 = *(int *)(iVar1 + 0x54)) {
    if ((*(char *)(iVar1 + 0x25) == '\r') &&
       (iVar2 = FUN_00416e70(iVar1,0xd,(int)(char)(&DAT_0059f162)[*(char *)(iVar1 + 8) * 0x2d8]),
       iVar2 != 0)) {
      iVar2 = FUN_00447b0c(iVar1);
      iVar3 = iVar3 + iVar2;
    }
  }
  return iVar3;
}

