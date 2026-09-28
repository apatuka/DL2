// FUN_00492ac4 @ 00492ac4 size=42 sig=undefined FUN_00492ac4() cc=unknown
// callers: 
// callees: FUN_00492578

void FUN_00492ac4(byte *param_1)

{
  byte bVar1;
  int iVar2;
  
  bVar1 = *param_1;
  iVar2 = 0;
  if (bVar1 != 0) {
    do {
      param_1 = param_1 + 1;
      FUN_00492578(*param_1);
      iVar2 = iVar2 + 1;
    } while (iVar2 < (int)(uint)bVar1);
  }
  return;
}

