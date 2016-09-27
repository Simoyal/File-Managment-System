using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace FMS_adapter
{
    public enum OpenType
    {
        Input, Output, Input_Output, Extend
    };
    public enum Choice
    {
        Student, Course
    };
    public class Disk
    {
        public IntPtr myDiskPointer;

        public Disk()
        {
            this.myDiskPointer = cppToCsharpAdapter.makeDiskObject();
        }

        ~Disk()
        {
            if (myDiskPointer != null)
                cppToCsharpAdapter.deleteDiskObject(ref myDiskPointer);
        }

        public DirEntry getDirEntry(int index, string location)
        {
            try
            {
                DirEntry dir = new DirEntry();
                int structsize = Marshal.SizeOf(dir.GetType());
                IntPtr buffer = Marshal.AllocHGlobal(structsize);
                Marshal.StructureToPtr(dir, buffer, true);

                cppToCsharpAdapter.GetDirEntry(this.myDiskPointer, buffer, index, location);
                Marshal.PtrToStructure(buffer, dir);

                // free allocate
                Marshal.FreeHGlobal(buffer);
                return dir;
            }
            catch (FormatException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public VolumeHeader GetVolumeHeader()
        {
            try
            {

                VolumeHeader v = new VolumeHeader();
                int structSize = Marshal.SizeOf(v.GetType()); //Marshal.SizeOf(typeof(Student)); 
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(v, buffer, true);

                // ... send buffer to dll
                cppToCsharpAdapter.getVolumeHeader(this.myDiskPointer, buffer);
                Marshal.PtrToStructure(buffer, v);

                // free allocate
                Marshal.FreeHGlobal(buffer);

                return v;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Createdisk(string diskName, string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.createdisk(this.myDiskPointer, diskName, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Mountdisk(string diskName)
        {
            try
            {
                cppToCsharpAdapter.mountdisk(this.myDiskPointer, diskName);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Unmountdisk(IntPtr THIS)
        {
            try
            {
                cppToCsharpAdapter.unmountdisk(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Recreatedisk(string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.recreatedisk(this.myDiskPointer, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        // Level 1

        public void Format(string diskOwner)
        {
            try
            {
                cppToCsharpAdapter.format(this.myDiskPointer, diskOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        public int Howmuchempty(IntPtr THIS)
        {
            try
            {
                return cppToCsharpAdapter.howmuchempty(this.myDiskPointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        //Level 2

        public void Createfile(string fileName, string fileOwner, string FinalOrVar,
                                uint recSize, uint fileSize,
                                string keyType, uint keyOffset, uint keySize = 4)
        {
            try
            {
                cppToCsharpAdapter.createfile(this.myDiskPointer, fileName, fileOwner, "F",
                              recSize, fileSize,
                                keyType, keyOffset, keySize);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void CreateStudentFile(string fileName, string fileOwner, uint fileSize)
        {
            try
            {
                cppToCsharpAdapter.createfile(this.myDiskPointer, fileName, fileOwner, "F",
                              (uint)Marshal.SizeOf(typeof(Student)), fileSize,
                                "I", 0, 4); 
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public void CreateCourseFile(string fileName, string fileOwner, uint fileSize)
        {
            try
            {
                cppToCsharpAdapter.createfile(this.myDiskPointer, fileName, fileOwner, "F",
                              (uint)Marshal.SizeOf(typeof(Course)), fileSize,
                                "D", 0, 4);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void Delfile(string fileName, string fileOwner)
        {
            try
            {
                cppToCsharpAdapter.delfile(this.myDiskPointer, fileName, fileOwner);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }


        public void Extendfile(string fileName, string fileOwner, uint size)
        {
            try
            {
                cppToCsharpAdapter.extendfile(this.myDiskPointer, fileName, fileOwner, size);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        // Level 3
        public FCB Openfile(string fileName, string fileOwner, string openMode)
        {
            try
            {
                IntPtr p = cppToCsharpAdapter.openfile(this.myDiskPointer, fileName, fileOwner, openMode);
                return new FCB(p);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public int CheckDirEntryExist(IntPtr THIS, int index, string location)
        {
            try
            {
                return cppToCsharpAdapter.CheckDirEntryExist(this.myDiskPointer, index, location);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public string getDAT()
        {
            try
            {
                IntPtr DAT = cppToCsharpAdapter.getDat(this.myDiskPointer);
                return Marshal.PtrToStringAnsi(DAT).ToString();
            }
            catch (Exception ex)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw ex;
            }
        }
        public void defragmentation()
        {
            try
            {
                cppToCsharpAdapter.defragmentation(this.myDiskPointer);
            }
            catch(Exception ex)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw ex;
            }
            catch
            {
                throw;
            }
        }
        public void flush()
        {
            try
            {
                cppToCsharpAdapter.flush(this.myDiskPointer);
            }
            catch (Exception ex)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myDiskPointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw ex;
            }
        }
    }
}
