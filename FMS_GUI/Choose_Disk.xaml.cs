// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using FMS_adapter;
using System.Linq;

namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour Choose_Disk.xaml
    /// </summary>
    public partial class Choose_Disk : UserControl, iSwitchable
    {
        /// <summary>
        /// Class file, represent a file
        /// </summary>
        public class file
        {
            public string name { get; set; }
            public string date { get; set; }
            public file(string _name, string _date)
            {
                this.name = _name;
                this.date = _date;
            }
        }
        public Disk disk;
        string path = @"C:\Users\Simon\Desktop\FMS5776_2397_7707\FMS5776_2397_7707\FMS5776_2397_7707\FMS_GUI\bin\Release\";
        /// <summary>
        /// Get creation date of a file
        /// </summary>
        /// <param name="filename"></param>
        /// <returns></returns>
        private string GetDate(string filename)
        {
            // mount the disk
            disk.Mountdisk(filename);
            // get the dat
            string tmp = disk.GetVolumeHeader().ProdDate;
            // new disk
            disk = new Disk();
            // return the path
            return tmp;
        }
        /// <summary>
        /// Constructor
        /// </summary>
        public Choose_Disk()
        {
            disk = new Disk();
            InitializeComponent();
            // getting all the file from our directory
            Disklist.ItemsSource = from path in Directory.GetFiles(path, "*.bin")
                                   select new file(Path.GetFileNameWithoutExtension(path), GetDate(path));
        }
        #region
        public void UtilizeState(object state)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// OPen the selected disk
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // no disk selected
                if (Disklist.SelectedCells.Count() == 0)
                    throw new Exception("No disk selected");
                // getting the file
                file file = Disklist.SelectedCells[0].Item as file;
                if (file == null)
                    throw new Exception("File is null ...");
                // checking his extension
                if (string.IsNullOrEmpty(Path.GetExtension(file.name)))
                {
                    file.name += ".bin";
                }
                // reading the disk
                disk.Mountdisk(file.name);
                // switch to main operation window
                Switcher.Switch(new Main_Operation(disk));
            }
            catch (Exception ex)
            {

                MessageBox.Show(ex.Message);
            }
            
        }
        /// <summary>
        /// Switching back to the main windows
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Switcher.Switch(new MainWindows());
        }
        #endregion


    }
}
