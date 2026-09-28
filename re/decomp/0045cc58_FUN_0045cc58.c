// FUN_0045cc58 @ 0045cc58 size=160 sig=undefined FUN_0045cc58() cc=unknown
// callers: 
// callees: FUN_00459588,FUN_0045951c,FUN_004594b8

void FUN_0045cc58(void)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  
  iVar2 = DAT_00583d64;
  if (DAT_00583d64 != 0) {
    iVar3 = DAT_004c5b50 * 0xadc;
    if ((&DAT_005a43f1)[iVar3] == '\0') {
      uVar1 = FUN_004594b8(DAT_00583d64);
    }
    else {
      uVar1 = FUN_0045951c(DAT_00583d64);
    }
    DAT_004d1bfc = DAT_004d1bfc + 1;
    iVar2 = FUN_00459588(&DAT_005a43d0 + iVar3,uVar1,DAT_004d1bfc,
                         *(char *)(DAT_00583d64 + 8) != (&DAT_005a43f0)[iVar3]);
    if (iVar2 == 0) {
      DAT_004d1bfc = 0;
      iVar2 = FUN_00459588(&DAT_005a43d0 + iVar3,uVar1,0,
                           *(char *)(DAT_00583d64 + 8) != (&DAT_005a43f0)[iVar3]);
    }
  }
  DAT_00583d64 = iVar2;
  return;
}

