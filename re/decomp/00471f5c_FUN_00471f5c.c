// FUN_00471f5c @ 00471f5c size=143 sig=undefined FUN_00471f5c() cc=unknown
// callers: FUN_0041acf8,CheckBuildingList
// callees: FUN_0044de9c,FUN_00471e58

undefined4 FUN_00471f5c(int param_1,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 local_38 [13];
  
  puVar3 = &DAT_004d6354;
  puVar4 = local_38;
  for (iVar2 = 0xd; iVar2 != 0; iVar2 = iVar2 + -1) {
    *puVar4 = *puVar3;
    puVar3 = puVar3 + 1;
    puVar4 = puVar4 + 1;
  }
  if (DAT_004d5aa0 == '\0') {
    if (param_1 < 0x30) {
      FUN_0044de9c(&DAT_0059f160 + *(char *)(param_2 + 0x20) * 0x2d8,param_1,
                   (int)*(char *)(param_2 + 0x21),local_38);
      uVar1 = FUN_00471e58(&DAT_0059f160 + *(char *)(param_2 + 0x20) * 0x2d8,param_2,local_38);
    }
    else {
      uVar1 = 0xffffffff;
    }
  }
  else {
    uVar1 = 0;
  }
  return uVar1;
}

