﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;

namespace FMS_adapter
{
    public class FCB
    {
        public IntPtr myFCBpointer;

        public FCB(IntPtr myFCBpointer)
        {
            this.myFCBpointer = myFCBpointer;
        }

        ~FCB()
        {
            if (myFCBpointer != null)
                cppToCsharpAdapter.deleteFcbObject(ref myFCBpointer);
        }

        public void Closefile()
        {
            try
            {
                cppToCsharpAdapter.closefile(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public object readRec(object dest, uint readForUpdate = 0)
        {
            try
            {

                IntPtr buffer;
                buffer = Marshal.AllocHGlobal(Marshal.SizeOf(dest.GetType()));
                cppToCsharpAdapter.readRec(this.myFCBpointer, buffer, readForUpdate);
                Marshal.PtrToStructure(buffer, dest);
                Marshal.FreeHGlobal(buffer);
                return dest;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void writeRec(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);

                cppToCsharpAdapter.writeRec(this.myFCBpointer, buffer);

                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void seekRec(uint from, int pos)
        {
            try
            {
                cppToCsharpAdapter.seekRec(this.myFCBpointer, from, pos);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void updateRecCancel()
        {
            try
            {
                cppToCsharpAdapter.updateRecCancel(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void deleteRec()
        {
            try
            {
                cppToCsharpAdapter.deleteRec(this.myFCBpointer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }

        public void updateRec(object source)
        {
            try
            {
                IntPtr buffer = Marshal.AllocHGlobal(Marshal.SizeOf(source.GetType()));
                Marshal.StructureToPtr(source, buffer, true);
                cppToCsharpAdapter.updateRec(this.myFCBpointer, buffer);
                Marshal.FreeHGlobal(buffer);
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
            catch
            {
                throw;
            }
        }
        public DirEntry GetFileDesc()
        {
            try
            {
                DirEntry dirTemp = new DirEntry();
                int structSize = Marshal.SizeOf(typeof(DirEntry));
                IntPtr buffer = Marshal.AllocHGlobal(structSize);
                Marshal.StructureToPtr(dirTemp, buffer, true);
                cppToCsharpAdapter.getFileDesc(this.myFCBpointer, buffer);
                Marshal.PtrToStructure(buffer, dirTemp);
                Marshal.FreeHGlobal(buffer);
                return dirTemp;
            }
            catch (SEHException)
            {
                IntPtr cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                cString = cppToCsharpAdapter.getLastFcbErrorMessage(this.myFCBpointer);
                string source = Marshal.PtrToStringAnsi(cString);
                throw;
            }
        }
        public string getOpenType()
        {
            try
            {
                IntPtr open = cppToCsharpAdapter.getDat(this.myFCBpointer);
                return Marshal.PtrToStringAnsi(open).ToString();
            }
            catch (Exception ex)
            {
                IntPtr cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myFCBpointer);
                string message = Marshal.PtrToStringAnsi(cString);
                cString = cppToCsharpAdapter.getLastDiskErrorMessage(this.myFCBpointer);
                string source = Marshal.PtrToStringAnsi(cString);
                throw new Exception(message);
            }
        }
        public void flushfile()
        {
            cppToCsharpAdapter.flushfile(this.myFCBpointer);
        }
    }
}
