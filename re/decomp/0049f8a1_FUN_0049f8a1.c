// FUN_0049f8a1 @ 0049f8a1 size=60 sig=undefined FUN_0049f8a1() cc=unknown
// callers: FUN_0049f8dd,FUN_0049f947
// callees: FUN_0049ea99,FUN_0049eb44

void FUN_0049f8a1(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  if (param_1 != 0) {
    uVar6 = 0;
    uVar5 = 0;
    uVar4 = 8;
    uVar3 = 2;
    iVar2 = param_1;
    uVar1 = FUN_0049ea99(param_1);
    FUN_0049eb44(uVar1,iVar2,uVar3,uVar4,uVar5,uVar6);
    *(uint *)(param_1 + 0x28) = *(uint *)(param_1 + 0x28) & 0xfffffffe | (uint)(param_2 != 0);
  }
  return;
}

