// FUN_0046a588 @ 0046a588 size=374 sig=undefined FUN_0046a588() cc=unknown
// callers: FUN_004824c4,FUN_00413428,FUN_00432824,FUN_0042f224,FUN_00421fc4
// callees: 

void FUN_0046a588(undefined1 *param_1,int param_2,int param_3,int param_4)

{
  ulonglong uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined1 *puVar9;
  undefined1 *puVar10;
  undefined1 *puVar11;
  int iVar12;
  undefined1 *local_30;
  int local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_14;
  
  local_2c = param_4;
  local_30 = DAT_0058f134;
  if ((DAT_0058f134 != (undefined1 *)0x0) && (param_1 != (undefined1 *)0x0)) {
    iVar3 = (int)DAT_004d5b1a;
    iVar7 = DAT_004d5b1b * param_2 + param_4;
    uVar1 = 0x20 / (longlong)param_2;
    iVar4 = (int)uVar1;
    iVar8 = (int)(0x20 % (longlong)param_2);
    iVar2 = DAT_0058f140 * iVar4;
    local_14 = 0;
    local_24 = 0;
    if (0 < iVar7) {
      do {
        local_28 = param_4;
        iVar12 = 0;
        local_20 = 0;
        iVar6 = iVar4 >> 1;
        puVar9 = local_30;
        puVar10 = param_1;
        if (0 < iVar3 * param_2) {
          do {
            *puVar10 = *puVar9;
            puVar11 = puVar10 + 1;
            if ((0 < local_28) && (iVar12 % param_2 == 1)) {
              local_28 = local_28 + -1;
              iVar5 = iVar6;
              if (iVar6 < 0) {
                iVar5 = iVar6 + (uint)((uVar1 & 1) != 0);
              }
              *puVar11 = puVar9[iVar5];
              puVar11 = puVar10 + 2;
            }
            puVar9 = puVar9 + iVar4;
            local_20 = local_20 + iVar8;
            if (param_2 <= local_20) {
              local_20 = local_20 - param_2;
              puVar9 = puVar9 + 1;
            }
            iVar12 = iVar12 + 1;
            puVar10 = puVar11;
          } while (iVar12 < iVar3 * param_2);
        }
        if ((local_2c < 1) || (local_14 % param_2 != 1)) {
          if ((0 < local_2c) && ((0 < local_14 && ((local_14 + -1) % param_2 == 1)))) {
            if (iVar6 < 0) {
              iVar6 = iVar6 + (uint)((uVar1 & 1) != 0);
            }
            local_30 = local_30 + -(iVar6 * DAT_0058f140);
          }
          local_30 = local_30 + iVar2;
          local_24 = local_24 + iVar8;
          if (param_2 <= local_24) {
            local_24 = local_24 - param_2;
            local_30 = local_30 + DAT_0058f140;
          }
        }
        else {
          local_2c = local_2c + -1;
          if (iVar6 < 0) {
            iVar6 = iVar6 + (uint)((uVar1 & 1) != 0);
          }
          local_30 = local_30 + iVar6 * DAT_0058f140;
        }
        param_1 = param_1 + param_3;
        local_14 = local_14 + 1;
      } while (local_14 < iVar7);
    }
  }
  return;
}

