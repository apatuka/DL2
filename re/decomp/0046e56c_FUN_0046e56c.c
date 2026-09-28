// FUN_0046e56c @ 0046e56c size=330 sig=undefined FUN_0046e56c() cc=unknown
// callers: FUN_00414004,FUN_0046e6b8,FUN_00485668,FUN_0045eadc,FUN_004471c0,FUN_00473e9c
// callees: FUN_004b02a8,FUN_00484c40,FUN_00484c2c

void FUN_0046e56c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 uVar3;
  
  *(undefined1 *)(param_1 + 0x29) = 0;
  *(undefined2 *)(param_1 + 0x30) = 0;
  *(undefined1 *)(param_1 + 0x26) = 0;
  *(undefined1 *)(param_1 + 0x9ae) = 0;
  *(char *)(param_1 + 0x20) = (char)param_2;
  if (*(int *)(param_1 + 0x99a) != 0) {
    FUN_00484c40(*(int *)(param_1 + 0x99a),3);
  }
  if (*(int *)(param_1 + 0x99e) != 0) {
    FUN_00484c40(*(int *)(param_1 + 0x99e),3);
  }
  if (*(int *)(param_1 + 0x9a2) != 0) {
    FUN_00484c40(*(int *)(param_1 + 0x9a2),3);
  }
  if (*(int *)(param_1 + 0x9a6) != 0) {
    FUN_00484c40(*(int *)(param_1 + 0x9a6),3);
  }
  if (*(int *)(param_1 + 0x9aa) != 0) {
    FUN_00484c40(*(int *)(param_1 + 0x9aa),3);
  }
  iVar1 = FUN_004b02a8(8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00484c2c(iVar1);
  }
  *(undefined4 *)(param_1 + 0x99a) = uVar2;
  iVar1 = FUN_004b02a8(8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00484c2c(iVar1);
  }
  *(undefined4 *)(param_1 + 0x99e) = uVar2;
  iVar1 = FUN_004b02a8(8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00484c2c(iVar1);
  }
  *(undefined4 *)(param_1 + 0x9a2) = uVar2;
  iVar1 = FUN_004b02a8(8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00484c2c(iVar1);
  }
  *(undefined4 *)(param_1 + 0x9a6) = uVar2;
  iVar1 = FUN_004b02a8(8);
  if (iVar1 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = FUN_00484c2c(iVar1);
  }
  *(undefined4 *)(param_1 + 0x9aa) = uVar2;
  if (param_2 != -1) {
    uVar3 = 0x50;
    if (*(short *)(&DAT_00559f7a + (char)(&DAT_0059f162)[param_2 * 0x2d8] * 2) != 0) {
      uVar3 = 100;
    }
    *(undefined1 *)(param_1 + 0x27) = uVar3;
  }
  return;
}

