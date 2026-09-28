// FUN_0045d418 @ 0045d418 size=96 sig=undefined FUN_0045d418() cc=unknown
// callers: FUN_0045d478
// callees: FUN_00449fe8,FUN_0045df90,FUN_0045dfd4,FUN_00449f5c,FUN_0045df3c,FUN_00449fd8,FUN_00449dec

void FUN_0045d418(void)

{
  undefined4 uVar1;
  
  FUN_0045df90();
  uVar1 = DAT_004c5b50;
  (&DAT_005a43ec)[DAT_00583d88 * 0x2b7] = (&DAT_005a43ec)[DAT_00583d88 * 0x2b7] | 1;
  FUN_0045dfd4(DAT_00583d88,1);
  FUN_0045df3c(uVar1);
  FUN_0045df3c(DAT_004c5b50);
  FUN_00449fd8();
  FUN_00449fe8();
  FUN_00449dec();
  FUN_00449f5c();
  return;
}

