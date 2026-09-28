// FUN_004105e8 @ 004105e8 size=310 sig=undefined FUN_004105e8() cc=unknown
// callers: FUN_004059bc
// callees: FUN_0040d4a8,TotalUnitLabor,FUN_00476324,FUN_0040f6b0,FUN_0040f5e0,FUN_0040f658,FUN_004068f8,FUN_0040f584,FUN_00406424,FUN_00407d60

void FUN_004105e8(undefined4 param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined *puVar5;
  undefined4 uVar6;
  int local_10;
  
  puVar5 = (undefined *)0x0;
  iVar4 = *(int *)(param_2 + 0x20);
  uVar6 = *(undefined4 *)(param_2 + 0x24);
  if (*(int *)(param_2 + 0x1c) != -1) {
    puVar5 = &DAT_005a43d0 + *(int *)(param_2 + 0x1c) * 0xadc;
  }
  if ((puVar5 == (undefined *)0x0) || (iVar1 = FUN_0040f6b0(puVar5,iVar4), iVar1 == 0)) {
    *(undefined4 *)(param_2 + 0x10) = 1;
    return;
  }
  uVar2 = FUN_0040f5e0(iVar4);
  local_10 = 0;
  if (((&DAT_004faf8d)[iVar4 * 0x24] == '\x02') &&
     (local_10 = FUN_0040d4a8(puVar5,uVar6), local_10 == 0)) {
    *(undefined4 *)(param_2 + 0xc) = 1;
    return;
  }
  iVar1 = FUN_0040f658(puVar5,iVar4);
  iVar3 = TotalUnitLabor(puVar5,uVar2);
  if (iVar1 <= iVar3) {
    if ((&DAT_004faf8d)[iVar4 * 0x24] == '\x02') {
      FUN_00476324(puVar5,(int)*(short *)(local_10 + 0x1a));
    }
    *(undefined4 *)(param_2 + 0xc) = 1;
    return;
  }
  iVar1 = FUN_00406424(param_1,puVar5);
  if ((iVar1 != 0) && (iVar1 = FUN_004068f8(param_1,puVar5,uVar2), iVar1 != 0)) {
    return;
  }
  iVar1 = FUN_0040f584(puVar5,uVar2);
  if (iVar1 != 0) {
    *(undefined4 *)(param_2 + 0xc) = 1;
    uVar2 = 1;
    uVar6 = 0xb;
    iVar1 = (int)*(short *)(puVar5 + 0x1a);
    iVar4 = FUN_0040f5e0(iVar4);
    FUN_00407d60(param_1,*(undefined4 *)(param_2 + 4),*(undefined4 *)(param_2 + 8),
                 *(undefined4 *)(&DAT_004b6f74 + iVar4 * 4),iVar1,uVar6,uVar2);
    return;
  }
  *(undefined4 *)(param_2 + 0xc) = 1;
  return;
}

