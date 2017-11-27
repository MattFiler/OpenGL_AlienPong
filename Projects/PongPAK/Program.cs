using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;

namespace PongPAK
{
    class Program
    {
        static void Main(string[] args)
        {
            /*
             * Pong PAK creator tool 
            */
            //string pong_build_directory = Directory.GetCurrentDirectory();
            string pong_build_directory = @"C:\Users\mattf\OneDrive\Github Repos\pong-MattFiler";
            int pak_byte_counter = 0;

            //Delete old PAK and manifest first
            if (File.Exists(pong_build_directory + @"\Resources\resources.pongpak"))
            {
                File.Delete(pong_build_directory + @"\Resources\resources.pongpak");
                File.Delete(pong_build_directory + @"\Resources\resources.pongmfst");
                Console.WriteLine("Resetting Pong PAK");
                Console.WriteLine("--------------------------");
            }

            string[] files = Directory.GetFiles(pong_build_directory + @"\Source Assets", "*", SearchOption.AllDirectories);
            StreamWriter update_manifest = new StreamWriter(pong_build_directory + @"\Resources\resources.pongmfst");
            foreach (string file in files)
            {
                if (Path.GetExtension(file) == ".psd")
                {
                    Console.WriteLine("Skipping illegal file: " + Path.GetFileName(file));
                }
                else
                {
                    //Get info
                    string content = File.ReadAllText(file);
                    int file_byte_size = Convert.ToInt32(new FileInfo(file).Length);

                    //Copy file to PAK
                    File.AppendAllText(pong_build_directory + @"\Resources\resources.pongpak", content);

                    //Update manifest with file info
                    update_manifest.WriteLine(Path.GetFileName(file) + Environment.NewLine + //Filename
                                                pak_byte_counter + Environment.NewLine + //File start position
                                                (pak_byte_counter + file_byte_size)); //File end position

                    //Update byte count
                    pak_byte_counter += file_byte_size;

                    //Alert
                    Console.WriteLine("Pong PAK'd " + Path.GetFileName(file));
                }
            }
            update_manifest.Close();

            Console.WriteLine("--------------------------");
            Console.WriteLine("Done! Press any key to close...");
            Console.ReadLine();
        }
    }
}
