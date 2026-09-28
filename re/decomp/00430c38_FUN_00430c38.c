// FUN_00430c38 @ 00430c38 size=158 sig=undefined FUN_00430c38() cc=unknown
// callers: FUN_00431088,FUN_00435ed0,FUN_00431128,FUN_00430cd8
// callees: FUN_004152ec,FUN_0049eb44,FUN_00432d30

void FUN_00430c38(void)

{
  undefined4 uVar1;
  undefined4 local_10;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  if (DAT_004c42e4 == 0) {
    local_c = 7;
    local_10 = 10;
    local_4 = 0xcf;
    local_8 = 0xd2;
    uVar1 = DAT_004c42d4;
    if (((DAT_00558d58 != 0) && (uVar1 = DAT_004c42d8, DAT_00558d58 != 1)) &&
       (uVar1 = DAT_004c42dc, DAT_00558d58 != 2)) {
      uVar1 = DAT_004c42e0;
    }
    FUN_0049eb44(uVar1,0xd,1,0xd,0,&local_10);
    FUN_004152ec();
    FUN_00432d30();
    DAT_004c42ec = 1;
  }
  return;
}

