#strict

global func DoEnergy(int iAmount, object pObj, bool bOtherCause, int iCause) {
  if(bOtherCause)
    Var(0)=ObjectCall(pObj, "Damaged", -iAmount, iCause);
  else
    Var(0)=ObjectCall(pObj, "Damaged", -iAmount, GetOwner());
  return(inherited(iAmount, pObj));
}

global func Punch (object pObj, int iX, bool bOtherCause, int iCause) {
  if(bOtherCause)
    Var(0)=ObjectCall(pObj, "Damaged", iX, iCause);
  else
    Var(0)=ObjectCall(pObj, "Damaged", iX, GetOwner());
  return(inherited(pObj, iX));
}