﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using OpenQA.Selenium.Appium.Windows;
using OpenQA.Selenium.Remote;
using OpenQA.Selenium;
using Microsoft.VisualStudio.TestTools.UnitTesting;

namespace UIXPathLib
{
	public class DesktopSession
	{
		private const string WindowsApplicationDriverUrl = "http://localhost:4723/";
		WindowsDriver<WindowsElement> desktopSession;

		public DesktopSession()
		{
			DesiredCapabilities appCapabilities = new DesiredCapabilities();
			appCapabilities.SetCapability("app", "Root");
			appCapabilities.SetCapability("deviceName", "WindowsPC");
			desktopSession = new WindowsDriver<WindowsElement>(new Uri(WindowsApplicationDriverUrl), appCapabilities);
		}

		~DesktopSession()
		{
			desktopSession.Quit();
		}

		public WindowsDriver<WindowsElement> DesktopSessionElement
		{
			get { return desktopSession; }
		}

		public WindowsElement FindElementByAbsoluteXPath(string xPath, int nTryCount = 10)
		{
			WindowsElement uiTarget = null;

			while (nTryCount-- > 0)
			{
				try
				{
					uiTarget = desktopSession.FindElementByXPath(xPath);
				}
				catch
				{
				}

				if (uiTarget != null)
				{
					break;
				}
				else
				{
					System.Threading.Thread.Sleep(2000);
				}
			}

			return uiTarget;
		}
	}

	class Program
	{
		static void Main(string[] args)
		{
			DesktopSession desktopSession = new DesktopSession();
			System.Threading.Thread.Sleep(2000);

			bool bSuccess = false;

			try
			{
				//Enter c# code here

				bSuccess = true;
			}
			finally
			{
				Assert.AreEqual(bSuccess, true);
			}
		}
	}
}
