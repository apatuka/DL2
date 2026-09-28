// FUN_004af624 @ 004af624 size=720 sig=undefined FUN_004af624() cc=unknown
// callers: FUN_004ae670
// callees: FUN_004ae1ac,FUN_004ae0c0,FUN_004ae0e4,FUN_004afc94,memset

/* WARNING: Restarted to delay deadcode elimination for space: stack */

int FUN_004af624(float10 *param_1,int param_2,uint *param_3,int param_4,int param_5)

{
  byte bVar1;
  ushort uVar2;
  uint uVar3;
  int iVar4;
  char *pcVar5;
  byte bVar6;
  int iVar7;
  int iVar8;
  float10 fVar9;
  undefined1 *local_28;
  int local_18;
  undefined1 local_10 [8];
  ushort uStack_8;
  short local_6;
  
  local_6 = 10;
  if (param_5 == 2) {
    _local_10 = (float10)*(float *)param_1;
  }
  else if (param_5 == 6) {
    _local_10 = (float10)*(double *)param_1;
  }
  else if (param_5 == 8) {
    _local_10 = *param_1;
  }
  uVar2 = uStack_8;
  uVar3 = (uint)uStack_8;
  _local_10 = (float10)CONCAT28(uStack_8 & 0x7fff,local_10);
  *param_3 = (uint)((uVar2 & 0x8000) != 0);
  uVar2 = FUN_004ae0e4(local_10);
  uVar2 = uVar2 & 0x4700;
  if (uVar2 != 0x4000) {
    if (uVar2 == 0x500) {
      return 0x7fff;
    }
    if (uVar2 == 0x100) {
      return 0x7ffe;
    }
    uVar3 = ((uVar3 & 0x7fff) - 0x3fff) * 0x4d10 + ((uint)local_10[7] * 2 & 0xff) * 0x4d;
    local_18 = (int)uVar3 >> 0x10;
    if ((uVar3 & 0xffff) != 0) {
      local_18 = local_18 + 1;
    }
    iVar8 = param_2;
    if ((0 < param_2) || (iVar8 = local_18 - param_2, -1 < iVar8)) {
      if (0x13 < iVar8) {
        iVar8 = 0x13;
      }
      for (iVar7 = iVar8 - local_18; iVar7 != 0; iVar7 = iVar7 + iVar4) {
        iVar4 = iVar7;
        if (iVar7 < 0) {
          iVar4 = -iVar7;
        }
        if (0x1344 < iVar4) {
          iVar4 = 0x1344;
        }
        fVar9 = (float10)FUN_004afc94(iVar4);
        if (iVar7 < 0) {
          _local_10 = _local_10 / fVar9;
        }
        else {
          _local_10 = _local_10 * fVar9;
          iVar4 = -iVar4;
        }
      }
      fVar9 = (float10)FUN_004afc94(iVar8);
      if (_local_10 <= fVar9) {
        fVar9 = (float10)FUN_004afc94(iVar8 + -1);
        iVar7 = iVar8;
        if (_local_10 < fVar9) {
          local_18 = local_18 + -1;
          iVar7 = iVar8 + -1;
          if (0 < param_2) {
            _local_10 = _local_10 * (float10)(int)local_6;
            iVar7 = iVar8;
          }
        }
      }
      else {
        local_18 = local_18 + 1;
        iVar7 = iVar8 + 1;
        if ((iVar7 < 0x14) && (0 < param_2)) {
          _local_10 = _local_10 / (float10)(int)local_6;
          iVar7 = iVar8;
        }
      }
      if (-1 < iVar7) {
        FUN_004ae0c0(local_10,local_10);
        local_28 = (undefined1 *)(param_4 + iVar7);
        bVar6 = 0;
        *local_28 = 0;
        pcVar5 = local_28 + -1;
        if (iVar7 == 0) {
          if (local_10[0] != '\x01') goto LAB_004af6ab;
          bVar6 = 0;
        }
        else {
          do {
            bVar1 = FUN_004ae1ac(local_10);
            bVar6 = bVar6 | bVar1;
            *pcVar5 = bVar1 + 0x30;
            pcVar5 = pcVar5 + -1;
            iVar7 = iVar7 + -1;
          } while (iVar7 != 0);
        }
        if (bVar6 == 0) {
          local_18 = local_18 + 1;
          if (param_2 < 1) {
            *local_28 = 0x30;
          }
          local_28 = local_28 + 1;
          pcVar5[1] = '1';
        }
        if (param_2 < 1) {
          param_2 = local_18 - param_2;
        }
        if (0x28 < param_2) {
          param_2 = 0x28;
        }
        *local_28 = 0;
        param_2 = param_2 - ((int)local_28 - param_4);
        if (param_2 < 1) {
          return local_18;
        }
        memset(local_28,0x30,param_2);
        local_28[param_2] = 0;
        return local_18;
      }
    }
  }
LAB_004af6ab:
  if (param_2 < 1) {
    param_2 = 1 - param_2;
  }
  if (0x28 < param_2) {
    param_2 = 0x28;
  }
  memset(param_4,0x30,param_2);
  *(undefined1 *)(param_4 + param_2) = 0;
  *param_3 = 0;
  return 1;
}

