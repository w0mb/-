namespace _4lab
{
    public static class Gaus
    {
        public static bool CheckMatrix(List<List<double>> matrix, List<double> result)
        {
            // Check for InfinityArgs and NoDicision
            for (int i = 0; i < matrix.Count; i++)
            {
                bool isAllZeroInRow = true;
                bool isAllZeroInColumn = true;
                int wrongColumn = 0;
                for (int j = 0; j < matrix.Count; j++)
                {
                    if (matrix[i][j] != 0)
                    {
                        isAllZeroInRow = false;
                    }
                    if (matrix[j][i] != 0)
                    {
                        isAllZeroInColumn = false;
                        wrongColumn = j;
                    }
                }
                if (isAllZeroInRow && result[i] == 0)
                {
                    Console.WriteLine($"Infinity argument: x{i + 1}");
                    return false;
                }
                else if (isAllZeroInRow)
                {
                    Console.WriteLine($"The problem: 0 * x{i + 1} != {result[i]}");
                    Console.WriteLine("Matrix doesn't have the decision.");
                    return false;
                }
                else if (isAllZeroInColumn)
                {
                    Console.WriteLine($"Column {wrongColumn + 1} has only 0.");
                    Console.WriteLine("Matrix doesn't have the decision.");
                    return false;
                }
            }

            return true;
        }
        public static State? DirectGauss(List<List<double>> matrix, List<double> result)
        {
            int n = matrix.Count;

            if (!CheckMatrix(matrix, result))
                return null;

            // Прямой ход
            for (int k = 0; k < n; k++)
            {
                for (int i = k + 1; i < n; i++)
                {
                    double prod;
                    double d = matrix[i][k] / matrix[k][k];
                    for (int j = k; j < n; j++)
                    {
                        prod = d * matrix[k][j];
                        matrix[i][j] = matrix[i][j] - prod;
                    }
                    prod = d * result[k];
                    result[i] = result[i] - prod;

                    if (!CheckMatrix(matrix, result))
                        return null;
                }
            }

            Painter.PrintMatrix(matrix, result);

            double[] args = new double[n];

            for (int k = n - 1; k >= 0; k--)
            {
                double summa = 0;
                for (int j = k + 1; j < n; j++)
                {
                    double prod = matrix[k][j] * args[j];
                    summa += prod;
                }
                args[k] = (result[k] - summa) / matrix[k][k];
            }

            return new State(args[0], args[1]);
        }
    }
}