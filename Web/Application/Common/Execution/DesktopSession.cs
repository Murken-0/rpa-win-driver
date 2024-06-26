﻿using OpenQA.Selenium.Appium.Windows;
using OpenQA.Selenium.Appium;

namespace Application.Common.Execution;

public class DesktopSession : IDisposable
{
    private readonly WindowsDriver<WindowsElement> _session;

    public DesktopSession(string uri)
    {
        var options = new AppiumOptions();
        options.AddAdditionalCapability("app", "Root");
        options.AddAdditionalCapability("deviceName", "WindowsPC");
        _session = new WindowsDriver<WindowsElement>(new Uri(uri), options);
        _session.Manage().Timeouts().ImplicitWait = TimeSpan.FromMilliseconds(500);
    }

    public WindowsDriver<WindowsElement> DesktopSessionElement
    {
        get { return _session; }
    }

    public void Dispose() => _session.Quit();

    public WindowsElement FindElementByAbsoluteXPath(string xPath, int nTryCount = 10)
    {
        WindowsElement uiTarget = null;

        while (nTryCount-- > 0)
        {
            try
            {
                uiTarget = _session.FindElementByXPath(xPath);
            }
            catch (Exception)
            {
            }

            if (uiTarget != null)
            {
                break;
            }
            else
            {
                Thread.Sleep(2000);
            }
        }

        return uiTarget;
    }
}