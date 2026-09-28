// FUN_00482c8c @ 00482c8c size=85 sig=undefined FUN_00482c8c() cc=unknown
// callers: FUN_00482b38
// callees: FUN_0046ca40

undefined4 FUN_00482c8c(void)

{
  int in_EAX;
  uint uVar1;
  
  if (DAT_00657e2c == 2) {
    uVar1 = FUN_0046ca40();
    in_EAX = (char)PTR_DAT_004d5988[2] * 3;
    if (uVar1 % 10 < 9) {
      if (5 < uVar1 % 10) {
        in_EAX = in_EAX + 1;
      }
    }
    else {
      in_EAX = in_EAX + 2;
    }
  }
  else if (DAT_00657e2c == 3) {
    uVar1 = FUN_0046ca40();
    in_EAX = uVar1 % 3 + 0x15;
  }
  return *(undefined4 *)(&DAT_004dceec + in_EAX * 4);
}

