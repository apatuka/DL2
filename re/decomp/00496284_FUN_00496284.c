// FUN_00496284 @ 00496284 size=82 sig=undefined FUN_00496284() cc=unknown
// callers: FUN_00482964
// callees: FUN_004955b2,FUN_00490122,FUN_0049624e

bool FUN_00496284(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  if (DAT_0051e090 == 0) {
    iVar1 = FUN_0049624e(param_1,param_2);
    if (iVar1 != 0) {
      FUN_00490122(0x45564157,&LAB_00495de4);
      if (DAT_0051e08c == 0) {
        DAT_0051e08c = FUN_004955b2(0,0);
      }
    }
  }
  return DAT_0051e090 != 0;
}

