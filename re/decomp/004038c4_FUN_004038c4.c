// FUN_004038c4 @ 004038c4 size=169 sig=undefined FUN_004038c4() cc=unknown
// callers: FUN_00408a88
// callees: FUN_0044ba40,FUN_004762a8,FUN_0044ba18

void FUN_004038c4(int param_1)

{
  int iVar1;
  undefined2 *puVar2;
  
  for (puVar2 = &DAT_005f0410; puVar2 < &DAT_00645370; puVar2 = puVar2 + 0x91) {
    if ((((puVar2 != (undefined2 *)0x0) &&
         (param_1 == (char)(&DAT_005a43f0)[(short)puVar2[4] * 0xadc])) &&
        (*(char *)(puVar2 + 2) != '\x11')) && ((*(byte *)(puVar2 + 1) & 4) != 0)) {
      iVar1 = FUN_0044ba18(puVar2);
      if (iVar1 == 0) {
        iVar1 = FUN_0044ba40(puVar2);
        if (((iVar1 != 0) && ((&DAT_004f9dc8)[*(char *)(puVar2 + 2) * 0x32] != '\0')) &&
           (puVar2[10] == 0)) {
          puVar2[1] = puVar2[1] & 0xfffb;
          FUN_004762a8(&DAT_005a43d0 + (short)puVar2[4] * 0xadc,puVar2);
        }
      }
    }
  }
  return;
}

