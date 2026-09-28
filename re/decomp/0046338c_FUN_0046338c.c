// FUN_0046338c @ 0046338c size=248 sig=undefined FUN_0046338c() cc=unknown
// callers: FUN_004634a0,FUN_004618e8
// callees: memcpy,FUN_00463a74

void FUN_0046338c(void)

{
  switch(DAT_004d5b1c) {
  case 0:
    memcpy(&DAT_0051a8e4,&DAT_00519ecc,0x100);
    break;
  case 1:
    memcpy(&DAT_0051a8e4,&DAT_00519fcc,0x100);
    break;
  case 2:
    memcpy(&DAT_0051a8e4,&DAT_0051a0cc,0x100);
    break;
  case 3:
    memcpy(&DAT_0051a8e4,&DAT_0051a1cc,0x100);
    break;
  case 4:
    memcpy(&DAT_0051a8e4,&DAT_0051a2cc,0x100);
    break;
  case 5:
    memcpy(&DAT_0051a8e4,&DAT_0051a3cc,0x100);
    break;
  case 6:
    memcpy(&DAT_0051a8e4,&DAT_0051a4cc,0x100);
  }
  memcpy(&DAT_0051a8cc,&DAT_0051a5cc,0x18);
  memcpy(&DAT_0051aae4,&DAT_0051a5e4,0x1c0);
  FUN_00463a74();
  return;
}

