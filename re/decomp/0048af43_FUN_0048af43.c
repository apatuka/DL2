// FUN_0048af43 @ 0048af43 size=117 sig=undefined FUN_0048af43() cc=unknown
// callers: FUN_0048afb8,FUN_0046ff98,FUN_0048ba34
// callees: 

void FUN_0048af43(void)

{
  if (DAT_0051b810 != (int *)0x0) {
    if (DAT_0051b814 != (int *)0x0) {
      (**(code **)(*DAT_0051b814 + 8))(DAT_0051b814);
      DAT_0051b814 = (int *)0x0;
    }
    if (DAT_0051b81c != (int *)0x0) {
      (**(code **)(*DAT_0051b81c + 8))(DAT_0051b81c);
      DAT_0051b81c = (int *)0x0;
    }
    if (DAT_0051b820 != (int *)0x0) {
      (**(code **)(*DAT_0051b820 + 8))(DAT_0051b820);
      DAT_0051b820 = (int *)0x0;
    }
    (**(code **)(*DAT_0051b810 + 8))(DAT_0051b810);
    DAT_0051b810 = (int *)0x0;
  }
  return;
}

