// FUN_00406424 @ 00406424 size=124 sig=undefined FUN_00406424() cc=unknown
// callers: FUN_00407e78,FUN_0040854c,FUN_004105e8,FUN_004068f8,FUN_004067d0,FUN_0041026c
// callees: FUN_0044c754,FUN_00476448,FUN_004063c0,FUN_0046b0e4

undefined4 FUN_00406424(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar1 = FUN_0044c754(param_2);
  if (iVar1 == 0) {
    iVar1 = FUN_004063c0(param_1,param_2,&DAT_00521bb4);
    if ((((iVar1 != 0) && (iVar3 = FUN_0046b0e4(param_2), *(short *)(param_2 + 0x30) + 100 <= iVar3)
         ) && (0x18 < (int)(&DAT_0059f16c)[param_1 * 0xb6])) &&
       (iVar1 = FUN_00476448(iVar1,param_2,100,0,0xffffffff,0xffffffff), iVar1 != 0)) {
      return 1;
    }
    uVar2 = 0;
  }
  else {
    uVar2 = 1;
  }
  return uVar2;
}

