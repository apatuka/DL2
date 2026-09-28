// FUN_0043e168 @ 0043e168 size=48 sig=undefined FUN_0043e168() cc=unknown
// callers: CheckViewCombat
// callees: FUN_0043df90,FUN_0043ded0,FUN_0043e024

void FUN_0043e168(void)

{
  int iVar1;
  
  FUN_0043e024();
  iVar1 = FUN_0043ded0(DAT_00559dd4);
  if (iVar1 != -1) {
    FUN_0043df90((int)&DAT_0057bd38 + iVar1 * 0x86);
  }
  return;
}

