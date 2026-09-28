// FUN_004652a8 @ 004652a8 size=79 sig=undefined FUN_004652a8() cc=unknown
// callers: 
// callees: thunk_FUN_0045792c,SelectObject

void FUN_004652a8(undefined4 param_1,HGDIOBJ param_2,undefined4 param_3,undefined4 param_4,
                 undefined4 param_5,undefined4 param_6)

{
  HGDIOBJ h;
  
  h = SelectObject(DAT_0058f1b0,param_2);
  thunk_FUN_0045792c(param_1,param_3,param_4,param_5,param_6,DAT_0058f1b0,0,0,0xcc0020);
  SelectObject(DAT_0058f1b0,h);
  return;
}

