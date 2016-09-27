using System.Windows.Controls;

namespace FMS_GUI
{
    public static class Switcher
    {
        public static File_System_Managment PageSwitcher;
        public static void Switch(UserControl newPage)
        {
            PageSwitcher.Navigate(newPage);
        }

        public static void Switch(UserControl newPage, object state)
        {
            PageSwitcher.Navigate(newPage, state);
        }
    }

    public interface iSwitchable
    {
        void UtilizeState(object state);
    }
}
