// FUN_004a9564 @ 004a9564 size=93 sig=undefined FUN_004a9564() cc=unknown
// callers: 
// callees: FUN_004a7b5d,__assertfail
// strings: \"XXTYPE.CPP\"|\"((unsigned __far *)vtablePtr)[-1] == 0\"

int FUN_004a9564(int param_1,int param_2,undefined4 param_3,int param_4)

{
  if (param_1 == 0) {
    FUN_004a7b5d(&DAT_004a9a89,&DAT_0069f3b4,0,0,0,0,0,0,0);
  }
  param_2 = param_2 - *(int *)(param_2 + -4);
  if (*(int *)(param_2 + -4) != 0) {
    __assertfail(s___unsigned___far___vtablePtr___1_0051faa4,s_XXTYPE_CPP_0051facb,0x27f);
  }
  *(undefined4 *)(param_4 + 4) = *(undefined4 *)(param_2 + -0xc);
  return param_4;
}

