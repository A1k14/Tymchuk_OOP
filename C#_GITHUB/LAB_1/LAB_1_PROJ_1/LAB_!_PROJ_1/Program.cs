using System;
using System.Collections.Generic;
using System.Linq;
using System.Net.Configuration;
using System.Text;
using System.Threading.Tasks;

namespace LAB___PROJ_1
{
    class Program
    {
        static void Main(string[] args)
        {

            Console.Write("N = ");
            int N = Convert.ToInt32(Console.ReadLine());

            Console.Write("M = ");
            int M = Convert.ToInt32(Console.ReadLine());

            int[] A = new int[N];
            int[] B = new int[M];

            int CMAS = N + M;

            int[] C = new int[CMAS];

            int c1 = 0;

            for (int i = 0; i < N; i++)
            {
                Console.Write("A[{0}] = ", i + 1);
                A[i] = Convert.ToInt32(Console.ReadLine());
            }

            for (int i = 0; i < M; i++)
            {
                Console.Write("B[{0}] = ", i  + 1);
                B[i] = Convert.ToInt32(Console.ReadLine());
            }


            for (int i = 0; i < N; i++)
            {
                if (A[i] >= 0)
                {
                    C[c1] = A[i];
                    c1++;
                }
            }

            for (int i = 0; i < M; i++)
            {
                if (B[i] >= 0)
                {
                    C[c1] = B[i];
                    c1++;
                }
            }


            for (int i = 0; i < N; i++)
            {
                if (A[i] < 0)
                {
                    C[c1] = A[i];
                    c1++;
                }
            }

            for (int i = 0; i < M; i++)
            {
                if (B[i] < 0)
                {
                    C[c1] = B[i];
                    c1++;
                }
            }

            for (int i = 0; i < CMAS; i++)
            {
                Console.WriteLine("C[{0}] = {1}", i + 1, C[i]);
            }   


        }

    }
}
