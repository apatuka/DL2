// FUN_0040548c @ 0040548c size=76 sig=undefined FUN_0040548c() cc=unknown
// callers: FUN_004054d8
// callees: FUN_0044ba40,FUN_004023dc,FUN_0044ba18

int FUN_0040548c(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  
  iVar5 = 0;
  piVar4 = (int *)(param_1 + 0x154);
  do {
    iVar1 = *piVar4;
    if (iVar1 != 0) {
      iVar2 = FUN_0044ba18(iVar1);
      iVar3 = FUN_0044ba40(iVar1);
      if ((iVar2 < iVar3) && (iVar2 = FUN_004023dc(iVar1,param_2), iVar2 != -1)) {
        return iVar1;
      }
    }
    iVar5 = iVar5 + 1;
    piVar4 = piVar4 + 0xd;
    if (0x23 < iVar5) {
      return 0;
    }
  } while( true );
}

