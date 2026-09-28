// FUN_0044b5bc @ 0044b5bc size=73 sig=undefined FUN_0044b5bc() cc=unknown
// callers: FUN_0044b620,FUN_00405b38,ProduceUnits,FUN_0044df94,FUN_0040f6b0,FUN_004488c8,FUN_0044e0a8,FUN_0040f658,FUN_0040f8cc,FUN_00420d34,FUN_0041ffd4
// callees: 

undefined4 FUN_0044b5bc(int param_1,undefined4 param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_1 != 0) {
    switch(param_2) {
    default:
      uVar1 = 0;
      break;
    case 1:
      uVar1 = *(undefined4 *)(param_1 + 0x99a);
      break;
    case 2:
      uVar1 = *(undefined4 *)(param_1 + 0x99e);
      break;
    case 3:
      uVar1 = *(undefined4 *)(param_1 + 0x9a2);
      break;
    case 4:
      uVar1 = *(undefined4 *)(param_1 + 0x9a6);
      break;
    case 5:
      uVar1 = *(undefined4 *)(param_1 + 0x9aa);
    }
  }
  return uVar1;
}

