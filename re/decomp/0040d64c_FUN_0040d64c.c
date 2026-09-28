// FUN_0040d64c @ 0040d64c size=282 sig=undefined FUN_0040d64c() cc=unknown
// callers: FUN_0040dbc4,FUN_0040c7a4,FUN_0040b644,FUN_0040fe58
// callees: FUN_0040d614,FUN_004726cc,FUN_004412d4

undefined4 * FUN_0040d64c(int param_1,int param_2,int param_3)

{
  int iVar1;
  int *piVar2;
  undefined4 *puVar3;
  int local_14;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == 0)) {
    local_8 = (undefined4 *)0x0;
  }
  else {
    local_8 = (undefined4 *)0x0;
    local_c = 1000;
    for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        puVar3 = puVar3 + 0x2b7) {
      if (((((*(char *)((int)puVar3 + 0x7e) != '\0') &&
            (*(char *)(param_2 + 0x22) == *(char *)((int)puVar3 + 0x22))) &&
           ((iVar1 = (int)*(char *)(puVar3 + 8), iVar1 == -1 ||
            ((iVar1 == *(short *)(param_1 + 10) ||
             (iVar1 = FUN_004412d4((int)*(short *)(param_1 + 10),iVar1,2), iVar1 != 0)))))) &&
          (iVar1 = FUN_004726cc(param_3,puVar3,(int)*(short *)(param_1 + 10)), iVar1 < 3)) &&
         ((1 << (*(byte *)(param_3 + 0x22) & 0x1f) & puVar3[0x228]) != 0)) {
        local_10 = FUN_0040d614(param_2,puVar3,(int)*(short *)(param_1 + 10),6);
        local_14 = FUN_0040d614(param_3,puVar3,(int)*(short *)(param_1 + 10),6);
        if (local_14 < local_10) {
          piVar2 = &local_10;
        }
        else {
          piVar2 = &local_14;
        }
        local_10 = *piVar2;
        if (local_10 < local_c) {
          local_c = local_10;
          local_8 = puVar3;
        }
      }
    }
  }
  return local_8;
}

