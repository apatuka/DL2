// FUN_004a421e @ 004a421e size=85 sig=undefined FUN_004a421e() cc=unknown
// callers: FUN_004a322d,FUN_00414f38
// callees: FUN_004a4185,FUN_004a41bc,FUN_004a2078,FUN_004a4209

void FUN_004a421e(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (param_1 == 0) {
    param_1 = FUN_004a4185(0);
  }
  iVar2 = param_1;
  if (param_1 != 0) {
    while (iVar1 = FUN_004a41bc(iVar2), iVar1 != 0) {
      iVar2 = FUN_004a41bc(iVar2);
    }
    for (; iVar2 != 0; iVar2 = FUN_004a4209(iVar2)) {
      if ((*(byte *)(iVar2 + 0x1c) & 0x80) == 0) {
        FUN_004a2078(iVar2);
      }
      if (param_1 == iVar2) {
        return;
      }
    }
  }
  return;
}

