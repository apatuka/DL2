// FUN_0049d7f4 @ 0049d7f4 size=653 sig=undefined FUN_0049d7f4() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049fa76,FUN_00491a2b,FUN_00495cc4,FUN_00491ace,FUN_00491efa,FUN_0049a8ed,FUN_0049aa64,FUN_004935fc,FUN_00498aab,FUN_0049a93f,FUN_0049eb9f,FUN_0049eafa,FUN_0049a760,FUN_00490ab3,FUN_00490796,FUN_004954f9,FUN_0049aa95,FUN_00496c61,FUN_00493108,FUN_00491e02

undefined4 FUN_0049d7f4(int param_1,int param_2,undefined4 param_3,int *param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  uint uVar5;
  int *piVar6;
  int *piVar7;
  int local_34;
  int local_30;
  int local_2c;
  int local_28;
  int local_24 [4];
  undefined1 local_14 [3];
  byte local_11;
  undefined4 local_10;
  undefined4 local_c;
  int *local_8;
  
  if (*(int *)(param_2 + 0x94) != 0) {
    iVar1 = FUN_004954f9(*(undefined4 *)(param_2 + 0x94),param_3);
    if (iVar1 != 0) {
      FUN_00491a2b(0);
      iVar2 = FUN_0049eafa(param_2);
      if ((iVar2 != 2) && (iVar2 = 1, (*(byte *)(iVar1 + 0xc) & 1) == 0)) {
        iVar2 = 0;
      }
      iVar3 = FUN_0049eb9f(param_2,0);
      if (iVar3 != 0) {
        if (iVar2 == 1) {
          if ((*(byte *)(param_2 + 0xdf) & 0x40) == 0) {
            uVar4 = *(undefined4 *)(param_2 + 0xdc);
          }
          else {
            uVar4 = *(undefined4 *)(param_1 + 0xa0);
          }
          FUN_004935fc(*param_4,param_4[1],param_4[2],param_4[3],uVar4);
        }
        if ((*(byte *)(param_2 + 0xab + iVar2 * 4) & 0x40) == 0) {
          uVar4 = *(undefined4 *)(param_2 + 0xa8 + iVar2 * 4);
        }
        else {
          uVar4 = *(undefined4 *)(param_1 + 0xf0 + iVar2 * 4);
        }
        FUN_00491efa(uVar4);
        if ((*(byte *)(param_2 + 0x9f + iVar2 * 4) & 0x40) == 0) {
          uVar4 = *(undefined4 *)(param_2 + 0x9c + iVar2 * 4);
        }
        else {
          uVar4 = *(undefined4 *)(param_1 + 0xc0 + iVar2 * 4);
        }
        FUN_00491e02(uVar4);
        if (*(int *)(iVar1 + 0x18) != 0) {
          iVar2 = FUN_00490ab3(0,0x47414d49,*(undefined4 *)(iVar1 + 0x18),0,0x80000000);
          if (iVar2 != 0) {
            local_c = FUN_00498aab(iVar2,1);
            local_8 = (int *)FUN_00496c61(local_c,*(undefined4 *)(iVar1 + 0x1c),
                                          *(undefined4 *)(iVar1 + 0x20),0,
                                          *(undefined4 *)(iVar1 + 0x24),0,0,local_14);
            if ((local_8 != (int *)0x0) && ((local_11 & 0x40) == 0)) {
              piVar6 = param_4;
              piVar7 = local_24;
              for (iVar3 = 4; iVar3 != 0; iVar3 = iVar3 + -1) {
                *piVar7 = *piVar6;
                piVar6 = piVar6 + 1;
                piVar7 = piVar7 + 1;
              }
              local_24[2] = local_24[0] + *(int *)(param_2 + 0x74);
              iVar3 = FUN_00495cc4(local_24,param_4);
              if (iVar3 != 0) {
                local_34 = 0;
                local_30 = 0;
                local_2c = (int)*(short *)(*local_8 + 4);
                local_28 = (int)*(short *)(*local_8 + 2);
                FUN_0049fa76(local_24,&local_34,0x408000);
                local_34 = local_34 - *(short *)(*local_8 + 10);
                local_30 = local_30 - *(short *)(*local_8 + 0xc);
                FUN_0049a8ed();
                uVar5 = 8;
                if ((*(byte *)(*local_8 + 8) & 3) != 0) {
                  uVar5 = 0x10;
                }
                local_10 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | uVar5);
                iVar3 = FUN_0049aa64(local_24);
                if (iVar3 != 0) {
                  FUN_0049aa95(*local_8,local_34,local_30,(int)*(short *)(*local_8 + 0xe),0);
                }
                FUN_0049a760(local_10);
                FUN_0049a93f();
              }
            }
            FUN_00498aab(iVar2,0);
            FUN_00490796(iVar2,0);
          }
        }
        piVar6 = local_24;
        for (iVar2 = 4; iVar2 != 0; iVar2 = iVar2 + -1) {
          *piVar6 = *param_4;
          param_4 = param_4 + 1;
          piVar6 = piVar6 + 1;
        }
        if (*(int *)(param_2 + 0x74) == 0) {
          iVar2 = 4;
        }
        else {
          iVar2 = *(int *)(param_2 + 0x74);
        }
        local_24[0] = local_24[0] + iVar2;
        local_24[2] = local_24[2] + -4;
        if (*(int *)(iVar1 + 0x10) != 0) {
          FUN_00493108(*(undefined4 *)(iVar1 + 0x10),local_24,*(uint *)(param_2 + 0x44) | 8,0);
        }
      }
      FUN_00491ace();
    }
  }
  return 1;
}

