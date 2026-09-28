// FUN_004a7c1f @ 004a7c1f size=101 sig=undefined FUN_004a7c1f() cc=unknown
// callers: FUN_004a7c94,FUN_004a7df4
// callees: FUN_004a9090,FUN_004a76d2,__assertfail
// strings: \"XX.CPP\"|\"dtorAddr\"

void FUN_004a7c1f(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4)

{
  undefined4 *puVar1;
  undefined2 in_FS;
  undefined4 local_28;
  
  FUN_004a9090();
  if (param_3 == 0) {
    __assertfail(s_dtorAddr_0051f35f,s_XX_CPP_0051f368,0x567);
  }
  FUN_004a76d2(param_1,param_2,0,param_3,param_4,1);
  puVar1 = (undefined4 *)segment(in_FS,0);
  *puVar1 = local_28;
  return;
}

