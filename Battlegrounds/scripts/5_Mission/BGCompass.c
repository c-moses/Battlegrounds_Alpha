class CompassWidget extends UIScriptedMenu
{
	private Widget m_CompassRootWidget;
	private Widget m_CompassFrameWidget;
	private ImageWidget m_CompassImageWidget;
	private bool m_CompassIsVisible;

	void CompassWidget(bool visible)
	{
		m_CompassRootWidget = GetGame().GetWorkspace().CreateWidgets("Battlegrounds/GUI/layouts/BattlegroundsCompass.layout");
		m_CompassFrameWidget = m_CompassRootWidget.FindAnyWidget("FrameCompass");
		m_CompassImageWidget = ImageWidget.Cast(m_CompassRootWidget.FindAnyWidget("ImageCompass"));
		m_CompassIsVisible = visible;

		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(this.CompassUpdate, 16, true);
	}

	void~CompassWidget()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(this.CompassUpdate);
		if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.Show(false);
		}
	}

	void CompassUpdate()
	{
		if (m_CompassIsVisible && m_CompassRootWidget != null && GetGame().GetPlayer())
		{
			float angle = CompassGetAngle();

			m_CompassFrameWidget.Show(true);
			CompassSetCompassPos(angle);
			m_CompassRootWidget.Update();
			m_CompassRootWidget.Show(true);
		}
		else if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.Show(false);
		}
	}

	void SetCompassAlpha(float alpha)
	{
		if (m_CompassRootWidget != null)
		{
			m_CompassRootWidget.SetAlpha(alpha);
		}
	}

	string CompassGetHeading(float angle)
	{
		float rounded = Math.Round(5 *Math.Round(angle / 5.0));
		return rounded.ToString();
	}

	void CompassSetCompassPos(float angle)
	{
		float width, height, x, y;
		m_CompassImageWidget.GetPos(x, y);
		m_CompassImageWidget.GetSize(width, height);

		float center_offset = width / -2.0 + 0.5;

		if (angle > 180)
		{
			angle = angle - 360;
		}

		float offset = angle *(center_offset / 180.0) + center_offset;

		m_CompassImageWidget.SetPos(offset, y);
	}

	float CompassGetAngle()
	{
		vector direction = GetGame().GetCurrentCameraDirection();
		float angle = direction.VectorToAngles()[0];
		return angle;
	}

	void CompassSetHeadingVisible(bool visible)
	{
		m_CompassIsVisible = visible;
	}

	void CompassToggleHeading()
	{
		m_CompassIsVisible = !m_CompassIsVisible;
	}
}