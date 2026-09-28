// FUN_004aa828 @ 004aa828 size=88 sig=undefined FUN_004aa828() cc=unknown
// callers: fclose,FUN_004aa880
// callees: FUN_004ae4d4,FUN_004b3e08,FUN_004a6bf8,FUN_004a68dc

int FUN_004aa828(int param_1,undefined *param_2,undefined2 param_3)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    param_1 = FUN_004b3e08(0x1c,0x1a);
  }
  if (param_2 == (undefined *)0x0) {
    param_2 = &DAT_00520268;
  }
  uVar1 = FUN_004a6bf8(param_1,param_2,10);
  FUN_004ae4d4(param_3,uVar1);
  FUN_004a68dc(param_1,&DAT_0052026c);
  return param_1;
}

