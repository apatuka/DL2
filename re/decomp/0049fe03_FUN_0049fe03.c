// FUN_0049fe03 @ 0049fe03 size=325 sig=undefined FUN_0049fe03() cc=unknown
// callers: FUN_004a03cf,FUN_0043b8b0,FUN_0041f7f0,FUN_004a016e,FUN_004a060f,FUN_004a034a,FUN_0041b330
// callees: FUN_00498aab,FUN_0049fa76,FUN_0049a93f,FUN_0049f64c,FUN_0049eafa,FUN_0049a760,FUN_00495c51,FUN_0049a8ed,FUN_0049aa95,FUN_00496c61,FUN_0049aa64

void FUN_0049fe03(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  uint uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  undefined4 local_1c;
  undefined4 local_18;
  int local_14;
  int local_10;
  undefined1 local_c [3];
  byte local_9;
  undefined4 local_8;
  
  if (*(int *)(param_1 + 0x38) != 0) {
    if ((*(int *)(param_1 + 0x1c) == 1) || (*(int *)(param_1 + 0x1c) == 2)) {
      iVar1 = FUN_0049f64c(param_1);
      iVar1 = (uint)(iVar1 != 0) * 3;
    }
    else {
      iVar1 = 0;
    }
    local_8 = FUN_00498aab(*(undefined4 *)(param_1 + 0x38),1);
    puVar8 = local_c;
    uVar7 = 0;
    uVar6 = 0;
    if ((*(byte *)(param_1 + 0x29) & 1) == 0) {
      uVar4 = 0;
    }
    else {
      uVar4 = (uint)*(ushort *)(param_1 + 0x50);
    }
    uVar5 = 0;
    iVar2 = FUN_0049eafa(param_1);
    piVar3 = (int *)FUN_00496c61(local_8,*(undefined4 *)(param_1 + 0x54),iVar1 + iVar2,uVar5,uVar4,
                                 uVar6,uVar7,puVar8);
    if ((piVar3 != (int *)0x0) && ((local_9 & 0x40) == 0)) {
      uVar4 = 8;
      if ((*(byte *)(*piVar3 + 8) & 3) != 0) {
        uVar4 = 0x10;
      }
      uVar6 = FUN_0049a760(*(int *)(DAT_0051bddc + 0xc) << 0x10 | uVar4);
      FUN_0049a8ed();
      iVar1 = FUN_0049aa64(param_2);
      if (iVar1 != 0) {
        local_1c = 0;
        local_18 = 0;
        local_14 = (int)*(short *)(*piVar3 + 4);
        local_10 = (int)*(short *)(*piVar3 + 2);
        FUN_0049fa76(param_2,&local_1c,*(uint *)(param_1 + 0x28) & 0x438000);
        if ((*(uint *)(param_1 + 0x28) & 0x438000) != 0) {
          FUN_00495c51(&local_1c,(int)*(short *)(*piVar3 + 10),(int)*(short *)(*piVar3 + 0xc));
        }
        FUN_0049aa95(*piVar3,local_1c,local_18,(int)*(short *)(*piVar3 + 0xe),0);
      }
      FUN_0049a93f();
      FUN_0049a760(uVar6);
    }
    FUN_00498aab(*(undefined4 *)(param_1 + 0x38),0);
  }
  return;
}

