// FUN_0040b788 @ 0040b788 size=241 sig=undefined FUN_0040b788() cc=unknown
// callers: FUN_0040b994
// callees: FUN_0040b12c,FUN_0040b2d4,FUN_0040ab54,FUN_0040b1b8,FUN_0040ac00,FUN_0040b644,FUN_0040b3d0,FUN_0040b4d0

undefined2 * FUN_0040b788(int *param_1)

{
  int iVar1;
  int iVar2;
  undefined2 *puVar3;
  undefined *local_14;
  int local_10;
  int local_c;
  undefined2 *local_8;
  
  puVar3 = &DAT_00645370;
  local_8 = (undefined2 *)0x0;
  local_c = -1;
  do {
    if ((undefined2 *)0x651caf < puVar3) {
      return local_8;
    }
    local_10 = 1;
    local_14 = &DAT_004b6644;
    do {
      iVar2 = *(int *)(local_14 + *param_1 * 0x40);
      if (iVar2 == 0xb) {
        iVar1 = FUN_0040b1b8(param_1);
        if (iVar1 != 0) goto LAB_0040b7d2;
      }
      else {
LAB_0040b7d2:
        if (iVar2 == 6) {
          iVar1 = FUN_0040b2d4(param_1);
          if (iVar1 == 0) goto LAB_0040b84b;
        }
        if (iVar2 == 0xd) {
          iVar1 = FUN_0040b3d0(param_1);
          if (iVar1 == 0) goto LAB_0040b84b;
        }
        if (iVar2 == 0x11) {
          iVar1 = FUN_0040b4d0(param_1);
          if (iVar1 == 0) goto LAB_0040b84b;
        }
        if (iVar2 == 0) break;
        if ((*(char *)(puVar3 + 3) != '\0') &&
           ((int)*(char *)(puVar3 + 4) == (int)*(short *)((int)param_1 + 10))) {
          iVar1 = FUN_0040ab54(param_1,puVar3);
          if (iVar1 == 0) {
            iVar1 = FUN_0040b12c(param_1,puVar3);
            if (iVar1 != 0) {
              iVar2 = FUN_0040ac00(puVar3,iVar2);
              if (iVar2 != 0) {
                iVar2 = FUN_0040b644(param_1,puVar3);
                if (local_c < iVar2) {
                  local_c = iVar2;
                  local_8 = puVar3;
                }
              }
            }
          }
        }
      }
LAB_0040b84b:
      local_10 = local_10 + 1;
      local_14 = local_14 + 4;
    } while (local_10 < 0x10);
    puVar3 = puVar3 + 0x2e;
  } while( true );
}

