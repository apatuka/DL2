// FUN_0043d594 @ 0043d594 size=155 sig=undefined FUN_0043d594() cc=unknown
// callers: FUN_00454160,FUN_00453ec8,FUN_00453568,FUN_00453350,FUN_004543f8,FUN_00454690
// callees: FUN_0043d004,FUN_00482ac4,FUN_00444f20,FUN_0046ca40,FUN_004864c4,FUN_00444b74

void FUN_0043d594(undefined4 param_1,undefined4 param_2,int param_3)

{
  uint uVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 uVar6;
  undefined4 local_24 [8];
  
  puVar4 = &DAT_004c4962;
  puVar5 = local_24;
  for (iVar3 = 7; iVar3 != 0; iVar3 = iVar3 + -1) {
    *puVar5 = *puVar4;
    puVar4 = puVar4 + 1;
    puVar5 = puVar5 + 1;
  }
  *(undefined2 *)puVar5 = *(undefined2 *)puVar4;
  iVar3 = FUN_00444f20(param_3 + 0xaf,param_1,param_2,0);
  if (iVar3 != 0) {
    uVar1 = FUN_0046ca40();
    *(short *)(iVar3 + 0x2c) = (short)((ulonglong)uVar1 % 3);
    uVar1 = FUN_0046ca40();
    *(undefined2 *)(iVar3 + 0x2e) = *(undefined2 *)((int)local_24 + (uVar1 % 0xf) * 2);
    FUN_004864c4(iVar3,param_1,param_2);
    FUN_00444b74(iVar3,0x7532);
    uVar6 = 0;
    uVar2 = FUN_0043d004((int)*(short *)(iVar3 + 0xe));
    FUN_00482ac4(0x3b,0,1,0,uVar2,uVar6);
  }
  return;
}

