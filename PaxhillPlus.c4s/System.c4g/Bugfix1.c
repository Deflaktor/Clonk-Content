/*-- Bugfix: Zugbrücke links kriegt keinen Schaden wenn Sprengpfeile sie von links treffen --*/

#strict
#appendto CPT4

private func InitializeTower()
{
	CreateObject(CPBL, -49, +35, GetOwner());
}
