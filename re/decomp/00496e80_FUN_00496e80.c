// FUN_00496e80 @ 00496e80 size=379 sig=undefined FUN_00496e80() cc=unknown
// callers: FUN_00418704,FUN_0041beac,FUN_0041ba74,DrawCAGuyPool,FUN_0043b2c4,FUN_0043b50c,FUN_0043e198,FUN_0049497a
// callees: FUN_0049a760,FUN_0049698a,FUN_0049aa95,FUN_00490ab3,FUN_00498aab

void FUN_00496e80(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 local_2c;
  undefined4 local_28;
  int local_24;
  int local_20;
  int local_1c;
  int local_18;
  uint local_14;
  int local_10;
  int local_c;
  short *local_8;
  
  local_18 = 0;
  local_24 = 0;
  local_20 = 0;
  local_1c = 0;
  while( true ) {
    iVar5 = local_18;
    local_18 = local_18 + 1;
    piVar2 = (int *)FUN_0049698a(param_1,param_2,iVar5,&local_2c);
    if (piVar2 == (int *)0x0) break;
    iVar5 = param_4;
    if (local_2c != param_2) {
      iVar5 = 0;
    }
    if (local_2c._3_1_ == '\0') {
      local_1c = param_3;
      local_24 = 0;
      local_20 = 0;
    }
    else if (local_1c < *piVar2) {
      local_20 = (int)*(short *)((int)piVar2 + piVar2[local_1c + 0x10] + 0x18);
      local_24 = (int)*(short *)((int)piVar2 + piVar2[local_1c + 0x10] + 0x1a);
    }
    if (param_3 < *piVar2) {
      iVar1 = piVar2[param_3 + 0x10];
      for (iVar4 = 0; iVar4 < (int)(uint)*(ushort *)((int)piVar2 + iVar1 + 0x1c); iVar4 = iVar4 + 1)
      {
        if (iVar5 < (int)(uint)*(ushort *)((int)piVar2 + iVar1 + 0x1e)) {
          iVar3 = ((uint)*(ushort *)((int)piVar2 + iVar1 + 0x1e) * iVar4 + iVar5) * 8 + iVar1;
          local_8 = (short *)((int)piVar2 + iVar3 + 0x20);
          local_14 = *(uint *)((int)piVar2 + iVar3 + 0x24);
          if (((local_14 & 0x40000000) == 0) &&
             (local_c = FUN_00490ab3(*(undefined4 *)(param_1 + 0xc),0x454c4954,local_14 & 0xffffff,0
                                     ,0), local_c != 0)) {
            local_10 = FUN_00498aab(local_c,1);
            local_28 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 |
                                    (((int)*(short *)(local_10 + 8) & 3U) + 1) * 8);
            iVar3 = param_7;
            if (param_7 == -1) {
              iVar3 = (int)*(short *)(local_10 + 0xe);
            }
            FUN_0049aa95(local_10,*local_8 + param_5 + local_20,local_8[1] + param_6 + local_24,
                         iVar3,1);
            FUN_00498aab(local_c,0);
            FUN_0049a760(local_28);
          }
        }
      }
    }
  }
  return;
}

