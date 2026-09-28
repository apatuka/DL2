// FUN_004067b4 @ 004067b4 size=26 sig=undefined FUN_004067b4() cc=unknown
// callers: FUN_004068f8,FUN_004067d0
// callees: 

void FUN_004067b4(void)

{
  undefined2 *puVar1;
  
  for (puVar1 = &DAT_005f0410; puVar1 < &DAT_00645370; puVar1 = puVar1 + 0x91) {
    puVar1[1] = puVar1[1] & 0xdfff;
  }
  return;
}

