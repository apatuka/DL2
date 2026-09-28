// FUN_0049e2d5 @ 0049e2d5 size=214 sig=undefined FUN_0049e2d5() cc=unknown
// callers: FUN_004a26e8,FUN_004a43da
// callees: GetTickCount,FUN_0049ea99,FUN_0049eb44

void FUN_0049e2d5(int param_1,int param_2)

{
  DWORD DVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  
  if (param_2 == 2) {
    DVar1 = GetTickCount();
    if (*(uint *)(param_1 + 0x5c) < DVar1) {
      *(uint *)(param_1 + 0xf8) = *(uint *)(param_1 + 0xf8) ^ 0x40000000;
      DVar1 = GetTickCount();
      iVar3 = 500;
      if ((*(byte *)(param_1 + 0xfb) & 0x40) == 0) {
        iVar3 = 1000;
      }
      *(DWORD *)(param_1 + 0x5c) = DVar1 + iVar3;
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 8;
      uVar4 = 2;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,param_1,uVar4,uVar5,uVar6,uVar7);
    }
  }
  else if (param_2 == 1) {
    if ((*(byte *)(param_1 + 0xfb) & 0xc0) != 0) {
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 8;
      uVar4 = 2;
      iVar3 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,iVar3,uVar4,uVar5,uVar6,uVar7);
    }
    *(uint *)(param_1 + 0xf8) = *(uint *)(param_1 + 0xf8) & 0x3fffffff;
    DVar1 = GetTickCount();
    *(DWORD *)(param_1 + 0x5c) = DVar1 + 1000;
  }
  else if (param_2 == 0) {
    if ((*(byte *)(param_1 + 0xfb) & 0xc0) == 0) {
      uVar7 = 0;
      uVar6 = 0;
      uVar5 = 8;
      uVar4 = 2;
      iVar3 = param_1;
      uVar2 = FUN_0049ea99(param_1);
      FUN_0049eb44(uVar2,iVar3,uVar4,uVar5,uVar6,uVar7);
    }
    *(undefined4 *)(param_1 + 0xf8) = 0x80000000;
    DVar1 = GetTickCount();
    *(DWORD *)(param_1 + 0x5c) = DVar1 + 500;
  }
  return;
}

