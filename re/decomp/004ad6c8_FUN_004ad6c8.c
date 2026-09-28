// FUN_004ad6c8 @ 004ad6c8 size=160 sig=undefined FUN_004ad6c8() cc=unknown
// callers: 
// callees: GetDateFormatA

int FUN_004ad6c8(LPSTR param_1,int param_2,WORD *param_3)

{
  int iVar1;
  SYSTEMTIME local_14;
  
  local_14.wYear = param_3[10] + 0x76c;
  local_14.wMonth = param_3[8];
  local_14.wDayOfWeek = param_3[0xc];
  local_14.wDay = param_3[6];
  local_14.wHour = param_3[4];
  local_14.wMinute = param_3[2];
  local_14.wSecond = *param_3;
  local_14.wMilliseconds = 0;
  iVar1 = GetDateFormatA(*(LCID *)(PTR_DAT_00520d10 + 4),4,&local_14,&DAT_00520bd0,param_1,0);
  if (iVar1 <= param_2) {
    GetDateFormatA(*(LCID *)(PTR_DAT_00520d10 + 4),4,&local_14,&DAT_00520bd3,param_1,param_2);
    iVar1 = 0;
  }
  return iVar1;
}

