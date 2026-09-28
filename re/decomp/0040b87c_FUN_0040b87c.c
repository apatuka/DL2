// FUN_0040b87c @ 0040b87c size=118 sig=undefined FUN_0040b87c() cc=unknown
// callers: FUN_0040febc,FUN_0040b994
// callees: FUN_0040b12c,FUN_0040ab54,FUN_0040ac00,FUN_0040b644

undefined4 * FUN_0040b87c(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *local_8;
  
  local_8 = (undefined4 *)0x0;
  iVar3 = -1;
  for (puVar2 = (undefined4 *)&DAT_00645370; puVar2 < &DAT_00651cb0; puVar2 = puVar2 + 0x17) {
    if ((*(char *)((int)puVar2 + 6) != '\0') &&
       ((int)*(char *)(puVar2 + 2) == (int)*(short *)(param_1 + 10))) {
      iVar1 = FUN_0040ab54(param_1,puVar2);
      if (iVar1 == 0) {
        iVar1 = FUN_0040b12c(param_1,puVar2);
        if (iVar1 != 0) {
          iVar1 = FUN_0040ac00(puVar2,param_2);
          if (iVar1 != 0) {
            iVar1 = FUN_0040b644(param_1,puVar2);
            if (iVar3 < iVar1) {
              iVar3 = iVar1;
              local_8 = puVar2;
            }
          }
        }
      }
    }
  }
  return local_8;
}

