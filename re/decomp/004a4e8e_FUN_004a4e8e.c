// FUN_004a4e8e @ 004a4e8e size=368 sig=undefined FUN_004a4e8e() cc=unknown
// callers: FUN_004a4ffe
// callees: FUN_0048fd38,FUN_0048f992

undefined4
FUN_004a4e8e(int param_1,ushort param_2,ushort param_3,undefined4 param_4,undefined4 param_5)

{
  byte bVar1;
  short sVar2;
  undefined2 extraout_var;
  undefined4 uVar3;
  int iVar4;
  undefined2 uVar5;
  ushort uVar6;
  ushort uVar7;
  ushort uVar8;
  ushort uVar9;
  ushort uVar10;
  bool bVar11;
  ushort local_c;
  ushort local_8;
  short local_6;
  
  uVar9 = 0;
  local_6 = 0;
  local_c = 0;
  sVar2 = (short)param_5;
  if (((sVar2 == 1) || (sVar2 == 2)) || (sVar2 == 3)) {
    local_6 = param_2 * param_3;
    FUN_0048f992(param_4,param_1,(int)local_6);
    uVar5 = extraout_var;
  }
  else {
    uVar5 = (undefined2)((uint)param_5 >> 0x10);
    if (param_2 != 0) {
      do {
        bVar1 = FUN_0048fd38(param_4);
        uVar6 = (ushort)bVar1;
        if ((uint)param_2 < (uint)local_c + (uVar6 & 0x7f) + 1) {
          return 0xffffffff;
        }
        if ((bVar1 & 0x80) == 0) {
          iVar4 = (ushort)(uVar6 + local_c) + 1;
          local_c = (ushort)iVar4;
          local_8 = uVar6;
          do {
            uVar10 = 0;
            if (param_3 != 0) {
              do {
                iVar4 = FUN_0048fd38(param_4);
                *(char *)(param_1 + (uint)uVar9) = (char)iVar4;
                uVar9 = uVar9 + 1;
                uVar10 = uVar10 + 1;
              } while (uVar10 < param_3);
            }
            uVar5 = (undefined2)((uint)iVar4 >> 0x10);
            iVar4 = CONCAT22(uVar5,local_8);
            bVar11 = local_8 != 0;
            uVar10 = uVar9;
            local_8 = local_8 - 1;
          } while (bVar11);
        }
        else {
          uVar6 = uVar6 & 0xff7f;
          local_c = uVar6 + local_c + 1;
          uVar3 = 0;
          uVar7 = 0;
          uVar10 = uVar9;
          local_8 = uVar6;
          if (param_3 != 0) {
            do {
              uVar3 = FUN_0048fd38(param_4);
              *(char *)(param_1 + (uint)uVar10) = (char)uVar3;
              uVar10 = uVar10 + 1;
              uVar7 = uVar7 + 1;
            } while (uVar7 < param_3);
          }
          while( true ) {
            uVar5 = (undefined2)((uint)uVar3 >> 0x10);
            uVar7 = local_8 - 1;
            if (local_8 == 0) break;
            uVar8 = 0;
            local_8 = uVar7;
            if (param_3 != 0) {
              do {
                uVar3 = 0;
                *(undefined1 *)(param_1 + (uint)uVar10) =
                     *(undefined1 *)(param_1 + (uint)uVar9 + (uint)uVar8);
                uVar10 = uVar10 + 1;
                uVar8 = uVar8 + 1;
              } while (uVar8 < param_3);
            }
          }
        }
        uVar9 = uVar10;
        local_6 = local_6 + (uVar6 + 1) * param_3;
      } while (local_c < param_2);
    }
  }
  return CONCAT22(uVar5,local_6);
}

