// thunk_FUN_004ace38 @ 004a9b54 size=5 sig=undefined thunk_FUN_004ace38() cc=unknown
// callers: FUN_004b1dac,FUN_004aa880,FUN_004b1c4c
// callees: 

undefined4 thunk_FUN_004ace38(LPCSTR param_1,byte param_2)

{
  DWORD DVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  
  DVar1 = GetFileAttributesA(param_1);
  if (DVar1 == 0xffffffff) {
    uVar2 = FUN_004acd5c();
    return uVar2;
  }
  if (((param_2 & 2) != 0) && ((DVar1 & 1) != 0)) {
    puVar3 = (undefined4 *)FUN_004b12c4();
    *puVar3 = 5;
    return 0xffffffff;
  }
  return 0;
}

