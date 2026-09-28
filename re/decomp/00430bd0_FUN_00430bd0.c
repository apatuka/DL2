// FUN_00430bd0 @ 00430bd0 size=102 sig=undefined FUN_00430bd0() cc=unknown
// callers: FUN_00431088,CheckSubRes
// callees: FUN_0049eb44,FUN_0043239c,FUN_00431f58

void FUN_00430bd0(void)

{
  char cVar1;
  int *piVar2;
  
  for (piVar2 = &DAT_004c4510; *piVar2 != -1; piVar2 = piVar2 + 1) {
    FUN_0049eb44(DAT_004c42d4,*piVar2,1,10,0,0);
  }
  cVar1 = FUN_00431f58();
  if (cVar1 == '\0') {
    FUN_0049eb44(DAT_004c42d4,0xb,1,10,1,0);
  }
  cVar1 = FUN_0043239c();
  if (cVar1 == '\0') {
    FUN_0049eb44(DAT_004c42d4,0xc,1,10,1,0);
  }
  return;
}

