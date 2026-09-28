// FUN_0042e2b8 @ 0042e2b8 size=64 sig=undefined FUN_0042e2b8() cc=unknown
// callers: FUN_00468ea4,RaceInit
// callees: FUN_0042dee0,FUN_0042df6c,FUN_0042e080,FUN_0042e054

void FUN_0042e2b8(void)

{
  int iVar1;
  
  iVar1 = FUN_0042df6c();
  if (iVar1 != 0) {
    FUN_0042dee0();
    while ((DAT_00557c80 == 0 && (DAT_004d8264 == 0))) {
      FUN_0042e080();
    }
    FUN_0042e054();
    if (DAT_004d8264 != 0) {
      DAT_0058f1ec = 1;
    }
  }
  return;
}

