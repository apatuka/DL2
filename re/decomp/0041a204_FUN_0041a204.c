// FUN_0041a204 @ 0041a204 size=613 sig=undefined FUN_0041a204() cc=unknown
// callers: FUN_0044abbc
// callees: GetKeyState,FUN_00418cf4,FUN_00419c88,FUN_00419c58,FUN_00418d18,FUN_00419fe0,FUN_00419d94,FUN_00419710

bool FUN_0041a204(undefined4 param_1,undefined4 param_2)

{
  undefined *puVar1;
  char cVar2;
  char cVar3;
  ushort uVar4;
  ushort uVar5;
  int *piVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  
  uVar4 = GetKeyState(0x10);
  uVar5 = GetKeyState(0x11);
  DAT_0053b260 = -1;
  DAT_0053b264 = -1;
  cVar2 = FUN_00419c88(param_1,param_2,&DAT_0053b260,&DAT_0053b264);
  if (cVar2 != '\0') {
    if ((uVar4 & 0x8000) != 0) {
      if ((DAT_0053b260 + DAT_005332bc < DAT_004b76c0) ||
         ((DAT_0053b260 + DAT_005332bc == DAT_004b76c0 && (DAT_0053b264 < DAT_004b76c4)))) {
        local_10 = DAT_0053b260 + DAT_005332bc;
        local_14 = DAT_0053b264;
        local_18 = DAT_004b76c0;
        local_1c = DAT_004b76c4;
      }
      else {
        local_10 = DAT_004b76c0;
        local_14 = DAT_004b76c4;
        local_18 = DAT_0053b260 + DAT_005332bc;
        local_1c = DAT_0053b264;
      }
      puVar1 = &DAT_005332c0 + local_10 * 0x146;
      for (iVar9 = local_10; iVar9 <= local_18; iVar9 = iVar9 + 1) {
        if (iVar9 == local_10) {
          iVar8 = local_14;
          if (iVar9 == local_18) {
            iVar7 = local_1c + 1;
          }
          else {
            iVar7 = 10;
          }
        }
        else if (iVar9 == local_18) {
          iVar8 = 0;
          iVar7 = local_1c + 1;
        }
        else {
          iVar8 = 0;
          iVar7 = 10;
        }
        piVar6 = (int *)(puVar1 + iVar8 * 0x20 + 0x18);
        for (; iVar8 < iVar7; iVar8 = iVar8 + 1) {
          if ((*piVar6 == 2) &&
             ((DAT_004d5aa0 != '\0' || (*(char *)(piVar6[1] + 8) == DAT_0058f1f4)))) {
            *piVar6 = 1;
          }
          piVar6 = piVar6 + 8;
        }
        puVar1 = puVar1 + 0x146;
      }
      if (DAT_005332b0 != '\0') {
        FUN_00419710();
      }
      FUN_00418d18();
      FUN_00418cf4();
      return true;
    }
    if ((uVar5 & 0x8000) != 0) {
      cVar2 = FUN_00419fe0(param_1,param_2,2);
      if ((cVar2 != '\0') && (DAT_005332b0 != '\0')) {
        FUN_00419710();
      }
      FUN_00418d18();
      FUN_00418cf4();
      return true;
    }
    cVar3 = FUN_00419c58(DAT_0053b260 + DAT_005332bc,DAT_0053b264);
    if (cVar3 == '\0') {
      FUN_00419d94();
      cVar2 = FUN_00419fe0(param_1,param_2,1);
      if ((cVar2 != '\0') && (DAT_005332b0 != '\0')) {
        FUN_00419710();
      }
      FUN_00418d18();
      FUN_00418cf4();
      return true;
    }
  }
  return cVar2 != '\0';
}

