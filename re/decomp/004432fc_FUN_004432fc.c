// FUN_004432fc @ 004432fc size=159 sig=undefined FUN_004432fc() cc=unknown
// callers: FUN_004437c4
// callees: FUN_004412d4

void FUN_004432fc(int param_1)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined2 *puVar4;
  char *local_10;
  int local_c;
  int local_8;
  
  for (puVar4 = &DAT_0055a820; puVar4 < &DAT_0055dc60; puVar4 = puVar4 + 0xd1) {
    local_8 = 0;
    local_c = 0;
    iVar2 = 0;
    piVar3 = (int *)(puVar4 + 0xad);
    local_10 = &DAT_0059f161;
    do {
      if ((*local_10 != '\0') && (iVar2 != param_1)) {
        iVar1 = FUN_004412d4(param_1,iVar2,0x10);
        if (iVar1 == 0) {
          if (local_8 < *piVar3) {
            local_8 = *piVar3;
          }
          if (local_c < piVar3[7]) {
            local_c = piVar3[7];
          }
        }
      }
      iVar2 = iVar2 + 1;
      *(int *)(puVar4 + 0xcd) = local_8;
      piVar3 = piVar3 + 1;
      *(int *)(puVar4 + 0xcf) = local_c;
      local_10 = local_10 + 0x2d8;
    } while (iVar2 < 7);
  }
  return;
}

