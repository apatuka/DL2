// FUN_004a903a @ 004a903a size=84 sig=undefined FUN_004a903a() cc=unknown
// callers: 
// callees: FUN_004a6a94
// strings: \"**BCCxh1\"

uint FUN_004a903a(int param_1)

{
  int iVar1;
  
  if (param_1 == -1) {
    return 0xffffffff;
  }
  if (**(short **)(param_1 + 4) == 0x25ff) {
    iVar1 = **(int **)(*(int *)(param_1 + 4) + 2);
  }
  else {
    iVar1 = *(int *)(param_1 + 4);
  }
  iVar1 = FUN_004a6a94(iVar1 + -8,s___BCCxh1_0051f9b8,8);
  if (iVar1 != 0) {
    return 0xffffffff;
  }
  return (uint)*(ushort *)(param_1 + 0x10);
}

