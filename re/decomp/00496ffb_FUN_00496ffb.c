// FUN_00496ffb @ 00496ffb size=326 sig=undefined FUN_00496ffb() cc=unknown
// callers: FUN_00494449,FUN_0049483f
// callees: FUN_0049698a,FUN_00490ab3,FUN_00498aab,FUN_0049ae0c

void FUN_00496ffb(int param_1,int param_2,int param_3,int param_4,int param_5,int param_6,
                 int param_7,undefined4 param_8,undefined4 param_9)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  uint local_10;
  int local_c;
  short *local_8;
  
  local_14 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  while( true ) {
    iVar6 = local_14;
    local_14 = local_14 + 1;
    piVar2 = (int *)FUN_0049698a(param_1,param_2,iVar6,&local_24);
    if (piVar2 == (int *)0x0) break;
    iVar6 = param_4;
    if (local_24 != param_2) {
      iVar6 = 0;
    }
    if (local_24._3_1_ == '\0') {
      local_18 = param_3;
      local_20 = 0;
      local_1c = 0;
    }
    else if (local_18 < *piVar2) {
      local_1c = (int)*(short *)((int)piVar2 + piVar2[local_18 + 0x10] + 0x18);
      local_20 = (int)*(short *)((int)piVar2 + piVar2[local_18 + 0x10] + 0x1a);
    }
    if (param_3 < *piVar2) {
      iVar1 = piVar2[param_3 + 0x10];
      for (iVar5 = 0; iVar5 < (int)(uint)*(ushort *)((int)piVar2 + iVar1 + 0x1c); iVar5 = iVar5 + 1)
      {
        if (iVar6 < (int)(uint)*(ushort *)((int)piVar2 + iVar1 + 0x1e)) {
          iVar4 = ((uint)*(ushort *)((int)piVar2 + iVar1 + 0x1e) * iVar5 + iVar6) * 8 + iVar1;
          local_8 = (short *)((int)piVar2 + iVar4 + 0x20);
          local_10 = *(uint *)((int)piVar2 + iVar4 + 0x24);
          if (((local_10 & 0x40000000) == 0) &&
             (local_c = FUN_00490ab3(*(undefined4 *)(param_1 + 0xc),0x454c4954,local_10 & 0xffffff,0
                                     ,0), local_c != 0)) {
            iVar3 = FUN_00498aab(local_c,1);
            iVar4 = param_7;
            if (param_7 == -1) {
              iVar4 = (int)*(short *)(iVar3 + 0xe);
            }
            FUN_0049ae0c(iVar3,*local_8 + param_5 + local_1c,local_8[1] + param_6 + local_20,iVar4,
                         param_8,param_9);
            FUN_00498aab(local_c,0);
          }
        }
      }
    }
  }
  return;
}

