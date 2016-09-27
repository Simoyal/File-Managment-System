// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Reflection;
using Microsoft.Win32;
using FMS_adapter;


namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour MainWindows.xaml
    /// </summary>
    public partial class MainWindows : UserControl, iSwitchable
    {
        public Disk disk;
        public VolumeHeader vhd;
        /// <summary>
        /// Constructor
        /// </summary>
        public MainWindows()
        {
            InitializeComponent();
            disk = new Disk();
        }

        #region
        public void UtilizeState(object state)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// Create disk button, jumping to createdisk page
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CreateButton_Click(object sender, RoutedEventArgs e)
        {
            Switcher.Switch(new CreateDisk());
        }
        /// <summary>
        /// Import a file
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void ImportButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                string[] filenames = {};
                // open a Dialog Window
                OpenFileDialog file = new OpenFileDialog();
                // filter
                file.Filter = "Binary file|* .bin";
                // multiSelect accepted :)
                file.Multiselect = true;
                // if the user select a file
                if (file.ShowDialog() == true)
                {
                    // mooving the file to a path where all the disk are located
                    moovefile(file.FileNames);
                    // switching to choose_disk page
                    Switcher.Switch(new Choose_Disk());
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Mooving all the file to an directory
        /// </summary>
        /// <param name="filenames"></param>
        private void moovefile(params string[] filenames)
        {
            if (filenames.Length == 0)
                return;
            // mooving all the file
            foreach (string files in filenames)
            {
                File.Move(@files, @"C:\Users\Simon\Desktop\FMS5776_2397_7707\FMS5776_2397_7707\FMS5776_2397_7707\FMS_GUI\bin\Release\" + Path.GetFileName(files));
            }
        }
        /// <summary>
        /// Delete a disk
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteButton_Click(object sender, RoutedEventArgs e)
        {
            // Switching to Delete disk section
            Switcher.Switch(new Unmount());
        }
        /// <summary>
        /// Open a disk who already exist
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenButton_Click(object sender, RoutedEventArgs e)
        {
            // Switching to choose_disk
            Switcher.Switch(new Choose_Disk());
        }
        #endregion


    }
}
