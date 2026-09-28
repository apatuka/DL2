// FUN_004983ae @ 004983ae size=327 sig=undefined FUN_004983ae() cc=unknown
// callers: FUN_004984f5
// callees: FUN_004982fc,FUN_00499840,FUN_0048f774,FUN_0048c434,FUN_00488c1c

int FUN_004983ae(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                int param_5,int param_6)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  byte local_15;
  int local_c;
  int local_8;
  
  uVar1 = DAT_0051bddc;
  local_8 = 0;
  iVar2 = param_6 + 0x1000;
  FUN_0048c434(param_2);
  if (DAT_0065ee14 == 0x204d4250) {
    iVar4 = 0;
    iVar3 = 0;
    if (0 < param_5) {
      do {
        FUN_00499840(iVar3,param_4);
        *(byte *)(param_6 + iVar4) = *DAT_0051c3c4;
        iVar4 = iVar4 + 1;
        iVar3 = iVar3 + 1;
      } while (iVar3 < param_5);
    }
    local_8 = FUN_004982fc(param_6,iVar2,param_5);
    iVar2 = FUN_00488c1c(param_1,iVar2,local_8);
    if (local_8 != iVar2) {
      return -1;
    }
  }
  else {
    local_15 = 1;
    local_c = 0;
    do {
      iVar3 = 7;
      iVar5 = 0;
      FUN_0048f774(param_6,0x400,0);
      iVar4 = 0;
      if (0 < param_5) {
        do {
          FUN_00499840(iVar4,param_4);
          *(byte *)(param_6 + iVar5) =
               *(byte *)(param_6 + iVar5) |
               (char)((int)(uint)(*DAT_0051c3c4 & local_15) >> ((byte)local_c & 0x1f)) <<
               ((byte)iVar3 & 0x1f);
          if (iVar3 == 0) {
            iVar5 = iVar5 + 1;
            iVar3 = 7;
          }
          else {
            iVar3 = iVar3 + -1;
          }
          iVar4 = iVar4 + 1;
        } while (iVar4 < param_5);
      }
      local_15 = local_15 << 1;
      iVar3 = FUN_004982fc(param_6,iVar2,param_5 >> 3);
      local_8 = local_8 + iVar3;
      iVar4 = FUN_00488c1c(param_1,iVar2,iVar3);
      if (iVar3 != iVar4) {
        return -1;
      }
      local_c = local_c + 1;
    } while (local_c < 8);
  }
  FUN_0048c434(uVar1);
  return local_8;
}

