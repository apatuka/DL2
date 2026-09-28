// FUN_0040668c @ 0040668c size=295 sig=undefined FUN_0040668c() cc=unknown
// callers: FUN_004068f8,FUN_004067d0
// callees: FUN_0044eeb4,FUN_0044ba40,FUN_004023dc,FUN_0044ba18

undefined2 * FUN_0040668c(int param_1,undefined4 param_2,undefined *param_3)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  int local_c;
  undefined2 *local_8;
  
  local_8 = (undefined2 *)0x0;
  local_c = -1;
  for (puVar3 = &DAT_005f0410; puVar3 < &DAT_00645370; puVar3 = puVar3 + 0x91) {
    if ((((puVar3 != (undefined2 *)0x0) && (*(char *)(puVar3 + 2) != '\0')) &&
        ((*(byte *)(puVar3 + 1) & 4) != 0)) && ((*(byte *)((int)puVar3 + 3) & 0x20) == 0)) {
      iVar1 = FUN_0044ba18(puVar3);
      iVar2 = FUN_0044ba40(puVar3);
      if (((iVar1 < iVar2) || (*(char *)((int)puVar3 + 5) == '\x11')) &&
         (((char)(&DAT_005a43f0)[(short)puVar3[4] * 0xadc] == param_1 &&
          ((param_3 == &DAT_005a43d0 + (short)puVar3[4] * 0xadc || (param_3 == (undefined *)0x0)))))
         ) {
        iVar1 = FUN_004023dc(puVar3,param_2);
        if (iVar1 != -1) {
          iVar1 = FUN_0044eeb4(&DAT_0059f160 + param_1 * 0x2d8,
                               &DAT_005a43d0 + (short)puVar3[4] * 0xadc,
                               (int)*(char *)((int)puVar3 + 7),iVar1,1);
          if (local_c < iVar1) {
            local_c = iVar1;
            local_8 = puVar3;
          }
        }
      }
    }
  }
  if (local_8 != (undefined2 *)0x0) {
    local_8[1] = local_8[1] | 0x2000;
  }
  return local_8;
}

