class CfgPatches
{
	class Battlegrounds
	{
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Structures"
		};
		units[]={};
		weapons[]={};
	};
};
class CfgMods
{
	class Battlegrounds
	{
		dir="Battlegrounds";
		author="Moses";
		type="mod";
		inputs="Battlegrounds/Inputs.xml";
		dependencies[]=
		{
			"Game",
			"World",
            "Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				files[]=
				{
					"Battlegrounds/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				files[]=
				{
					"Battlegrounds/scripts/4_World"
				};
			};
            class missionScriptModule
			{
				files[]=
				{
					"Battlegrounds/scripts/5_Mission"
				};
			};
		};
	};
};
class cfgVehicles
{
	class M18SmokeGrenade_Green;
	class BGSmokeGreen : M18SmokeGrenade_Green
	{
		scope=1;
	};
	class M18SmokeGrenade_Red;
	class BGSmokeRed : M18SmokeGrenade_Red
	{
		scope=1;
	};
	class Container_Base;
	class BattlegroundsRewardCrate: Container_Base
	{
		scope=2;
		displayName="Rewards";
		descriptionShort="";
		model="DZ\structures_bliss\Residential\Misc\Misc_WoodenCrate_5x.p3d";
		attachments[]=
		{};
		itemsCargoSize[]={10,10};
		weight=30000;
		physLayer="item_large";
		simulation="inventoryItem";
		carveNavmesh=1;
		canBeDigged=0;
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
		};
		class Cargo
		{
			itemsCargoSize[]={10,10};
			openable=0;
			allowOwnedCargoManipulation=1;
		};
		class AnimEvents
		{
			class SoundWeapon
			{
				class movement
				{
					soundSet="seachest_movement_SoundSet";
					id=1;
				};
				class pickUpItem_Light
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=796;
				};
				class pickUpItem
				{
					soundSet="pickUpSeaChest_SoundSet";
					id=797;
				};
				class drop
				{
					soundset="seachest_drop_SoundSet";
					id=898;
				};
			};
		};
	};
	class HouseNoDestruct;
    class StaticObj_TeleporterPanel: HouseNoDestruct
	{
		scope=1;
		model="DZ\structures\Furniture\radar_equipment\radar_panel_flat.p3d";
        class Doors
		{
			class doorOpen
			{
				displayName="Door1";
				component="doorOpen";
				soundPos="door1_action";
				animPeriod=1;
				initPhase=0;
				initOpened=0;
				soundOpen="";
				soundClose="";
				soundLocked="";
				soundOpenABit="";
			};
		};
		class DamageSystem
		{
			class GlobalHealth
			{
				class Health
				{
					hitpoints=1000;
				};
			};
			class GlobalArmor
			{
				class Projectile
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class Melee
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
				class FragGrenade
				{
					class Health
					{
						damage=0;
					};
					class Blood
					{
						damage=0;
					};
					class Shock
					{
						damage=0;
					};
				};
			};
			class DamageZones
			{
				class twin1
				{
					class Health
					{
						hitpoints=1000;
						transferToGlobalCoef=0;
					};
					componentNames[]=
					{
						"door1"
					};
					fatalInjuryCoef=-1;
					class ArmorType
					{
						class Projectile
						{
							class Health
							{
								damage=3;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class Melee
						{
							class Health
							{
								damage=5;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
						class FragGrenade
						{
							class Health
							{
								damage=3;
							};
							class Blood
							{
								damage=0;
							};
							class Shock
							{
								damage=0;
							};
						};
					};
				};
			};
		};
	};
};