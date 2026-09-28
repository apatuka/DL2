// FUN_004213fc @ 004213fc size=392 sig=undefined FUN_004213fc() cc=unknown
// callers: FUN_00421734
// callees: FUN_0041ff24,FUN_0041b934,GetKeyState,FUN_00421340,FUN_0041ff18,FUN_0041b908

void FUN_004213fc(undefined4 param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  ushort uVar2;
  ushort uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  uVar2 = GetKeyState(0x10);
  uVar3 = GetKeyState(0x11);
  DAT_0053b8c5 = FUN_0041b934(param_1,param_2,&local_8,&local_c);
  if ((DAT_0053b8c5 != '\0') && ((&DAT_004b7760)[local_8 * 0xd + local_c] != 1)) {
    if ((uVar2 & 0x8000) == 0) {
      if ((uVar3 & 0x8000) == 0) {
        FUN_0041b908();
        FUN_00421340(param_1,param_2);
        FUN_0041ff24();
      }
      else {
        FUN_00421340(param_1,param_2);
        FUN_0041ff24();
      }
    }
    else {
      if ((local_8 < DAT_004b7a18) || ((DAT_004b7a18 == local_8 && (local_c < DAT_004b7a1c)))) {
        local_10 = local_8;
        local_14 = local_c;
        local_18 = DAT_004b7a1c;
        local_8 = DAT_004b7a18;
      }
      else {
        local_10 = DAT_004b7a18;
        local_14 = DAT_004b7a1c;
        local_18 = local_c;
      }
      puVar1 = &DAT_004b7760 + local_10 * 0xd;
      for (iVar7 = local_10; iVar7 <= local_8; iVar7 = iVar7 + 1) {
        if (iVar7 == local_10) {
          iVar6 = local_14;
          if (local_8 == iVar7) {
            iVar5 = local_18 + 1;
          }
          else {
            iVar5 = 0xd;
          }
        }
        else if (local_8 == iVar7) {
          iVar6 = 0;
          iVar5 = local_18 + 1;
        }
        else {
          iVar6 = 0;
          iVar5 = 0xd;
        }
        piVar4 = puVar1 + iVar6;
        for (; iVar6 < iVar5; iVar6 = iVar6 + 1) {
          if (*piVar4 == 2) {
            *piVar4 = 1;
          }
          piVar4 = piVar4 + 1;
        }
        puVar1 = puVar1 + 0xd;
      }
      FUN_0041ff24();
      FUN_0041ff18();
    }
  }
  return;
}

