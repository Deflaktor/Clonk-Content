/* Mini KI */

#strict
#include CLON
#include _PEM

local alpha,GoTo,NoWalk,throwdelay,weap,On2Throw,result,enemyx,enemyy,projectile,target,randomSign,graber,zorn;

Throwdelay:
  return(6);
  
SetWeapID:
  weap = Par(0);
  return(1);
  
ExplodeKamikaze:
  // We got killed by someone specific?
  if(died == 2) {
    CreateObject(PRNT,0,3,killedBy)->Explode(30);
	CreateObject(PRNT,0,3,killedBy)->Explode(30);
  } else {
    Explode(30,CreateObject(PRNT,0,3));
    Explode(30,CreateObject(PRNT,0,3));
  }
  return(1);
 
ExplodeDistance:
  return(16);

// Munitions ID
WeapID: 
  if(weap==P57M) { 
    ChangeDef(KIL2);
	this()->Initialize();
	this()->SetWeapID(P57M);
  }
  if(weap) return(weap);
  return(FLNT);

CheckKamikaze:
  if(weap == KAZE)
  {
    SetAction("KamikazeWalk");
    return(1);
  }
  //ResetPhysical();
  return(1);
CheckKamikazeExplode:
  if(weap == KAZE)
  {
    Kill();
  }
  return(1);

Throwing:/*
  while(Var(3) = FindObject( GetID(), GetX(target)-GetX()-20, GetY(target)-GetY()-30, 40, 60, OCF_Alive(),0,0, NoContainer(),Var(3)))
    if(!Comes2Me(Var(3)))
    {
      if(projectile)
        RemoveObject(projectile);
      SetAction("Walk");
      SetComDir(COMD_Stop());
      return(1);
    }
  Var(3) = 0;
  while(Var(3) = FindObject( GetID(), -100+GetDir()*120, -30, 80, 60, OCF_Alive(),0,0, NoContainer(),Var(3)))
  {
    if(projectile)
      RemoveObject(projectile);
    SetAction("Walk");
    SetComDir(COMD_Stop());
    return(1);
  }*/
  if(projectile) {
    ObjectCall(projectile,"Check");
    ObjectCall(projectile,"ActivateBomb");
  }
  return(1);
    
Initialize:
  SetAction("Walk");
  SetDir(Random(2));
  Local(0)=Local(1)=0;
  // Farben machen Fröhlich!
  SetRandomColor();
  weap=GameCall("Zufallsflint");
  SetOwner(-1);
  randomSign = -1;
  if(Random(2))
    randomSign = 1;
  // Graber sind selten
  // if(!Random(20))
  graber = true;
  return(0);

Activity:
  var objangle, moveangle, sign, i;
  if(!GetAlive() || GetID(Contained())==_WPT) return(0);
  if(throwdelay>0) throwdelay--;
  if(!Contents())
    if(WeapID() != KAZE)
      projectile = SetVar(6,CreateContents(WeapID()));

  // Türen aufrufen
  if(Var(0) = FindObject(_DR1, -20,-20,40,40))
    ObjectCall(Var(0),"CheckArea");
/*
if(GBackSolid(-5,0))  DigFree(GetX(this()),GetY(this()),13);
if(GBackSolid(5,0))   DigFree(GetX(this()),GetY(this()),13);
if(GBackSolid(0,0))   DigFree(GetX(this()),GetY(this()),13);*/

  // Kamfmodus wenn Clonk in der Nähe
  if(WeapID()==KAZE)
    if(!IsFighting() && !Contained() && GetAction()ne"Tumble")
    while(Var(0)=FindObject(0,-8,-10,16,20,
OCF_CrewMember(),0,0,NoContainer(),Var(0)))
      if(GetOwner(Var(0))!=GetOwner() && !IsFighting(Var(0)) &&  GetAction(Var(0))ne"Tumble")
      {
	      Kill();
      }

  // Fliegenden Objekten ausweichen  
  while(Var(0)=FindObject(0,-30,-50,60,100,OCF_HitSpeed2(),0,0,NoContainer(),Var(0)))
    if(GetCategory(Var(0)) & C4D_Object())
    {
      objangle = ObjectsAngle(Var(0));
      moveangle = ObjAngle( GetX(Var(0))+GetXDir(Var(0)),GetY(Var(0))+GetYDir(Var(0)),Var(0) );
      if(Inside(Abs(objangle-moveangle),135,225))
      {
        if((GetXDir(Var(0))**2 + GetYDir(Var(0))**2) >= 50)
          for(i=0; i<2; i++)
          {
	    if(!sign)
	      if(!(sign = GetSign(GetX()-GetX(Var(0)))))
		sign = 1-Random(2)*2;
            if(ObjPathFree( GetX()+25*sign,GetY()-20 ))
            {
              SetCommand(this(),"Jump",0,GetXDir(Var(0)));
              if(GetX() > GetX(Var(0))) return(SetComDir(COMD_Right()));
              return(SetComDir(COMD_Left()));
            }
            if(ObjPathFree( GetX()+30*sign,GetY() ))
              return(AddCommand(this(),"MoveTo",0,GetX()+30*sign,GetY()));
            sign *= -1;
          }
      }
    }
  // über Brennendes springen
  if(!OnFire() && GetAction() ne "Jump")
    if(Var(0)=FindObject(0,-40*!GetDir(),-40,40,80,OCF_OnFire(),0,0,NoContainer()))
    {
      if(GetDir()) SetComDir(COMD_Left());
	else SetComDir(COMD_Right());
      return(AddCommand(this(),"Jump"));
    }
  // über Minen und T-Flints springen
  if(GetAction() ne "Jump")
    while(Var(1)=FindObject(0,-20,-10,40,20,OCF_Collectible(),0,0,NoContainer(),Var(1)))
      if(GetDefCoreVal("Explosive","DefCore",GetID(Var(1))) && GetAction(Var(1)) S= "Activated")
        if(Abs(GetX()-GetX(Var(1))) > Abs(GetX()-GetX(Var(1))+GetXDir()))
          return(AddCommand(this(),"Jump"));
  // Zeugs anwerfen
  Var(1)=0;
  if(!IsFighting() && throwdelay<1) {
    if(Var(1)=FindObject(MNTK)) {
      if(Var(1)=Var(1)->GetCurrentGod()) {
	    if(GetOwner()!=GetOwner(Var(1))) 
          AttackEnemy(Var(1));
		else
		  Var(1)=0;
      }
    }
    if(!Var(1))
    while(Var(0)=FindObject(0,0,0,-1,-1,OCF_CrewMember(),0,0,0,Var(0))) {
      if((zorn>10||GetOwner(Var(0))!=GetOwner()) && InsideX(GetX(Var(0)),GetX(Local(0)),GetX(Local(1)))) {
        if(Global(75+GetOwner(Var(0))))
          Global(75+GetOwner(Var(0)))--;
        else
        if(GetPathLength( GetX(), GetY(), GetX(Var()), GetY(Var()))) {
          AttackEnemy(Var(0));
          break;
        } else if(AttackEnemyInEarth(Var(0))) {
          break;
        } else {
          Global(75+GetOwner(Var(0))) = 30;
        }
      }
    }
  }
  
  if(Local(0) && !Local(1) && !GetCommand() && Abs(GetX()-GetX(Local(0)))>8 )  return(SetCommand(this(),"MoveTo",Local(0)));
  if((!NoWalk && !GetCommand ()) || Abs(GetX()-GetX(GoTo))<8) 
      if(Local(0) && Local(1)) return(SetCommand(this(),"MoveTo",GoTo));
  if(!GetCommand())
    SetComDir( COMD_Stop());
  return(1);

AttackEnemyInEarth:
  Var(0)=Par(0);
  if(GetY()<GetY(Var(0))) {
    if(WeapID()==KAZE||graber) {
      if(!graber)
        return(0);
      SetCommand(this(),"Dig",0,GetX(Var(0)),GetY(Var(0)));
      target = Var(0);
    } else if(Contents()) {
      throwdelay=Throwdelay();
      if(Inside(GetX(), GetX(Var(0))-80, GetX(Var(0))+80)) {
	    FaceTarget(Var(0));
        SetCommand(this(),"Throw");
      } else {
        SetCommand(this(),"MoveTo",0,GetX(Var(0))+40*randomSign, 10);
        AppendCommand(this(),"Call",this(),Var(0),0,0,0,"FaceTarget");
        AppendCommand(this(),"Throw");
      }
      target = Var(0);
    }
  } else {
    SetCommand(this(),"MoveTo",0,GetX(Var(0)),10);
  }
  AppendCommand(this(),"Call",this(),Var(0),0,0,0,"AttackClonk");
  return(1);
  
FaceTarget:
  return(SetDir(GetX()<GetX(Par(0))));
  
AttackEnemy:
  Var(0)=Par(0);
  /*if(EnemyAmbush(Var(0)))
    if(WeapID()!=KAZE)
      if(GetAction() ne "Swim")
  return(SetCommand( this(),"None"),SetComDir( COMD_Stop()));*/
  if(Contents()) {
      throwdelay=Throwdelay();
      if(Inside(GetX(), GetX(Var(0))-40, GetX(Var(0))+40)&&Inside(GetY(), GetY(Var(0))-40, GetY(Var(0))+400)) {
        if(!Random(3)) {
          FaceTarget(Var(0));
          SetCommand(this(),"Throw");
        } else
          SetCommand(this(),"Throw", 0, GetX(Var(0)), GetY(Var(0)));
      } else {
        SetCommand(this(),"MoveTo",Var(0));
        AppendCommand(this(),"Call",this(),Var(0),0,0,0,"FaceTarget");
        AppendCommand(this(),"Throw");
      }
      target = Var(0);
  }
  if(WeapID()==KAZE) {
    SetCommand( this(), "MoveTo", Var(0));
    if(ObjectDistance(GetCommand(0,1)) <= ExplodeDistance()) {
      Kill();
    }
  }
  AppendCommand(this(),"Call",this(),Var(0),0,0,0,"AttackClonk");
  return(1);
        
  
IsFighting: //c4object
  if(GetAction(Par())S="Fight" ||
     GetAction(Par())S="Punch" ||
     GetAction(Par())S="GetPunched") return(1);
  return(0);

global Dir2Target:
  if(GetX()<GetX(Par(0))) return(1);
  return(0);

Comes2Me: // pObj
  if(GetAction(Par(0)) S= "Walk")
  {
    if(GetDir()==DIR_Right() && GetComDir(Par(0))== COMD_Left()) return(1);
    if(GetDir()== DIR_Left() && GetComDir(Par(0))==COMD_Right()) return(1);
  }
  return(0);

InsideX:
  if(Par(2)==Par(1))  return(Inside(Par(0),Par(0)-400,Par(0)+400));
  if(Par(2)==Par(0))  return(Inside(Par(0),Par(1)-150,Par(1)+150));
  if(Par(1)>Par(2)) {
    Par(1)+=130;
    Par(2)-=130;
  }
  if(Par(1)<Par(2)) {
    Par(2)+=130;
    Par(1)-=130;
  }
  if(Par(1)>Par(2)) return(Inside(Par(0),Par(2),Par(1)));
  return(Inside(Par(0),Par(1),Par(2)));
  
GetSign: //int
  return(Abs(Par(0))/Par(0));

EnemyAmbush:  // OBJ Enemy
  var sign, width, highy, lowy;
  // Clonk etwa auf selber Höhe
  if(GetY(Par(0))-GetY() >= -20) return(0);
  //if(!Inside(GetY(Par(0))-GetY(),-80,-21)) return(0);
  // sowieso nahe dran
  if(Abs(width = GetX(Par(0))-GetX()) < 10) return(0);
  // nur wenn im gefährlichen Bereich unter der Treppe/Schräge
  if(!Inside( Abs(GetX(Par(0))-GetX()),Var(0)=Abs(GetY(Par(0))-GetY())-20,Var(0)+270 )) return(0);
  // checken ob Gegner sich bewegt hat
  if(Inside(GetX(Par(0)),enemyx-8,enemyx+8 ))
    if(Inside(GetY(Par(0)),enemyy-10,enemyy+10 ))
      return(result);
  enemyx = GetX(Par(0));
  enemyy = GetY(Par(0));
  // checken ob andere Bots das gleiche Problem haben
  while(Var(1) = FindObject(GetID(),0,0,-1,-1,0,0,0,0,Var(1)))
    if(Inside( LocalN("enemyx",Var(1)) ,enemyx-8,enemyx+8 ))
      if(Inside( LocalN("enemyy",Var(1)) ,enemyy-8,enemyy+8 ))
	return( result = LocalN("result",Var(1)) );
  highy = 10;
  lowy = -10;
  sign = GetSign(width);
  //if((result = AnalyseTerrain(sign,width,10,-10, GetY(Par(0))-GetY() )) == 0)
  //  result = AnalyseTerrain(sign,width,-10,-30, GetY(Par(0))-GetY() );
  return(result = AnalyseTerrain(sign,width,10,-10, GetY(Par(0))-GetY()));

/* Terrain-Analyse-Algorythmus von Clonk Nukem */
AnalyseTerrain:  // INT sign, width, highy, lowy, upperborder
  var i, j, sign, width, highx, highy, lowx, lowy, highx2, highy2;
  //if(GetY(Par(0))-GetY() >= -20) return(0);
  //if(Abs(width = GetX(Par(0))-GetX()) < 10) return(0);
  width = Par(1);
  highy = Par(2);
  lowy = Par(3);
  sign = Par(0);
  // Spalten durchgehen
  for(i=sign; Abs(i) < Abs(width); i+=sign*2)
  {
    // Zeilen (mit Breite 1) durchchecken
    for(j=-10; j<10; j++)
    {
      // GBackSolid: Wenn höher als bereits bekannter Punkt: Speichern
      if(GBackSolid(i,j))
      {
        // Feste Materie weiter oben als ein bisher bekannter Punkt
	if(j<highy)
	{
	  // Achtung: Relative Koordinaten!
	  highx = i;
	  highy = j;
	}
	continue;
      }
      if(j>=lowy)
	if(PathFree( GetX()+i,GetY()+lowy, GetX()+i,GetY()+j))
        {
	  lowx = i;
	  lowy = j;
        }
    }
  }

  highx2 = highx;
  highy2 = highy;

  if(Par(4) <= -40)
  {
    for(i=highx+sign*2; Abs(i) < Abs(width); i+=sign*2)
    {
      while(GBackSolid(i,highy2-1) && (highy2>=Par(4)))
      {
	highx2 = i;
	highy2-=2;
      }
    }
  }
  Var(0) = Angle(lowx,lowy,highx2,highy2);
  if( (Abs(lowx)-GetX()) < (Abs(highx2)-GetX()) )
    if( Inside(Var(0), 300, 330) || Inside(Var(0), 30, 60) )
      return(1);
  //Log("%d bei %d, %d",Var(0),lowx,highx);
  return(0);


AttackClonk:
  zorn=0;
  return(1);
AttackClonkFailed:
  zorn++;
  AddCommand(this(),"MoveTo",0,GetX(Par(1))+8-Dir2Target(Par(1))*16,GetY(Par(1)));
  return(1);
  
CatchBlow:
  if(GetAction() S= "Dead") return(0);
  // Schlagen bringt Punkte
  if( GetOwner(Par(1)) != GetOwner() )
  {
  }
  return(_inherited());

Death:
  SetCommand(this(),"None");
  Sound("Death");
  var threattype = Random(11);
  if(threattype == 10)
  CreateObject(S582,0,0,GetOwner(this()));
  if(threattype < 10)
  CreateObject(ST58,0,0,GetOwner(this()));
  GameCall("RelaunchKi",GetOwner());
  //Log(Format("Killer: %d",GetKiller()));
  if(Local(9)==0)
    if(WeapID() == KAZE)
      ExplodeKamikaze();
  return(1);

RemoveC: 
  if(Contents()) RemoveObject(Contents());
  return(1);
  
FadeOut:
  if(GetActTime()<70) return(0);
  alpha+=20;
  if(Random(2)) CreateParticle("PxSpark",-7+Random(14),Random(6),0,0,15);
  SetClrModulation(RGBa(255,255,255,alpha));
  if(alpha>240)
  {
    CreateParticle("PxSpark",0,6,0,0,150,RGBa(100,100,180,100));
    return(RemoveObject());
  }
  return(1);

Hurt:
  Sound("Wound");
  return(1);

// Zusätzliche Funktionen

global GetSign: // INT
  return(Abs(Par(0))/Par(0));

// Winkel zwischen Objekt und Koordinaten
global ObjAngle: // INT x, y [, OBJ]
  return(Angle(GetX(Par(2)),GetY(Par(2)),Par(0),Par(1)));

// Winkel zwischen 2 Objekten
global ObjectsAngle:  // OBJ1 [, OBJ2]
  return(Angle(GetX(Par(1)),GetY(Par(1)),GetX(Par(0)),GetY(Par(0))));

// Weg zwischen Objekt und Koordinaten
global ObjPathFree:  // INT x, y [, OBJ]
  return(PathFree( GetX(Par(2)),GetY(Par(2)),Par(0),Par(1) ));

