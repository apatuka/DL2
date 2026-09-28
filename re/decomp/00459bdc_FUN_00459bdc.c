// FUN_00459bdc @ 00459bdc size=106 sig=undefined FUN_00459bdc() cc=unknown
// callers: FUN_00440b68,FUN_0045a91c
// callees: FUN_00459948,FUN_0047e074,FUN_0045973c,FUN_00459a3c

void FUN_00459bdc(undefined4 param_1)

{
  int iVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 local_38 [5];
  undefined4 local_24 [7];
  undefined4 local_8;
  
  puVar2 = &DAT_004d1ae0;
  puVar3 = local_24;
  for (iVar1 = 7; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  puVar2 = &DAT_004d1afc;
  puVar3 = local_38;
  for (iVar1 = 5; iVar1 != 0; iVar1 = iVar1 + -1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + 1;
    puVar3 = puVar3 + 1;
  }
  iVar1 = FUN_0047e074();
  if (iVar1 != 0) {
    FUN_0045973c(param_1,local_24,local_38,&local_8);
    FUN_00459948(iVar1,param_1,local_24);
    FUN_00459a3c(iVar1,param_1,local_38,local_8);
  }
  return;
}

