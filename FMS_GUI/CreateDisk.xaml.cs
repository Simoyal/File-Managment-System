// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
using System;
using System.Windows;
using System.Windows.Controls;
using System.IO;
using FMS_adapter;

namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour CreateDisk.xaml
    /// </summary>
    public partial class CreateDisk : UserControl, iSwitchable
    {
        Disk disk;
        /// <summary>
        /// Constructor
        /// </summary>
        public CreateDisk()
        {
            InitializeComponent();
            disk = new Disk();
        }
        
        #region 
        /// <summary>
        /// Implementation of the interface
        /// </summary>
        /// <param name="state"></param>
        public void UtilizeState(object state)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// Swiching back to the main window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Switcher.Switch(new MainWindows());
        }
        /// <summary>
        /// Create a new disk
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // getting info from the user
                string name = diskNameTextBox.Text;
                string owner = diskOwnerTextBox.Text;
                // checking the extension
                if (string.IsNullOrEmpty(Path.GetExtension(name)))
                {
                    name += ".bin";
                }
                //create disk
                disk.Createdisk(name, owner);
                MessageBox.Show("Disk succefully created", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                // if want to create new disk , to function otherwise to main operation disk 
                diskNameTextBox.Text = diskOwnerTextBox.Text = "";
                disk = new Disk();

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        #endregion

    }
}
