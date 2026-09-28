// FUN_004171e0 @ 004171e0 size=349 sig=undefined FUN_004171e0() cc=unknown
// callers: FUN_00417340,FUN_004193e0,FUN_0040f060,FUN_00417b60
// callees: 

undefined4 FUN_004171e0(int param_1,int param_2,int param_3)

{
  char cVar1;
  bool bVar2;
  bool bVar3;
  undefined4 uVar4;
  
  cVar1 = (&DAT_004faf87)[*(char *)(param_1 + 6) * 0x24];
  if ((cVar1 != '\x01') || (*(short *)(&DAT_00559fce + param_3 * 2) == 0)) {
    bVar2 = false;
  }
  else {
    bVar2 = true;
  }
  if ((cVar1 != '\x01') || (*(short *)(&DAT_00559fdc + param_3 * 2) == 0)) {
    bVar3 = false;
  }
  else {
    bVar3 = true;
  }
  if (((((param_2 == 1) && (!bVar2)) || ((param_2 == 2 && (!bVar3)))) ||
      ((param_2 == 0x19 ||
       ((cVar1 == '\t' &&
        ((param_2 == 0x1a ||
         ((param_2 != 0x17 && ((1 << (*(byte *)(param_1 + 8) & 0x1f) & (int)DAT_004fc02a) == 0))))))
       )))) || (((param_2 == 4 && ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x03')) ||
                ((((((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] != '\x02' &&
                    ((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] != '\x06')) && (param_2 == 0x15)
                   ) || (param_2 == 0x18)) ||
                 ((((&DAT_004faf8d)[*(char *)(param_1 + 6) * 0x24] == '\x02' &&
                   (((param_2 == 7 || (param_2 == 9)) ||
                    ((((param_2 == 0xb || ((param_2 == 0xc || (param_2 == 0xd)))) ||
                      (param_2 == 0xe)) ||
                     (((param_2 == 0x12 || (param_2 == 0x13)) || (param_2 == 0x14)))))))) ||
                  (param_2 == 0x16)))))))) {
    uVar4 = 0;
  }
  else {
    uVar4 = 1;
  }
  return uVar4;
}

