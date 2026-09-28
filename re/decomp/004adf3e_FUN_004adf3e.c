// FUN_004adf3e @ 004adf3e size=78 sig=undefined FUN_004adf3e() cc=unknown
// callers: FUN_004ae0f8
// callees: 

undefined8 FUN_004adf3e(uint param_1,uint param_2)

{
  int in_EAX;
  int iVar1;
  uint in_EDX;
  uint uVar2;
  uint uVar3;
  bool bVar4;
  bool bVar5;
  
  if ((param_2 == 0) && ((in_EDX == 0 || (param_1 == 0)))) {
    uVar2 = (uint)(CONCAT44(in_EDX,in_EAX) % (ulonglong)param_1);
    uVar3 = 0;
  }
  else {
    iVar1 = 0x40;
    uVar3 = 0;
    uVar2 = 0;
    do {
      bVar4 = in_EAX < 0;
      in_EAX = in_EAX * 2;
      bVar5 = (int)in_EDX < 0;
      in_EDX = in_EDX << 1 | (uint)bVar4;
      bVar4 = (int)uVar2 < 0;
      uVar2 = uVar2 << 1 | (uint)bVar5;
      uVar3 = uVar3 << 1 | (uint)bVar4;
      if ((param_2 <= uVar3) && ((param_2 < uVar3 || (param_1 <= uVar2)))) {
        bVar4 = uVar2 < param_1;
        uVar2 = uVar2 - param_1;
        uVar3 = (uVar3 - param_2) - (uint)bVar4;
        in_EAX = in_EAX + 1;
      }
      iVar1 = iVar1 + -1;
    } while (iVar1 != 0);
  }
  return CONCAT44(uVar3,uVar2);
}

