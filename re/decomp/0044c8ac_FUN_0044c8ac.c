// FUN_0044c8ac @ 0044c8ac size=204 sig=undefined FUN_0044c8ac() cc=unknown
// callers: FUN_00403a10,FUN_004031b0,FUN_004068f8,FUN_0040854c,FUN_0041db10,FUN_004067d0,FUN_00406538
// callees: FUN_0044ba40,FUN_004023dc,FUN_0044ba18,FUN_00475ce8

undefined4 FUN_0044c8ac(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int local_8;
  
  if (*(char *)(param_2 + 5) == '\x11') {
    iVar1 = FUN_0044ba18(param_2);
    iVar2 = FUN_0044ba40(param_2);
    if (iVar1 == iVar2) {
      iVar1 = FUN_004023dc(param_2,0x14);
      if (((iVar1 != -1) && (param_3 != -1)) && (*(int *)(param_2 + 0x18 + iVar1 * 4) != 0)) {
        uVar3 = FUN_00475ce8(param_1,param_2,iVar1,param_2,param_3);
        return uVar3;
      }
      return 0;
    }
  }
  if ((param_1 != 0) && (param_2 != 0)) {
    iVar1 = FUN_0044ba18(param_2);
    iVar2 = FUN_0044ba40(param_2);
    if (iVar1 < iVar2) {
      local_8 = 0;
      piVar4 = (int *)(param_1 + 0x154);
      do {
        iVar1 = *piVar4;
        if (((iVar1 != 0) && (iVar2 = FUN_004023dc(iVar1,0x14), iVar2 != -1)) &&
           ((param_3 != -1 && (*(int *)(iVar1 + 0x18 + iVar2 * 4) != 0)))) {
          uVar3 = FUN_00475ce8(param_1,iVar1,iVar2,param_2,param_3);
          return uVar3;
        }
        local_8 = local_8 + 1;
        piVar4 = piVar4 + 0xd;
      } while (local_8 < 0x24);
    }
  }
  return 0;
}

