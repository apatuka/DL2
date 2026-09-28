// FUN_004b0428 @ 004b0428 size=64 sig=undefined FUN_004b0428() cc=unknown
// callers: FUN_004b0468
// callees: 

void FUN_004b0428(void)

{
  int iVar1;
  uint uVar2;
  
  for (uVar2 = 0xc; uVar2 < DAT_005211e0; uVar2 = uVar2 + 4) {
    iVar1 = uVar2 * 2 + DAT_005211f4;
    *(int *)(iVar1 + -8) = iVar1 + -0xc;
    *(int *)(iVar1 + -4) = iVar1 + -0xc;
  }
  iVar1 = DAT_005211e0 * 2 + DAT_005211f4;
  *(undefined4 *)(iVar1 + -8) = 0;
  *(undefined4 *)(iVar1 + -4) = 0;
  return;
}

