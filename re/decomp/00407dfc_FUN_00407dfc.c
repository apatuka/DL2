// FUN_00407dfc @ 00407dfc size=124 sig=undefined FUN_00407dfc() cc=unknown
// callers: FUN_00407dfc,FUN_00407e78
// callees: FUN_004054d8,FUN_00407dfc

undefined4 FUN_00407dfc(int param_1,int param_2)

{
  int iVar1;
  char *pcVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = *(int *)(&DAT_004b6444 + param_2 * 4);
  iVar1 = FUN_004054d8(iVar3,0);
  if (iVar1 != 0) {
    iVar1 = 0;
    pcVar2 = &DAT_004f9dd4 + param_1 * 0x32;
    do {
      if (iVar3 == *pcVar2) {
        return 1;
      }
      iVar1 = iVar1 + 1;
      pcVar2 = pcVar2 + 1;
    } while (iVar1 < 5);
  }
  if ((param_2 == 4) &&
     (((iVar3 = FUN_00407dfc(param_1,5), iVar3 != 0 || (iVar3 = FUN_00407dfc(param_1,6), iVar3 != 0)
       ) || (iVar3 = FUN_00407dfc(param_1,7), iVar3 != 0)))) {
    uVar4 = 1;
  }
  else {
    uVar4 = 0;
  }
  return uVar4;
}

