// FUN_00496cc3 @ 00496cc3 size=445 sig=undefined FUN_00496cc3() cc=unknown
// callers: FUN_00494449,FUN_004941f5,FUN_0041beac,FUN_00494aa7,FUN_0049483f,FUN_0049497a
// callees: FUN_0049698a,FUN_00490ab3,FUN_00498aab,FUN_00495c6c

undefined4 FUN_00496cc3(int param_1,int param_2,int param_3,int param_4,int *param_5)

{
  int iVar1;
  uint uVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int *piVar7;
  int *piVar8;
  int local_34 [4];
  undefined4 local_24;
  int local_20;
  int local_1c;
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  undefined4 local_8;
  
  local_10 = 0;
  local_20 = 0;
  local_1c = 0;
  local_18 = 0;
  param_5[2] = 0;
  *param_5 = 0;
  while( true ) {
    iVar1 = local_10;
    local_10 = local_10 + 1;
    piVar3 = (int *)FUN_0049698a(param_1,param_2,iVar1,&local_24);
    if (piVar3 == (int *)0x0) break;
    local_14 = param_4;
    if (local_24 != param_2) {
      local_14 = 0;
    }
    if (local_24._3_1_ == '\0') {
      local_18 = param_3;
      local_20 = 0;
      local_1c = 0;
    }
    else if (local_18 < *piVar3) {
      local_1c = (int)*(short *)((int)piVar3 + piVar3[local_18 + 0x10] + 0x18);
      local_20 = (int)*(short *)((int)piVar3 + piVar3[local_18 + 0x10] + 0x1a);
    }
    if (param_3 < *piVar3) {
      iVar1 = piVar3[param_3 + 0x10];
      for (local_c = 0; local_c < (int)(uint)*(ushort *)((int)piVar3 + iVar1 + 0x1c);
          local_c = local_c + 1) {
        if (local_14 < (int)(uint)*(ushort *)((int)piVar3 + iVar1 + 0x1e)) {
          iVar5 = ((uint)*(ushort *)((int)piVar3 + iVar1 + 0x1e) * local_c + local_14) * 8 + iVar1;
          uVar2 = *(uint *)((int)piVar3 + iVar5 + 0x24);
          if (((uVar2 & 0x40000000) == 0) && ((*(byte *)((int)piVar3 + iVar5 + 0x27) & 0x10) == 0))
          {
            local_8 = FUN_00490ab3(*(undefined4 *)(param_1 + 0xc),0x454c4954,uVar2 & 0xffffff,0,0);
            iVar4 = FUN_00498aab(local_8,1);
            local_34[0] = (*(short *)((int)piVar3 + iVar5 + 0x20) + local_1c) -
                          (int)*(short *)(iVar4 + 10);
            local_34[1] = (*(short *)((int)piVar3 + iVar5 + 0x22) + local_20) -
                          (int)*(short *)(iVar4 + 0xc);
            local_34[2] = *(short *)(iVar4 + 4) + local_34[0];
            local_34[3] = *(short *)(iVar4 + 2) + local_34[1];
            iVar5 = FUN_00495c6c(param_5);
            if (iVar5 == 0) {
              if (local_34[0] < *param_5) {
                *param_5 = local_34[0];
              }
              if (local_34[1] < param_5[1]) {
                param_5[1] = local_34[1];
              }
              if (param_5[2] < local_34[2]) {
                param_5[2] = local_34[2];
              }
              if (param_5[3] < local_34[3]) {
                param_5[3] = local_34[3];
              }
            }
            else {
              piVar7 = local_34;
              piVar8 = param_5;
              for (iVar5 = 4; iVar5 != 0; iVar5 = iVar5 + -1) {
                *piVar8 = *piVar7;
                piVar7 = piVar7 + 1;
                piVar8 = piVar8 + 1;
              }
            }
            FUN_00498aab(local_8,0);
          }
        }
      }
    }
  }
  if ((*param_5 < param_5[2]) && (param_5[1] < param_5[3])) {
    uVar6 = 1;
  }
  else {
    uVar6 = 0;
  }
  return uVar6;
}

