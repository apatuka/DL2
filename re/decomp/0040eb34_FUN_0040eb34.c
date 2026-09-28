// FUN_0040eb34 @ 0040eb34 size=206 sig=undefined FUN_0040eb34() cc=unknown
// callers: FUN_0040ec04
// callees: FUN_0044d1e4,FUN_0040dd80,FUN_0040c668

undefined4 * FUN_0040eb34(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  int local_c;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  iVar1 = FUN_0040c668(param_1);
  if (iVar1 != 0) {
    local_c = 0;
    for (puVar4 = &DAT_005a4eac; puVar4 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        puVar4 = puVar4 + 0x2b7) {
      if ((((*(char *)((int)puVar4 + 0x7e) != '\0') &&
           ((int)*(char *)(puVar4 + 8) == (int)*(short *)(param_1 + 10))) && (puVar4[0x22a] == 0))
         && (((*(char *)(iVar1 + 6) == '\x19' && (*(char *)((int)puVar4 + 0x21) != '\0')) ||
             ((*(char *)(iVar1 + 6) == '\f' && (*(char *)((int)puVar4 + 0x21) == '\0')))))) {
        iVar2 = FUN_0040dd80(puVar4,0,(int)*(short *)(param_1 + 10));
        if (local_c <= iVar2) {
          if (*(short *)(puVar4 + 0xc) != 0) {
            iVar3 = FUN_0044d1e4(puVar4,6,0);
            if (iVar3 == -1) goto LAB_0040ebd5;
          }
          local_c = iVar2;
          local_8 = puVar4;
        }
      }
LAB_0040ebd5:
    }
  }
  return local_8;
}

