// FUN_00430ba8 @ 00430ba8 size=40 sig=undefined FUN_00430ba8() cc=unknown
// callers: FUN_00431088
// callees: FUN_0049eb44

void FUN_00430ba8(void)

{
  int *piVar1;
  
  for (piVar1 = &DAT_004c4510; *piVar1 != -1; piVar1 = piVar1 + 1) {
    FUN_0049eb44(DAT_004c42d4,*piVar1,1,10,1,0);
  }
  return;
}

