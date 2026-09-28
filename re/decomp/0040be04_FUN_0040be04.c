// FUN_0040be04 @ 0040be04 size=175 sig=undefined FUN_0040be04() cc=unknown
// callers: FUN_00409544,FUN_00401ac0,FUN_0040a898,FUN_0040c018,FUN_0040a524,FUN_0040f974,FUN_0040a710,FUN_004096a8,FUN_00403f5c,FUN_0040aaa4,FUN_0040effc,FUN_0040f2e0,FUN_00409b58
// callees: FUN_0040ad88,memset,FUN_004100e0,FUN_0044fe1c

int * FUN_0040be04(int param_1,undefined2 param_2,undefined2 param_3,undefined4 param_4,int param_5,
                  undefined4 param_6)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  
  iVar1 = FUN_0044fe1c(7);
  if ((iVar1 == 0) || ((param_5 != 0x12 && (param_5 != 0x11)))) {
    if (param_5 == 1) {
      iVar1 = 0;
    }
    else {
      iVar1 = FUN_0040ad88(param_1);
    }
    if (iVar1 == -1) {
      piVar2 = (int *)0x0;
    }
    else {
      iVar3 = param_1 * 0x2648 + iVar1 * 0xc4;
      piVar2 = (int *)(&DAT_00522584 + iVar3);
      memset(piVar2,0,0xc4);
      *(undefined2 *)(&DAT_0052258c + iVar3) = param_3;
      *piVar2 = param_5;
      *(undefined2 *)(&DAT_00522590 + iVar3) = param_2;
      (&DAT_00522594)[iVar1 * 0x31 + param_1 * 0x992] = param_4;
      *(undefined2 *)(&DAT_00522592 + iVar3) = (undefined2)param_6;
      *(undefined2 *)(&DAT_0052258e + iVar3) = (undefined2)param_1;
      FUN_004100e0(param_1,1,param_6,iVar1,1);
    }
  }
  else {
    piVar2 = (int *)0x0;
  }
  return piVar2;
}

