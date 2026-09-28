// FUN_00419e0c @ 00419e0c size=160 sig=undefined FUN_00419e0c() cc=unknown
// callers: FUN_0045bde4,FUN_0045ccf8,FUN_0045bb88
// callees: FUN_0045965c,FUN_004596d0

int FUN_00419e0c(int param_1)

{
  int in_EAX;
  int *piVar1;
  int iVar2;
  int *local_10;
  int local_c;
  int local_8;
  
  local_8 = 0;
  local_c = 0;
  local_10 = &DAT_005332d8;
  do {
    iVar2 = 0;
    piVar1 = local_10;
    do {
      if (*piVar1 != 0) {
        if (*(char *)(piVar1[1] + 8) == DAT_0058f1f4) {
          if ((&DAT_005a43f1)[DAT_004c5b50 * 0xadc] == '\0') {
            in_EAX = FUN_0045965c(piVar1[1]);
          }
          else {
            in_EAX = FUN_004596d0(piVar1[1]);
          }
        }
        if (param_1 == in_EAX) {
          *piVar1 = 1;
          local_8 = local_8 + 1;
        }
      }
      iVar2 = iVar2 + 1;
      piVar1 = piVar1 + 8;
    } while (iVar2 < 10);
    local_c = local_c + 1;
    local_10 = (int *)((int)local_10 + 0x146);
  } while (local_c < 100);
  return local_8;
}

