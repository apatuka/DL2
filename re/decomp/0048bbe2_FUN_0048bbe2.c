// FUN_0048bbe2 @ 0048bbe2 size=43 sig=undefined FUN_0048bbe2() cc=unknown
// callers: FUN_0048bc0d
// callees: 

int FUN_0048bbe2(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = (uint)*(ushort *)(param_1 + 0xc) * *(int *)(param_1 + 4) *
          (uint)*(ushort *)(param_1 + 0xe);
  iVar2 = iVar1 + 0x1f;
  if (iVar2 < 0) {
    iVar2 = iVar1 + 0x3e;
  }
  return (iVar2 >> 5) << 2;
}

