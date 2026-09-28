// FUN_0043d8dc @ 0043d8dc size=121 sig=undefined FUN_0043d8dc() cc=unknown
// callers: FUN_00455c88
// callees: FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_00444b74

void FUN_0043d8dc(int param_1)

{
  undefined4 uVar1;
  ushort *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  if (((param_1 != 0) && (*(int *)(param_1 + 0x38) != 0)) && (*(char *)(param_1 + 0x1d) != '\0')) {
    uVar4 = 0;
    uVar1 = FUN_0043d004((int)*(short *)(*(int *)(param_1 + 0x38) + 0xe));
    FUN_00482ac4(0x72,0,1,0,uVar1,uVar4);
    puVar2 = (ushort *)FUN_00444f20(0x196,0,0,0);
    if (puVar2 != (ushort *)0x0) {
      iVar3 = *(int *)(param_1 + 0x38) + -0x561a34;
      if (iVar3 < 0) {
        iVar3 = *(int *)(param_1 + 0x38) + -0x5619f5;
      }
      puVar2[0x19] = (ushort)(iVar3 >> 6);
      *puVar2 = *puVar2 | 0x10;
      FUN_00444b74(puVar2,*(short *)(*(int *)(param_1 + 0x38) + 4) + 1);
    }
  }
  return;
}

