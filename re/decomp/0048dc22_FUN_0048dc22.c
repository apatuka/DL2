// FUN_0048dc22 @ 0048dc22 size=153 sig=undefined FUN_0048dc22() cc=unknown
// callers: FUN_0048dcbb
// callees: 

void FUN_0048dc22(short param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  int local_10;
  int local_c;
  undefined4 *local_8;
  
  local_c = DAT_0051c2f4;
  for (local_10 = 0; local_10 < DAT_0051c2f8; local_10 = local_10 + 1) {
    iVar2 = local_c;
    iVar3 = local_10;
    local_8 = &DAT_0065e804 + local_c * 5;
    if ((int)(&DAT_0065e80c)[local_c * 5] < (int)param_1) {
      while (iVar3 = iVar3 + 1, iVar3 < DAT_0051c2f8) {
        iVar2 = iVar2 + -1;
        if (iVar2 < 0) {
          iVar2 = 0x13;
        }
        puVar4 = &DAT_0065e804 + iVar2 * 5;
        puVar5 = local_8;
        for (iVar1 = 5; local_8 = &DAT_0065e804 + iVar2 * 5, iVar1 != 0; iVar1 = iVar1 + -1) {
          *puVar5 = *puVar4;
          puVar4 = puVar4 + 1;
          puVar5 = puVar5 + 1;
        }
      }
      DAT_0051c2f8 = DAT_0051c2f8 + -1;
    }
    else {
      local_c = local_c + -1;
      if (local_c < 0) {
        local_c = 0x13;
      }
    }
  }
  return;
}

