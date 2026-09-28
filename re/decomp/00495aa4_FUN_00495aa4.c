// FUN_00495aa4 @ 00495aa4 size=132 sig=undefined FUN_00495aa4() cc=unknown
// callers: FUN_00499470
// callees: FUN_004a6b00,FUN_004893dd

undefined4
FUN_00495aa4(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,undefined4 param_5
            )

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_108 [260];
  
  if (param_3 == 0) {
    FUN_004893dd(param_1,local_108);
    param_3 = 1;
    do {
      iVar1 = FUN_004a6b00(local_108,&DAT_0065edc8 + param_3 * 0xc);
      if (iVar1 == 0) break;
      param_3 = param_3 + 1;
    } while (param_3 < 4);
  }
  if ((param_3 < 4) && (*(int *)(&DAT_0065edc0 + param_3 * 0xc) != 0)) {
    uVar2 = (**(code **)(&DAT_0065edc0 + param_3 * 0xc))(param_1,param_2,param_3,param_4,param_5);
  }
  else {
    uVar2 = 0;
  }
  return uVar2;
}

