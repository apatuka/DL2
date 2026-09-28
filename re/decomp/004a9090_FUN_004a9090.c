// FUN_004a9090 @ 004a9090 size=59 sig=undefined FUN_004a9090() cc=unknown
// callers: FUN_004b3028,FUN_004b343c,FUN_004b2fd4,FUN_004b30c8,FUN_004b2f97,FUN_004a78a4,FUN_004b33b0,FUN_004b3208,FUN_004b03bc,FUN_004b335c,FUN_004a86dc,FUN_004a7c1f,FUN_004b2e50,FUN_004a6f28,FUN_004a6f6c,FUN_004b2e1c,FUN_004b32c0,FUN_004b3304,FUN_004a70ca,FUN_004a6dd9,FUN_004a6e64,FUN_004a6ec4,FUN_004b3400,FUN_004a6c88,FUN_004b3168,FUN_004a6fc0,FUN_004b035c,FUN_004a6ccc
// callees: 

void FUN_004a9090(void)

{
  undefined4 *puVar1;
  int in_EAX;
  undefined4 *puVar2;
  int unaff_EBP;
  undefined2 in_FS;
  
  puVar2 = (undefined4 *)(unaff_EBP + *(int *)(in_EAX + 4));
  puVar2[2] = in_EAX;
  puVar2[3] = &stack0x00000004;
  puVar2[1] = &DAT_004a82a4;
  puVar2[4] = 0;
  *(undefined4 *)((int)puVar2 + 0x12) = 0;
  puVar2[7] = 0;
  puVar1 = (undefined4 *)segment(in_FS,0);
  *puVar2 = *puVar1;
  puVar1 = (undefined4 *)segment(in_FS,0);
  *puVar1 = puVar2;
  return;
}

