// FUN_0043d630 @ 0043d630 size=178 sig=undefined FUN_0043d630() cc=unknown
// callers: FUN_00453d9c
// callees: FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_0046ca40,FUN_004864c4,FUN_00444b74

void FUN_0043d630(int param_1)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_24 [8];
  
  puVar4 = &DAT_004c4980;
  puVar5 = local_24;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = *(undefined2 *)puVar4;
  if (*(int *)(param_1 + 4) == 0x25) {
    iVar3 = FUN_00444f20(0xb6,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),0);
  }
  else {
    iVar3 = FUN_00444f20(0xb7,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24),0);
  }
  if (iVar3 != 0) {
    *(undefined2 *)(iVar3 + 0x2c) = 0;
    uVar1 = FUN_0046ca40();
    *(undefined2 *)(iVar3 + 0x2e) = *(undefined2 *)((int)local_24 + (uVar1 % 0xf) * 2);
    FUN_004864c4(iVar3,*(undefined4 *)(param_1 + 0x20),*(undefined4 *)(param_1 + 0x24));
    FUN_00444b74(iVar3,0x7532);
    uVar6 = 0;
    uVar2 = FUN_0043d004((int)*(short *)(iVar3 + 0xe));
    FUN_00482ac4(0x3b,0,1,0,uVar2,uVar6);
  }
  return;
}

