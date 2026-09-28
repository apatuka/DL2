// thunk_FUN_0045792c @ 004b4353 size=5 sig=undefined thunk_FUN_0045792c() cc=unknown
// callers: FUN_0046534c,FUN_0048bdb0,FUN_004652a8
// callees: 

void thunk_FUN_0045792c(int param_1,int param_2,int param_3,HDC param_4,int param_5,int param_6,
                       DWORD param_7)

{
  int unaff_retaddr;
  
  if (DAT_0051b814 != (int *)0x0) {
    DAT_0065e5c4 = 1;
    (**(code **)(*DAT_0051b814 + 0x44))(DAT_0051b814,&DAT_0065e5c0);
    BitBlt(DAT_0065e5c0,unaff_retaddr,param_1,param_2,param_3,param_4,param_5,param_6,param_7);
    if (DAT_0065e5c4 != 0) {
      (**(code **)(*DAT_0051b814 + 0x68))();
    }
  }
  return;
}

