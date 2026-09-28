// FUN_0049b7f0 @ 0049b7f0 size=282 sig=undefined FUN_0049b7f0() cc=unknown
// callers: FUN_0049cb2f,FUN_004a43da
// callees: FUN_0049c244,FUN_0049eb44,FUN_0049f7c9,FUN_0049ea99

undefined4 FUN_0049b7f0(undefined4 param_1,int param_2,byte *param_3)

{
  bool bVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  
  bVar1 = false;
  if (((param_3 == (byte *)0x0) || (param_2 == 0)) || (*(int *)(param_2 + 0x1c) != 9)) {
    uVar2 = 0;
  }
  else {
    if (((*param_3 & 2) != 0) && (*(int *)(param_2 + 0xe8) != *(int *)(param_3 + 8))) {
      bVar1 = true;
      *(undefined4 *)(param_2 + 0xe8) = *(undefined4 *)(param_3 + 8);
    }
    if (((*param_3 & 4) != 0) && (*(int *)(param_2 + 0xec) != *(int *)(param_3 + 0xc))) {
      bVar1 = true;
      *(undefined4 *)(param_2 + 0xec) = *(undefined4 *)(param_3 + 0xc);
    }
    if (((*param_3 & 1) != 0) && (*(int *)(param_2 + 0x48) != *(int *)(param_3 + 4))) {
      bVar1 = true;
      *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(param_3 + 4);
    }
    if (((*param_3 & 8) != 0) && (*(int *)(param_2 + 0xf4) != *(int *)(param_3 + 0x10))) {
      bVar1 = true;
      *(undefined4 *)(param_2 + 0xf4) = *(undefined4 *)(param_3 + 0x10);
    }
    if ((*(int *)(param_2 + 0x48) < *(int *)(param_2 + 0xe8)) &&
       (*(int *)(param_2 + 0x48) != *(int *)(param_2 + 0xe8))) {
      bVar1 = true;
      *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(param_2 + 0xe8);
    }
    if ((*(int *)(param_2 + 0xec) <= *(int *)(param_2 + 0x48)) &&
       (*(int *)(param_2 + 0x48) != *(int *)(param_2 + 0xec))) {
      bVar1 = true;
      *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(param_2 + 0xec);
    }
    FUN_0049c244(param_1,param_2,0);
    if (bVar1) {
      FUN_0049f7c9(param_2);
      uVar6 = 0;
      uVar5 = 0;
      uVar4 = 0x32;
      uVar3 = 2;
      uVar2 = FUN_0049ea99(param_2);
      FUN_0049eb44(uVar2,param_2,uVar3,uVar4,uVar5,uVar6);
    }
    uVar2 = 1;
  }
  return uVar2;
}

