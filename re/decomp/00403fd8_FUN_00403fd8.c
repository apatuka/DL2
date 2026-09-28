// FUN_00403fd8 @ 00403fd8 size=65 sig=undefined FUN_00403fd8() cc=unknown
// callers: FUN_00407e78,FUN_0040401c
// callees: 

int FUN_00403fd8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != 0) {
    iVar2 = 0;
    piVar3 = (int *)(param_1 + 0x154);
    do {
      iVar1 = *piVar3;
      if (((iVar1 != 0) && (param_2 == *(char *)(iVar1 + 5))) && (*(short *)(iVar1 + 0x14) != 0)) {
        return iVar1;
      }
      iVar2 = iVar2 + 1;
      piVar3 = piVar3 + 0xd;
    } while (iVar2 < 0x24);
  }
  return 0;
}

