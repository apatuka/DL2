// FUN_004adde0 @ 004adde0 size=35 sig=undefined FUN_004adde0() cc=unknown
// callers: FUN_004ab1a0
// callees: 

undefined8 FUN_004adde0(uint param_1,int param_2)

{
  uint in_EAX;
  int in_EDX;
  
  return CONCAT44((int)((ulonglong)in_EAX * (ulonglong)param_1 >> 0x20) +
                  param_2 * in_EAX + in_EDX * param_1,(int)((ulonglong)in_EAX * (ulonglong)param_1))
  ;
}

