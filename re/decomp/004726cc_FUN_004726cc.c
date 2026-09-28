// FUN_004726cc @ 004726cc size=99 sig=undefined FUN_004726cc() cc=unknown
// callers: FUN_0040da78,FUN_0040d9d4,FUN_0040b8f4,FUN_0040d64c,FUN_0040d768,FUN_0045ca3c,FUN_00401440,FUN_00408838,FUN_004435b0,FUN_004727dc,FUN_0040d808
// callees: FUN_00472578,FUN_0045dfb0,FUN_00446b08

int FUN_004726cc(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  
  DAT_00653430 = 0;
  for (iVar1 = 0; (DAT_00653430 == 0 && (iVar1 < 3)); iVar1 = iVar1 + 1) {
    FUN_0045dfb0(0x2000 << ((byte)param_3 & 0x1f));
    FUN_00446b08(0,param_3);
    FUN_00472578(param_1,param_2,1,param_3,iVar1);
    if (DAT_00653430 != 0) {
      return iVar1;
    }
  }
  return iVar1;
}

