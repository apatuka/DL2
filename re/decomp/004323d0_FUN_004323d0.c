// FUN_004323d0 @ 004323d0 size=89 sig=undefined FUN_004323d0() cc=unknown
// callers: CheckSubUnit
// callees: FUN_0049eb44,memcpy

void FUN_004323d0(int param_1)

{
  int iVar1;
  
  for (iVar1 = param_1; iVar1 < DAT_00558e64; iVar1 = iVar1 + 1) {
    memcpy(&DAT_00558cd4 + iVar1 * 2,&DAT_00558cdc + iVar1 * 2,8);
  }
  DAT_00558e64 = DAT_00558e64 + -1;
  FUN_0049eb44(DAT_004c42e0,0xe,1,0x27,param_1,0);
  return;
}

