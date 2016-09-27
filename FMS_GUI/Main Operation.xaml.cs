/********************************************************************************************
// @author Moyal Simon 1177707
// @author Shimshon Attal 209552397
/********************************************************************************************/

using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows;
using System.Windows.Controls;
using FMS_adapter;

namespace FMS_GUI
{
    /// <summary>
    /// Logique d'interaction pour Main_Operation.xaml
    /// </summary>
    public partial class Main_Operation : UserControl, iSwitchable
    {
        Disk disk;
        FCB fcb;
        int ID;
        int CoursePosition;
        // class , represent dirEntry file (for the datagrid)
        public class fileDir
        {
            // name
            public string name { set; get; }
            // owner
            public string owner { set; get; }
            // creation date
            public string date { set; get; }
            // type of the file
            private string Type;
            // type of the file
            public string type
            {
                set
                {
                    if (value == "I")
                        Type = "S";
                    else if (value == "D")
                        Type = "C";
                    else
                        Type = "";
                }
                get
                {
                    return Type;
                }
            }
            // size
            public uint size { set; get; }
            // constructor
            public fileDir(string _name, string _owner, string _date, uint _size, string _type)
            {
                name = _name;
                date = _date;
                owner = _owner;
                size = _size;
                type = _type;
            }
            // default constructor
            public fileDir()
            {
                name = owner = date = type = "";
                size = 0;
            }
        }
        // getAllrecord of a file
        public IEnumerable<T> getAllRecord<T>() where T : class, new()
        {
            List<T> allRec = new List<T>();
            // seeking to the beginning of the file
            fcb.seekRec(0, 0);
            T obj;
            // getting the number of record
            int eof = fcb.GetFileDesc().maxRecSize;
            for (int i = 0; i < eof; i++)
            {
                obj = new T();
                // read
                fcb.readRec(obj);
                // add the object
                allRec.Add(obj);
            }
           return allRec;
        }
        // getting the position of a record 
        public int GetCoursePosition(Course c)
        {
            // getting the number of record
            int eof = fcb.GetFileDesc().maxRecSize;
            int counter = 0;
            Course tmp;
            // seeking to the beginning of the file
            fcb.seekRec(0, 0);
            for (int i = 0; i < eof; i++)
            {
                tmp = new Course();
                // read
                fcb.readRec(tmp);
                // if we found our file
                if (tmp.Name == c.Name && tmp.Id == c.Id)
                    break;
                counter++;
            }
            if (counter > 0)
                // return the position - 1 , because it's the index is beginning from 0
                return counter--;
            else
                return 0;
        }
        /// <summary>
        /// Constructor of the page
        /// </summary>
        /// <param name="_disk"></param>
        public Main_Operation(Disk _disk)
        {
            InitializeComponent();
            // initialize
            disk = new Disk();
            // getting the opendisk
            disk = _disk;
            fcb = null;
            // printing the file
            PrintFile();
        }

        #region Other
        /// <summary>
        /// Implementation of the interface, allowing switching to this window
        /// </summary>
        /// <param name="state"></param>
        public void UtilizeState(object state)
        {
            throw new NotImplementedException();
        }
        /// <summary>
        /// Priting all the file
        /// </summary>
        public void PrintFile()
        {
            this.NextButton.IsEnabled = true;
            FileList.Visibility = Visibility.Visible;
            // getting all the file from the disk
            FileList.ItemsSource = from path in GetAllfile()
                                   select new fileDir(path.filename, path.fileOwner, path.crDate, path.fileSize, path.keyType);
        }
        /// <summary>
        /// Getting all the DirEntry of the disk
        /// </summary>
        /// <returns></returns>
        public List<DirEntry> GetAllfile()
        {
            List<DirEntry> dir = new List<DirEntry>();
            DirEntry d;
            // msb
            for (int i = 0; i < 14; i++)
            {
                // checking if a file exist 
                if (disk.CheckDirEntryExist(disk.myDiskPointer, i, "msb") == 1)
                {
                    d = disk.getDirEntry(i, "msb");
                    dir.Add(d);
                }
            }
            // lsb
            for (int i = 0; i < 14; i++)
            {
                // checking if a file exist
                if (disk.CheckDirEntryExist(disk.myDiskPointer, i, "lsb") == 1)
                {
                    d = disk.getDirEntry(i, "lsb");
                    dir.Add(d);
                }
            }
            return dir;
        }
        /// <summary>
        /// Switching back to the MainWindows
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void BackButton_Click(object sender, RoutedEventArgs e)
        {
            // if the user is in the recordMenu Section
            if (RecordMenu.Visibility == Visibility.Visible)
            {
                // jumping back to the file menu section
                RecordMenu.Visibility = Visibility.Hidden;
                // checking the fcb
                if (fcb != null)
                    // getting the keytype to hide the right datagrid
                    if (fcb.GetFileDesc().keyType == "S")
                    RecordList.Visibility = Visibility.Hidden;
                else
                    CourseList.Visibility = Visibility.Hidden;
                FileList.Visibility = Visibility.Visible;
                FileMenu.Visibility = Visibility.Visible;
                this.NextButton.IsEnabled = this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.UpdateFileButton.IsEnabled = true;
                this.RecordList.Visibility = this.CourseList.Visibility = Visibility.Hidden;
                // closing the file
                if (fcb != null)
                {
                    fcb.Closefile();
                }
                // print all the file
                PrintFile();
            }
            else
            {
                // unmount the disk
                disk.Unmountdisk(disk.myDiskPointer);
                // switching back to the main window
                Switcher.Switch(new MainWindows());
            }
        }
        #endregion

        #region FileOption
        /// <summary>
        /// AddFile , FileOption
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddFileButton_Click(object sender, RoutedEventArgs e)
        {
            this.NextButton.IsEnabled = this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.UpdateFileButton.IsEnabled = false;
            FileList.Visibility = Visibility.Hidden;
            AddFileSection.Visibility = Visibility.Visible;
            FileType.ItemsSource = Enum.GetValues(typeof(Choice));
        }
        /// <summary>
        /// DeleteFile operation, FileOption
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (FileList.SelectedCells.Count() == 0)
                    throw new Exception("No File selected");

                fileDir file = FileList.SelectedCells[0].Item as fileDir;
                if (file == null)
                    throw new Exception("File is null ...");

                if (MessageBox.Show("Are you sur to delete the file, this is irreversible", "Confirmation", MessageBoxButton.YesNo, MessageBoxImage.Information) == MessageBoxResult.Yes)
                {
                    disk.Delfile(file.name, file.owner);
                    MessageBox.Show("File succefully deleted :)", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                    PrintFile();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }


        /// <summary>
        /// UpdateFile, FileOption
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void UpdateFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (FileList.SelectedCells.Count() == 0)
                    throw new Exception("Please select a file before");
                FileList.Visibility = Visibility.Hidden;
                Extend.Visibility = Visibility.Visible;
                this.NextButton.IsEnabled = this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }

        }
        /// <summary>
        /// DiskInformation, FileOption
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void InformationButton_Click(object sender, RoutedEventArgs e)
        {
            Switcher.Switch(new DiskInformation(disk));
        }
        #endregion

        #region OperationInsideWindow
        /// <summary>
        /// ExtendFile, Window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Extended_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                uint result;
                if (!uint.TryParse(FileSizeTextBox.Text, out result))
                {
                    throw new Exception("Size could not be letter but only number");
                }
                if (result > 3192 || result < 0)
                    throw new Exception("Overflow or Underflow prevention");
                uint tmp = 0;
                if (result % 2 == 0)
                    tmp = result / 2;
                else
                    tmp = (result / 2) + 1;
                if (tmp > disk.Howmuchempty(disk.myDiskPointer))
                    this.NextButton.IsEnabled = false;
                if (FileList.SelectedCells.Count() == 0)
                    throw new Exception("No File selected");

                fileDir file = FileList.SelectedCells[0].Item as fileDir;
                if (file == null)
                    throw new Exception("File is null ...");

                disk.Extendfile(file.name, file.owner, result);
                MessageBox.Show("Success :)");
                Extend.Visibility = Visibility.Hidden;
                FileList.Visibility = Visibility.Visible;
                this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = true;
                PrintFile();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Cancel ExtendFile, Window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void cancel_Click(object sender, RoutedEventArgs e)
        {
            Extend.Visibility = Visibility.Hidden;
            FileList.Visibility = Visibility.Visible;
            PrintFile();
            this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.NextButton.IsEnabled = true;
        }

        /// <summary>
        /// Cancel AddFile operation, Window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Addcancel_Click(object sender, RoutedEventArgs e)
        {
            this.AddFileSection.Visibility = Visibility.Hidden;
            FileList.Visibility = Visibility.Visible;
            PrintFile();
            this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.UpdateFileButton.IsEnabled = this.NextButton.IsEnabled = true;
        }

        /// <summary>
        /// AddFile operation, Window
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddFile_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                uint result;
                if (!uint.TryParse(AddFileSizeTextBox.Text, out result))
                {
                    throw new Exception("Size could not be letter but only number");
                }
                if (result > 3192 || result < 0)
                    throw new Exception("Overflow or Underflow prevention");
                uint tmp = 0;
                if (result % 2 == 0)
                    tmp = result / 2;
                else
                    tmp = (result / 2) + 1;
                if (tmp > disk.Howmuchempty(disk.myDiskPointer))
                    throw new Exception("There is no space for this file in the disk");
                string choice = ((Enum)FileType.SelectedItem).ToString();
                if (choice == "Student")
                    disk.CreateStudentFile(AddFileNameTextBox.Text, AddFileOwnerTextBox.Text, result);
                else
                    disk.CreateCourseFile(AddFileNameTextBox.Text, AddFileOwnerTextBox.Text, result);
                MessageBox.Show("File succefully created", "Information", MessageBoxButton.OK, MessageBoxImage.Information);
                AddFileSection.Visibility = Visibility.Hidden;
                this.NextButton.IsEnabled = this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.UpdateFileButton.IsEnabled = true;
                PrintFile();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        #endregion

        #region RecordOption
        /// <summary>
        /// Open a file button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void NextButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                if (FileList.SelectedCells.Count() == 0)
                    throw new Exception("No File selected");
                // getting data of the file
                fileDir file = FileList.SelectedCells[0].Item as fileDir;
                if (file == null)
                    throw new Exception("File is null ...");
                FileList.Visibility = Visibility.Hidden;
                OpenFile.Visibility = Visibility.Visible;
                // loading the openfile type
                this.OpenTypeCombobox.ItemsSource = Enum.GetValues(typeof(OpenType));
                this.NextButton.IsEnabled = this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.UpdateFileButton.IsEnabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// Open a file with a specific opentype
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void OpenFileButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // getting the file info
                fileDir file = FileList.SelectedCells[0].Item as fileDir;
                // getting the opentype
                string open = ((OpenType)OpenTypeCombobox.SelectedValue).ToString();
                if (open == "")
                    throw new Exception("No choice selected");
                string type = "";
                switch (open)
                {
                    case "Input":
                        type = "I";
                        break;
                    case "Output":
                        type = "O";
                        break;
                    case "Input_Output":
                        type = "IO";
                        break;
                    case "Extend":
                        type = "E";
                        break;
                    default:
                        throw new Exception("A problem occur when checking the value of the combobox");
                }
                // openfile
                fcb = disk.Openfile(file.name, file.owner, type);
                // checking if a problem occurs
                if (fcb == null)
                    throw new Exception("Unable to open the file");
                FileMenu.Visibility = Visibility.Hidden;
                OpenFile.Visibility = Visibility.Hidden;
                RecordMenu.Visibility = Visibility.Visible;
                // if the type is student
                if (file.type == "S")
                {
                    // show his grid and priting all the record inside the file
                    RecordList.Visibility = Visibility.Visible;
                    RecordList.ItemsSource = from item in getAllRecord<Student>()
                                             select new Student(item.Id, item.Name, item.Year, item.Average);
                }
                // if the type is course
                else
                {
                    // show his grid and priting all the record inside the file
                    CourseList.Visibility = Visibility.Visible;
                    CourseList.ItemsSource = from item in getAllRecord<Course>()
                                             select new Course(item.Id, item.Name, item.Credit);
                }

                this.NextButton.IsEnabled = false;
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Cancel an open, back to main menu
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void Opencancel_Click(object sender, RoutedEventArgs e)
        {
            // hide and show grid
            OpenFile.Visibility = Visibility.Hidden;
            FileList.Visibility = Visibility.Visible;
            // print the file 
            PrintFile();
            this.DeleteFileButton.IsEnabled = this.AddFileButton.IsEnabled = this.InformationButton.IsEnabled = this.NextButton.IsEnabled = this.UpdateFileButton.IsEnabled = true;
        }
        /// <summary>
        /// add a record Option
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddRecordButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // if the opentype is O you can't create a new record
                if (fcb.getOpenType() == "O")
                    throw new Exception("You can't add a record when opening the file for output");
                RecordList.Visibility = CourseList.Visibility = Visibility.Hidden;
                // for student
                if (fcb.GetFileDesc().keyType == "I")
                    AddRecordOrCourse.Visibility = StudentGridOption.Visibility = Visibility.Visible;
                // for course
                else
                    AddRecordOrCourse.Visibility = CourseGridOption.Visibility = Visibility.Visible;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }

        /// <summary>
        /// Add a new Student
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddRecordStudent_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // checking the input from the user
                int result, result2;
                if (!int.TryParse(StudentAgeNameTextBox.Text, out result) || !int.TryParse(StudentAverageTextBox.Text, out result2))
                {
                    throw new Exception("Size could not be letter but only number");
                }
                // write the record
                fcb.writeRec(new Student(getAllRecord<Student>().LastOrDefault().Id + 1, StudentNameTextBox.Text, result, result2));
                //save the changment
                fcb.flushfile();
                AddRecordOrCourse.Visibility = StudentGridOption.Visibility = Visibility.Hidden;
                RecordList.Visibility = Visibility.Visible;
                // refresh the list
                RecordList.ItemsSource = from item in getAllRecord<Student>()
                                         select new Student(item.Id, item.Name, item.Year, item.Average);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Add a new course
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void AddRecordCourse_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // checking the input from the user
                int result, result1;
                if (!int.TryParse(CourseIDTextBox.Text, out result) || !int.TryParse(CourseCreditTextBox.Text, out result1))
                {
                    throw new Exception("Size could not be letter but only number");
                }
                // write the record
                fcb.writeRec(new Course(result, CourseNameTextBox.Text, result1));
                // saving the file
                fcb.flushfile();
                AddRecordOrCourse.Visibility = CourseGridOption.Visibility = Visibility.Hidden;
                CourseList.Visibility = Visibility.Visible;
                // refresh the grid
                CourseList.ItemsSource = from item in getAllRecord<Course>()
                                         select new Course(item.Id, item.Name, item.Credit);
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Update a record
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void UpdateRecordButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // checking the opentype
                if (fcb.getOpenType() == "O" || fcb.getOpenType() == "E")
                    throw new Exception("You can't perfom this operation");


                RecordList.Visibility = CourseList.Visibility = Visibility.Hidden;
                // for student
                if (fcb.GetFileDesc().keyType == "I")
                {
                    if (RecordList.SelectedCells.Count() == 0)
                        throw new Exception("No File selected");
                    // getting the record to update
                    Student tmp = RecordList.SelectedCells[0].Item as Student;
                    if (tmp == null)
                        throw new Exception("Problem");
                    //checking if we have astudent to update
                    int record = getAllRecord<Student>().Count();
                    if (record == 0)
                        throw new Exception("There is not student to update");
                    // ID hold the recordNumber of the student
                    ID = tmp.Id - 1;
                    AddRecordOrCourse.Visibility = UpdateStudentGrid.Visibility = Visibility.Visible;
                }
                else
                {
                    if (CourseList.SelectedCells.Count() == 0)
                        throw new Exception("No File selected");
                    // getting the record to update
                    Course tmp = CourseList.SelectedCells[0].Item as Course;
                    if (tmp == null)
                        throw new Exception("Problem");
                    //checking if we have a course to update
                    int record = getAllRecord<Course>().Count();
                    if (record == 0)
                        throw new Exception("There is not course to update");
                    // getting the record number
                    CoursePosition = GetCoursePosition(tmp);
                    AddRecordOrCourse.Visibility = UpdateCourseOption.Visibility = Visibility.Visible;
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Update a  record
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void UpdateRecordStudent_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                int result, result1;
                // checking if we have student 
                if (fcb.GetFileDesc().keyType == "I")
                {
                    // checking the input from the user
                    if (!int.TryParse(StudentAgeNamTextBox.Text, out result) || !int.TryParse(StudentAveragTextBox.Text, out result1))
                    {
                        throw new Exception("Only number are accepted");
                    }
                    Student tmp = new Student();
                    // seek to his position in the file
                    fcb.seekRec(0, ID);
                    // read data
                    fcb.readRec(tmp, 1);
                    // update data
                    tmp.Name = StudentNamTextBox.Text;
                    tmp.Year = result;
                    tmp.Average = result1;
                    // update the data
                    fcb.updateRec(tmp);
                    // saving change
                    fcb.flushfile();
                    AddRecordOrCourse.Visibility = UpdateStudentGrid.Visibility = Visibility.Hidden;
                    RecordList.Visibility = Visibility.Visible;
                    // refresh the datagrid
                    RecordList.ItemsSource = from item in getAllRecord<Student>()
                                             select new Student(item.Id, item.Name, item.Year, item.Average);

                }
                // otherwise we have course record
                else
                {
                    // checking the input from the user
                    if (!int.TryParse(CourseCrediTextBox.Text, out result) || !int.TryParse(CourseIdTextBox.Text, out result1))
                    {
                        throw new Exception("Only number are accepted");
                    }
                    Course tmp = new Course();
                    // seek to his position in the file
                    fcb.seekRec(0, CoursePosition);
                    // read data
                    fcb.readRec(tmp, 1);
                    tmp.Name = CourseNamTextBox.Text;
                    tmp.Credit = result;
                    tmp.Id = result1;
                    // update data
                    fcb.updateRec(tmp);
                    // saving change
                    fcb.flushfile();
                    CourseList.Visibility = Visibility.Visible;
                    // refresh the datagrid
                    CourseList.ItemsSource = from item in getAllRecord<Course>()
                                             select new Course(item.Id, item.Name, item.Credit);
                }
                AddRecordOrCourse.Visibility = UpdateCourseOption.Visibility = UpdateStudentGrid.Visibility = Visibility.Hidden;

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        /// <summary>
        /// Cancel Update of student
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CancelUpdateStudent_Click(object sender, RoutedEventArgs e)
        {
            AddRecordOrCourse.Visibility = UpdateCourseOption.Visibility = UpdateStudentGrid.Visibility = Visibility.Hidden;
            // for student
            if (fcb.GetFileDesc().keyType == "I")
            {
                RecordList.Visibility = Visibility.Visible;
                // show and print the records
                RecordList.ItemsSource = from item in getAllRecord<Student>()
                                         select new Student(item.Id, item.Name, item.Year, item.Average);
            }
            else
            {
                // show and print the records
                CourseList.Visibility = Visibility.Visible;
                CourseList.ItemsSource = from item in getAllRecord<Course>()
                                         select new Course(item.Id, item.Name, item.Credit);
            }
        }
        /// <summary>
        /// Cancel Button
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CancelAddStudent_Click(object sender, RoutedEventArgs e)
        {
            AddRecordOrCourse.Visibility = StudentGridOption.Visibility = CourseGridOption.Visibility = Visibility.Hidden;
            // if student
            if (fcb.GetFileDesc().keyType == "I")
            {
                // show and print the records
                RecordList.Visibility = Visibility.Visible;
                RecordList.ItemsSource = from item in getAllRecord<Student>()
                                         select new Student(item.Id, item.Name, item.Year, item.Average);
            }
            // course
            else
            {
                // show and print the records
                CourseList.Visibility = Visibility.Visible;
                CourseList.ItemsSource = from item in getAllRecord<Course>()
                                         select new Course(item.Id, item.Name, item.Credit);
            }
        }
        /// <summary>
        /// Delete a record
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void DeleteRecordButton_Click(object sender, RoutedEventArgs e)
        {
            try
            {
                // checking the type
                if (fcb.GetFileDesc().keyType == "I")
                {
                    // getting the student to delete
                    Student tmp = RecordList.SelectedCells[0].Item as Student;
                    if (tmp == null)
                        throw new Exception("Problem");
                    // checking the number of student
                    int record = getAllRecord<Student>().Count();
                    if (record == 0)
                        throw new Exception("There is not student to update");
                    ID = tmp.Id - 1;
                    // seeking to the right place
                    fcb.seekRec(0, ID);
                    // delete record
                    fcb.deleteRec();
                    // saving change
                    fcb.flushfile();
                    RecordList.Visibility = Visibility.Visible;
                    // printing all the record
                    RecordList.ItemsSource = from item in getAllRecord<Student>()
                                             select new Student(item.Id, item.Name, item.Year, item.Average);
                }
                else
                {
                    Course tmp = CourseList.SelectedCells[0].Item as Course;
                    if (tmp == null)
                        throw new Exception("Problem");
                    int record = getAllRecord<Course>().Count();
                    if (record == 0)
                        throw new Exception("There is not course to update");
                    CoursePosition = GetCoursePosition(tmp);
                    // seeking to the right place
                    fcb.seekRec(0, CoursePosition);
                    // delete record
                    fcb.deleteRec();
                    // saving change
                    fcb.flushfile();
                    CourseList.Visibility = Visibility.Visible;
                    // printing all the record
                    CourseList.ItemsSource = from item in getAllRecord<Course>()
                                             select new Course(item.Id, item.Name, item.Credit);
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message, "Error", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        #endregion
    }
}


