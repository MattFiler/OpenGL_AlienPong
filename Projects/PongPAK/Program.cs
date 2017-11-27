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
            string pong_build_directory = Directory.GetCurrentDirectory();
            int pak_byte_counter = 0;

            if (Directory.Exists(pong_build_directory + @"\Resources") && Directory.Exists(pong_build_directory + @"\Source Assets"))
            {
                //Delete old PAK and manifest first
                if (File.Exists(pong_build_directory + @"\Resources\resources.pongpak"))
                {
                    File.Delete(pong_build_directory + @"\Resources\resources.pongpak");
                    File.Delete(pong_build_directory + @"\Resources\resources.pongmfst");
                    Console.WriteLine("Resetting Pong PAK");
                    Console.WriteLine("--------------------------");
                    File.WriteAllText(pong_build_directory + @"\Resources\resources.pongpak", "");
                    File.WriteAllText(pong_build_directory + @"\Resources\resources.pongmfst", "");
                }

                string[] files = Directory.GetFiles(pong_build_directory + @"\Source Assets", "*", SearchOption.AllDirectories);
                StreamWriter update_manifest = new StreamWriter(pong_build_directory + @"\Resources\resources.pongmfst");
                BinaryWriter pak_creator = new BinaryWriter(new FileStream(pong_build_directory + @"\Resources\resources.pongpak", FileMode.Open, FileAccess.Write));
                foreach (string file in files)
                {
                    if (Path.GetExtension(file) == ".psd")
                    {
                        Console.WriteLine("Skipping illegal file: " + Path.GetFileName(file));
                    }
                    else
                    {
                        //Open file and write to PongPAK
                        BinaryReader current_file = new BinaryReader(new FileStream(file, FileMode.Open, FileAccess.Read));
                        pak_creator.Write(current_file.ReadBytes(Convert.ToInt32(new FileInfo(file).Length)));
                        current_file.Close();

                        //Update manifest with file info
                        update_manifest.WriteLine(Path.GetFileName(file) + Environment.NewLine + //Filename
                                                  pak_byte_counter + Environment.NewLine + //File start position
                                                  (pak_byte_counter + Convert.ToInt32(new FileInfo(file).Length))); //File end position

                        //Update byte count
                        pak_byte_counter += Convert.ToInt32(new FileInfo(file).Length);

                        //Alert
                        Console.WriteLine("Pong PAK'd " + Path.GetFileName(file));
                    }
                }
                pak_creator.Close();
                update_manifest.Close();

                Console.WriteLine("--------------------------");
                Console.WriteLine("Done! Press any key to close...");
                Console.ReadLine();
            }
            else
            {
                Console.WriteLine("PongPAK FAILED! Check your directories.");
                Console.WriteLine("Press any key to close...");
                Console.ReadLine();
            }
        }
    }
}
