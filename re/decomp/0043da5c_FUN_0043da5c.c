// FUN_0043da5c @ 0043da5c size=132 sig=undefined FUN_0043da5c() cc=unknown
// callers: FUN_00453c30
// callees: FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_004864c4,FUN_0043da44,FUN_00444b74

void FUN_0043da5c(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  if ((param_1 != 0) && (*(char *)(param_1 + 0x1d) != '\0')) {
    iVar1 = FUN_00444f20(0xb5,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),0);
    if (iVar1 != 0) {
      FUN_004864c4(iVar1,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24));
      if (*(int *)(param_1 + 0x38) == 0) {
        FUN_00444b74(iVar1,0x7531);
      }
      else {
        FUN_00444b74(iVar1,*(short *)(*(int *)(param_1 + 0x38) + 4) + 1);
        FUN_0043da44(param_1);
        uVar3 = 0;
        uVar2 = FUN_0043d004((int)*(short *)(*(int *)(param_1 + 0x38) + 0xe));
        FUN_00482ac4(0x43,0,1,0,uVar2,uVar3);
      }
    }
  }
  return;
}

