// FUN_0048d165 @ 0048d165 size=61 sig=undefined FUN_0048d165() cc=unknown
// callers: 
// callees: 

bool FUN_0048d165(int param_1)

{
  bool bVar1;
  undefined4 local_70 [26];
  uint local_8;
  
  if (*(short *)(param_1 + 0x2a) == 0) {
    local_70[0] = 0x6c;
    (**(code **)(**(int **)(param_1 + 0x40) + 0x58))(*(int **)(param_1 + 0x40),local_70);
    bVar1 = (local_8 & 0x800) == 0;
  }
  else {
    bVar1 = false;
  }
  return bVar1;
}

