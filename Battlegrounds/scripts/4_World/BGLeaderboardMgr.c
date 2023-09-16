class BGLeaderboardManager
{
    protected ref array<ref BGPlayerStats> sortedArray;
    private static ref BGLeaderboardManager instance;

    void BGLeaderboardManager(ref array<ref BGPlayerStats> arr)
    {
        sortedArray = new ref array<ref BGPlayerStats>();
        for (int i = 0; i < arr.Count(); i++)
        {
            sortedArray.Insert(arr[i]);
        }
    }

    static BGLeaderboardManager GetInstance(ref array<ref BGPlayerStats> arr = null)
    {
        if (!instance)
        {
            if (!arr)
            {
                return null;
            }
            instance = new BGLeaderboardManager(arr);
        }
        return instance;
    }

    array<BGPlayerStats> GetSortedList(string order = "asc")
    {
        int count = sortedArray.Count();
        ref BGPlayerStats player;

        if (order == "desc")
        {
            array<BGPlayerStats> reversedSortedArray = new array<BGPlayerStats>();
            for (int i = count; i > 0; i--)
            {
                player = sortedArray[i - 1];
                reversedSortedArray.Insert(player);
            }
            return reversedSortedArray;
        }
        else
        {
            array<BGPlayerStats> nonRefSortedArray = new array<BGPlayerStats>();
            for (int j = 0; j < count; j++)
            {
                player = sortedArray[j];
                nonRefSortedArray.Insert(player);
            }
            return nonRefSortedArray;
        }
    }

    protected int intCompare(int x, int y)
    {
        if (x == y) return 0;

        if (x < y)
            return -1;
        else
            return 1;
    }

    void QuickSortByCashEarned(int left, int right)
    {
        int i = left;
        int j = right;
        BGPlayerStats pivot = sortedArray[(left + right) / 2];

        while (i <= j)
        {
            while (intCompare(sortedArray[i].cashEarned, pivot.cashEarned) < 0) i++;
            while (intCompare(sortedArray[j].cashEarned, pivot.cashEarned) > 0) j--;

            if (i <= j)
            {
                BGPlayerStats tmp = sortedArray[i];
                sortedArray[i] = sortedArray[j];
                sortedArray[j] = tmp;
                i++;
                j--;
            }
        }

        if (left < j) QuickSortByCashEarned(left, j);
        if (i < right) QuickSortByCashEarned(i, right);
    }
}
