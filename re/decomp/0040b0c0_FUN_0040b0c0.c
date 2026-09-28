// FUN_0040b0c0 @ 0040b0c0 size=57 sig=undefined FUN_0040b0c0() cc=unknown
// callers: FUN_00401ac0,FUN_0040c018,FUN_0040febc,FUN_0040b994,FUN_0040cd0c,FUN_0040beb4,FUN_0040b968
// callees: FUN_0040ab54,FUN_0040b074

void FUN_0040b0c0(int param_1,undefined4 param_2)

{
  int iVar1;
  int *piVar2;
  
  iVar1 = FUN_0040ab54(param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = 0;
    piVar2 = (int *)(param_1 + 0x44);
    do {
      if (*piVar2 == 0) {
        FUN_0040b074(param_1,param_2,iVar1);
        return;
      }
      iVar1 = iVar1 + 1;
      piVar2 = piVar2 + 1;
    } while (iVar1 < 0x10);
  }
  return;
}

