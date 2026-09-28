// FUN_0048192c @ 0048192c size=302 sig=undefined FUN_0048192c() cc=unknown
// callers: FUN_00481da0
// callees: FUN_00456d00,FUN_00481b80,FUN_004818ac

void FUN_0048192c(int param_1,int param_2,int param_3,uint param_4,int param_5,int param_6)

{
  char cVar1;
  char *pcVar2;
  undefined *puVar3;
  int iVar4;
  int iVar5;
  char *local_14;
  int local_c;
  int local_8;
  
  cVar1 = (&DAT_0059f162)[*(char *)(param_1 + 0x20) * 0x2d8];
  pcVar2 = *(char **)(param_1 + 0x80 + *(char *)(param_1 + 0x74) * 4);
  iVar5 = (int)*pcVar2;
  iVar4 = (int)pcVar2[1];
  if (param_6 == 0) {
    local_8 = (int)param_4 >> 1;
    if (local_8 < 0) {
      local_8 = local_8 + (uint)((param_4 & 1) != 0);
    }
    local_8 = iVar5 * param_4 + param_2 + local_8;
    local_c = param_4 + iVar4 * param_4 + param_3 + -2;
  }
  else {
    FUN_00481b80(iVar5,iVar4,&local_8,&local_c,param_4,param_6);
  }
  if (param_5 == 2) {
    local_14 = &DAT_0059f162;
    iVar4 = 0;
    do {
      iVar5 = FUN_00456d00((int)*(short *)(param_1 + 0x1a),iVar4);
      if (iVar5 != 0) {
        puVar3 = (&PTR_DAT_004d0918)[*local_14 * 3];
        FUN_004818ac(puVar3 + 0x140,local_8,local_c);
        local_8 = local_8 + *(short *)(puVar3 + 0x144);
      }
      iVar4 = iVar4 + 1;
      local_14 = local_14 + 0x2d8;
    } while (iVar4 < 7);
  }
  else if (param_5 == 3) {
    FUN_004818ac((&PTR_DAT_004d0918)[cVar1 * 3] + 0x140,local_8,local_c);
  }
  else {
    FUN_004818ac(&DAT_004f625c + cVar1 * 0x10,local_8,local_c);
  }
  return;
}

