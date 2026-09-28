// FUN_0048bb6c @ 0048bb6c size=18 sig=undefined FUN_0048bb6c() cc=unknown
// callers: FUN_00489ea6,FUN_00489c98
// callees: CoUninitialize

void FUN_0048bb6c(void)

{
  DAT_0051bdd4 = DAT_0051bdd4 + -1;
  if (DAT_0051bdd4 == 0) {
    CoUninitialize();
  }
  return;
}

