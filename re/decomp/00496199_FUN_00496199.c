// FUN_00496199 @ 00496199 size=79 sig=undefined FUN_00496199() cc=unknown
// callers: FUN_004a1555,FUN_00482ba0
// callees: FUN_0048a667,FUN_00490ab3

int FUN_00496199(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  
  iVar1 = 0;
  if (((byte)DAT_0051e090 & 2) != 0) {
    iVar1 = FUN_00490ab3(param_1,0x45564157,param_2,0,0x80000000);
    if ((iVar1 != 0) && (1 < *(int *)(DAT_0065eba0 + 0x20))) {
      iVar1 = FUN_0048a667(iVar1);
      if (iVar1 != 0) {
        *(uint *)(iVar1 + 0xc) = *(uint *)(iVar1 + 0xc) & 0xfffffffe;
      }
    }
  }
  return iVar1;
}

