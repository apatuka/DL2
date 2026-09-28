// FUN_00483bd4 @ 00483bd4 size=103 sig=undefined FUN_00483bd4() cc=unknown
// callers: FUN_00483d58
// callees: FUN_00423690,FUN_00483b84,FUN_0048394c,FUN_004839a4,FUN_004764dc

void FUN_00483bd4(undefined4 param_1)

{
  int iVar1;
  
  FUN_0048394c(PTR_DAT_004d5988 + 0x3a,param_1);
  FUN_00483b84(DAT_0058f1f4,PTR_DAT_004d5988 + 0x3a);
  iVar1 = FUN_004839a4(*(undefined4 *)(PTR_DAT_004d5988 + 0x3a));
  if (iVar1 == -1) {
    FUN_00423690(DAT_0058f1f4,0x39,0,0,0,0);
  }
  else {
    FUN_004764dc(DAT_0058f1f4,iVar1);
  }
  return;
}

