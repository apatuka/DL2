// FUN_0040f3d8 @ 0040f3d8 size=158 sig=undefined FUN_0040f3d8() cc=unknown
// callers: FUN_0040f478
// callees: FUN_0040c538

undefined4 * FUN_0040f3d8(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_c;
  undefined4 *local_8;
  
  iVar1 = param_1[2];
  local_8 = (undefined4 *)0x0;
  local_c = 1000000;
  for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
      puVar3 = puVar3 + 0x2b7) {
    if ((*(char *)((int)puVar3 + 0x7e) != '\0') && ((int)(short)iVar1 == (int)*(char *)(puVar3 + 8))
       ) {
      iVar2 = FUN_0040c538(param_1,puVar3,0);
      if ((iVar2 != 0) &&
         ((((*param_1 == 4 && (*(char *)((int)puVar3 + 0x21) != '\0')) ||
           ((*param_1 == 0xc && (*(char *)((int)puVar3 + 0x21) == '\0')))) &&
          ((*(short *)(puVar3 + 0xc) == 0 && ((int)puVar3[0x296] < local_c)))))) {
        local_c = puVar3[0x296];
        local_8 = puVar3;
      }
    }
  }
  return local_8;
}

