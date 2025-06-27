static Object SpawnObject(string type, vector position, vector orientation, float scale = 1.0)
{
    Object obj;
    if (type.Contains(".p3d")) {
        obj = GetGame().CreateStaticObjectUsingP3D(type, position, orientation, scale, false);
    } else {        
        obj = GetGame().CreateObjectEx(type, position, ECE_SETUP | ECE_CREATEPHYSICS | ECE_NOLIFETIME | ECE_NOPERSISTENCY_WORLD | ECE_NOPERSISTENCY_CHAR);
    }

    if (!obj) {
        Error("Failed to create object " + type);
        return null;
    }

    obj.SetPosition(position);
    obj.SetOrientation(orientation);
    obj.SetOrientation(obj.GetOrientation());
    obj.SetScale(scale);
    obj.Update();
	obj.SetAffectPathgraph(true, false);
	if (obj.CanAffectPathgraph()) {
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(GetGame().UpdatePathgraphRegionByObject, 100, false, obj);
    } 

    return obj;
}
void main()
{
	//INIT ECONOMY--------------------------------------
	Hive ce = CreateHive();
	if ( ce )
		ce.InitOffline();
GetCEApi().ExportProxyData(Vector(10240, GetGame().SurfaceY(10240, 10240), 10240), 20480);  //Center of map, radius of how far to go out and find buildings.
	//GetCEApi().ExportProxyProto();
	//GetCEApi().ListCloseProxy(1024);
GetCEApi().ExportClusterData();
	//DATE RESET AFTER ECONOMY INIT-------------------------
	int year, month, day, hour, minute;
	int reset_month = 6, reset_day = 7;
	GetGame().GetWorld().GetDate(year, month, day, hour, minute);

	if ((month == reset_month) && (day < reset_day))
	{
		GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
	}
	else
	{
		if ((month == reset_month + 1) && (day > reset_day))
		{
			GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
		}
		else
		{
			if ((month < reset_month) || (month > reset_month + 1))
			{
				GetGame().GetWorld().SetDate(year, reset_month, reset_day, hour, minute);
			}
		}
	}
}

class CustomMission: MissionServer
{
	void SetRandomHealth(EntityAI itemEnt)
	{
		if ( itemEnt )
		{
			float rndHlt = Math.RandomFloat( 0.45, 0.65 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}

override PlayerBase CreateCharacter(PlayerIdentity identity, vector pos, ParamsReadContext ctx, string characterName) 
	{

    Entity playerEnt;
    playerEnt = GetGame().CreatePlayer(identity, characterName, pos, 0, "NONE");
    Class.CastTo(m_player, playerEnt);
    GetGame().SelectPlayer(identity, m_player);
    return m_player;
	}

  override void StartingEquipSetup(PlayerBase player, bool clothesChosen) 
  {
    //Random arrays
    TStringArray jacket = 
	{
      "MrBanana"
    };
    TStringArray pants = 
	{
      "Hawaii_Breeches_1",
      "Hawaii_Breeches_2",
      "Hawaii_Breeches_3",
      "Hawaii_Breeches_4",
      "Hawaii_Breeches_5"
    };
    TStringArray drink = 
	{
      "SodaCan_Cola",
      "SodaCan_Kvass",
      "SodaCan_Pipsi",
      "SodaCan_Spite"
    };
    TStringArray food = 
	{
      "TunaCan",
      "PowderedMilk",
      "PeachesCan",
      "Pear"
    };
    player.RemoveAllItems();
    //loadout
    player.GetInventory().CreateInInventory(pants.GetRandomElement());
    player.GetInventory().CreateInInventory(jacket.GetRandomElement());
    player.GetInventory().CreateInInventory("Sneakers_White");
    player.GetInventory().CreateInInventory(drink.GetRandomElement());
    player.GetInventory().CreateInInventory(food.GetRandomElement());
    player.GetInventory().CreateInInventory(food.GetRandomElement());
    player.GetInventory().CreateInInventory("BandageDressing");
    player.GetInventory().CreateInInventory("Compass");
    player.GetInventory().CreateInInventory("HuntingKnife");
	player.GetInventory().CreateInInventory("SahraniMap");

	};
};

Mission CreateCustomMission(string path)
{
	return new CustomMission();
}