// FUN_0045dfd4 @ 0045dfd4 size=223 sig=undefined FUN_0045dfd4() cc=unknown
// callers: FUN_0045e274,FUN_0045d418,FUN_0045e8e8,FUN_00419c08,FUN_0045e99c,FUN_0045d984,FUN_00449d54,FUN_0045d6a4,FUN_0045dd18
// callees: FUN_00449fe8,FUN_0045df90,FUN_0043ba98,FUN_00449f5c,FUN_00472fb4,FUN_00449fd8,FUN_00449dec

void FUN_0045dfd4(int param_1,int param_2)

{
  bool bVar1;
  int iVar2;
  
  bVar1 = false;
  if (param_1 != DAT_004c5b50) {
    FUN_0045df90();
    bVar1 = true;
    (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] = (&DAT_005a43ec)[DAT_004c5b50 * 0x2b7] & 0xfffffffe;
    DAT_004c5b50 = param_1;
    (&DAT_005a43ec)[param_1 * 0x2b7] = (&DAT_005a43ec)[param_1 * 0x2b7] | 1;
    if (((DAT_004d5aa0 != '\0') &&
        (iVar2 = (int)(char)(&DAT_005a43f0)[param_1 * 0xadc], iVar2 != DAT_0058f1f4)) &&
       (iVar2 != -1)) {
      FUN_00472fb4(iVar2);
    }
  }
  if ((bVar1) || (param_2 != 0)) {
    FUN_00449fd8();
    FUN_00449fe8();
    FUN_00449dec();
    FUN_00449f5c();
    FUN_0043ba98();
  }
  return;
}

