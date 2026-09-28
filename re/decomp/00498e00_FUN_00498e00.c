// FUN_00498e00 @ 00498e00 size=218 sig=undefined FUN_00498e00() cc=unknown
// callers: FUN_00499227,FUN_00498f8c
// callees: FUN_0048fcc3,FUN_0048fd38

undefined4 FUN_00498e00(undefined1 *param_1,undefined4 param_2)

{
  undefined1 uVar1;
  undefined2 uVar2;
  short sVar3;
  
  uVar1 = FUN_0048fd38(param_2);
  *param_1 = uVar1;
  uVar1 = FUN_0048fd38(param_2);
  param_1[1] = uVar1;
  uVar1 = FUN_0048fd38(param_2);
  param_1[2] = uVar1;
  uVar1 = FUN_0048fd38(param_2);
  param_1[3] = uVar1;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 4) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 6) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 8) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 10) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0xc) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0xe) = uVar2;
  sVar3 = 0;
  do {
    uVar1 = FUN_0048fd38(param_2);
    param_1[sVar3 + 0x10] = uVar1;
    sVar3 = sVar3 + 1;
  } while (sVar3 < 0x30);
  uVar1 = FUN_0048fd38(param_2);
  param_1[0x40] = uVar1;
  uVar1 = FUN_0048fd38(param_2);
  param_1[0x41] = uVar1;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0x42) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0x44) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0x46) = uVar2;
  uVar2 = FUN_0048fcc3(param_2);
  *(undefined2 *)(param_1 + 0x48) = uVar2;
  sVar3 = 0;
  do {
    uVar1 = FUN_0048fd38(param_2);
    param_1[sVar3 + 0x4a] = uVar1;
    sVar3 = sVar3 + 1;
  } while (sVar3 < 0x36);
  return 0;
}

