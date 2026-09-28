// FUN_0045792c @ 0045792c size=94 sig=undefined FUN_0045792c() cc=unknown
// callers: 
// callees: BitBlt

void FUN_0045792c(int param_1,int param_2,int param_3,HDC param_4,int param_5,int param_6,
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

