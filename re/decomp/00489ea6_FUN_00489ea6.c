// FUN_00489ea6 @ 00489ea6 size=79 sig=undefined FUN_00489ea6() cc=unknown
// callers: FUN_004962d6
// callees: FUN_0048bb6c

void FUN_00489ea6(void)

{
  if (DAT_0051b600 != (int *)0x0) {
    (**(code **)(*DAT_0051b600 + 0x48))(DAT_0051b600);
    (**(code **)(*DAT_0051b600 + 8))(DAT_0051b600);
    DAT_0051b600 = (int *)0x0;
  }
  if (DAT_0051b5fc != (int *)0x0) {
    (**(code **)(*DAT_0051b5fc + 8))(DAT_0051b5fc);
    DAT_0051b5fc = (int *)0x0;
    FUN_0048bb6c();
  }
  return;
}

