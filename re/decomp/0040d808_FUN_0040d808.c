// FUN_0040d808 @ 0040d808 size=278 sig=undefined FUN_0040d808() cc=unknown
// callers: FUN_0040dbc4,FUN_0040b644,FUN_0040fe58
// callees: FUN_0040d768,FUN_0040d614,FUN_004726cc,FUN_0040d5c0,FUN_004412d4

undefined4 * FUN_0040d808(int param_1,int param_2,undefined4 *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 *puVar3;
  int local_c;
  undefined4 *local_8;
  
  if (((param_1 == 0) || (param_2 == 0)) || (param_3 == (undefined4 *)0x0)) {
    local_8 = (undefined4 *)0x0;
  }
  else {
    local_8 = (undefined4 *)0x0;
    local_c = 1000;
    for (puVar3 = &DAT_005a4eac; puVar3 <= &DAT_005a43d0 + DAT_004d5b18 * 0xadc;
        puVar3 = puVar3 + 0x2b7) {
      if (((((*(char *)((int)puVar3 + 0x7e) != '\0') &&
            (*(char *)((int)param_3 + 0x22) == *(char *)((int)puVar3 + 0x22))) &&
           (iVar1 = FUN_0040d5c0(puVar3,param_1), iVar1 != 0)) &&
          (((param_3 == puVar3 || (*(char *)(puVar3 + 8) == -1)) ||
           (((int)*(char *)(puVar3 + 8) == (int)*(short *)(param_1 + 10) ||
            (iVar1 = FUN_004412d4((int)*(short *)(param_1 + 10),(int)*(char *)(puVar3 + 8),2),
            iVar1 != 0)))))) &&
         ((iVar1 = FUN_004726cc(puVar3,param_3,(int)*(short *)(param_1 + 10)), iVar1 < 2 &&
          (iVar1 = FUN_0040d768(param_2,puVar3,(int)*(short *)(param_1 + 10)), iVar1 != 0)))) {
        iVar1 = FUN_0040d614(param_2,puVar3,(int)*(short *)(param_1 + 10),6);
        iVar2 = FUN_0040d614(puVar3,param_3,(int)*(short *)(param_1 + 10),6);
        if (iVar1 + iVar2 < local_c) {
          local_c = iVar1 + iVar2;
          local_8 = puVar3;
        }
      }
    }
  }
  return local_8;
}

