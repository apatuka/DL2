// FUN_0041e26c @ 0041e26c size=361 sig=undefined FUN_0041e26c() cc=unknown
// callers: FUN_0041e3d8
// callees: FUN_0041c378,FUN_0041b934,FUN_0041e0a8,GetKeyState,FUN_0041b908,FUN_0041c36c

void FUN_0041e26c(undefined4 param_1,undefined4 param_2)

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
  DAT_0053b878 = FUN_0041b934(param_1,param_2,&local_8,&local_c);
  if (DAT_0053b878 != '\0') {
    if ((uVar2 & 0x8000) == 0) {
      if ((uVar3 & 0x8000) == 0) {
        FUN_0041b908();
        FUN_0041e0a8(param_1,param_2);
      }
      else {
        FUN_0041e0a8(param_1,param_2);
      }
    }
    else {
      if ((DAT_0053b878 == '\0') ||
         ((DAT_004b7848 <= local_8 && ((DAT_004b7848 != local_8 || (DAT_004b784c <= local_c)))))) {
        local_10 = DAT_004b7848;
        local_14 = DAT_004b784c;
        local_18 = local_c;
      }
      else {
        local_10 = local_8;
        local_14 = local_c;
        local_18 = DAT_004b784c;
        local_8 = DAT_004b7848;
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
    }
    FUN_0041c378();
    FUN_0041c36c();
  }
  return;
}

