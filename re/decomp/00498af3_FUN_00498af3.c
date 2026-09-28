// FUN_00498af3 @ 00498af3 size=80 sig=undefined FUN_00498af3() cc=unknown
// callers: FUN_004a5699
// callees: GlobalFlags,GlobalReAlloc

void FUN_00498af3(HGLOBAL param_1,int param_2)

{
  UINT UVar1;
  uint uVar2;
  
  UVar1 = GlobalFlags(param_1);
  if (((UVar1 & 0x100) != 0) != (param_2 != 0)) {
    uVar2 = 0x100;
    if (param_2 == 0) {
      uVar2 = 0;
    }
    GlobalReAlloc(param_1,0,uVar2 | 0x80);
  }
  return;
}

