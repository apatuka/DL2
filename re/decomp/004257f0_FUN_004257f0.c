// FUN_004257f0 @ 004257f0 size=263 sig=undefined FUN_004257f0() cc=unknown
// callers: FUN_0042623c,FUN_00425f58,FUN_00425bc4
// callees: FUN_004a68dc,LoadStringA,FUN_0049eb44

void FUN_004257f0(short *param_1)

{
  CHAR local_1010 [1024];
  undefined1 local_c10 [3084];
  
  local_c10[0] = 0;
  if (*param_1 != 0) {
    LoadStringA(DAT_0058f19c,(int)*param_1,local_1010,0x3ff);
    FUN_004a68dc(local_c10,local_1010);
    FUN_004a68dc(local_c10,&DAT_004b7d12);
  }
  if (param_1[1] != 0) {
    LoadStringA(DAT_0058f19c,(int)param_1[1],local_1010,0x3ff);
    FUN_004a68dc(local_c10,local_1010);
    FUN_004a68dc(local_c10,&DAT_004b7d12);
  }
  LoadStringA(DAT_0058f19c,(int)param_1[2],local_1010,0x3ff);
  FUN_004a68dc(local_c10,local_1010);
  FUN_0049eb44(DAT_004b7ce4,0xe,1,0xf,0,local_c10);
  return;
}

