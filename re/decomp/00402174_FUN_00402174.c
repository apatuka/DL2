// FUN_00402174 @ 00402174 size=105 sig=undefined FUN_00402174() cc=unknown
// callers: 
// callees: 

int FUN_00402174(int param_1)

{
  undefined2 *puVar1;
  int iVar2;
  
  iVar2 = 0;
  for (puVar1 = &DAT_005f0410; puVar1 < &DAT_00645370; puVar1 = puVar1 + 0x91) {
    if (((*(char *)(puVar1 + 2) != '\0') &&
        (((puVar1[10] != 0 || ((*(byte *)(puVar1 + 1) & 2) == 0)) ||
         ((*(byte *)(puVar1 + 1) & 4) == 0)))) &&
       (param_1 == (char)(&DAT_005a43f0)[(short)puVar1[4] * 0xadc])) {
      iVar2 = iVar2 + (char)(&DAT_004f9dc8)[*(char *)(puVar1 + 2) * 0x32];
    }
  }
  return iVar2;
}

