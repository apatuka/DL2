// ProduceUnits @ 0044e174 size=1138 sig=undefined ProduceUnits() cc=unknown
// callers: FUN_0044f3f0
// callees: FUN_004720f4,FUN_00484e24,FUN_004722e0,UnitList__Insert,FUN_00484ea4,FUN_00484ee0,FUN_00471cc0,FUN_00423690,FUN_0044ddf4,FUN_00484f74,memset,FUN_00484f2c,FUN_00484f48,DebugMessage,SyncCreateUnit,FUN_0044b5bc,FUN_0044df94
// strings: \"Invalid territory in ProduceUnits()\"|\"No queue in ProduceUnits()\"

/* auto-named from string evidence: ProduceUnits */

void ProduceUnits(undefined *param_1,undefined4 param_2,int param_3)

{
  char cVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined *puVar5;
  undefined4 uVar6;
  undefined2 *puVar7;
  undefined4 uVar8;
  short local_ec [2];
  undefined4 local_e8;
  undefined4 local_e4 [11];
  int local_b8;
  int local_b4 [10];
  undefined2 local_8c [2];
  int local_88;
  int local_84 [11];
  char local_58 [2];
  short local_56;
  undefined1 local_54 [44];
  undefined4 *local_28;
  int *local_24;
  int *local_20;
  int local_1c;
  char local_15;
  int local_14;
  int local_10;
  int local_c;
  char local_5;
  
  local_5 = '\0';
  if (param_1 == (undefined *)0x0) {
    DebugMessage(s_Invalid_territory_in_ProduceUnit_004c6127);
  }
  else {
    local_c = FUN_0044b5bc(param_1,param_2);
    if (local_c == 0) {
      DebugMessage(s_No_queue_in_ProduceUnits___004c614b);
    }
    else {
      iVar2 = FUN_00484ea4(local_c);
      if (iVar2 != 0) {
        puVar7 = local_8c;
        local_10 = 0;
        cVar1 = FUN_00484ee0(local_c);
        FUN_0044ddf4(&DAT_0059f160 + (char)param_1[0x20] * 0x2d8,(int)cVar1,puVar7);
        local_14 = local_88;
        FUN_00484f48(local_c,&local_b8);
        if (local_b8 < local_14) {
          local_10 = 1;
        }
        else {
          iVar2 = 1;
          local_24 = local_84;
          local_20 = local_b4;
          do {
            if ((iVar2 < 5) || (7 < iVar2)) {
              iVar3 = *local_20;
              if (iVar2 == 4) {
                iVar3 = FUN_00471cc0(&local_b8);
              }
              if (iVar3 < *local_24) {
                local_10 = 1;
                break;
              }
            }
            iVar2 = iVar2 + 1;
            local_24 = local_24 + 1;
            local_20 = local_20 + 1;
          } while (iVar2 < 0xb);
        }
        if (local_10 != 0) {
          local_15 = '\0';
          if (local_b8 < local_14) {
            if ((int)(&DAT_0059f16c)[(char)param_1[0x20] * 0xb6] < local_14 - local_b8) {
              local_15 = '\x01';
            }
            else {
              (&DAT_0059f16c)[(char)param_1[0x20] * 0xb6] =
                   (&DAT_0059f16c)[(char)param_1[0x20] * 0xb6] - (local_14 - local_b8);
              local_b8 = local_14;
            }
          }
          iVar2 = FUN_004720f4(param_1,local_8c,&local_b8);
          if (iVar2 != 0) {
            local_15 = '\x01';
          }
          if (local_15 != '\0') {
            uVar8 = 0;
            uVar6 = 0;
            cVar1 = FUN_00484ee0(local_c);
            FUN_00423690((int)(char)param_1[0x20],0x4a,param_1,(&PTR_s_No_Unit_004faf7c)[cVar1 * 9],
                         uVar6,uVar8);
            FUN_00484f74(local_c,&local_b8);
            return;
          }
          FUN_00484f2c(local_c,local_8c[0]);
        }
      }
      while ((0 < param_3 && (iVar2 = FUN_00484e24(local_c,local_58), iVar2 != 0))) {
        local_1c = 0;
        for (; (0 < param_3 && (0 < local_56)); local_56 = local_56 + -1) {
          param_3 = param_3 + -1;
        }
        if (local_56 < 1) {
          puVar5 = param_1;
          if ((&DAT_004faf8d)[local_58[0] * 0x24] == '\x02') {
            puVar5 = &DAT_005a43d0 + *(short *)(param_1 + 0x9b0) * 0xadc;
          }
          iVar2 = SyncCreateUnit(puVar5,(int)(char)param_1[0x20],(int)local_58[0]);
          if (iVar2 == 0) {
            local_1c = 1;
            param_3 = 0;
          }
          else {
            FUN_00423690((int)(char)param_1[0x20],0x44,(&PTR_s_No_Unit_004faf7c)[local_58[0] * 9],
                         param_1,0,0);
            local_5 = '\x01';
            if ((1 << ((byte)param_2 & 0x1f) & (int)(char)param_1[0x9ae]) != 0) {
              uVar4 = FUN_0044df94(param_1,&DAT_0059f160 + (char)param_1[0x20] * 0x2d8,
                                   (int)local_58[0]);
              if ((uVar4 & 0xf001) == 0) {
                FUN_00423690((int)(char)param_1[0x20],0x40,
                             (&PTR_s_No_Unit_004faf7c)[local_58[0] * 9],param_1,0,0);
              }
              else {
                FUN_00423690((int)(char)param_1[0x20],0x4a,param_1,
                             (&PTR_s_No_Unit_004faf7c)[local_58[0] * 9],0,0);
                local_1c = 1;
                param_3 = 0;
                FUN_0044ddf4(&DAT_0059f160 + (char)param_1[0x20] * 0x2d8,(int)local_58[0],local_ec);
                memset(local_54,0,0x2c);
                if ((uVar4 & 1) != 0) {
                  local_e8 = 0;
                }
                iVar2 = 1;
                local_28 = local_e4;
                do {
                  if ((1 << ((byte)iVar2 & 0x1f) & uVar4) != 0) {
                    *local_28 = 0;
                  }
                  iVar2 = iVar2 + 1;
                  local_28 = local_28 + 1;
                } while (iVar2 < 0xb);
                FUN_004722e0(&DAT_0059f160 + (char)param_1[0x20] * 0x2d8,param_1,local_ec,local_54);
                local_56 = local_ec[0];
              }
            }
          }
        }
        else {
          local_1c = 1;
        }
        if (local_1c != 0) {
          FUN_00484ea4(local_c);
          UnitList__Insert(local_c,local_58);
        }
      }
      if ((local_5 != '\0') && (iVar2 = FUN_00484ea4(local_c), iVar2 == 0)) {
        uVar6 = 0x45;
        switch(param_2) {
        case 1:
          uVar6 = 0x45;
          break;
        case 2:
          uVar6 = 0x46;
          break;
        case 3:
          uVar6 = 0x47;
          break;
        case 4:
          uVar6 = 0x48;
          break;
        case 5:
          uVar6 = 0x49;
        }
        FUN_00423690((int)(char)param_1[0x20],uVar6,param_1,0,0,0);
      }
    }
  }
  return;
}

