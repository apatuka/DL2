// FUN_004a42f0 @ 004a42f0 size=234 sig=undefined FUN_004a42f0() cc=unknown
// callers: FUN_004a43da
// callees: FUN_0049eb44,FUN_0049ea99,sprintf,FUN_004a18c5,FUN_004a18a9

void FUN_004a42f0(int param_1,int param_2,uint param_3)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  undefined1 local_24 [32];
  
  FUN_004a18a9(param_1 + 0x34);
  if ((param_3 & 4) == 0) {
    if ((param_3 & 1) == 0) {
      sprintf(local_24,&DAT_0051e4e4,param_2);
    }
    else if ((param_2 < 1) && (((param_3 & 3) == 0 || (param_2 != 0)))) {
      sprintf(local_24,&DAT_0051e4e1,param_2);
    }
    else {
      sprintf(local_24,&DAT_0051e4dd,param_2);
    }
  }
  else if ((param_2 == 0) && ((param_3 & 3) == 0)) {
    sprintf(local_24,&DAT_0051e4d9,0);
  }
  else {
    sprintf(local_24,&DAT_0051e4d4,param_2);
  }
  uVar1 = FUN_004a18c5(local_24,0);
  *(undefined4 *)(param_1 + 0x34) = uVar1;
  uVar6 = 0;
  uVar5 = 3;
  uVar4 = 0x1c;
  uVar3 = 2;
  iVar2 = param_1;
  uVar1 = FUN_0049ea99(param_1);
  FUN_0049eb44(uVar1,iVar2,uVar3,uVar4,uVar5,uVar6);
  uVar6 = 0;
  uVar5 = 0;
  uVar4 = 8;
  uVar3 = 2;
  uVar1 = FUN_0049ea99(param_1);
  FUN_0049eb44(uVar1,param_1,uVar3,uVar4,uVar5,uVar6);
  return;
}

