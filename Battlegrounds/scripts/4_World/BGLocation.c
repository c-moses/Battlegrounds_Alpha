class BattlegroundsLocation
{
    vector m_Position;
    string m_Name;

    void BattlegroundsLocation(vector position, string name = "")
    {
        m_Position = position;
        m_Name = name;
    }

    vector GetPosition()
    {
        return m_Position;
    }

    string GetName()
    {
        return m_Name;
    }
}