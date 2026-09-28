// FUN_0040dd80 @ 0040dd80 size=334 sig=undefined FUN_0040dd80() cc=unknown
// callers: FUN_0040eb34,FUN_0040df44,FUN_0040f974
// callees: FUN_0044d1a4,FUN_00402548

int FUN_0040dd80(int param_1,int param_2,int param_3)

{
  char *pcVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  ushort uVar5;
  int iVar6;
  ushort *local_10;
  undefined1 local_c [4];
  int local_8;
  
  local_8 = 0;
  if ('\x02' < *(char *)(param_1 + 0x66 + param_3)) {
    FUN_00402548(param_1,(int)*(short *)(&DAT_004b6f5c + param_2 * 2),
                 (int)*(short *)(&DAT_004b6f68 + param_2 * 2),local_c,&local_8);
    iVar4 = 0;
    pcVar1 = (char *)(param_1 + 0x144);
    do {
      if (*pcVar1 != '\0') {
        local_8 = local_8 + 1;
      }
      if (*(int *)(pcVar1 + 0x10) != 0) {
        local_8 = local_8 + 1;
      }
      iVar4 = iVar4 + 1;
      pcVar1 = pcVar1 + 0x34;
    } while (iVar4 < 0x24);
    iVar4 = 0;
    piVar2 = (int *)(param_1 + 0x3a);
    do {
      iVar6 = *piVar2;
      piVar2 = piVar2 + 1;
      local_8 = local_8 + iVar6;
      iVar4 = iVar4 + 1;
    } while (iVar4 < 0xb);
  }
  iVar4 = FUN_0044d1a4(param_1,0x14,0);
  if (iVar4 != -1) {
    local_8 = local_8 + 100;
  }
  iVar4 = FUN_0044d1a4(param_1,9,0);
  if (iVar4 != -1) {
    if (DAT_004d5b00 == '\0') {
      local_8 = local_8 + 100;
    }
    else {
      local_8 = local_8 + 5;
    }
  }
  if (0 < *(int *)(param_1 + 0x978 + param_3 * 4)) {
    if (DAT_004d5b00 == '\x02') {
      local_8 = local_8 + 200;
    }
    else {
      local_8 = local_8 + 5;
    }
  }
  if (*(char *)(param_1 + 0x21) == '\0') {
    iVar4 = 0;
    local_10 = (ushort *)(param_1 + 0x890);
    do {
      uVar5 = *local_10;
      for (iVar6 = 0; (uVar5 != 0 && (iVar6 < 0x10)); iVar6 = iVar6 + 1) {
        if ((uVar5 & 1) != 0) {
          iVar3 = (iVar4 * 0x10 + iVar6) * 0xadc;
          if (('\x02' < (char)(&DAT_005a4436)[param_3 + iVar3]) && ((&DAT_005a43f1)[iVar3] != '\0'))
          {
            iVar3 = FUN_0044d1a4(&DAT_005a43d0 + iVar3,7,0);
            if (iVar3 != 0) {
              local_8 = local_8 + 100;
            }
          }
        }
        uVar5 = (short)uVar5 >> 1;
      }
      iVar4 = iVar4 + 1;
      local_10 = local_10 + 1;
    } while (iVar4 < 7);
  }
  return local_8;
}

