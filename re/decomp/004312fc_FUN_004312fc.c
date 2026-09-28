// FUN_004312fc @ 004312fc size=153 sig=undefined FUN_004312fc() cc=unknown
// callers: FUN_0043210c
// callees: FUN_0049eb44,sprintf
// strings: \"%s @ %d credits\"

void FUN_004312fc(void)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined1 local_5c [80];
  
  piVar2 = &DAT_00558de0;
  for (iVar3 = 0; iVar3 < DAT_00558e60; iVar3 = iVar3 + 1) {
    sprintf(local_5c,PTR_s__s____d_credits_00509578,
            *(undefined4 *)((int)&PTR_s_Nothing_004fbbc0 + *piVar2 * 0x32),piVar2[1]);
    iVar1 = FUN_0049eb44(DAT_004c42dc,0x14,1,0x26,0xffffffff,local_5c);
    if (iVar1 != 0) {
      FUN_0049eb44(DAT_004c42dc,0x14,1,0x23,iVar1 + -1,local_5c);
    }
    piVar2 = piVar2 + 2;
  }
  FUN_0049eb44(DAT_004c42dc,0x14,1,0x1b,0,0);
  return;
}

