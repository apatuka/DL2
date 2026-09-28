// FUN_00491b46 @ 00491b46 size=24 sig=undefined FUN_00491b46() cc=unknown
// callers: FUN_00491b5e,FUN_00491bf7
// callees: 

ushort * FUN_00491b46(byte *param_1)

{
  return (ushort *)((int)(param_1 + *param_1 + 1) + (uint)*(ushort *)(param_1 + *param_1 + 1) * 2);
}

