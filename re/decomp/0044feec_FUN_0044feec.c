// FUN_0044feec @ 0044feec size=57 sig=undefined FUN_0044feec() cc=unknown
// callers: FUN_00407d60,FUN_0041acf8
// callees: FUN_0044fe1c

undefined4 FUN_0044feec(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = FUN_0044fe1c(7);
  if ((iVar1 == 0) ||
     ((((param_1 != 0x1a && (param_1 != 0x1b)) && (param_1 != 0x1e)) &&
      ((param_1 != 0x21 && (param_1 != 0x22)))))) {
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

