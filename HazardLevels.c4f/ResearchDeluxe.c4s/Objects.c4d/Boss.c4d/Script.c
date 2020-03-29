#strict

local letzteEnergie, initiative, maxHP, leben, maxLeben, autoFire, specialAttack, specialPhase, attackPhase;

Initialize:
  SetPhysical("Energy",GetPhysical("Energy")/100*(Global(4)+100),2);
  DoEnergy(10000);
  maxLeben=5;
  leben=maxLeben;
  maxHP=GetEnergy();
  letzteEnergie = GetEnergy()-GetEnergy()%100;
  SetOwner(-1);
  SetAction("AugenZu");
  return(1);

CatchBlow:
  return(Damage());

Damage:
  if(GetEnergy()-GetEnergy()%100!=letzteEnergie) {
    if(GetAction()S="AugenZu")
      SetAction("Hurt");
    letzteEnergie = GetEnergy()-GetEnergy()%100;
    Sound("BossHurt*",0, this(), 100);
    Local(0)++;
  }
  return(1);

Zornig:
  return(leben<=maxLeben/2);

Test:
  if(!(GetAction()S="AugenZu"||GetAction()S="Wach"||GetAction()S="Schlafen"))
    return(1);

  if (SetVar(0,FindObject(0, -30,-20,60,40, OCF_CrewMember(), 0,0, NoContainer())))
    Punch(Var(0),20);

  if(!(SetVar(0,FindObject(0,-260,-100,300,150,OCF_CrewMember(),0,0,NoContainer()))))
    return(0);
  
  initiative+=maxLeben-leben;
  if(Zornig())
    initiative+=maxLeben-leben;
  if(Local(0)>=2)
    initiative++;

  if(initiative>=maxLeben*3&&Local(0)) {
    initiative = 0;
    if(GetAction()S="AugenZu")
      SetAction("Angriff");
    if(GetAction()S="Wach")
      SetAction("Angriff2");
  }
  return(1);

MaulOffen:
  if(autoFire>0) {
    autoFire--;
	if((autoFire % 10)==0)
	  Fire();
	if(autoFire==0) {
	  initiative -= maxLeben*3;
      SetAction("Angriff3");
	}
    return(1);
  }
  if(GetActTime()>100) {
    SetVar(0,SpecialFire());
    SetLocal(1,-60,Var(0));
    SetLocal(4,40,Var(0));
    SetVar(0,SpecialFire());
    SetLocal(1,-60,Var(0));
    SetLocal(4,40,Var(0));
    SetVar(0,SpecialFire());
    SetLocal(1,-60,Var(0));
    SetLocal(4,40,Var(0));
  } else {
    SetVar(0,SpecialFire());
    SetLocal(1,-25,Var(0));
    SetLocal(4,10,Var(0));
  }
  if(GetActTime()>300) {
    SetAction("Angriff3");
  }
  return(1);

Angriff:
  if(specialAttack) {
    specialAttack--;
    return(SetAction("MaulOffen"));
  }
  attackPhase++;
  if(Zornig()&&(attackPhase % 2)==0) {
    if((attackPhase % 4) == 0) {
      autoFire=20;
	  SetAction("MaulOffen");
      return(Fire());
    } else {
      var i;
      for(var i=10;i<=40;i+=10) {
        SetVar(0,Fire());
        SetLocal(0,-Cos(i,100),Var(0));
        SetLocal(1,-Sin(i,100),Var(0));
        SetR(i,Var(0));
        initiative -= maxLeben*3;
      }
      return(Fire());
    }
  }
  return(Fire());

Fire:
  SetVar(0,CreateContents(DA1D));
  Exit(Var(0), -42,12-Random(4),0, 0,0,0 );
  ObjectCall(Var(0),"Launch",DIR_Left());
  return(Var(0));

SpecialFire:
  SetVar(0,CreateContents(_AM3));
  Exit(Var(0), -34-Random(10),14-Random(6),0, 0,0,0 );
  ObjectCall(Var(0),"Launch",DIR_Left());
  return(Var(0));

Frozen:
  Extinguish();
  if(Zornig())
    return(SetDir(DIR_Left()));
  return(SetDir(DIR_Right()));

AngriffZuEnde:
  SetDir(DIR_Left());
  if(!Zornig())
    return(SetAction("Schlafen"));
  return(SetAction("Wach"));

Death:
  if(GetAction()S="Tot")
    return(1);
  if(leben>0) {
    leben--;
    SetAlive(1);
    DoEnergy(10000);
    AngriffZuEnde();
    if(leben<=(100+Global(4))/100)
      specialAttack++;
    return(1);
  }
  Music("@M3sonstiges6.mid");
  SetGlobal(22,1);
  ObjectCall(CreateObject(SW3V,0,30,-1),"Launch",this());
  return(SetAction("Tot"));