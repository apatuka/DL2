// FUN_00438dbc @ 00438dbc size=315 sig=undefined FUN_00438dbc() cc=unknown
// callers: 
// callees: FUN_0049eb44,FUN_004a2c1b,FUN_0049ea99,FUN_004a43da,FUN_004a1150,FUN_0049eafa

void FUN_00438dbc(undefined4 param_1,int param_2,undefined4 param_3,int param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  undefined1 *puVar8;
  undefined1 local_110 [260];
  int local_c;
  int local_8;
  
  if (param_2 == 0x2f) {
    if (*(int *)(param_4 + 0x14) == 0x11) {
      FUN_004a43da(param_1,0x2f,param_3,param_4);
      uVar6 = 1;
      uVar4 = 5;
      uVar1 = FUN_0049ea99(param_1);
      uVar1 = FUN_004a1150(uVar1,uVar4,uVar6);
      iVar2 = FUN_0049eafa(uVar1);
      if (iVar2 == 0) {
        uVar7 = 0;
        uVar5 = 1;
        uVar3 = 9;
        uVar6 = 1;
        uVar4 = 5;
        uVar1 = FUN_0049ea99(param_1);
        FUN_0049eb44(uVar1,uVar4,uVar6,uVar3,uVar5,uVar7);
      }
    }
  }
  else if (param_2 == 0x45) {
    uVar6 = 1;
    uVar4 = 5;
    uVar1 = FUN_0049ea99(param_1);
    uVar1 = FUN_004a1150(uVar1,uVar4,uVar6);
    iVar2 = FUN_0049eafa(uVar1);
    if (iVar2 == 1) {
      uVar4 = 5;
      uVar1 = FUN_0049ea99(param_1);
      FUN_004a2c1b(uVar1,uVar4);
      uVar7 = 0;
      uVar5 = 0;
      uVar3 = 9;
      uVar6 = 1;
      uVar4 = 5;
      uVar1 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar1,uVar4,uVar6,uVar3,uVar5,uVar7);
    }
  }
  else if (param_2 == 0x3b) {
    uVar7 = 0;
    uVar5 = 0;
    uVar3 = 0x18;
    uVar6 = 2;
    uVar1 = param_1;
    uVar4 = FUN_0049ea99(param_1);
    local_8 = FUN_0049eb44(uVar4,uVar1,uVar6,uVar3,uVar5,uVar7);
    uVar7 = 0;
    uVar5 = 0;
    uVar3 = 0x22;
    uVar6 = 2;
    uVar1 = param_1;
    uVar4 = FUN_0049ea99(param_1);
    iVar2 = FUN_0049eb44(uVar4,uVar1,uVar6,uVar3,uVar5,uVar7);
    local_c = iVar2;
    if (iVar2 < local_8) {
      puVar8 = local_110;
      uVar3 = 0x35;
      uVar6 = 2;
      uVar1 = param_1;
      uVar4 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar4,uVar1,uVar6,uVar3,iVar2,puVar8);
      FUN_0049eb44(DAT_004c4788,0xf,1,0xf,0,local_110);
    }
  }
  FUN_004a43da(param_1,param_2,param_3,param_4);
  return;
}

