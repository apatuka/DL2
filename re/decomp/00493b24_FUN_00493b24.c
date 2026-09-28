// FUN_00493b24 @ 00493b24 size=705 sig=undefined FUN_00493b24() cc=unknown
// callers: FUN_00464444
// callees: FUN_004935fc

void FUN_00493b24(uint param_1,uint param_2,uint param_3,uint param_4,undefined4 param_5)

{
  short sVar1;
  short sVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  short sVar6;
  uint uVar7;
  ushort uVar8;
  short sVar9;
  uint uVar10;
  undefined2 local_e;
  undefined2 local_c;
  undefined2 local_a;
  
  local_e = (short)param_1;
  uVar5 = (short)param_3 - local_e;
  local_c = (short)param_2;
  uVar8 = local_c - (short)param_4;
  if (uVar5 == 0) {
    if ((int)param_4 < (int)param_2) {
      FUN_004935fc(param_1,param_4,param_1 + 1,param_2 + 1,param_5);
    }
    else {
      FUN_004935fc(param_1,param_2,param_1 + 1,param_4 + 1,param_5);
    }
  }
  else if (uVar8 == 0) {
    if ((int)param_1 < (int)param_3) {
      FUN_004935fc(param_1,param_4,param_3 + 1,param_4 + 1,param_5);
    }
    else {
      FUN_004935fc(param_3,param_2,param_1 + 1,param_2 + 1,param_5);
    }
  }
  else {
    sVar1 = (uVar5 ^ (short)uVar5 >> 0xf) - ((short)uVar5 >> 0xf);
    sVar2 = (uVar8 ^ (short)uVar8 >> 0xf) - ((short)uVar8 >> 0xf);
    if (sVar1 < sVar2) {
      if ((int)param_2 < (int)param_4) {
        local_c = (short)param_4;
        uVar10 = param_1;
        if ((int)param_1 < (int)param_3) {
          local_a = 1;
        }
        else {
          local_a = -1;
        }
      }
      else {
        param_2 = param_4 & 0xffff;
        uVar10 = param_3 & 0xffff;
        if ((int)param_3 < (int)param_1) {
          local_a = 1;
        }
        else {
          local_a = -1;
        }
      }
      iVar4 = (int)(short)(sVar1 * 2) - (int)sVar2;
      sVar6 = (short)param_2;
      sVar9 = (short)uVar10;
      FUN_004935fc((int)sVar9,(int)sVar6,sVar9 + 1,sVar6 + 1,param_5);
      iVar3 = sVar6 + 1;
      while (sVar6 < local_c) {
        param_2 = param_2 + 1;
        sVar6 = (short)param_2;
        sVar9 = (short)uVar10;
        if (iVar4 < 0) {
          iVar4 = iVar4 + (short)(sVar1 * 2);
          if (-1 < iVar4) {
            FUN_004935fc((int)sVar9,iVar3,sVar9 + 1,sVar6 + 1,param_5);
            iVar3 = sVar6 + 1;
          }
        }
        else {
          uVar5 = sVar9 + local_a;
          uVar10 = (uint)uVar5;
          iVar4 = iVar4 + (short)((sVar1 - sVar2) * 2);
          if (-1 < iVar4) {
            FUN_004935fc((int)(short)uVar5,(int)sVar6,(short)uVar5 + 1,sVar6 + 1,param_5);
            iVar3 = sVar6 + 1;
          }
        }
        sVar9 = (short)uVar10;
      }
      if (iVar3 < sVar6) {
        FUN_004935fc((int)sVar9,iVar3,sVar9 + 1,(int)sVar6,param_5);
      }
    }
    else {
      if ((int)param_1 < (int)param_3) {
        local_e = (short)param_3;
        uVar10 = param_2;
        if ((int)param_2 < (int)param_4) {
          local_a = 1;
        }
        else {
          local_a = -1;
        }
      }
      else {
        uVar10 = param_4 & 0xffff;
        param_1 = param_3;
        if ((int)param_4 < (int)param_2) {
          local_a = 1;
        }
        else {
          local_a = -1;
        }
      }
      iVar3 = (int)(short)(sVar2 * 2) - (int)sVar1;
      FUN_004935fc(param_1,(int)(short)uVar10,param_1 + 1,(short)uVar10 + 1,param_5);
      iVar4 = param_1 + 1;
      while (uVar7 = param_1, sVar6 = (short)uVar10, (int)uVar7 < (int)local_e) {
        param_1 = uVar7 + 1;
        if (iVar3 < 0) {
          iVar3 = iVar3 + (short)(sVar2 * 2);
          if (-1 < iVar3) {
            FUN_004935fc(iVar4,(int)sVar6,uVar7 + 2,sVar6 + 1,param_5);
            iVar4 = uVar7 + 2;
          }
        }
        else {
          uVar5 = sVar6 + local_a;
          uVar10 = (uint)uVar5;
          iVar3 = iVar3 + (short)((sVar2 - sVar1) * 2);
          if (-1 < iVar3) {
            FUN_004935fc(param_1,(int)(short)uVar5,uVar7 + 2,(short)uVar5 + 1,param_5);
            iVar4 = uVar7 + 2;
          }
        }
      }
      if (iVar4 < (int)uVar7) {
        FUN_004935fc(iVar4,(int)sVar6,uVar7 + 1,sVar6 + 1,param_5);
      }
    }
  }
  return;
}

