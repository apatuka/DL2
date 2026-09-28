// FUN_0043c78c @ 0043c78c size=506 sig=undefined FUN_0043c78c() cc=unknown
// callers: 
// callees: FUN_004839a4,FUN_0049aa64,FUN_0049b3c9,FUN_004935fc,FUN_0046ac44,FUN_00483c3c,FUN_004a43da,FUN_0049a8ed,FUN_0049f09b,FUN_0049a93f

undefined4 FUN_0043c78c(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  undefined1 local_b4 [16];
  int local_a4;
  int local_3c;
  int local_38;
  int local_2c;
  int local_28;
  int local_24 [3];
  int local_18;
  int local_14;
  int local_10;
  int local_c;
  int local_8;
  
  if (param_2 == 3) {
    FUN_0049a8ed();
    FUN_0049f09b(param_1,&local_3c);
    iVar1 = FUN_0049aa64(&local_3c);
    if (iVar1 != 0) {
      FUN_0046ac44(local_b4,DAT_0058f1f4);
      local_8 = 8;
      local_c = FUN_004839a4(DAT_00559da8);
      if (0 < local_c) {
        iVar1 = FUN_00483c3c(PTR_DAT_004d5988,&DAT_004fbbac + local_c * 0x19);
        local_10 = (int)(short)(&DAT_004fbbb2)[local_c * 0x19 + (int)(char)*PTR_DAT_004d5988];
        local_14 = local_a4;
        local_18 = (local_10 * 100) / iVar1;
        local_24[2] = (local_a4 * 100) / iVar1 + local_18;
        local_24[1] = 100;
        if (local_18 < 0x65) {
          piVar3 = &local_18;
        }
        else {
          piVar3 = local_24 + 1;
        }
        local_18 = *piVar3;
        local_24[0] = 100;
        if (local_24[2] < 0x65) {
          piVar4 = local_24 + 2;
        }
        else {
          piVar4 = local_24;
        }
        local_24[2] = *piVar4;
        local_28 = (local_24[2] * 0x99) / 100;
        local_2c = (*piVar3 * 0x99) / 100;
        if (local_24[2] == 100) {
          uVar2 = FUN_0049b3c9(DAT_0058df44,0xda);
          FUN_004935fc(local_3c,local_38,local_8 + local_3c,local_28 + local_38,uVar2);
        }
        else {
          if (local_28 != 0) {
            uVar2 = FUN_0049b3c9(DAT_0058df44,0xd);
            FUN_004935fc(local_3c,(0x99 - local_28) + local_38,local_8 + local_3c,local_38 + 0x99,
                         uVar2);
          }
          if (local_2c != 0) {
            uVar2 = FUN_0049b3c9(DAT_0058df44,0xdb);
            FUN_004935fc(local_3c,local_38 + (0x99 - local_2c),local_8 + local_3c,local_38 + 0x99,
                         uVar2);
          }
        }
      }
    }
    FUN_0049a93f();
    uVar2 = 1;
  }
  else {
    uVar2 = FUN_004a43da(param_1,param_2,param_3,param_4);
  }
  return uVar2;
}

