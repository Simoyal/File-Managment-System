// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
using System;
using System.Windows;
using System.Windows.Controls;
using FMS_adapter;
using System.Windows.Media;
using System.Windows.Shapes;
using System.IO;

namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour DiskInformation.xaml
    /// </summary>
    public partial class DiskInformation : UserControl, iSwitchable
    {
        public Disk disk;
        /// <summary>
        /// Constructor
        /// </summary>
        /// <param name="_disk"></param>
        public DiskInformation(Disk _disk)
        {
           InitializeComponent();
           disk = new Disk();
           disk = _disk;
            // getting all the info of the disk
           GetInformation();
            // printing the dat
           DisplayDAT();
        }
        /// <summary>
        /// Get Information of the disk
        /// </summary>
        public void GetInformation()
        {
            // name
            DiskName.Content = System.IO.Path.GetFileNameWithoutExtension(disk.GetVolumeHeader().DiskName);
            // owner
            DiskOwner.Content = disk.GetVolumeHeader().DiskOwner;
            // creation date
            CreationDate.Content = disk.GetVolumeHeader().ProdDate;
            // isFormated
            IsFormated.Content = disk.GetVolumeHeader().IsFormated;
            // capacity
            Capacity.Content = disk.GetVolumeHeader().ClusQty * 2 + "kb";
            // Actual Size
            Size.Content = disk.Howmuchempty(disk.myDiskPointer) * 2 + "kb";
            // Load of the disk
            DiskSpace.Value = (100 - ((100 * ((double)disk.Howmuchempty(disk.myDiskPointer) / 1600))));
        }
        public static string reverse(string s)
        {
            char[] array = s.ToCharArray();
            Array.Reverse(array);
            return new string(array);
        }
        /// <summary>
        /// Print Dat function, filling a canvas with rectangle
        /// </summary>
        public void DisplayDAT()
        {
            string dat = null;
            dat = reverse(disk.getDAT());
            Rectangle rec;
            //i = Height
            for (int i = 15; i >= 0; i--)
            {
                //j = width 
                for (int j = 99; j >= 0; j--)
                {
                    rec = new Rectangle();
                    if (dat[(i * 100) + j] == '1')
                        rec.Fill = Brushes.LightGreen;

                    if (!string.IsNullOrEmpty(dat) && dat[(i * 100) + j] == '0')
                        rec.Fill = Brushes.Red;

                    rec.Height = 11;
                    Canvas.SetLeft(rec, j * 9.8);

                    rec.Width = 13;
                    rec.Stroke = Brushes.Black;
                    Canvas.SetTop(rec, i * 13);
                    DAT.Children.Add(rec);
                }
            }
        }
        /// <summary>
        /// INterface
        /// </summary>
        /// <param name="state"></param>
        public void UtilizeState(object state)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// Switching back to main operation
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            Switcher.Switch(new Main_Operation(disk));
        }
        /// <summary>
        /// Format Button, erase all the disk
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void FormatButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // format
                disk.Format(disk.GetVolumeHeader().DiskOwner);
                // update info of the disk , and printing the dat 
                GetInformation();
                DisplayDAT();
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Defragment the disk, re-organise the disk
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Defragmentation_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // defragment
                disk.defragmentation();
                // update info of the disk , and printing the dat 
                GetInformation();
                DisplayDAT();
                MessageBox.Show("End of defragmentation :)", "Success", MessageBoxButton.OK, MessageBoxImage.Information);
            }
            catch(Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
    }
}
