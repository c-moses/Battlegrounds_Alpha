const static ref array<string> BGObjective = {"Rev_M110_Black","Rev_SR25_Black","Rev_M2010_Tan","Rev_R700","Rev_WA2000","Rev_MG3"};

class BattlegroundsLootManager 
{
    static void AddRewardLoot(EntityAI crate) 
    {
        int i;

		int rndIndex;
		EntityAI obj;
		EntityAI attachment;

        int firstrandomIndex = Math.RandomInt(0, BGObjective.Count() - 1);

		obj = crate.GetInventory().CreateInInventory(BGObjective[firstrandomIndex]);

		switch (BGObjective[firstrandomIndex])
        {
			case "Rev_M110_Black":

				Rev_M110_Black m110Instance = Rev_M110_Black.Cast(obj);
				if (m110Instance)
				{
					m110Instance.GetInventory().CreateAttachment("HuntingOptic");
					m110Instance.SpawnAttachedMagazine("Rev_Mag_M110_20Rnd");
				}
                for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Rev_Mag_M110_20Rnd");
				break;

			case "Rev_SR25_Black":

				Rev_SR25_Black sr25Instance = Rev_SR25_Black.Cast(obj);
				if (sr25Instance)
				{
					sr25Instance.GetInventory().CreateAttachment("HuntingOptic");
					sr25Instance.SpawnAttachedMagazine("Rev_Mag_SR25_20Rnd");
				}
				for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Rev_Mag_SR25_20Rnd");
				break;

			case "Rev_M2010_Tan":

				Rev_M2010_Tan m2010Instance = Rev_M2010_Tan.Cast(obj);
				if (m2010Instance)
				{
					m2010Instance.GetInventory().CreateAttachment("HuntingOptic");
					m2010Instance.SpawnAttachedMagazine("Rev_Mag_M2010_10rnd");
				}
                for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Rev_Mag_M2010_10rnd");
				break;

			case "Rev_R700":

				Rev_R700 r700Instance = Rev_R700.Cast(obj);
				if (r700Instance)
				{
					r700Instance.GetInventory().CreateAttachment("HuntingOptic");
					r700Instance.SpawnAttachedMagazine("Rev_Mag_R700_7rnd");
				}
				for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Rev_Mag_R700_7rnd");
				break;

            case "Rev_WA2000":

				Rev_WA2000 wa2000Instance = Rev_WA2000.Cast(obj);
				if (wa2000Instance)
				{
					wa2000Instance.GetInventory().CreateAttachment("HuntingOptic");
					wa2000Instance.SpawnAttachedMagazine("Rev_Mag_WA2000_5rnd");
				}
				for (i = 0; i < 1; i++) crate.GetInventory().CreateInInventory("Rev_Mag_WA2000_5rnd");
				break;    

			case "Rev_MG3":

				Rev_MG3 mg3Instance = Rev_MG3.Cast(obj);
				if (mg3Instance)
				{
					mg3Instance.SpawnAttachedMagazine("Rev_Mag_MG3_75rnd");
				}
				break;

			default:

				Rev_MG3 defaultmg3Instance = Rev_MG3.Cast(crate.GetInventory().CreateInInventory("Rev_MG3"));
				if (defaultmg3Instance)
				{
					defaultmg3Instance.SpawnAttachedMagazine("Rev_Mag_MG3_75rnd");
				}
				break;
		}

		obj = crate.GetInventory().CreateInInventory("MVS_Rucksack_Black");
        obj = crate.GetInventory().CreateInInventory("Keycard_Orange");
	}
};