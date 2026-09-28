// FUN_004455fc @ 004455fc size=157 sig=undefined FUN_004455fc() cc=unknown
// callers: ReLinkArmy,FUN_00445710,FUN_0046c7d4,FUN_0044577c,DeleteArmy
// callees: 

void FUN_004455fc(void)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  
  if ((((DAT_004c515c == (undefined4 *)0x0) || (DAT_004c515c < &DAT_00645370)) ||
      ((undefined4 *)0x651caf < DAT_004c515c)) ||
     (((uint)(DAT_004c515c + -0x1914dc) % 0x5c != 0 || (*(char *)((int)DAT_004c515c + 6) != '\0'))))
  {
    for (puVar1 = (undefined4 *)&DAT_00645370;
        (puVar1 < &DAT_00651cb0 && (*(char *)((int)puVar1 + 6) != '\0')); puVar1 = puVar1 + 0x17) {
    }
    puVar2 = puVar1;
    DAT_004c515c = puVar1;
    if (puVar1 == &DAT_00651cb0) {
      DAT_004c515c = (undefined4 *)0x0;
    }
    else {
      for (; puVar1 < &DAT_00651cb0; puVar1 = puVar1 + 0x17) {
        if (*(char *)((int)puVar1 + 6) == '\0') {
          puVar2[0x15] = puVar1;
          puVar1[0x16] = puVar2;
          puVar2 = puVar1;
        }
      }
      puVar2[0x15] = 0;
      DAT_004c515c[0x16] = 0;
    }
  }
  return;
}

