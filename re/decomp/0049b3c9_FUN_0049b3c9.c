// FUN_0049b3c9 @ 0049b3c9 size=77 sig=undefined FUN_0049b3c9() cc=unknown
// callers: FUN_00464444,FUN_0047e0e8,FUN_0043c78c,FUN_00463e20,FUN_00463ee0,FUN_00463e88,FUN_00414bd8,FUN_00464620,FUN_0047eed8
// callees: 

ushort FUN_0049b3c9(int param_1,int param_2)

{
  int iVar1;
  ushort uVar2;
  
  if ((*(byte *)(param_1 + 6) & 0xf) == 0) {
    iVar1 = param_1 + 8 + param_2 * 4;
    uVar2 = (*(byte *)(iVar1 + 1) & 3) << 8 | (ushort)*(byte *)(iVar1 + 2);
  }
  else {
    uVar2 = *(ushort *)(param_1 + 8 + param_2 * 2);
  }
  return uVar2;
}

