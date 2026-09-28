// FUN_0048300c @ 0048300c size=42 sig=undefined FUN_0048300c() cc=unknown
// callers: FUN_0048307c,LoadPhaseSpriteFile
// callees: 

int FUN_0048300c(int param_1)

{
  int iVar1;
  
  iVar1 = 0;
  for (; *(short *)(param_1 + 4) != 0; param_1 = param_1 + 0x10) {
    iVar1 = iVar1 + (int)*(short *)(param_1 + 4) * (int)*(short *)(param_1 + 6);
  }
  return iVar1;
}

