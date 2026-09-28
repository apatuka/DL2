// FUN_004ace38 @ 004ace38 size=61 sig=undefined FUN_004ace38() cc=unknown
// callers: 
// callees: FUN_004acd5c,FUN_004b12c4,GetFileAttributesA

undefined4 FUN_004ace38(LPCSTR param_1,byte param_2)

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

