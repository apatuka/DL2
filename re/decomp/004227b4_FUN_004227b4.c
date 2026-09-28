// FUN_004227b4 @ 004227b4 size=60 sig=undefined FUN_004227b4() cc=unknown
// callers: FUN_004227f0
// callees: FUN_0049eb44

void FUN_004227b4(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0049eb44(DAT_004b7b50,0xe,1,0x18,0,0);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004b7b50,0xe,1,0x27,0,0);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}

