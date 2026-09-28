// FUN_0044de48 @ 0044de48 size=81 sig=undefined FUN_0044de48() cc=unknown
// callers: FUN_0044de9c,FUN_0044d890
// callees: 

int FUN_0044de48(int param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = &DAT_005f0410; puVar1 < &DAT_00645370; puVar1 = puVar1 + 0x91) {
    if ((*(char *)(puVar1 + 2) == '%') &&
       (param_1 == (char)(&DAT_005a43f0)[(short)puVar1[4] * 0xadc])) {
      iVar2 = iVar2 + 1;
    }
  }
  return iVar2;
}

