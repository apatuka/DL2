// FUN_00409b28 @ 00409b28 size=47 sig=undefined FUN_00409b28() cc=unknown
// callers: FUN_00409b58
// callees: FUN_0040e868

undefined4 FUN_00409b28(void)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  int iVar5;
  
  uVar4 = 0;
  puVar3 = &DAT_00521bb4;
  iVar5 = 0;
  do {
    uVar1 = *puVar3;
    iVar2 = FUN_0040e868(uVar1);
    if (iVar5 < iVar2) {
      uVar4 = uVar1;
      iVar5 = iVar2;
    }
    puVar3 = (undefined4 *)puVar3[1];
  } while (puVar3 != &DAT_00521bb4);
  return uVar4;
}

