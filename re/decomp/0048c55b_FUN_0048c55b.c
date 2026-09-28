// FUN_0048c55b @ 0048c55b size=106 sig=undefined FUN_0048c55b() cc=unknown
// callers: FUN_0048c62f
// callees: FUN_0048c2c5,FUN_0048c3f4

void FUN_0048c55b(undefined4 *param_1)

{
  int iVar1;
  ushort *puVar2;
  ushort *puVar3;
  int iVar4;
  
  iVar1 = FUN_0048c2c5(param_1);
  if (iVar1 != 0) {
    puVar3 = (ushort *)*param_1;
    for (iVar1 = param_1[2]; iVar1 != 0; iVar1 = iVar1 + -1) {
      puVar2 = puVar3;
      for (iVar4 = param_1[1]; iVar4 != 0; iVar4 = iVar4 + -1) {
        *puVar2 = *puVar2 * 2 & 0xffc0 | *puVar2 & 0x1f;
        puVar2 = puVar2 + 1;
      }
      puVar3 = (ushort *)((int)puVar3 + param_1[4]);
    }
    *(undefined2 *)((int)param_1 + 0x26) = 3;
    FUN_0048c3f4(param_1);
  }
  return;
}

