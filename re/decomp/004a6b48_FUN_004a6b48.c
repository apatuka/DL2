// FUN_004a6b48 @ 004a6b48 size=79 sig=undefined FUN_004a6b48() cc=unknown
// callers: FUN_004418ec,FUN_00424f14,FUN_0042e7ec,FUN_00439e98,BroadcastText,FUN_004749f8,FUN_004843ac,FUN_00476ee4,FUN_00438fe0,FUN_004582e0,FUN_00468ea4,FUN_004393e8,ChCht,FUN_00411990,FUN_00468da0,FUN_00412358,FUN_004770fc,SendSlaveInfo,FUN_004234d4,FUN_0047526c,FUN_0041b500,FUN_00487820,FUN_00445d30,FUN_00475228,FUN_00423960,FUN_0041287c,FUN_0041244c,FUN_004399dc
// callees: memset,strlen,memcpy

int FUN_004a6b48(int param_1,undefined4 param_2,uint param_3)

{
  uint uVar1;
  
  uVar1 = strlen(param_2);
  if (param_3 < uVar1) {
    memcpy(param_1,param_2,param_3);
  }
  else {
    memcpy(param_1,param_2,uVar1);
    memset(uVar1 + param_1,0,param_3 - uVar1);
  }
  return param_1;
}

