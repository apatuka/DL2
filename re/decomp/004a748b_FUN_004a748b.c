// FUN_004a748b @ 004a748b size=74 sig=undefined FUN_004a748b() cc=unknown
// callers: FUN_004a78a4
// callees: FUN_004b17d4,FUN_004b0b44,FUN_004010f9

int FUN_004a748b(uint param_1)

{
  int iVar1;
  
  iVar1 = FUN_004b0b44(param_1);
  if (iVar1 != 0) {
    return iVar1;
  }
  if (param_1 < 0x81) {
    iVar1 = FUN_004010f9();
    if ((*(byte *)(iVar1 + 4) & 1) == 0) goto LAB_004a74b8;
  }
  FUN_004b17d4();
LAB_004a74b8:
  iVar1 = FUN_004010f9();
  *(uint *)(iVar1 + 4) = *(uint *)(iVar1 + 4) | 1;
  iVar1 = FUN_004010f9();
  return *(int *)(iVar1 + 0x28);
}

