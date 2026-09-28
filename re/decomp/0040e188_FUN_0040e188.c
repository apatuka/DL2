// FUN_0040e188 @ 0040e188 size=115 sig=undefined FUN_0040e188() cc=unknown
// callers: 
// callees: 

bool FUN_0040e188(int param_1,int param_2)

{
  uint uVar1;
  uint uVar2;
  bool bVar3;
  
  if (param_2 == -1) {
    bVar3 = false;
  }
  else if (param_2 == *(char *)(param_1 + 0x9b4)) {
    bVar3 = true;
  }
  else {
    uVar2 = (uint)*(short *)(param_1 + 0x1a);
    uVar1 = uVar2;
    if ((int)uVar2 < 0) {
      uVar1 = uVar2 + 0xf;
    }
    uVar2 = uVar2 & 0x8000000f;
    if ((int)uVar2 < 0) {
      uVar2 = (uVar2 - 1 | 0xfffffff0) + 1;
    }
    bVar3 = ((int)*(short *)(&DAT_0055dc86 + ((int)uVar1 >> 4) * 2 + param_2 * 0x7a) &
            1 << ((byte)uVar2 & 0x1f)) != 0;
  }
  return bVar3;
}

