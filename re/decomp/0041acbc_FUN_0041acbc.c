// FUN_0041acbc @ 0041acbc size=60 sig=undefined FUN_0041acbc() cc=unknown
// callers: FUN_0041afec,FUN_0041b1c8
// callees: FUN_0049eb44

void FUN_0041acbc(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0049eb44(DAT_004b76f8,6,1,0x18,0,0);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004b76f8,6,1,0x27,0,0);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}

