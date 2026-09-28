// FUN_00498f8c @ 00498f8c size=667 sig=undefined FUN_00498f8c() cc=unknown
// callers: FUN_004994ed
// callees: FUN_00498eda,FUN_0048fade,FUN_00498e00,FUN_0048fbf8,FUN_004989cf,FUN_0048fd38,FUN_0048fbbf,FUN_0048f8e8,FUN_00498ba9

undefined4 FUN_00498f8c(undefined4 param_1,undefined4 param_2,code *param_3,undefined4 *param_4)

{
  char cVar1;
  undefined1 uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  ushort uVar7;
  short sVar8;
  uint uVar9;
  char acStackY_1005a [63902];
  char local_98;
  char local_97;
  byte local_95;
  short local_94;
  short local_92;
  short local_90;
  short local_8e;
  undefined1 local_5b [4];
  byte local_57;
  ushort local_56;
  int local_18;
  int local_14;
  short local_e;
  int local_c;
  ushort local_8;
  short local_6;
  
  iVar3 = FUN_0048f8e8(param_1,param_2);
  if (iVar3 == 0) {
    uVar4 = 0;
  }
  else {
    iVar5 = FUN_00498e00(&stack0xffffff68,iVar3);
    if (iVar5 == 0) {
      iVar5 = FUN_0048fbf8(iVar3);
      if (iVar5 == 0) {
        if (local_98 == '\n') {
          local_6 = (local_90 - local_94) + 1;
          local_8 = (local_8e - local_92) + 1;
          uVar9 = (uint)local_57;
          uVar6 = (uint)local_56;
          local_14 = (uint)local_95 * (uint)local_57;
          sVar8 = (short)(uVar9 * uVar6);
          local_c = FUN_00498ba9((int)sVar8);
          if (local_c == 0) {
            FUN_0048fbbf(iVar3,0);
            uVar4 = 0;
          }
          else {
            if ((param_3 != (code *)0x0) &&
               (local_18 = (*param_3)(0,0,local_8,local_6,5,local_14), local_18 == 0)) {
              FUN_0048fbbf(iVar3,0);
              FUN_004989cf(local_c);
              return 0;
            }
            DAT_0051e20c = 0;
            DAT_0051e20d = 0;
            uVar7 = 0;
            if (local_8 != 0) {
              do {
                local_e = FUN_00498eda(local_c,uVar9 * uVar6,iVar3);
                if (sVar8 != local_e) {
                  FUN_0048fbbf(iVar3,0);
                  if (param_3 != (code *)0x0) {
                    (*param_3)(2,0,0,0,0,0);
                  }
                  return 0;
                }
                if (param_3 != (code *)0x0) {
                  (*param_3)(3,local_c,uVar7,local_56,local_57,local_14);
                }
                uVar7 = uVar7 + 1;
              } while (uVar7 < local_8);
            }
            if ((local_97 == '\x05') && (local_14 == 8)) {
              FUN_0048fade(iVar3,0xfffffcff,2);
              cVar1 = FUN_0048fd38(iVar3);
              if (cVar1 == '\f') {
                uVar7 = 0;
                do {
                  uVar2 = FUN_0048fd38(iVar3);
                  (&stack0xfffffc68)[uVar7] = uVar2;
                  uVar7 = uVar7 + 1;
                } while (uVar7 < 0x300);
                if (((local_18 != 0) && (param_4 != (undefined4 *)0x0)) && (param_3 != (code *)0x0))
                {
                  uVar4 = (*param_3)(4,&stack0xfffffc68,0,0,0,0x100);
                  *param_4 = uVar4;
                }
              }
            }
            else if ((local_14 == 4) && ((param_4 != (undefined4 *)0x0 && (param_3 != (code *)0x0)))
                    ) {
              uVar7 = 0;
              do {
                iVar5 = 0;
                do {
                  (&stack0xfffff968)[iVar5 + (uint)uVar7] = local_5b[iVar5 - (uint)uVar7];
                  iVar5 = iVar5 + 1;
                } while (iVar5 < 3);
                uVar7 = uVar7 + 3;
              } while (uVar7 < 0x30);
              uVar4 = (*param_3)(4,&stack0xfffff968,0,0,0,0x10);
              *param_4 = uVar4;
            }
            FUN_004989cf(local_c);
            FUN_0048fbbf(iVar3,0);
            if (param_3 == (code *)0x0) {
              uVar4 = 0;
            }
            else {
              uVar4 = (*param_3)(1,0,local_8,local_6,0,local_14);
            }
          }
        }
        else {
          FUN_0048fbbf(iVar3,0);
          uVar4 = 0;
        }
      }
      else {
        FUN_0048fbbf(iVar3,0);
        uVar4 = 0;
      }
    }
    else {
      FUN_0048fbbf(iVar3,0);
      uVar4 = 0;
    }
  }
  return uVar4;
}

