// FUN_00413fe4 @ 00413fe4 size=31 sig=undefined FUN_00413fe4() cc=unknown
// callers: FUN_0045b8a8
// callees: FUN_00413eb4,FUN_00413c70,FUN_00413e88,FUN_00413cd0

void FUN_00413fe4(void)

{
  int iVar1;
  
  iVar1 = FUN_00413cd0();
  if (iVar1 != 0) {
    FUN_00413c70();
    do {
      iVar1 = FUN_00413eb4();
    } while (iVar1 == 0);
    FUN_00413e88();
  }
  return;
}

