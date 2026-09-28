// FUN_00447a40 @ 00447a40 size=38 sig=undefined FUN_00447a40() cc=unknown
// callers: FUN_00484fa0,FUN_00448118,FUN_004474b0,FUN_00418704,FUN_00431e58,FUN_004851ec,FUN_0045940c,FUN_0040febc,FUN_0044f2fc
// callees: 

undefined4 FUN_00447a40(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 < 100) {
    uVar1 = 0;
  }
  else if (param_1 < 0x191) {
    uVar1 = 1;
  }
  else {
    uVar1 = 2;
  }
  return uVar1;
}

