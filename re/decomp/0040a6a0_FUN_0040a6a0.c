// FUN_0040a6a0 @ 0040a6a0 size=53 sig=undefined FUN_0040a6a0() cc=unknown
// callers: 
// callees: FUN_00416c28

undefined4 FUN_0040a6a0(undefined4 param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_00416c28(param_1,1);
  if ((iVar1 == 0) && ((1 << ((byte)param_1 & 0x1f) & (int)DAT_004fc34a) == 0)) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

