using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ConsoleApp2
{
    internal class Program
    {
        static void Main(string[] args)
        {
            Console.Write("Ak = ");
            int n = Convert.ToInt32(Console.ReadLine());
            int ak = n;

            Console.Write("bk = ");
            int m = Convert.ToInt32(Console.ReadLine());
            int bk = m;

            if (ak <= bk)
            {



                int ak1 = ak, mas1 = 0;



                Console.Write("How much element:");
                mas1 = Convert.ToInt32(Console.ReadLine());


                int[] mas = new int[mas1];

                for (int i = 0; i < mas1; i++)
                {
                    Console.Write($"Write number (max: " + mas1 + ") for masive: ");
                    mas[i] = Convert.ToInt32(Console.ReadLine());
                    if (mas[i] < ak || mas[i] > bk)
                    {
                        Console.WriteLine("it`s can`t be");
                        i--;
                    }
                }

                int dodat = 0;
                int num = 0;

                for (int i = 0; i < mas1; i++)
                {
                    if (mas[i] > 0)
                    {
                        dodat = mas[i];
                        num = i +1;
                        break;

                    }
                }

                int max = 0;

                for (int i = num; i < mas1; i++)
                {
                    if (mas[i] > max)
                        {
                        max = mas[i];
                    }
                }

                Console.WriteLine(" This your max: " + max);
            }


        }
    }
}
