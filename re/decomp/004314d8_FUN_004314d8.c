// FUN_004314d8 @ 004314d8 size=89 sig=undefined FUN_004314d8() cc=unknown
// callers: CheckSubTech
// callees: FUN_0049eb44,memcpy

void FUN_004314d8(int param_1)

{
  int iVar1;
  
  for (iVar1 = param_1; iVar1 < DAT_00558e60; iVar1 = iVar1 + 1) {
    memcpy(&DAT_00558de0 + iVar1 * 2,&DAT_00558de8 + iVar1 * 8,8);
  }
  DAT_00558e60 = DAT_00558e60 + -1;
  FUN_0049eb44(DAT_004c42dc,0x14,1,0x27,param_1,0);
  return;
}

