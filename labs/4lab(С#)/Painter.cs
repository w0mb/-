using MathNet.Symbolics;

namespace _4lab
{
    public static class Painter
    {
        public static void PrintMatrix(List<List<Equation>> matrix)
        {
            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    Console.Write(matrix[i][j].Expression.ToString() + "\t");
                }
                Console.WriteLine();
            }
            Console.Write("\n\n");
        }

        public static void PrintMatrix(List<List<SymbolicExpression>> matrix)
        {
            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    Console.Write(matrix[i][j].ToString() + "\t");
                }
                Console.WriteLine();
            }
            Console.Write("\n\n");
        }

        public static void PrintMatrix(List<List<double>> matrix)
        {
            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    Console.Write(matrix[i][j] + "\t");
                }
                Console.WriteLine();
            }
            Console.Write("\n\n");
        }

        public static void PrintMatrix(List<List<double>> matrix, List<double> result)
        {
            for (int i = 0; i < matrix.Count; i++)
            {
                for (int j = 0; j < matrix[i].Count; j++)
                {
                    Console.Write(matrix[i][j].ToString() + "\t");
                }
                Console.WriteLine(result[i]);
            }
            Console.Write("\n");
        }
    }
}