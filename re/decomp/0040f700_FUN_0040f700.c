// FUN_0040f700 @ 0040f700 size=147 sig=undefined FUN_0040f700() cc=unknown
// callers: FUN_0040f818,FUN_0040fb14,FUN_0040f974,FUN_0040f8cc
// callees: FUN_0040d4a8,FUN_00401440,memset

undefined4 FUN_0040f700(int param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined1 local_60 [6];
  undefined1 local_5a;
  undefined1 local_59;
  undefined1 local_58;
  int local_28;
  int local_24;
  int local_20;
  
  if ((param_1 == 0) || (param_2 == 0)) {
    uVar2 = 1;
  }
  else if ((&DAT_004faf8d)[param_3 * 0x24] == '\x02') {
    iVar1 = FUN_0040d4a8(param_1,(int)*(short *)(param_2 + 0x1a));
    if (iVar1 == 0) {
      uVar2 = 0;
    }
    else {
      uVar2 = 1;
    }
  }
  else {
    memset(local_60,0,0x5c);
    local_5a = (undefined1)param_3;
    local_59 = (&DAT_004faf87)[param_3 * 0x24];
    local_58 = *(undefined1 *)(param_1 + 0x20);
    local_24 = param_1;
    local_28 = param_1;
    local_20 = param_1;
    uVar2 = FUN_00401440(local_60,param_2,param_4);
  }
  return uVar2;
}

