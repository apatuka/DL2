// FUN_0041b330 @ 0041b330 size=438 sig=undefined FUN_0041b330() cc=unknown
// callers: 
// callees: FUN_0046ab18,FUN_0046ac44,FUN_0049eb9f,FUN_0046d250,FUN_004a43da,FUN_0049f09b,FUN_00495c51,FUN_0049fe03,FUN_00491e02,FUN_00491efa,FUN_00493108,sprintf

undefined4 FUN_0041b330(int param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  int iVar3;
  undefined1 local_a4 [32];
  undefined4 auStack_84 [11];
  int aiStack_58 [11];
  undefined1 local_2c [4];
  int local_28;
  int local_20;
  undefined1 local_1c [8];
  undefined1 local_14 [8];
  undefined1 local_c [8];
  
  if (param_2 == 3) {
    FUN_0049f09b(param_1,local_2c);
    FUN_0049fe03(param_1,local_2c);
    FUN_0046ac44(local_a4,DAT_0058f1f4);
    if (DAT_004c48a4 == 0) {
      iVar3 = 1;
      puVar1 = auStack_84;
      do {
        puVar1 = puVar1 + 1;
        iVar3 = iVar3 + 1;
        *puVar1 = 0;
        puVar1[0xb] = 0;
      } while (iVar3 < 0xb);
      FUN_0046ab18(&DAT_005a43d0 + DAT_004c5b50 * 0xadc,local_a4);
    }
    iVar3 = FUN_0049eb9f(param_1,0);
    if (iVar3 != 0) {
      FUN_00491e02(0x30);
      FUN_00491efa(0);
      FUN_0046d250(auStack_84[*(int *)(s_RRGCONE_004c1c33 + *(int *)(param_1 + 0x30) * 0x10 + 5)],
                   local_c);
      sprintf(local_1c,&DAT_004b7893,local_c);
      local_28 = local_20 + DAT_0065ec0c * -2 + -5;
      local_20 = local_20 - (DAT_0065ec0c + -5);
      FUN_00493108(local_1c,local_2c,1,0);
      FUN_0046d250(aiStack_58[*(int *)(s_RRGCONE_004c1c33 + *(int *)(param_1 + 0x30) * 0x10 + 5)],
                   local_14);
      if (aiStack_58[*(int *)(s_RRGCONE_004c1c33 + *(int *)(param_1 + 0x30) * 0x10 + 5)] < 0) {
        sprintf(local_1c,&DAT_004b7893,local_14);
        uVar2 = 0x60;
      }
      else {
        sprintf(local_1c,&DAT_004b7896,local_14);
        uVar2 = 0x50;
      }
      FUN_00491e02(uVar2);
      FUN_00495c51(local_2c,0,DAT_0065ec0c);
      FUN_00493108(local_1c,local_2c,1,0);
    }
    FUN_0046ac44(local_a4,DAT_0058f1f4);
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

