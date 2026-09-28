// FUN_0045973c @ 0045973c size=294 sig=undefined FUN_0045973c() cc=unknown
// callers: FUN_00459bdc,FUN_0045b970,FUN_00459c48,FUN_0045bf78
// callees: FUN_004596d0,FUN_0045965c

void FUN_0045973c(int param_1,int param_2,int param_3,undefined4 *param_4)

{
  int *piVar1;
  int iVar2;
  undefined4 *puVar3;
  
  *param_4 = 0;
  for (puVar3 = (undefined4 *)&DAT_00645370; puVar3 < &DAT_00651cb0; puVar3 = puVar3 + 0x17) {
    if (((*(char *)((int)puVar3 + 6) != '\0') &&
        ((((DAT_004d5aa0 != '\0' || (*(char *)(puVar3 + 2) == DAT_0058f1f4)) &&
          (param_1 == puVar3[0xf])) ||
         ((((DAT_004d5aa0 == '\0' && (*(char *)(puVar3 + 2) != DAT_0058f1f4)) &&
           ((param_1 == puVar3[0xe] &&
            (((*(byte *)((int)puVar3 + 2) & 1) == 0 || (DAT_00583c20 != 0)))))) &&
          ('\x01' < *(char *)(param_1 + 0x66 + DAT_0058f1f4))))))) &&
       ((*(char *)((int)puVar3 + 6) != '$' || (*(char *)(puVar3 + 2) == DAT_0058f1f4)))) {
      if (*(char *)(param_1 + 0x21) == '\0') {
        iVar2 = FUN_0045965c(puVar3);
      }
      else {
        iVar2 = FUN_004596d0(puVar3);
      }
      if (iVar2 != -1) {
        if (*(char *)(puVar3 + 2) == DAT_0058f1f4) {
          piVar1 = (int *)(param_3 + iVar2 * 4);
          *piVar1 = *piVar1 + 1;
          if ((*(char *)((int)puVar3 + 7) == '\x04') && (puVar3[0x12] != 0)) {
            *param_4 = 1;
          }
        }
        else {
          piVar1 = (int *)(param_2 + (char)(&DAT_0059f162)[*(char *)(puVar3 + 2) * 0x2d8] * 4);
          *piVar1 = *piVar1 + 1;
        }
      }
    }
  }
  return;
}

