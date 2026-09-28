// FUN_00496c61 @ 00496c61 size=98 sig=undefined FUN_00496c61() cc=unknown
// callers: FUN_0049fca2,FUN_0049d7f4,FUN_0049efae,FUN_00458d80,FUN_00459864,FUN_0047fffc,FUN_0049fd2e,FUN_004a1eb4,FUN_0049fe03
// callees: FUN_00496c03,FUN_00490ab3

undefined4
FUN_00496c61(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,undefined4 param_5
            ,undefined4 param_6,undefined4 param_7,uint *param_8)

{
  uint uVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  uVar1 = FUN_00496c03(param_1,param_2,param_3,param_4,param_5,param_6,param_7);
  if ((uVar1 != 0xffffffff) && ((uVar1 & 0x10000000) == 0)) {
    uVar2 = FUN_00490ab3(*(undefined4 *)(param_1 + 0xc),0x454c4954,uVar1 & 0xffffff,0,0);
    if (param_8 != (uint *)0x0) {
      *param_8 = uVar1;
    }
  }
  return uVar2;
}

