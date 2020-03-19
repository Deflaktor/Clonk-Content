/*-- Neues Objekt --*/

#strict

global LongRangeWeapon:
  return(4);
  
global MiddleRangeWeapon:
  return(2);
  
global ShortRangeWeapon:
  return(1);

global KannTreten:
  // KannTreten( TretObjekt, Call Objekt)
  // Liefert den Schaden, den das Call Objekt dem Tretobjekt 
  // durch einen einzigen Schlag anrichten kann.
  var target,attacker,targetHeight,attackerHeight;
  target=Par(0);
  if(!Par(1))
    attacker=this();
  else
    attacker=Par(1);
  targetHeight=GetDefCoreVal("Height","DefCore",GetID(target))*GetCon(target);
  attackerHeight=GetDefCoreVal("Height","DefCore",GetID(attacker))*GetCon(attacker);
  if(GetID(target)==_CHP)
    targetHeight=targetHeight*3/4;
  if(GetID()==_CHP)
    attackerHeight=attackerHeight*4/2;
  if(GetID(target)==ST5B)
    targetHeight=targetHeight/2;
  if(attackerHeight-targetHeight<10)
    return(0);
  return(20*attackerHeight/targetHeight-30);

global GetTarget:
  if (!GetAlive(Par(0)) && GetID(Par(0)) != _DRN) return(0);
  // Sicht versperrt
  // if (Not(PathFree(GetX(),GetY(),GetX(Par(0)),GetY(Par(0))))) return(0);
  return(GetHostile(Par(0)));

global GetHostile:
  // Unsichtbar
  if ( !Visible(GetOwner(Par(1)), Par(0)) ) return(0);
  // Verfeindet
  if( GetOwner(Par(1))==NO_OWNER()&&GetOwner(Par(0))==NO_OWNER() && !GameCall("HostileAnimals")) return(0);
  if( GetOwner(Par(1))!=NO_OWNER()&&GetOwner(Par(0))!=NO_OWNER()&&!(Hostile(GetOwner(Par(1)), GetOwner(Par(0)))||Hostile(GetOwner(Par(0)), GetOwner(Par(1)))) ) return(0);
  return(Par(0));
  
global func FindTarget(int x, int y, int w, int h) {
  var gen = FindContents(_FFG), fieldId = 0, field = 0;
  if(gen) fieldId = Local(8,gen);
  if(fieldId==_FFD) field = 1;
  
  Var(3)=FindObject(0,0,-1,0,0,OCF_Prey(),0,0,NoContainer());
  while(Var(3)||(Var(0)=FindObject(0,x,y,w,h,OCF_Prey(),0,0,NoContainer(),Var(4)))) {
    Var(4)=Var(0);
    if(Var(3)) {
	  Var(0)=Var(3);
	  Var(3)=0;
	  Var(4)=0;
	}
    if(GetTarget(Var(0)))
      if(Visible(GetOwner(),Var(0))) {
	    if(field) {
		  // Hat selber ein Force Field?
		  var hori = 0;
		  var vert = 0;
		  if(GetX()+25<GetX(Var(0)))
		    hori=-25;
		  else if(GetX()-25>GetX(Var(0)))
		    hori=25;
		  if(GetY()+25<GetY(Var(0)))
		    vert=-25;
		  else if(GetY()-25>GetY(Var(0)))
		    vert=25;
		  if(PathFree( GetX()-hori,GetY()-vert,GetX(Var(0)),GetY(Var(0)) ))
             return(Var(0));
		} else {
          // Hinter einem Force Field?
          // Suche alle ForceFieldGeneratoren im target ab
          while(Var(1)=FindObject(_FFG,0,0,0,0,0,0,0,Var(0),Var(1)))
            // Ist es aktiviert?
            if(Var(2)=FindObject(_FFD,0,0,0,0,0,"Exist",Var(1))) {
			  var hori = 0;
			  var vert = 0;
			  if(GetX()+25<GetX(Var(0)))
			    hori=-25;
			  else if(GetX()-25>GetX(Var(0)))
			    hori=25;
			  if(GetY()+25<GetY(Var(0)))
			    vert=-25;
			  else if(GetY()-25>GetY(Var(0)))
			    vert=25;
			  if(PathFree( GetX(),GetY(),GetX(Var(0))+hori,GetY(Var(0))+vert ))
              return(Var(0));
			}
		  // Kein ForceField?
          if(PathFree( GetX(),GetY(),GetX(Var(0)),GetY(Var(0)) ))
            return(Var(0));
        }
	  }
  }
  return(0);
}
  
global FindAOETarget:
  Var(1)=FindObject(0,0,-1,0,0,OCF_Prey(),0,0,NoContainer());
  while(Var(1)||(Var(0)=FindObject(0,Par(0),Par(1),Par(2),Par(3),OCF_Prey(),0,0,NoContainer(),Var(0)))) {
    if(Var(1))
	  Var(0)=Var(1);
    return(Var(0));
  }
  return(0);

global CreateAlien:
  Var(0)=PlaceInMaterial(Par(0),Material("Wall"),100000);
  SetOwner(-1, Var(0));
  return(Var(0));

global CreateAlienInMaterial:
  Var(0)=PlaceInMaterial(Par(0),Par(1),100000);
  SetOwner(-1, Var(0));
  return(Var(0));
