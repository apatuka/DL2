// FUN_004227f0 @ 004227f0 size=129 sig=undefined FUN_004227f0() cc=unknown
// callers: FUN_00422bd8
// callees: sprintf,FUN_004227b4,FUN_0049eb44

void FUN_004227f0(void)

{
  undefined *puVar1;
  undefined1 local_3ec [1000];
  
  FUN_004227b4();
  for (puVar1 = &DAT_0053c4e0; puVar1[DAT_004b7b44 * 0x4802 + 4] == '\x01'; puVar1 = puVar1 + 6) {
    sprintf(local_3ec,&DAT_004b7bb2,(&DAT_00651cb8)[*(int *)(puVar1 + DAT_004b7b44 * 0x4802) * 5]);
    FUN_0049eb44(DAT_004b7b50,0xe,1,0x26,0xffffffff,local_3ec);
  }
  FUN_0049eb44(DAT_004b7b50,0xf,1,0x31,0xe,1);
  return;
}

