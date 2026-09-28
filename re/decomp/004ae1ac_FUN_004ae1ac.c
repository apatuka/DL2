// FUN_004ae1ac @ 004ae1ac size=37 sig=undefined FUN_004ae1ac() cc=unknown
// callers: FUN_004af8f4,FUN_004af624
// callees: 

undefined4 FUN_004ae1ac(undefined4 *param_1)

{
  uint uVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar1 = param_1[1];
  uVar3 = 0;
  if (uVar1 != 0) {
    uVar3 = uVar1 % 10;
    param_1[1] = uVar1 / 10;
  }
  uVar2 = *param_1;
  *param_1 = (int)(CONCAT44(uVar3,uVar2) / 10);
  return (int)(CONCAT44(uVar3,uVar2) % 10);
}

