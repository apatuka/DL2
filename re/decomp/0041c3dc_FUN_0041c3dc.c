// FUN_0041c3dc @ 0041c3dc size=60 sig=undefined FUN_0041c3dc() cc=unknown
// callers: FUN_0041c814,CheckBuilding,FUN_0041d414,FUN_0041d710,FUN_0041db10
// callees: FUN_0049eb44

void FUN_0041c3dc(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = FUN_0049eb44(DAT_004b7758,0x1e,1,0x18,0,0);
  iVar2 = 0;
  if (0 < iVar1) {
    do {
      FUN_0049eb44(DAT_004b7758,0x1e,1,0x27,0,0);
      iVar2 = iVar2 + 1;
    } while (iVar2 < iVar1);
  }
  return;
}

