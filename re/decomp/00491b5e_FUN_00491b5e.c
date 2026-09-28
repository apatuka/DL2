// FUN_00491b5e @ 00491b5e size=62 sig=undefined FUN_00491b5e() cc=unknown
// callers: FUN_00492d67,FUN_0049e47a,FUN_0048463c,FUN_00491bf7,FUN_004931b0,FUN_004a57e0,FUN_0049331e
// callees: FUN_00491b46

void FUN_00491b5e(undefined4 *param_1)

{
  int iVar1;
  
  *param_1 = DAT_0065ebf8;
  iVar1 = FUN_00491b46(DAT_0065ebf8);
  *(undefined2 *)(param_1 + 1) = *(undefined2 *)(iVar1 + 0x12);
  *(undefined2 *)((int)param_1 + 6) = *(undefined2 *)(iVar1 + 0x14);
  *(undefined2 *)((int)param_1 + 10) = *(undefined2 *)(iVar1 + 0x16);
  *(undefined2 *)(param_1 + 2) = *(undefined2 *)(iVar1 + 6);
  return;
}

