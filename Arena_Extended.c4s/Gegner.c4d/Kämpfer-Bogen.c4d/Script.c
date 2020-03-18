#strict
#include _PEM

Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  SetLocal(0,0);
  SetLocal(1,3);
  SetEntrance(1);
  SetOwner(-1);
  SetMyColor();
  SetColor(9);
  return(1);

SetMyColor:
  if(GetOwner()==-1)
    SetColorDw(RGBa(255, 255, 255, 0));
  return(1);

Death:
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
  CreateObject(ST58,0,0,GetOwner(this()));
  Sound("Die");
//  SetAction("Dead");
//  ObjectCall(CreateObject(KT3A,0,10, GetOwner()),"Sterb","Bogen");
//  RemoveObject();
  return(1);

Remove:
  RemoveObject();
  return(1);

Activity:
  if(GetAction() S= "Dead") return(DoCon(-1));
  if(Not(SEqual(GetAction(),"Walk"))) return(0);
  while(Var(0)=FindObject(0,0,0,-1,-1,OCF_Prey(),0,0,0,Var(0)))
    if(GetOwner(Var(0))!=GetOwner()) {
      Local(0)=Var(0);
      break;
    }
  if(Local(0)) {
    if(GetX()>GetX(Local(0)))
      SetDir(DIR_Left());
    else
      SetDir(DIR_Right());
    if(Inside(Distance(GetX(),GetY(),GetX(Local(0)),GetY(Local(0))),20,200)) {
      SetAction("AimBow");
    } else {
      if(GetX()<GetX(Local(0)))
        SetCommand(this(),"MoveTo",0, GetX(Local(0)) - 100, GetY(Local(0)));
      else
        SetCommand(this(),"MoveTo",0, GetX(Local(0)) + 100, GetY(Local(0)));
    }
  }
  return(1);

SimulierWerfen:
  // Feuer
  AimTo(GetX(Local(0)),GetY(Local(0)));
  Fire();
  return(1);


public func AimTo(int iX,int iY)
{
  var iAngle;
  // Zielwinkel
  iAngle = Angle(GetX(),GetY(),iX,iY);
  // Bei größerer Distanz höher zielen
  if(Inside(iX-GetX(),+1,+300))
     iAngle -= Abs(iX-GetX())/12;
  if(Inside(iX-GetX(),-300,-1))
     iAngle += Abs(iX-GetX())/12;
  // Winkel anpassen
  while(iAngle > 180) iAngle-=360;
  // Richtung
  if(iAngle > 0) SetDir(DIR_Right());
  if(iAngle < 0) SetDir(DIR_Left());
  // Zielrichtung
  Local(1)=BoundBy( 20*Abs(iAngle)/90, 0,19);
}


public func Fire()
{
  var pArrow=Contents();
  // Pfeil suchen
  if (!pArrow) pArrow=CreateContents(XA3A);

  SetOwner(GetOwner(), pArrow);
  // Austritt berechnen
  var iX = Local(1)*(GetDir()*2-1);
  var iY = Local(1)-15;
  var iR = iX*5;
  var iAngle = BoundBy(Local(1)*5,0,90);
  var iXDir = Sin(iAngle,13*(GetDir()*2-1));
  var iYDir = Cos(iAngle,-13);
  var iRDir = GetDir()*6-3;

  // Pfeil abfeuern
  Exit(pArrow,iX,iY,iR,iXDir,iYDir,iRDir);
  pArrow->~Launch(this());

  // Sound
  Sound("Arrow");
  // Fertig
  return(1);
}

BinIchRedwolfWuerdig:
  if(GreaterThan(GetActTime(this()),59)) SetAction("Walk");
  return(1);



