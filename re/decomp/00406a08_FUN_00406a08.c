// FUN_00406a08 @ 00406a08 size=80 sig=undefined FUN_00406a08() cc=unknown
// callers: 
// callees: FUN_004067d0

void FUN_00406a08(undefined4 param_1)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *puVar4;
  
  puVar4 = &DAT_00521bb4;
  do {
    uVar1 = *puVar4;
    iVar3 = 0;
    puVar2 = &DAT_004b6230;
    do {
      FUN_004067d0(param_1,uVar1,*puVar2,10000,10000,0);
      iVar3 = iVar3 + 1;
      puVar2 = puVar2 + 1;
    } while (iVar3 < 0x13);
    puVar4 = (undefined4 *)puVar4[1];
  } while (puVar4 != &DAT_00521bb4);
  return;
}

