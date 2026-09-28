// FUN_0047d930 @ 0047d930 size=87 sig=undefined FUN_0047d930() cc=unknown
// callers: FUN_0047da24
// callees: 

bool FUN_0047d930(int *param_1,int *param_2)

{
  bool bVar1;
  
  bVar1 = DAT_00655044 != DAT_00655048;
  if (bVar1) {
    *param_1 = (int)*(short *)(&DAT_0065504c + DAT_00655044 * 4);
    *param_2 = (int)*(short *)(&DAT_0065504e + DAT_00655044 * 4);
    DAT_00655044 = (DAT_00655044 + 1) % 0xa0;
  }
  return bVar1;
}

