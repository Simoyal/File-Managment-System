using System;
using System.Windows;
using System.Windows.Controls;

namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour File_System_Managment.xaml
    /// </summary>
    public partial class File_System_Managment : Window
    {
        public File_System_Managment()
        {
            InitializeComponent();
            Switcher.PageSwitcher = this;
            Switcher.Switch(new MainWindows());
        }
        public void Navigate(UserControl nextPage)
        {
            this.Content = nextPage;
        }
       
        public void Navigate(UserControl nextPage, object state)
        {
            this.Content = nextPage;
            iSwitchable s = nextPage as iSwitchable;

            if (s != null)
                s.UtilizeState(state);
            else
                throw new Exception("NextPage isn't iSwitchable!" + nextPage.Name.ToString());

        }
    }
}
