// FUN_004887cb @ 004887cb size=255 sig=undefined FUN_004887cb() cc=unknown
// callers: FUN_00464498
// callees: 

void FUN_004887cb(int param_1,int param_2,int param_3,int param_4,undefined4 param_5,int param_6,
                 int param_7,int param_8,int param_9)

{
  byte bVar1;
  byte *pbVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int local_18;
  int local_10;
  int local_8;
  
  local_8 = 1;
  if ((param_3 <= param_1) && (local_8 = -1, param_3 == param_1)) {
    local_8 = 0;
  }
  local_10 = DAT_00583e14;
  local_18 = 1;
  if (param_4 <= param_2) {
    local_10 = -DAT_00583e14;
    local_18 = -1;
    if (local_10 == 0) {
      local_10 = 0;
      local_18 = 0;
    }
  }
  param_4 = param_4 - param_2;
  if (param_4 < 0) {
    param_4 = -param_4;
  }
  param_4 = param_4 + 1;
  param_3 = param_3 - param_1;
  if (param_3 < 0) {
    param_3 = -param_3;
  }
  param_3 = param_3 + 1;
  iVar3 = param_4;
  iVar6 = param_3;
  if (param_4 <= param_3) {
    iVar3 = param_3;
    iVar6 = param_4;
  }
  pbVar2 = (byte *)(*(int *)(DAT_00583e08 + param_2 * 4) + param_1 + DAT_00583e04);
  iVar5 = 0;
  iVar4 = 0;
  do {
    if ((((param_6 <= param_1) && (param_1 < param_8)) && (param_7 <= param_2)) &&
       (param_2 < param_9)) {
      bVar1 = (*pbVar2 & 7) - 4;
      if ((*pbVar2 & 7) < 4) {
        bVar1 = 0;
      }
      *pbVar2 = *pbVar2 & 0xf8;
      *pbVar2 = *pbVar2 | bVar1;
    }
    iVar5 = iVar5 + iVar6;
    if (param_4 <= iVar5) {
      pbVar2 = pbVar2 + local_8;
      iVar5 = iVar5 - param_4;
      param_1 = local_8 + param_1;
    }
    iVar4 = iVar4 + iVar6;
    if (param_3 <= iVar4) {
      pbVar2 = pbVar2 + local_10;
      iVar4 = iVar4 - param_3;
      param_2 = local_18 + param_2;
    }
    iVar3 = iVar3 + -1;
  } while (iVar3 != 0);
  return;
}

