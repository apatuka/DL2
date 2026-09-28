// FUN_004396a0 @ 004396a0 size=74 sig=undefined FUN_004396a0() cc=unknown
// callers: ChCht
// callees: FUN_004393e8,FUN_00438fe0,FUN_00438ef8,FUN_004393a0

undefined * FUN_004396a0(undefined4 param_1,undefined4 *param_2)

{
  int iVar1;
  undefined *puVar2;
  
  iVar1 = FUN_00438fe0(param_1);
  if (iVar1 == 0) {
    puVar2 = (undefined *)0x0;
  }
  else {
    FUN_00438ef8();
    do {
      iVar1 = FUN_004393e8();
    } while (iVar1 == 0);
    FUN_004393a0();
    if (iVar1 == 5) {
      *param_2 = DAT_005596c4;
      puVar2 = &DAT_005595bd;
    }
    else {
      puVar2 = (undefined *)0x0;
    }
  }
  return puVar2;
}

