// FUN_0046f804 @ 0046f804 size=88 sig=undefined FUN_0046f804() cc=unknown
// callers: WinMain
// callees: FUN_004764dc,FUN_0046f7d0,FUN_00483cbc

void FUN_0046f804(void)

{
  int iVar1;
  undefined4 uVar2;
  
  if ((PTR_DAT_004d5988[0x3e] == '\0') && (iVar1 = FUN_0046f7d0(), iVar1 == 0)) {
    return;
  }
  if ((1 << ((byte)DAT_0058f1f4 & 0x1f) &
      (int)(short)(&DAT_004fbbac)[(char)PTR_DAT_004d5988[0x3e] * 0x19]) != 0) {
    uVar2 = FUN_00483cbc(PTR_DAT_004d5988,0);
    FUN_004764dc(DAT_0058f1f4,uVar2);
  }
  return;
}

