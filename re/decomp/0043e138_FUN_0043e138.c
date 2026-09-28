// FUN_0043e138 @ 0043e138 size=48 sig=undefined FUN_0043e138() cc=unknown
// callers: CheckViewCombat
// callees: FUN_0043df90,FUN_0043df3c,FUN_0043e024

void FUN_0043e138(void)

{
  int iVar1;
  
  FUN_0043e024();
  iVar1 = FUN_0043df3c(DAT_00559dd4);
  if (iVar1 != -1) {
    FUN_0043df90((int)&DAT_0057bd38 + iVar1 * 0x86);
  }
  return;
}

