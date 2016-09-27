/********************************************************************************************
// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
/********************************************************************************************/
using System;
using System.IO;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using FMS_adapter;


namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour Unmount.xaml
    /// </summary>
    public partial class Unmount : UserControl, iSwitchable
    {
        /// <summary>
        /// Class file to represent file
        /// </summary>
        public class file
        {
            public string name { get; set; }
            public string date { get; set; }
            public file (string _name, string _date)
            {
                this.name = _name;
                this.date = _date;
            }
        }
        Disk disk;
        string path = @"C:\Users\Simon\Desktop\FMS5776_2397_7707\FMS5776_2397_7707\FMS5776_2397_7707\FMS_GUI\bin\Release\";
        /// <summary>
        /// Getting date
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        private string GetDate(string filename)
        {
            disk.Mountdisk(filename);
            string tmp = disk.GetVolumeHeader().ProdDate;
            disk = new Disk();
            return tmp;
        }
        public Unmount()
        {
            disk = new Disk();
            InitializeComponent();
            // getting all the disk in our directory
            Disklist.ItemsSource = from path in Directory.GetFiles(path, "*.bin")
                                   select new file(Path.GetFileNameWithoutExtension(path), GetDate(path));
        }
        /// <summary>
        /// Implement the interface
        /// </summary>
        /// <param name="state"></param>
        public void UtilizeState(object state)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// Back button, switch to mainWindow
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Switcher.Switch(new MainWindows());
        }
        /// <summary>
        /// Delete file
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // check if a disk has been selected
                if (Disklist.SelectedCells.Count() == 0)
                    throw new Exception("No disk selected");
                // getting info
                file file = Disklist.SelectedCells[0].Item as file;
                if (file == null)
                    throw new Exception("File is null ...");
                if (MessageBox.Show("Are you sure to delete this disk ?", "Confirmation", MessageBoxButton.YesNo, MessageBoxImage.Question) == MessageBoxResult.Yes)
                {
                    // delete the file from the computer of the user
                    File.Delete(path + file.name + ".bin");
                    MessageBox.Show("File to delete: " + file.name);
                    // refresh the present item
                    Disklist.ItemsSource = from path in Directory.GetFiles(path, "*.bin")
                                           select new file(Path.GetFileNameWithoutExtension(path), GetDate(path));
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
