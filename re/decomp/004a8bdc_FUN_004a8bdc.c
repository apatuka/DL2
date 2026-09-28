// FUN_004a8bdc @ 004a8bdc size=124 sig=undefined FUN_004a8bdc() cc=unknown
// callers: FUN_004a8c58
// callees: __assertfail
// strings: \"XX.CPP\"|\"IS_CLASS(varType->tpMask)\"|\"((unsigned __far *)vftAddr)[-1] == 0\"

int FUN_004a8bdc(int param_1,int *param_2)

{
  int iVar1;
  
  iVar1 = *param_2;
  if ((*(byte *)(iVar1 + 4) & 2) == 0) {
    __assertfail(s_IS_CLASS_varType_>tpMask__0051f7ce,s_XX_CPP_0051f7e8,0xda2);
  }
  if (((*(uint *)(iVar1 + 0xc) & 0x50) == 0x50) && (*(int *)(iVar1 + 8) != -1)) {
    iVar1 = *(int *)(*(int *)(iVar1 + 8) + param_1);
    param_1 = param_1 - *(int *)(iVar1 + -8);
    iVar1 = iVar1 - *(int *)(iVar1 + -4);
    if (*(int *)(iVar1 + -4) != 0) {
      __assertfail(s___unsigned___far___vftAddr___1____0051f7ef,s_XX_CPP_0051f814,0xdc1);
    }
    *param_2 = *(int *)(iVar1 + -0xc);
  }
  return param_1;
}

