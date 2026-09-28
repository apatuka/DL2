// FUN_004693b0 @ 004693b0 size=272 sig=undefined FUN_004693b0() cc=unknown
// callers: FUN_004694c0
// callees: FUN_004ae5d8

void FUN_004693b0(int param_1,int param_2,char param_3,int param_4,int param_5)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  char *pcVar6;
  int local_1c [3];
  int local_10;
  int local_c;
  int local_8;
  
  local_c = param_4 >> 1;
  local_10 = 0;
  local_1c[2] = param_2 - local_c;
  if (param_2 - local_c < 1) {
    piVar1 = &local_10;
  }
  else {
    piVar1 = local_1c + 2;
  }
  for (local_8 = *piVar1; (local_8 < param_2 + local_c && (local_8 < DAT_0058f13c));
      local_8 = local_8 + 1) {
    uVar4 = local_8 - param_2 >> 0x1f;
    iVar2 = (local_8 - param_2 ^ uVar4) - uVar4;
    local_1c[1] = 0;
    local_1c[0] = param_1 - local_c;
    if (param_1 - local_c < 1) {
      piVar1 = local_1c + 1;
    }
    else {
      piVar1 = local_1c;
    }
    iVar5 = *piVar1;
    pcVar6 = (char *)(local_8 * DAT_0058f140 + iVar5 + DAT_0058f134);
    for (; (iVar5 < param_1 + local_c && (iVar5 < DAT_0058f140)); iVar5 = iVar5 + 1) {
      iVar3 = FUN_004ae5d8();
      if ((iVar3 % 100 < param_5) && (*pcVar6 != '@')) {
        uVar4 = iVar5 - param_1 >> 0x1f;
        iVar3 = (iVar5 - param_1 ^ uVar4) - uVar4;
        if (iVar2 < iVar3) {
          iVar3 = iVar3 + (iVar2 >> 1);
        }
        else {
          iVar3 = (iVar3 >> 1) + iVar2;
        }
        if (iVar3 <= local_c) {
          *pcVar6 = param_3;
        }
      }
      pcVar6 = pcVar6 + 1;
    }
  }
  return;
}

