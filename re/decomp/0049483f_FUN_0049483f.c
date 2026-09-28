// FUN_0049483f @ 0049483f size=315 sig=undefined FUN_0049483f() cc=unknown
// callers: FUN_00444398
// callees: FUN_00494346,FUN_0048c85e,FUN_00496cc3,FUN_00496ffb,FUN_00495c51

void FUN_0049483f(int param_1,int *param_2,int *param_3,int *param_4)

{
  int iVar1;
  int *piVar2;
  int local_14 [4];
  
  if (param_3 != (int *)0x0) {
    *param_3 = 0;
  }
  if ((((DAT_0065ec80 != 0) && (DAT_0065ec7c != 0)) && (DAT_0051dc9c != 0)) && (param_1 != 0)) {
    FUN_00496cc3(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,local_14);
    FUN_00495c51(local_14,DAT_0065ec84,DAT_0065ec88);
    if ((param_2 == (int *)0x0) ||
       (((*param_2 < local_14[2] && (local_14[0] < param_2[2])) &&
        ((param_2[1] < local_14[3] && (local_14[1] < param_2[3])))))) {
      if ((param_3 != (int *)0x0) &&
         (iVar1 = FUN_00494346(local_14[2] - local_14[0],local_14[3] - local_14[1]), iVar1 != 0)) {
        FUN_0048c85e(param_1,DAT_0065ecb8,local_14,DAT_0065ecb8 + 0x2c,0,0,0);
        *param_3 = DAT_0065ecb8;
        if (param_4 != (int *)0x0) {
          piVar2 = local_14;
          for (iVar1 = 4; iVar1 != 0; iVar1 = iVar1 + -1) {
            *param_4 = *piVar2;
            piVar2 = piVar2 + 1;
            param_4 = param_4 + 1;
          }
        }
      }
      FUN_00496ffb(DAT_0065ecb0,DAT_0051dc78,0,DAT_0051dc70,DAT_0065ec84,DAT_0065ec88,0xffffffff,0,
                   param_1);
    }
  }
  return;
}

