// FUN_00421828 @ 00421828 size=77 sig=undefined FUN_00421828() cc=unknown
// callers: FUN_0045d478
// callees: FUN_004483d0,FUN_0045e274,FUN_0041fd38,FUN_0041ff24,FUN_00420734,FUN_004217f4

bool FUN_00421828(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  char cVar1;
  
  cVar1 = FUN_004217f4(param_1);
  if (cVar1 != '\0') {
    FUN_0045e274(param_2,param_3);
    FUN_004483d0(param_1);
    DAT_0053b8b8 = param_1;
    FUN_00420734();
    FUN_0041fd38(DAT_0053b8ac,0);
    FUN_0041ff24();
  }
  return cVar1 != '\0';
}

